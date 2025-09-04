#ifndef DATABINDINGWINDOW_H
#define DATABINDINGWINDOW_H

#include <QDialog>
#include <QVariant>
#include <QMap>
#include "customwidget.h"

namespace Ui {
    class DataBindingWindow;
}

class DataBindingWindow : public QDialog
{
    Q_OBJECT

public:
    explicit DataBindingWindow(CustomWidget::WidgetType widgetType, QWidget* parent = nullptr);
    ~DataBindingWindow();

    // 获取绑定的数据配置
    QMap<QString, QVariant> getDataBindings() const;

    // 设置数据绑定（用于编辑已有控件时）
    void setDataBindings(const QMap<QString, QVariant>& bindings);

private slots:
    void on_testConnectionButton_clicked();  // 测试连接按钮
    void on_confirmButton_clicked();
    void on_cancelButton_clicked();
    void on_addBindingButton_clicked();      // 添加数据绑定
    void on_removeBindingButton_clicked();   // 移除数据绑定

private:
    Ui::DataBindingWindow* ui;
    CustomWidget::WidgetType m_widgetType;
    QMap<QString, QVariant> m_dataBindings;

    void setupWidgetSpecificBindings();     // 根据控件类型设置特定的绑定选项
    void updateBindingList();               // 更新绑定列表显示

    // 预留的数据库接口函数位置
    bool connectToDatabase();               // 连接数据库
    QStringList getAvailableDataSources();  // 获取可用数据源
    QVariant fetchDataFromSource(const QString& source); // 从数据源获取数据
};

#endif // DATABINDINGWINDOW_H