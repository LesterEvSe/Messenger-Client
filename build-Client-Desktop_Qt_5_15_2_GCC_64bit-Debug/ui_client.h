/********************************************************************************
** Form generated from reading UI file 'client.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENT_H
#define UI_CLIENT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Client
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *connectButton;
    QHBoxLayout *horizontalLayout;
    QListWidget *listWidget;
    QTextBrowser *textBrowser;
    QListWidget *listWidget_3;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *sendMessageLineEdit;
    QPushButton *sendMessageButton;

    void setupUi(QWidget *Client)
    {
        if (Client->objectName().isEmpty())
            Client->setObjectName(QString::fromUtf8("Client"));
        Client->resize(670, 453);
        QFont font;
        font.setPointSize(14);
        Client->setFont(font);
        verticalLayout = new QVBoxLayout(Client);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(Client);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(label);

        label_2 = new QLabel(Client);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(2);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);
        label_2->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(label_2);

        label_3 = new QLabel(Client);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);
        label_3->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(label_3);


        verticalLayout->addLayout(horizontalLayout_2);

        connectButton = new QPushButton(Client);
        connectButton->setObjectName(QString::fromUtf8("connectButton"));

        verticalLayout->addWidget(connectButton);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        listWidget = new QListWidget(Client);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(1);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(listWidget->sizePolicy().hasHeightForWidth());
        listWidget->setSizePolicy(sizePolicy2);

        horizontalLayout->addWidget(listWidget);

        textBrowser = new QTextBrowser(Client);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(2);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(textBrowser->sizePolicy().hasHeightForWidth());
        textBrowser->setSizePolicy(sizePolicy3);

        horizontalLayout->addWidget(textBrowser);

        listWidget_3 = new QListWidget(Client);
        listWidget_3->setObjectName(QString::fromUtf8("listWidget_3"));
        sizePolicy2.setHeightForWidth(listWidget_3->sizePolicy().hasHeightForWidth());
        listWidget_3->setSizePolicy(sizePolicy2);

        horizontalLayout->addWidget(listWidget_3);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        sendMessageLineEdit = new QLineEdit(Client);
        sendMessageLineEdit->setObjectName(QString::fromUtf8("sendMessageLineEdit"));

        horizontalLayout_3->addWidget(sendMessageLineEdit);

        sendMessageButton = new QPushButton(Client);
        sendMessageButton->setObjectName(QString::fromUtf8("sendMessageButton"));

        horizontalLayout_3->addWidget(sendMessageButton);


        verticalLayout->addLayout(horizontalLayout_3);


        retranslateUi(Client);

        QMetaObject::connectSlotsByName(Client);
    } // setupUi

    void retranslateUi(QWidget *Client)
    {
        Client->setWindowTitle(QCoreApplication::translate("Client", "Form", nullptr));
        label->setText(QCoreApplication::translate("Client", "Online Users", nullptr));
        label_2->setText(QCoreApplication::translate("Client", "Current Chat", nullptr));
        label_3->setText(QCoreApplication::translate("Client", "My Chats", nullptr));
        connectButton->setText(QCoreApplication::translate("Client", "Connect", nullptr));
        sendMessageButton->setText(QCoreApplication::translate("Client", "->", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Client: public Ui_Client {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENT_H
