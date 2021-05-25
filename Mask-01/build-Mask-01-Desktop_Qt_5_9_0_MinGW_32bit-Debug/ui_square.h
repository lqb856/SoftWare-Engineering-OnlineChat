/********************************************************************************
** Form generated from reading UI file 'square.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SQUARE_H
#define UI_SQUARE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Square
{
public:
    QWidget *centralwidget;
    QLabel *label_currentNum;
    QPushButton *squareMatch;
    QLabel *label_2;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QPlainTextEdit *squareShow;
    QHBoxLayout *horizontalLayout;
    QLineEdit *squareText;
    QPushButton *squareSend;
    QLCDNumber *squareCurOnline;
    QPushButton *squareMatchCancel;

    void setupUi(QMainWindow *Square)
    {
        if (Square->objectName().isEmpty())
            Square->setObjectName(QStringLiteral("Square"));
        Square->resize(949, 558);
        centralwidget = new QWidget(Square);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        label_currentNum = new QLabel(centralwidget);
        label_currentNum->setObjectName(QStringLiteral("label_currentNum"));
        label_currentNum->setGeometry(QRect(640, 30, 111, 31));
        squareMatch = new QPushButton(centralwidget);
        squareMatch->setObjectName(QStringLiteral("squareMatch"));
        squareMatch->setGeometry(QRect(700, 500, 161, 41));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(610, 120, 321, 321));
        label_2->setPixmap(QPixmap(QString::fromUtf8(":/rest.png")));
        label_2->setScaledContents(true);
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 30, 591, 521));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        squareShow = new QPlainTextEdit(layoutWidget);
        squareShow->setObjectName(QStringLiteral("squareShow"));

        verticalLayout->addWidget(squareShow);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        squareText = new QLineEdit(layoutWidget);
        squareText->setObjectName(QStringLiteral("squareText"));

        horizontalLayout->addWidget(squareText);

        squareSend = new QPushButton(layoutWidget);
        squareSend->setObjectName(QStringLiteral("squareSend"));

        horizontalLayout->addWidget(squareSend);


        verticalLayout->addLayout(horizontalLayout);

        squareCurOnline = new QLCDNumber(centralwidget);
        squareCurOnline->setObjectName(QStringLiteral("squareCurOnline"));
        squareCurOnline->setGeometry(QRect(650, 60, 81, 31));
        squareCurOnline->setSmallDecimalPoint(false);
        squareCurOnline->setDigitCount(3);
        squareCurOnline->setProperty("value", QVariant(0));
        squareMatchCancel = new QPushButton(centralwidget);
        squareMatchCancel->setObjectName(QStringLiteral("squareMatchCancel"));
        squareMatchCancel->setGeometry(QRect(700, 440, 161, 41));
        Square->setCentralWidget(centralwidget);
        layoutWidget->raise();
        label_2->raise();
        label_currentNum->raise();
        squareMatch->raise();
        squareCurOnline->raise();
        squareMatchCancel->raise();

        retranslateUi(Square);

        QMetaObject::connectSlotsByName(Square);
    } // setupUi

    void retranslateUi(QMainWindow *Square)
    {
        Square->setWindowTitle(QApplication::translate("Square", "MainWindow", Q_NULLPTR));
        label_currentNum->setText(QApplication::translate("Square", "\345\275\223\345\211\215\345\234\250\347\272\277\344\272\272\346\225\260\357\274\232", Q_NULLPTR));
        squareMatch->setText(QApplication::translate("Square", "\345\214\271\351\205\215\350\201\212\345\244\251\345\257\271\350\261\241", Q_NULLPTR));
        label_2->setText(QString());
        squareSend->setText(QApplication::translate("Square", "\345\217\221\351\200\201", Q_NULLPTR));
        squareMatchCancel->setText(QApplication::translate("Square", "\345\217\226\346\266\210\345\214\271\351\205\215", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Square: public Ui_Square {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SQUARE_H
