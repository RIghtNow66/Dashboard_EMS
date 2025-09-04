/********************************************************************************
** Form generated from reading UI file 'databindingwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATABINDINGWINDOW_H
#define UI_DATABINDINGWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DataBindingWindow
{
public:
    QVBoxLayout* verticalLayout;
    QWidget* contentWidget;
    QVBoxLayout* contentLayout;
    QGroupBox* connectionGroupBox;
    QVBoxLayout* connectionLayout;
    QHBoxLayout* connectionInputLayout;
    QLabel* connectionLabel;
    QLineEdit* connectionEdit;
    QPushButton* testConnectionButton;
    QLabel* statusLabel;
    QGroupBox* instructionGroupBox;
    QVBoxLayout* instructionLayout;
    QLabel* instructionLabel;
    QGroupBox* bindingGroupBox;
    QVBoxLayout* bindingLayout;
    QHBoxLayout* bindingControlLayout;
    QLabel* bindingTypeLabel;
    QComboBox* bindingTypeCombo;
    QSpacerItem* horizontalSpacer;
    QPushButton* addBindingButton;
    QPushButton* removeBindingButton;
    QListWidget* bindingList;
    QWidget* buttonWidget;
    QHBoxLayout* buttonLayout;
    QSpacerItem* buttonSpacer;
    QPushButton* cancelButton;
    QPushButton* confirmButton;

    void setupUi(QWidget* DataBindingWindow)
    {
        if (DataBindingWindow->objectName().isEmpty())
            DataBindingWindow->setObjectName(QString::fromUtf8("DataBindingWindow"));
        DataBindingWindow->resize(500, 600);
        verticalLayout = new QVBoxLayout(DataBindingWindow);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));

        contentWidget = new QWidget(DataBindingWindow);
        contentWidget->setObjectName(QString::fromUtf8("contentWidget"));
        contentLayout = new QVBoxLayout(contentWidget);
        contentLayout->setObjectName(QString::fromUtf8("contentLayout"));

        // 连接配置分组
        connectionGroupBox = new QGroupBox(contentWidget);
        connectionGroupBox->setObjectName(QString::fromUtf8("connectionGroupBox"));
        connectionLayout = new QVBoxLayout(connectionGroupBox);
        connectionLayout->setObjectName(QString::fromUtf8("connectionLayout"));

        connectionInputLayout = new QHBoxLayout();
        connectionInputLayout->setObjectName(QString::fromUtf8("connectionInputLayout"));

        connectionLabel = new QLabel(connectionGroupBox);
        connectionLabel->setObjectName(QString::fromUtf8("connectionLabel"));
        connectionInputLayout->addWidget(connectionLabel);

        connectionEdit = new QLineEdit(connectionGroupBox);
        connectionEdit->setObjectName(QString::fromUtf8("connectionEdit"));
        connectionEdit->setPlaceholderText("请输入数据库连接字符串");
        connectionInputLayout->addWidget(connectionEdit);

        testConnectionButton = new QPushButton(connectionGroupBox);
        testConnectionButton->setObjectName(QString::fromUtf8("testConnectionButton"));
        connectionInputLayout->addWidget(testConnectionButton);

        connectionLayout->addLayout(connectionInputLayout);

        statusLabel = new QLabel(connectionGroupBox);
        statusLabel->setObjectName(QString::fromUtf8("statusLabel"));
        statusLabel->setStyleSheet("color: #666666;");
        connectionLayout->addWidget(statusLabel);

        contentLayout->addWidget(connectionGroupBox);

        // 说明信息分组
        instructionGroupBox = new QGroupBox(contentWidget);
        instructionGroupBox->setObjectName(QString::fromUtf8("instructionGroupBox"));
        instructionLayout = new QVBoxLayout(instructionGroupBox);
        instructionLayout->setObjectName(QString::fromUtf8("instructionLayout"));

        instructionLabel = new QLabel(instructionGroupBox);
        instructionLabel->setObjectName(QString::fromUtf8("instructionLabel"));
        instructionLabel->setWordWrap(true);
        instructionLabel->setStyleSheet("color: #333333; background-color: #f9f9f9; padding: 10px; border-radius: 5px;");
        instructionLayout->addWidget(instructionLabel);

        contentLayout->addWidget(instructionGroupBox);

        // 数据绑定配置分组
        bindingGroupBox = new QGroupBox(contentWidget);
        bindingGroupBox->setObjectName(QString::fromUtf8("bindingGroupBox"));
        bindingLayout = new QVBoxLayout(bindingGroupBox);
        bindingLayout->setObjectName(QString::fromUtf8("bindingLayout"));

        bindingControlLayout = new QHBoxLayout();
        bindingControlLayout->setObjectName(QString::fromUtf8("bindingControlLayout"));

        bindingTypeLabel = new QLabel(bindingGroupBox);
        bindingTypeLabel->setObjectName(QString::fromUtf8("bindingTypeLabel"));
        bindingControlLayout->addWidget(bindingTypeLabel);

        bindingTypeCombo = new QComboBox(bindingGroupBox);
        bindingTypeCombo->setObjectName(QString::fromUtf8("bindingTypeCombo"));
        bindingControlLayout->addWidget(bindingTypeCombo);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
        bindingControlLayout->addItem(horizontalSpacer);

        addBindingButton = new QPushButton(bindingGroupBox);
        addBindingButton->setObjectName(QString::fromUtf8("addBindingButton"));
        bindingControlLayout->addWidget(addBindingButton);

        removeBindingButton = new QPushButton(bindingGroupBox);
        removeBindingButton->setObjectName(QString::fromUtf8("removeBindingButton"));
        bindingControlLayout->addWidget(removeBindingButton);

        bindingLayout->addLayout(bindingControlLayout);

        bindingList = new QListWidget(bindingGroupBox);
        bindingList->setObjectName(QString::fromUtf8("bindingList"));
        bindingList->setMinimumHeight(150);
        bindingLayout->addWidget(bindingList);

        contentLayout->addWidget(bindingGroupBox);

        verticalLayout->addWidget(contentWidget);

        // 按钮区域
        buttonWidget = new QWidget(DataBindingWindow);
        buttonWidget->setObjectName(QString::fromUtf8("buttonWidget"));
        buttonLayout = new QHBoxLayout(buttonWidget);
        buttonLayout->setObjectName(QString::fromUtf8("buttonLayout"));

        buttonSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
        buttonLayout->addItem(buttonSpacer);

        cancelButton = new QPushButton(buttonWidget);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));
        buttonLayout->addWidget(cancelButton);

        confirmButton = new QPushButton(buttonWidget);
        confirmButton->setObjectName(QString::fromUtf8("confirmButton"));
        buttonLayout->addWidget(confirmButton);

        verticalLayout->addWidget(buttonWidget);

        retranslateUi(DataBindingWindow);

        QMetaObject::connectSlotsByName(DataBindingWindow);
    } // setupUi

    void retranslateUi(QWidget* DataBindingWindow)
    {
        DataBindingWindow->setWindowTitle(QCoreApplication::translate("DataBindingWindow", "\346\225\260\346\215\256\347\273\221\345\256\232\351\205\215\347\275\256", nullptr));
        connectionGroupBox->setTitle(QCoreApplication::translate("DataBindingWindow", "\346\225\260\346\215\256\346\272\220\350\277\236\346\216\245", nullptr));
        connectionLabel->setText(QCoreApplication::translate("DataBindingWindow", "\350\277\236\346\216\245\345\255\227\347\254\246\344\270\262:", nullptr));
        testConnectionButton->setText(QCoreApplication::translate("DataBindingWindow", "\346\265\213\350\257\225\350\277\236\346\216\245", nullptr));
        statusLabel->setText(QCoreApplication::translate("DataBindingWindow", "\345\260\261\347\273\252", nullptr));
        instructionGroupBox->setTitle(QCoreApplication::translate("DataBindingWindow", "\347\273\221\345\256\232\350\257\264\346\230\216", nullptr));
        instructionLabel->setText(QCoreApplication::translate("DataBindingWindow", "\350\257\267\351\200\211\346\213\251\346\216\247\344\273\266\347\261\273\345\236\213\346\235\245\346\237\245\347\234\213\347\233\270\345\272\224\347\232\204\346\225\260\346\215\256\347\273\221\345\256\232\350\257\264\346\230\216", nullptr));
        bindingGroupBox->setTitle(QCoreApplication::translate("DataBindingWindow", "\346\225\260\346\215\256\347\273\221\345\256\232\351\205\215\347\275\256", nullptr));
        bindingTypeLabel->setText(QCoreApplication::translate("DataBindingWindow", "\347\273\221\345\256\232\347\261\273\345\236\213:", nullptr));
        addBindingButton->setText(QCoreApplication::translate("DataBindingWindow", "\346\267\273\345\212\240", nullptr));
        removeBindingButton->setText(QCoreApplication::translate("DataBindingWindow", "\347\247\273\351\231\244", nullptr));
        cancelButton->setText(QCoreApplication::translate("DataBindingWindow", "\345\217\226\346\266\210", nullptr));
        confirmButton->setText(QCoreApplication::translate("DataBindingWindow", "\347\241\256\350\256\244", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DataBindingWindow : public Ui_DataBindingWindow {};
} // namespace Ui

QT_BEGIN_NAMESPACE

#endif // UI_DATABINDINGWINDOW_H