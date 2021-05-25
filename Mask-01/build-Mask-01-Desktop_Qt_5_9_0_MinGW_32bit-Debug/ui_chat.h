/********************************************************************************
** Form generated from reading UI file 'chat.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHAT_H
#define UI_CHAT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Chat
{
public:
    QWidget *centralwidget;
    QLabel *showLable;
    QPushButton *chatReturn;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QPlainTextEdit *chatShow;
    QHBoxLayout *horizontalLayout;
    QLineEdit *chatText;
    QPushButton *chatSend;

    void setupUi(QMainWindow *Chat)
    {
        if (Chat->objectName().isEmpty())
            Chat->setObjectName(QStringLiteral("Chat"));
        Chat->resize(578, 354);
        QIcon icon;
        icon.addFile(QStringLiteral(":/maskicon.png"), QSize(), QIcon::Normal, QIcon::Off);
        Chat->setWindowIcon(icon);
        centralwidget = new QWidget(Chat);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        showLable = new QLabel(centralwidget);
        showLable->setObjectName(QStringLiteral("showLable"));
        showLable->setGeometry(QRect(430, 80, 141, 181));
        showLable->setPixmap(QPixmap(QString::fromUtf8("maskman1.png")));
        showLable->setScaledContents(true);
        chatReturn = new QPushButton(centralwidget);
        chatReturn->setObjectName(QStringLiteral("chatReturn"));
        chatReturn->setGeometry(QRect(460, 310, 91, 31));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(0, 20, 421, 321));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        chatShow = new QPlainTextEdit(widget);
        chatShow->setObjectName(QStringLiteral("chatShow"));

        verticalLayout->addWidget(chatShow);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        chatText = new QLineEdit(widget);
        chatText->setObjectName(QStringLiteral("chatText"));

        horizontalLayout->addWidget(chatText);

        chatSend = new QPushButton(widget);
        chatSend->setObjectName(QStringLiteral("chatSend"));

        horizontalLayout->addWidget(chatSend);


        verticalLayout->addLayout(horizontalLayout);

        Chat->setCentralWidget(centralwidget);

        retranslateUi(Chat);

        QMetaObject::connectSlotsByName(Chat);
    } // setupUi

    void retranslateUi(QMainWindow *Chat)
    {
        Chat->setWindowTitle(QApplication::translate("Chat", "\347\247\201\350\201\212", Q_NULLPTR));
        showLable->setText(QString());
        chatReturn->setText(QApplication::translate("Chat", "\350\277\224\345\233\236\347\276\244\350\201\212", Q_NULLPTR));
        chatSend->setText(QApplication::translate("Chat", "\345\217\221\351\200\201", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Chat: public Ui_Chat {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHAT_H
