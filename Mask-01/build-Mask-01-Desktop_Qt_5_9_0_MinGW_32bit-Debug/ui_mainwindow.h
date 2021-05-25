/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *label_3;
    QPushButton *LogBtn;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *serverIp;
    QLineEdit *serverPort;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(541, 414);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(160, 10, 191, 191));
        label_3->setPixmap(QPixmap(QString::fromUtf8(":/g.png")));
        LogBtn = new QPushButton(centralwidget);
        LogBtn->setObjectName(QStringLiteral("LogBtn"));
        LogBtn->setGeometry(QRect(100, 240, 341, 51));
        LogBtn->setCursor(QCursor(Qt::IBeamCursor));
        LogBtn->setIconSize(QSize(400, 100));
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(100, 122, 339, 101));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        serverIp = new QLineEdit(layoutWidget);
        serverIp->setObjectName(QStringLiteral("serverIp"));

        verticalLayout_2->addWidget(serverIp);

        serverPort = new QLineEdit(layoutWidget);
        serverPort->setObjectName(QStringLiteral("serverPort"));

        verticalLayout_2->addWidget(serverPort);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        label_3->setText(QString());
        LogBtn->setText(QApplication::translate("MainWindow", "\347\231\273\345\275\225", Q_NULLPTR));
        serverIp->setPlaceholderText(QApplication::translate("MainWindow", "\346\234\215\345\212\241\345\231\250IP", Q_NULLPTR));
        serverPort->setPlaceholderText(QApplication::translate("MainWindow", "\347\253\257\345\217\243\345\217\267", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
