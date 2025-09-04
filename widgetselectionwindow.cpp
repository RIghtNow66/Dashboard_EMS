#include "widgetselectionwindow.h"
#include "ui_widgetselectionwindow.h"
#include "databindingwindow.h"
#include "customwidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QGroupBox>
#include <QColorDialog>
#include <QSpinBox>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QMessageBox>
#include <QGraphicsView>
#include <QGraphicsScene>

WidgetSelectionWindow::WidgetSelectionWindow(QWidget* parent)
    : QDialog(parent, Qt::Window | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint
        | Qt::WindowStaysOnTopHint | Qt::WindowCloseButtonHint),
    ui(new Ui::WidgetSelectionWindow), m_selectedType(CustomWidget::Table),
    m_previewView(nullptr), m_previewScene(nullptr), m_previewWidget(nullptr),
    m_configGroup(nullptr), m_configLayout(nullptr),
    m_curveSelectedColor(Qt::blue), m_barSelectedColor(Qt::green),
    // 初始化所有配置控件指针为空
    m_tableRowSpin(nullptr), m_tableColSpin(nullptr),
    m_tableRowNamesEdit(nullptr), m_tableColNamesEdit(nullptr),
    m_curveYAxisNameEdit(nullptr), m_curveColorButton(nullptr),
    m_timeRangeCombo(nullptr), m_barOrientationCombo(nullptr),
    m_barColorButton(nullptr), m_barNameEdit(nullptr)
{
    ui->setupUi(this);
    setWindowTitle("选择控件");

    // 初始化控件列表
    ui->widgetList->addItem("表格");
    ui->widgetList->addItem("曲线");
    ui->widgetList->addItem("柱状图");
    ui->widgetList->setCurrentRow(0);

    // 初始化预览视图
    m_previewScene = new QGraphicsScene(this);
    m_previewView = new QGraphicsView(ui->previewWidget);
    m_previewView->setScene(m_previewScene);
    m_previewView->setRenderHint(QPainter::Antialiasing);

    // 设置预览视图的布局
    QVBoxLayout* previewLayout = new QVBoxLayout(ui->previewWidget);
    previewLayout->setContentsMargins(5, 5, 5, 5);
    previewLayout->addWidget(m_previewView);


    // 设置配置选项
    setupConfigOptions();

    // 初始化预览
    updatePreview();
}

WidgetSelectionWindow::~WidgetSelectionWindow()
{
    // 安全地清理预览控件
    clearPreviewSafely();
    delete ui;
}

void WidgetSelectionWindow::clearPreviewSafely()
{
    if (m_previewScene && m_previewWidget) {
        m_previewScene->removeItem(m_previewWidget);
    }

    if (m_previewWidget) {
        delete m_previewWidget;
        m_previewWidget = nullptr;
    }
}

CustomWidget::WidgetType WidgetSelectionWindow::selectedWidgetType() const
{
    return m_selectedType;
}

QString WidgetSelectionWindow::widgetName() const
{
    QString name = ui->nameEdit->text().trimmed();
    if (name.isEmpty())
    {
        // 如果未输入名称，使用默认名称
        switch (m_selectedType)
        {
            case CustomWidget::Table: return "表格";
            case CustomWidget::Curve: return "曲线";
            case CustomWidget::BarChart: return "柱状图";
            default: return "控件";
        }
    }
    return name;
}

QVariantMap WidgetSelectionWindow::getWidgetConfig() const
{
    QVariantMap config;

    // 根据控件类型添加特定配置
    switch (m_selectedType) {
    case CustomWidget::Table:
        if (m_tableRowSpin) config["rows"] = m_tableRowSpin->value();
        if (m_tableColSpin) config["columns"] = m_tableColSpin->value();
        if (m_tableRowNamesEdit) config["rowNames"] = m_tableRowNamesEdit->text();
        if (m_tableColNamesEdit) config["columnNames"] = m_tableColNamesEdit->text();
        break;

    case CustomWidget::Curve:
        if (m_curveYAxisNameEdit) config["yAxisName"] = m_curveYAxisNameEdit->text();
        config["curveColor"] = m_curveSelectedColor;
        if (m_timeRangeCombo) config["timeRange"] = m_timeRangeCombo->currentText();
        break;

    case CustomWidget::BarChart:
        if (m_barOrientationCombo) config["orientation"] = m_barOrientationCombo->currentText();
        config["barColor"] = m_barSelectedColor;
        if (m_barNameEdit) config["chartName"] = m_barNameEdit->text();
        break;
    }

    return config;
}

QVariantMap WidgetSelectionWindow::getDataBindings() const
{
    return m_dataBindings;
}

