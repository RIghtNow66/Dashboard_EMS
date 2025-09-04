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

    // ��ȡ�ؼ����ò���
    QVariantMap getWidgetConfig() const;

    // ��ȡ���ݰ�����
    QVariantMap getDataBindings() const;

private slots:
    void on_widgetList_itemSelectionChanged();
    void on_confirmButton_clicked();
    void on_cancelButton_clicked();
    void on_dataBindingButton_clicked();      // ���ݰ󶨰�ť�ۺ���
    void on_configChanged();

private:
    Ui::WidgetSelectionWindow *ui;
    CustomWidget::WidgetType m_selectedType;
    QGraphicsView* m_previewView;            // Ԥ����ͼ
    QGraphicsScene* m_previewScene;          // Ԥ������
    CustomWidget* m_previewWidget;           // Ԥ���ؼ�
    QVariantMap m_dataBindings;              // ���ݰ�����

    // ���ÿؼ���
    QGroupBox* m_configGroup;
    QFormLayout* m_configLayout;

    // ����ض����ÿؼ�
    QSpinBox* m_tableRowSpin;               // �������
    QSpinBox* m_tableColSpin;               // �������
    QLineEdit* m_tableRowNamesEdit;         // ��������
    QLineEdit* m_tableColNamesEdit;         // ��������

    // �����ض����ÿؼ�
    QLineEdit* m_curveYAxisNameEdit;        // ��������
    QPushButton* m_curveColorButton;        // ������ɫ��ť
    QColor m_curveSelectedColor;            // ����ѡ����ɫ
    QComboBox* m_timeRangeCombo;            // ʱ������ѡ��

    // ��״ͼ�ض����ÿؼ�
    QComboBox* m_barOrientationCombo;       // ��״ͼ���򣨺���/����
    QPushButton* m_barColorButton;          // ��״ͼ��ɫ��ť
    QColor m_barSelectedColor;              // ��״ͼѡ����ɫ
    QLineEdit* m_barNameEdit;               // ��״ͼ����

    void updatePreview();                    // ����Ԥ��
    void setupConfigOptions();               // ��������ѡ��
    void clearConfigLayout();                // ������ò���
    void setupTableConfig();                 // ���ñ������
    void setupCurveConfig();                 // ������������
    void setupBarChartConfig();              // ������״ͼ����
    void updatePreviewWithConfig();          // �����ø���Ԥ��
    void clearPreviewSafely();               // ��ȫ������Ԥ���ؼ�

    // Ԥ���Ŀؼ�����ú���λ��
    QWidget* createTableWidget(const QVariantMap& config);      // �������ؼ�
    QWidget* createCurveWidget(const QVariantMap& config);      // �������߿ؼ�
    QWidget* createBarChartWidget(const QVariantMap& config);   // ������״ͼ�ؼ�
};

#endif // WIDGETSELECTIONWINDOW_H
