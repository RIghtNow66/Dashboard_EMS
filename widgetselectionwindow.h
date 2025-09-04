#ifndef WIDGETSELECTIONWINDOW_H
#define WIDGETSELECTIONWINDOW_H

#include <QWidget>
#include <QDialog>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QColorDialog>
#include <QSpinBox>
#include <QLineEdit>
#include <QLabel>
#include <QComboBox>
#include <QGroupBox>
#include <QFormLayout>
#include "customwidget.h"

namespace Ui
{
class WidgetSelectionWindow;
}

class WidgetSelectionWindow : public QDialog
{
    Q_OBJECT

public:
    explicit WidgetSelectionWindow(QWidget* parent = nullptr);
    ~WidgetSelectionWindow() override;

    CustomWidget::WidgetType selectedWidgetType() const;
    QString widgetName() const;

    // 获取控件配置参数
    QVariantMap getWidgetConfig() const;

    // 获取数据绑定配置
    QVariantMap getDataBindings() const;

private slots:
    void on_widgetList_itemSelectionChanged();
    void on_confirmButton_clicked();
    void on_cancelButton_clicked();
    void on_dataBindingButton_clicked();      // 数据绑定按钮槽函数
    void on_configChanged();

private:
    Ui::WidgetSelectionWindow *ui;
    CustomWidget::WidgetType m_selectedType;
    QGraphicsView* m_previewView;            // 预览视图
    QGraphicsScene* m_previewScene;          // 预览场景
    CustomWidget* m_previewWidget;           // 预览控件
    QVariantMap m_dataBindings;              // 数据绑定配置

    // 配置控件组
    QGroupBox* m_configGroup;
    QFormLayout* m_configLayout;

    // 表格特定配置控件
    QSpinBox* m_tableRowSpin;               // 表格行数
    QSpinBox* m_tableColSpin;               // 表格列数
    QLineEdit* m_tableRowNamesEdit;         // 行名设置
    QLineEdit* m_tableColNamesEdit;         // 列名设置

    // 曲线特定配置控件
    QLineEdit* m_curveYAxisNameEdit;        // 纵轴名称
    QPushButton* m_curveColorButton;        // 曲线颜色按钮
    QColor m_curveSelectedColor;            // 曲线选中颜色
    QComboBox* m_timeRangeCombo;            // 时间区间选择

    // 柱状图特定配置控件
    QComboBox* m_barOrientationCombo;       // 柱状图方向（横向/纵向）
    QPushButton* m_barColorButton;          // 柱状图颜色按钮
    QColor m_barSelectedColor;              // 柱状图选中颜色
    QLineEdit* m_barNameEdit;               // 柱状图名称

    void updatePreview();                    // 更新预览
    void setupConfigOptions();               // 设置配置选项
    void clearConfigLayout();                // 清空配置布局
    void setupTableConfig();                 // 设置表格配置
    void setupCurveConfig();                 // 设置曲线配置
    void setupBarChartConfig();              // 设置柱状图配置
    void updatePreviewWithConfig();          // 用配置更新预览
    void clearPreviewSafely();               // 安全地清理预览控件

    // 预留的控件库调用函数位置
    QWidget* createTableWidget(const QVariantMap& config);      // 创建表格控件
    QWidget* createCurveWidget(const QVariantMap& config);      // 创建曲线控件
    QWidget* createBarChartWidget(const QVariantMap& config);   // 创建柱状图控件
};

#endif // WIDGETSELECTIONWINDOW_H