void WidgetSelectionWindow::on_widgetList_itemSelectionChanged()
{
    int index = ui->widgetList->currentRow();
    if (index >= 0 && index < 3)
    {
        m_selectedType = static_cast<CustomWidget::WidgetType>(index);
        setupConfigOptions();
        updatePreview();
    }
}

void WidgetSelectionWindow::setupConfigOptions()
{
    clearConfigLayout();

    if (!m_configGroup) {
        m_configGroup = ui->configGroupBox;
        // 隐藏原有的formLayoutWidget
        if (ui->formLayoutWidget) {
            ui->formLayoutWidget->hide();
        }
    }

    // 创建新的布局
    if (m_configLayout) {
        delete m_configLayout;
    }
    m_configLayout = new QFormLayout(m_configGroup);

    // 根据控件类型添加特定配置
    switch (m_selectedType) {
    case CustomWidget::Table:
        setupTableConfig();
        break;
    case CustomWidget::Curve:
        setupCurveConfig();
        break;
    case CustomWidget::BarChart:
        setupBarChartConfig();
        break;
    }
}

void WidgetSelectionWindow::clearConfigLayout()
{
    if (!m_configLayout) return;

    // 安全地清理所有子控件
    QLayoutItem* item;
    while ((item = m_configLayout->takeAt(0)) != nullptr) {
        if (QWidget* widget = item->widget()) {
            widget->deleteLater();
        }
        delete item;
    }

    // 重置所有控件指针
    m_tableRowSpin = nullptr;
    m_tableColSpin = nullptr;
    m_tableRowNamesEdit = nullptr;
    m_tableColNamesEdit = nullptr;
    m_curveYAxisNameEdit = nullptr;
    m_curveColorButton = nullptr;
    m_timeRangeCombo = nullptr;
    m_barOrientationCombo = nullptr;
    m_barColorButton = nullptr;
    m_barNameEdit = nullptr;
}

void WidgetSelectionWindow::setupTableConfig()
{
    m_tableRowSpin = new QSpinBox();
    m_tableRowSpin->setMinimum(1);
    m_tableRowSpin->setMaximum(100);
    m_tableRowSpin->setValue(5);
    connect(m_tableRowSpin, QOverload<int>::of(&QSpinBox::valueChanged), this, &WidgetSelectionWindow::on_configChanged);
    m_configLayout->addRow("行数:", m_tableRowSpin);

    m_tableColSpin = new QSpinBox();
    m_tableColSpin->setMinimum(1);
    m_tableColSpin->setMaximum(20);
    m_tableColSpin->setValue(3);
    connect(m_tableColSpin, QOverload<int>::of(&QSpinBox::valueChanged), this, &WidgetSelectionWindow::on_configChanged);
    m_configLayout->addRow("列数:", m_tableColSpin);

    m_tableRowNamesEdit = new QLineEdit();
    m_tableRowNamesEdit->setPlaceholderText("用逗号分隔，如：行1,行2,行3");
    connect(m_tableRowNamesEdit, &QLineEdit::textChanged, this, &WidgetSelectionWindow::on_configChanged);
    m_configLayout->addRow("行名设置:", m_tableRowNamesEdit);

    m_tableColNamesEdit = new QLineEdit();
    m_tableColNamesEdit->setPlaceholderText("用逗号分隔，如：列1,列2,列3");
    connect(m_tableColNamesEdit, &QLineEdit::textChanged, this, &WidgetSelectionWindow::on_configChanged);
    m_configLayout->addRow("列名设置:", m_tableColNamesEdit);
}

void WidgetSelectionWindow::setupCurveConfig()
{
    m_curveYAxisNameEdit = new QLineEdit();
    m_curveYAxisNameEdit->setPlaceholderText("输入纵轴名称，如：温度(°C)");
    connect(m_curveYAxisNameEdit, &QLineEdit::textChanged, this, &WidgetSelectionWindow::on_configChanged);
    m_configLayout->addRow("纵轴名称:", m_curveYAxisNameEdit);

    m_curveColorButton = new QPushButton("选择颜色");
    m_curveColorButton->setStyleSheet(QString("background-color: %1; color: white; border-radius: 5px; padding: 5px;").arg(m_curveSelectedColor.name()));
    connect(m_curveColorButton, &QPushButton::clicked, [this]() {
        QColor color = QColorDialog::getColor(m_curveSelectedColor, this, "选择曲线颜色");
        if (color.isValid()) {
            m_curveSelectedColor = color;
            m_curveColorButton->setStyleSheet(QString("background-color: %1; color: white; border-radius: 5px; padding: 5px;").arg(color.name()));
            on_configChanged();
        }
        });
    m_configLayout->addRow("曲线颜色:", m_curveColorButton);

    m_timeRangeCombo = new QComboBox();
    m_timeRangeCombo->addItems({ "最近1小时", "最近6小时", "最近24小时", "最近7天", "最近30天", "自定义区间" });
    m_timeRangeCombo->setCurrentText("最近24小时");
    connect(m_timeRangeCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &WidgetSelectionWindow::on_configChanged);
    m_configLayout->addRow("时间区间:", m_timeRangeCombo);
}

