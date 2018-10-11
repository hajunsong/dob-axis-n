/********************************************************************************
** Form generated from reading UI file 'dob_ui.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DOB_UI_H
#define UI_DOB_UI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DOB_ui
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *DOB_ui)
    {
        if (DOB_ui->objectName().isEmpty())
            DOB_ui->setObjectName(QStringLiteral("DOB_ui"));
        DOB_ui->resize(729, 527);
        centralWidget = new QWidget(DOB_ui);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(60, 130, 251, 201));
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(380, 130, 251, 201));
        DOB_ui->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(DOB_ui);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 729, 20));
        DOB_ui->setMenuBar(menuBar);
        mainToolBar = new QToolBar(DOB_ui);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        DOB_ui->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(DOB_ui);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        DOB_ui->setStatusBar(statusBar);

        retranslateUi(DOB_ui);

        QMetaObject::connectSlotsByName(DOB_ui);
    } // setupUi

    void retranslateUi(QMainWindow *DOB_ui)
    {
        DOB_ui->setWindowTitle(QApplication::translate("DOB_ui", "DOB_ui", nullptr));
        pushButton->setText(QApplication::translate("DOB_ui", "Start", nullptr));
        pushButton_2->setText(QApplication::translate("DOB_ui", "Quit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DOB_ui: public Ui_DOB_ui {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DOB_UI_H
