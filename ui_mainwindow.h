/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Thu Aug 29 12:14:04 2013
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMdiArea>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionStart;
    QAction *actionStop;
    QAction *actionExit;
    QAction *actionAbout;
    QAction *actionModul_Akuisisi;
    QAction *actionParameter;
    QAction *actionClear_Buffer;
    QAction *actionSetting_Motor;
    QAction *actionMode_Simulasi;
    QAction *actionSatuan;
    QAction *actionCH1;
    QAction *actionCH2;
    QAction *actionCH3;
    QAction *actionCH4;
    QAction *actionDatabase;
    QAction *actionCOMPARE;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QMdiArea *mdiArea;
    QStatusBar *statusBar;
    QToolBar *mainToolBar;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuSetting;
    QMenu *menuHelp;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1000, 600);
        QIcon icon;
        icon.addFile(QString::fromUtf8("leaf.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        actionStart = new QAction(MainWindow);
        actionStart->setObjectName(QString::fromUtf8("actionStart"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("icon/play-icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionStart->setIcon(icon1);
        actionStop = new QAction(MainWindow);
        actionStop->setObjectName(QString::fromUtf8("actionStop"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8("icon/stop-2-icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionStop->setIcon(icon2);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8("icon/gnome_application_exit.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionExit->setIcon(icon3);
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8("icon/info (1).ico"), QSize(), QIcon::Normal, QIcon::On);
        actionAbout->setIcon(icon4);
        actionModul_Akuisisi = new QAction(MainWindow);
        actionModul_Akuisisi->setObjectName(QString::fromUtf8("actionModul_Akuisisi"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8("icon/documents.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionModul_Akuisisi->setIcon(icon5);
        actionParameter = new QAction(MainWindow);
        actionParameter->setObjectName(QString::fromUtf8("actionParameter"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8("icon/gnome_system_monitor.ico"), QSize(), QIcon::Normal, QIcon::Off);
        actionParameter->setIcon(icon6);
        actionClear_Buffer = new QAction(MainWindow);
        actionClear_Buffer->setObjectName(QString::fromUtf8("actionClear_Buffer"));
        actionSetting_Motor = new QAction(MainWindow);
        actionSetting_Motor->setObjectName(QString::fromUtf8("actionSetting_Motor"));
        actionMode_Simulasi = new QAction(MainWindow);
        actionMode_Simulasi->setObjectName(QString::fromUtf8("actionMode_Simulasi"));
        actionSatuan = new QAction(MainWindow);
        actionSatuan->setObjectName(QString::fromUtf8("actionSatuan"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8("icon/flowRoot6871-4.png"), QSize(), QIcon::Normal, QIcon::On);
        actionSatuan->setIcon(icon7);
        actionCH1 = new QAction(MainWindow);
        actionCH1->setObjectName(QString::fromUtf8("actionCH1"));
        actionCH2 = new QAction(MainWindow);
        actionCH2->setObjectName(QString::fromUtf8("actionCH2"));
        actionCH3 = new QAction(MainWindow);
        actionCH3->setObjectName(QString::fromUtf8("actionCH3"));
        actionCH4 = new QAction(MainWindow);
        actionCH4->setObjectName(QString::fromUtf8("actionCH4"));
        actionDatabase = new QAction(MainWindow);
        actionDatabase->setObjectName(QString::fromUtf8("actionDatabase"));
        actionCOMPARE = new QAction(MainWindow);
        actionCOMPARE->setObjectName(QString::fromUtf8("actionCOMPARE"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(2);
        gridLayout->setContentsMargins(2, 2, 2, 2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        mdiArea = new QMdiArea(centralWidget);
        mdiArea->setObjectName(QString::fromUtf8("mdiArea"));

        gridLayout->addWidget(mdiArea, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        mainToolBar->setMovable(false);
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1000, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuSetting = new QMenu(menuBar);
        menuSetting->setObjectName(QString::fromUtf8("menuSetting"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        MainWindow->setMenuBar(menuBar);

        mainToolBar->addAction(actionStart);
        mainToolBar->addAction(actionStop);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionCH1);
        mainToolBar->addAction(actionCH2);
        mainToolBar->addAction(actionCH3);
        mainToolBar->addAction(actionCH4);
        mainToolBar->addAction(actionCOMPARE);
        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuSetting->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuSetting->addAction(actionModul_Akuisisi);
        menuSetting->addAction(actionMode_Simulasi);
        menuSetting->addSeparator();
        menuSetting->addAction(actionSetting_Motor);
        menuHelp->addAction(actionAbout);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        actionStart->setText(QApplication::translate("MainWindow", "Start", 0, QApplication::UnicodeUTF8));
        actionStop->setText(QApplication::translate("MainWindow", "Stop", 0, QApplication::UnicodeUTF8));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", 0, QApplication::UnicodeUTF8));
        actionAbout->setText(QApplication::translate("MainWindow", "About", 0, QApplication::UnicodeUTF8));
        actionModul_Akuisisi->setText(QApplication::translate("MainWindow", "Modul Vibrasi", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        actionModul_Akuisisi->setToolTip(QApplication::translate("MainWindow", "Modul Data Akuisisi", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        actionParameter->setText(QApplication::translate("MainWindow", "Vibration Parameter", 0, QApplication::UnicodeUTF8));
        actionClear_Buffer->setText(QApplication::translate("MainWindow", "Clear Buffer", 0, QApplication::UnicodeUTF8));
        actionSetting_Motor->setText(QApplication::translate("MainWindow", "Motor Setting", 0, QApplication::UnicodeUTF8));
        actionMode_Simulasi->setText(QApplication::translate("MainWindow", "Mode Simulasi", 0, QApplication::UnicodeUTF8));
        actionSatuan->setText(QApplication::translate("MainWindow", "Units", 0, QApplication::UnicodeUTF8));
        actionCH1->setText(QApplication::translate("MainWindow", "CH1", 0, QApplication::UnicodeUTF8));
        actionCH2->setText(QApplication::translate("MainWindow", "CH2", 0, QApplication::UnicodeUTF8));
        actionCH3->setText(QApplication::translate("MainWindow", "CH3", 0, QApplication::UnicodeUTF8));
        actionCH4->setText(QApplication::translate("MainWindow", "CH4", 0, QApplication::UnicodeUTF8));
        actionDatabase->setText(QApplication::translate("MainWindow", "Database", 0, QApplication::UnicodeUTF8));
        actionCOMPARE->setText(QApplication::translate("MainWindow", "COMPARE", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0, QApplication::UnicodeUTF8));
        menuSetting->setTitle(QApplication::translate("MainWindow", "Setting", 0, QApplication::UnicodeUTF8));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
