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

    // ��ȡ�󶨵���������
    QMap<QString, QVariant> getDataBindings() const;

    // �������ݰ󶨣����ڱ༭���пؼ�ʱ��
    void setDataBindings(const QMap<QString, QVariant>& bindings);

private slots:
    void on_testConnectionButton_clicked();  // �������Ӱ�ť
    void on_confirmButton_clicked();
    void on_cancelButton_clicked();
    void on_addBindingButton_clicked();      // ������ݰ�
    void on_removeBindingButton_clicked();   // �Ƴ����ݰ�

private:
    Ui::DataBindingWindow* ui;
    CustomWidget::WidgetType m_widgetType;
    QMap<QString, QVariant> m_dataBindings;

    void setupWidgetSpecificBindings();     // ���ݿؼ����������ض��İ�ѡ��
    void updateBindingList();               // ���°��б���ʾ

    // Ԥ�������ݿ�ӿں���λ��
    bool connectToDatabase();               // �������ݿ�
    QStringList getAvailableDataSources();  // ��ȡ��������Դ
    QVariant fetchDataFromSource(const QString& source); // ������Դ��ȡ����
};

#endif // DATABINDINGWINDOW_H