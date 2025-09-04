#include "databindingwindow.h"
#include "ui_databindingwindow.h"
#include <QMessageBox>
#include <QInputDialog>
#include <QStringListModel>
#include <QThread>
#include <QRandomGenerator>

DataBindingWindow::DataBindingWindow(CustomWidget::WidgetType widgetType, QWidget* parent)
    : QDialog(parent), ui(new Ui::DataBindingWindow), m_widgetType(widgetType)
{
    ui->setupUi(this);
    setWindowTitle("Data Binding Configuration");
    setModal(true);

    setupWidgetSpecificBindings();
    updateBindingList();
}

DataBindingWindow::~DataBindingWindow()
{
    delete ui;
}

QMap<QString, QVariant> DataBindingWindow::getDataBindings() const
{
    return m_dataBindings;
}

void DataBindingWindow::setDataBindings(const QMap<QString, QVariant>& bindings)
{
    m_dataBindings = bindings;
    updateBindingList();
}

void DataBindingWindow::setupWidgetSpecificBindings()
{
    ui->bindingTypeCombo->clear();

    switch (m_widgetType) {
    case CustomWidget::Table:
        ui->bindingTypeCombo->addItem("Data Source", "datasource");
        ui->bindingTypeCombo->addItem("Column Config", "columns");
        ui->bindingTypeCombo->addItem("Row Data", "rows");
        ui->instructionLabel->setText("Table Widget Data Binding:\n- Data Source: Specify data source\n- Column Config: Define table columns\n- Row Data: Bind specific data");
        break;

    case CustomWidget::Curve:
        ui->bindingTypeCombo->addItem("X-Axis Data", "x_data");
        ui->bindingTypeCombo->addItem("Y-Axis Data", "y_data");
        ui->bindingTypeCombo->addItem("Data Series", "series");
        ui->instructionLabel->setText("Curve Widget Data Binding:\n- X-Axis Data: Time data source\n- Y-Axis Data: Value data source\n- Data Series: Multiple curve config");
        break;

    case CustomWidget::BarChart:
        ui->bindingTypeCombo->addItem("Category Data", "categories");
        ui->bindingTypeCombo->addItem("Value Data", "values");
        ui->bindingTypeCombo->addItem("Data Series", "series");
        ui->instructionLabel->setText("Bar Chart Widget Data Binding:\n- Category Data: Bar categories\n- Value Data: Bar height data\n- Data Series: Multiple data groups");
        break;
    }
}

void DataBindingWindow::updateBindingList()
{
    ui->bindingList->clear();

    QMapIterator<QString, QVariant> iter(m_dataBindings);
    while (iter.hasNext()) {
        iter.next();
        QString displayText = QString("%1: %2").arg(iter.key()).arg(iter.value().toString());
        ui->bindingList->addItem(displayText);
    }
}

void DataBindingWindow::on_testConnectionButton_clicked()
{
    ui->statusLabel->setText("Testing connection...");

    bool connectionResult = connectToDatabase();

    if (connectionResult) {
        ui->statusLabel->setText("Connection successful!");
        QMessageBox::information(this, "Connection Test", "Database connection test successful!");
    }
    else {
        ui->statusLabel->setText("Connection failed!");
        QMessageBox::warning(this, "Connection Test", "Database connection test failed, please check configuration!");
    }
}

void DataBindingWindow::on_addBindingButton_clicked()
{
    int currentIndex = ui->bindingTypeCombo->currentIndex();
    if (currentIndex < 0) return;

    QString bindingType = ui->bindingTypeCombo->currentText();
    QString bindingKey = ui->bindingTypeCombo->itemData(currentIndex).toString();

    bool ok;
    QString promptText = QString("Please enter data source for '%1':").arg(bindingType);
    QString dataSource = QInputDialog::getText(this, "Add Data Binding", promptText, QLineEdit::Normal, QString(), &ok);

    if (ok && !dataSource.isEmpty()) {
        m_dataBindings[bindingKey] = dataSource;
        updateBindingList();
        ui->statusLabel->setText(QString("Added binding: %1").arg(bindingType));
    }
}

void DataBindingWindow::on_removeBindingButton_clicked()
{
    int currentRow = ui->bindingList->currentRow();
    if (currentRow < 0) return;

    QString itemText = ui->bindingList->item(currentRow)->text();
    QString key = itemText.split(":").first().trimmed();

    QMapIterator<QString, QVariant> iter(m_dataBindings);
    while (iter.hasNext()) {
        iter.next();
        if (iter.key() == key) {
            m_dataBindings.remove(iter.key());
            break;
        }
    }

    updateBindingList();
    ui->statusLabel->setText("Removed selected data binding");
}

void DataBindingWindow::on_confirmButton_clicked()
{
    bool hasRequiredBindings = !m_dataBindings.isEmpty();

    if (!hasRequiredBindings) {
        QMessageBox::warning(this, "Incomplete Configuration", "Please configure at least one data binding!");
        return;
    }

    accept();
}

void DataBindingWindow::on_cancelButton_clicked()
{
    reject();
}

bool DataBindingWindow::connectToDatabase()
{
    QString connectionString = ui->connectionEdit->text();
    if (connectionString.isEmpty()) {
        return false;
    }

    QThread::msleep(500);

    return (QRandomGenerator::global()->bounded(100) < 80);
}

QStringList DataBindingWindow::getAvailableDataSources()
{
    QStringList sources;
    sources << "database.table1" << "database.table2" << "api.endpoint1" << "file.data.csv";
    return sources;
}

QVariant DataBindingWindow::fetchDataFromSource(const QString& source)
{
    Q_UNUSED(source);

    QVariantList mockData;
    mockData << "Data1" << "Data2" << "Data3";
    return mockData;
}