void WidgetSelectionWindow::setupBarChartConfig()
{
    m_barOrientationCombo = new QComboBox();
    m_barOrientationCombo->addItems({ "纵向显示", "横向显示" });
    connect(m_barOrientationCombo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &WidgetSelectionWindow::on_configChanged);
    m_configLayout->addRow("显示方向:", m_barOrientationCombo);

    m_barColorButton = new QPushButton("选择颜色");
    m_barColorButton->setStyleSheet(QString("background-color: %1; color: white; border-radius: 5px; padding: 5px;").arg(m_barSelectedColor.name()));
    connect(m_barColorButton, &QPushButton::clicked, [this]() {
        QColor color = QColorDialog::getColor(m_barSelectedColor, this, "选择柱状图颜色");
        if (color.isValid()) {
            m_barSelectedColor = color;
            m_barColorButton->setStyleSheet(QString("background-color: %1; color: white; border-radius: 5px; padding: 5px;").arg(color.name()));
            on_configChanged();
        }
        });
    m_configLayout->addRow("柱状图颜色:", m_barColorButton);

    m_barNameEdit = new QLineEdit();
    m_barNameEdit->setPlaceholderText("输入图表名称，如：销售数据统计");
    connect(m_barNameEdit, &QLineEdit::textChanged, this, &WidgetSelectionWindow::on_configChanged);
    m_configLayout->addRow("图表名称:", m_barNameEdit);
}

void WidgetSelectionWindow::on_configChanged()
{
    updatePreviewWithConfig();
}


void WidgetSelectionWindow::updatePreview()
{
    // 清理旧的预览控件
    clearPreviewSafely();

    // 创建新的预览控件
    m_previewWidget = new CustomWidget(m_selectedType, "preview_widget");
    m_previewWidget->setEnabled(false); // 预览控件不可交互

    // 设置预览控件大小和位置
    m_previewWidget->setPos(10, 10);
    m_previewWidget->resize(180, 120);

    // 添加到预览场景
    if (m_previewScene) {
        m_previewScene->addItem(m_previewWidget);
        // 设置场景大小
        m_previewScene->setSceneRect(0, 0, 200, 140);
    }

    // 应用当前配置
    updatePreviewWithConfig();
}

void WidgetSelectionWindow::updatePreviewWithConfig()
{
    if (!m_previewWidget) return;

    // 这里可以根据配置更新预览控件的显示
    // 目前CustomWidget还是使用基本的绘制，后续集成控件库后可以更详细地预览

    m_previewWidget->update();
}

void WidgetSelectionWindow::on_dataBindingButton_clicked()
{
    DataBindingWindow dialog(m_selectedType, this);
    dialog.setDataBindings(m_dataBindings);

    if (dialog.exec() == QDialog::Accepted) {
        m_dataBindings = dialog.getDataBindings();
        // 可以在这里更新预览，显示绑定了数据的效果
        updatePreviewWithConfig();
    }
}

void WidgetSelectionWindow::on_confirmButton_clicked()
{
    accept(); // 触发QDialog的accept信号
    close();
}

void WidgetSelectionWindow::on_cancelButton_clicked()
{
    reject();
}

// ========== 预留的控件库调用函数 ==========

QWidget* WidgetSelectionWindow::createTableWidget(const QVariantMap& config)
{
    // TODO: 这里将来调用实际的表格控件库
    // 例如：return TableWidgetLibrary::createTable(config);
    Q_UNUSED(config);

    // 现在返回空指针，使用CustomWidget的基本绘制
    return nullptr;
}

QWidget* WidgetSelectionWindow::createCurveWidget(const QVariantMap& config)
{
    // TODO: 这里将来调用实际的曲线控件库
    // 例如：return ChartWidgetLibrary::createCurve(config);
    Q_UNUSED(config);

    // 现在返回空指针，使用CustomWidget的基本绘制
    return nullptr;
}

QWidget* WidgetSelectionWindow::createBarChartWidget(const QVariantMap& config)
{
    // TODO: 这里将来调用实际的柱状图控件库
    // 例如：return ChartWidgetLibrary::createBarChart(config);
    Q_UNUSED(config);

    // 现在返回空指针，使用CustomWidget的基本绘制
    return nullptr;
}