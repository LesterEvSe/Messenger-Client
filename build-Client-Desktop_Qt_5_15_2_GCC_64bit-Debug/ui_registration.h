/********************************************************************************
** Form generated from reading UI file 'registration.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTRATION_H
#define UI_REGISTRATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Registration
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *usernameLineEdit;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *passwordLineEdit;
    QCheckBox *showPasswordCheckBox;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *signUpButton;
    QPushButton *signInButton;

    void setupUi(QDialog *Registration)
    {
        if (Registration->objectName().isEmpty())
            Registration->setObjectName(QString::fromUtf8("Registration"));
        Registration->resize(345, 190);
        QFont font;
        font.setPointSize(14);
        font.setBold(false);
        Registration->setFont(font);
        verticalLayout = new QVBoxLayout(Registration);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(Registration);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font1;
        font1.setPointSize(14);
        font1.setBold(true);
        label->setFont(font1);

        horizontalLayout->addWidget(label);

        usernameLineEdit = new QLineEdit(Registration);
        usernameLineEdit->setObjectName(QString::fromUtf8("usernameLineEdit"));

        horizontalLayout->addWidget(usernameLineEdit);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(Registration);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font1);

        horizontalLayout_2->addWidget(label_2);

        passwordLineEdit = new QLineEdit(Registration);
        passwordLineEdit->setObjectName(QString::fromUtf8("passwordLineEdit"));

        horizontalLayout_2->addWidget(passwordLineEdit);


        verticalLayout->addLayout(horizontalLayout_2);

        showPasswordCheckBox = new QCheckBox(Registration);
        showPasswordCheckBox->setObjectName(QString::fromUtf8("showPasswordCheckBox"));
        QFont font2;
        font2.setPointSize(11);
        font2.setBold(false);
        showPasswordCheckBox->setFont(font2);

        verticalLayout->addWidget(showPasswordCheckBox);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        signUpButton = new QPushButton(Registration);
        signUpButton->setObjectName(QString::fromUtf8("signUpButton"));

        horizontalLayout_3->addWidget(signUpButton);

        signInButton = new QPushButton(Registration);
        signInButton->setObjectName(QString::fromUtf8("signInButton"));

        horizontalLayout_3->addWidget(signInButton);


        verticalLayout->addLayout(horizontalLayout_3);


        retranslateUi(Registration);

        QMetaObject::connectSlotsByName(Registration);
    } // setupUi

    void retranslateUi(QDialog *Registration)
    {
        Registration->setWindowTitle(QCoreApplication::translate("Registration", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("Registration", "Username", nullptr));
        label_2->setText(QCoreApplication::translate("Registration", "Password ", nullptr));
        showPasswordCheckBox->setText(QCoreApplication::translate("Registration", "Show Password", nullptr));
        signUpButton->setText(QCoreApplication::translate("Registration", "Sign Up", nullptr));
        signInButton->setText(QCoreApplication::translate("Registration", "Sign In", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Registration: public Ui_Registration {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTRATION_H
