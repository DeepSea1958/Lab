/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <codeedit.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actNew;
    QAction *actOpen;
    QAction *actSave;
    QAction *actSaveAs;
    QAction *actExit;
    QAction *actUndo;
    QAction *actCut;
    QAction *actCopy;
    QAction *actPaste;
    QAction *actFind;
    QAction *actReplace;
    QAction *actFont;
    QAction *actWrap;
    QAction *actToolBar;
    QAction *actStatusBar;
    QAction *actRedo;
    QAction *actSelectAll;
    QAction *actLine;
    QAction *actAbout;
    QAction *actionFontColor;
    QAction *actFontBackgroundcolor;
    QAction *actEditorBackgroundColor;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    CodeEditor *textEdit;
    QMenuBar *menubar;
    QMenu *menu;
    QMenu *menu_E;
    QMenu *menu_O;
    QMenu *menu_V;
    QMenu *menu_H;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(536, 258);
        actNew = new QAction(MainWindow);
        actNew->setObjectName("actNew");
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/image/new.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actNew->setIcon(icon);
        actNew->setMenuRole(QAction::MenuRole::NoRole);
        actOpen = new QAction(MainWindow);
        actOpen->setObjectName("actOpen");
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/image/open.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actOpen->setIcon(icon1);
        actOpen->setMenuRole(QAction::MenuRole::NoRole);
        actSave = new QAction(MainWindow);
        actSave->setObjectName("actSave");
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/image/save.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actSave->setIcon(icon2);
        actSave->setMenuRole(QAction::MenuRole::NoRole);
        actSaveAs = new QAction(MainWindow);
        actSaveAs->setObjectName("actSaveAs");
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/image/saveas.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actSaveAs->setIcon(icon3);
        actSaveAs->setMenuRole(QAction::MenuRole::NoRole);
        actExit = new QAction(MainWindow);
        actExit->setObjectName("actExit");
        actExit->setMenuRole(QAction::MenuRole::NoRole);
        actUndo = new QAction(MainWindow);
        actUndo->setObjectName("actUndo");
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/image/undo.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actUndo->setIcon(icon4);
        actUndo->setMenuRole(QAction::MenuRole::NoRole);
        actCut = new QAction(MainWindow);
        actCut->setObjectName("actCut");
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/image/cut.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actCut->setIcon(icon5);
        actCut->setMenuRole(QAction::MenuRole::NoRole);
        actCopy = new QAction(MainWindow);
        actCopy->setObjectName("actCopy");
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/image/copy.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actCopy->setIcon(icon6);
        actCopy->setMenuRole(QAction::MenuRole::NoRole);
        actPaste = new QAction(MainWindow);
        actPaste->setObjectName("actPaste");
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/image/paste.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actPaste->setIcon(icon7);
        actPaste->setMenuRole(QAction::MenuRole::NoRole);
        actFind = new QAction(MainWindow);
        actFind->setObjectName("actFind");
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/image/find.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actFind->setIcon(icon8);
        actFind->setMenuRole(QAction::MenuRole::NoRole);
        actReplace = new QAction(MainWindow);
        actReplace->setObjectName("actReplace");
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/image/replace.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actReplace->setIcon(icon9);
        actReplace->setMenuRole(QAction::MenuRole::NoRole);
        actFont = new QAction(MainWindow);
        actFont->setObjectName("actFont");
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/image/font.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actFont->setIcon(icon10);
        actFont->setMenuRole(QAction::MenuRole::NoRole);
        actWrap = new QAction(MainWindow);
        actWrap->setObjectName("actWrap");
        actWrap->setCheckable(true);
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/image/wrap.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actWrap->setIcon(icon11);
        actWrap->setMenuRole(QAction::MenuRole::NoRole);
        actToolBar = new QAction(MainWindow);
        actToolBar->setObjectName("actToolBar");
        actToolBar->setCheckable(true);
        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/image/tool.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actToolBar->setIcon(icon12);
        actToolBar->setMenuRole(QAction::MenuRole::NoRole);
        actStatusBar = new QAction(MainWindow);
        actStatusBar->setObjectName("actStatusBar");
        actStatusBar->setCheckable(true);
        QIcon icon13;
        icon13.addFile(QString::fromUtf8(":/image/status.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actStatusBar->setIcon(icon13);
        actStatusBar->setMenuRole(QAction::MenuRole::NoRole);
        actRedo = new QAction(MainWindow);
        actRedo->setObjectName("actRedo");
        QIcon icon14;
        icon14.addFile(QString::fromUtf8(":/image/redo.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actRedo->setIcon(icon14);
        actRedo->setMenuRole(QAction::MenuRole::NoRole);
        actSelectAll = new QAction(MainWindow);
        actSelectAll->setObjectName("actSelectAll");
        actSelectAll->setMenuRole(QAction::MenuRole::NoRole);
        actLine = new QAction(MainWindow);
        actLine->setObjectName("actLine");
        QIcon icon15;
        icon15.addFile(QString::fromUtf8(":/image/line.svg"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        actLine->setIcon(icon15);
        actLine->setMenuRole(QAction::MenuRole::NoRole);
        actAbout = new QAction(MainWindow);
        actAbout->setObjectName("actAbout");
        actAbout->setMenuRole(QAction::MenuRole::NoRole);
        actionFontColor = new QAction(MainWindow);
        actionFontColor->setObjectName("actionFontColor");
        actionFontColor->setMenuRole(QAction::MenuRole::NoRole);
        actFontBackgroundcolor = new QAction(MainWindow);
        actFontBackgroundcolor->setObjectName("actFontBackgroundcolor");
        actFontBackgroundcolor->setMenuRole(QAction::MenuRole::NoRole);
        actEditorBackgroundColor = new QAction(MainWindow);
        actEditorBackgroundColor->setObjectName("actEditorBackgroundColor");
        actEditorBackgroundColor->setMenuRole(QAction::MenuRole::NoRole);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(1, 1, 1, 1);
        textEdit = new CodeEditor(centralwidget);
        textEdit->setObjectName("textEdit");

        verticalLayout->addWidget(textEdit);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 536, 22));
        menu = new QMenu(menubar);
        menu->setObjectName("menu");
        menu_E = new QMenu(menubar);
        menu_E->setObjectName("menu_E");
        menu_O = new QMenu(menubar);
        menu_O->setObjectName("menu_O");
        menu_V = new QMenu(menubar);
        menu_V->setObjectName("menu_V");
        menu_H = new QMenu(menubar);
        menu_H->setObjectName("menu_H");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName("toolBar");
        MainWindow->addToolBar(Qt::ToolBarArea::TopToolBarArea, toolBar);

        menubar->addAction(menu->menuAction());
        menubar->addAction(menu_E->menuAction());
        menubar->addAction(menu_O->menuAction());
        menubar->addAction(menu_V->menuAction());
        menubar->addAction(menu_H->menuAction());
        menu->addAction(actNew);
        menu->addAction(actOpen);
        menu->addAction(actSave);
        menu->addAction(actSaveAs);
        menu->addSeparator();
        menu->addAction(actExit);
        menu_E->addAction(actUndo);
        menu_E->addAction(actRedo);
        menu_E->addAction(actCut);
        menu_E->addAction(actCopy);
        menu_E->addAction(actPaste);
        menu_E->addAction(actFind);
        menu_E->addAction(actReplace);
        menu_E->addSeparator();
        menu_E->addAction(actSelectAll);
        menu_O->addAction(actFont);
        menu_O->addAction(actLine);
        menu_O->addAction(actWrap);
        menu_O->addAction(actionFontColor);
        menu_O->addSeparator();
        menu_O->addAction(actFontBackgroundcolor);
        menu_O->addAction(actEditorBackgroundColor);
        menu_V->addAction(actToolBar);
        menu_V->addAction(actStatusBar);
        menu_H->addAction(actAbout);
        toolBar->addAction(actNew);
        toolBar->addAction(actOpen);
        toolBar->addAction(actSave);
        toolBar->addAction(actSaveAs);
        toolBar->addSeparator();
        toolBar->addAction(actUndo);
        toolBar->addAction(actRedo);
        toolBar->addAction(actCut);
        toolBar->addAction(actCopy);
        toolBar->addAction(actPaste);
        toolBar->addSeparator();
        toolBar->addAction(actFind);
        toolBar->addAction(actReplace);
        toolBar->addSeparator();
        toolBar->addAction(actFont);
        toolBar->addAction(actLine);
        toolBar->addAction(actWrap);
        toolBar->addSeparator();
        toolBar->addAction(actToolBar);
        toolBar->addAction(actStatusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        actNew->setText(QCoreApplication::translate("MainWindow", "\346\226\260\345\273\272(&N)", nullptr));
#if QT_CONFIG(shortcut)
        actNew->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+N", nullptr));
#endif // QT_CONFIG(shortcut)
        actOpen->setText(QCoreApplication::translate("MainWindow", "\346\211\223\345\274\200(&O)", nullptr));
#if QT_CONFIG(shortcut)
        actOpen->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+O", nullptr));
#endif // QT_CONFIG(shortcut)
        actSave->setText(QCoreApplication::translate("MainWindow", "\344\277\235\345\255\230(&S)", nullptr));
#if QT_CONFIG(shortcut)
        actSave->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+S", nullptr));
#endif // QT_CONFIG(shortcut)
        actSaveAs->setText(QCoreApplication::translate("MainWindow", "\345\217\246\345\255\230\344\270\272(&A)", nullptr));
        actExit->setText(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272(&X)", nullptr));
        actUndo->setText(QCoreApplication::translate("MainWindow", "\346\222\244\351\224\200(&U)", nullptr));
#if QT_CONFIG(shortcut)
        actUndo->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Z", nullptr));
#endif // QT_CONFIG(shortcut)
        actCut->setText(QCoreApplication::translate("MainWindow", "\345\211\252\345\210\207(&T)", nullptr));
#if QT_CONFIG(shortcut)
        actCut->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+X", nullptr));
#endif // QT_CONFIG(shortcut)
        actCopy->setText(QCoreApplication::translate("MainWindow", "\345\244\215\345\210\266(&C)", nullptr));
#if QT_CONFIG(shortcut)
        actCopy->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+C", nullptr));
#endif // QT_CONFIG(shortcut)
        actPaste->setText(QCoreApplication::translate("MainWindow", "\347\262\230\350\264\264(&P)", nullptr));
#if QT_CONFIG(shortcut)
        actPaste->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+V", nullptr));
#endif // QT_CONFIG(shortcut)
        actFind->setText(QCoreApplication::translate("MainWindow", "\346\237\245\346\211\276(&F)", nullptr));
#if QT_CONFIG(shortcut)
        actFind->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+F", nullptr));
#endif // QT_CONFIG(shortcut)
        actReplace->setText(QCoreApplication::translate("MainWindow", "\346\233\277\346\215\242(&R)", nullptr));
        actFont->setText(QCoreApplication::translate("MainWindow", "\345\255\227\344\275\223(&F)", nullptr));
        actWrap->setText(QCoreApplication::translate("MainWindow", "\350\207\252\345\212\250\346\215\242\350\241\214(&W)", nullptr));
        actToolBar->setText(QCoreApplication::translate("MainWindow", "\345\267\245\345\205\267\346\240\217(&T)", nullptr));
        actStatusBar->setText(QCoreApplication::translate("MainWindow", "\347\212\266\346\200\201\346\240\217(&S)", nullptr));
        actRedo->setText(QCoreApplication::translate("MainWindow", "\346\201\242\345\244\215(&R)", nullptr));
#if QT_CONFIG(shortcut)
        actRedo->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Shift+Z", nullptr));
#endif // QT_CONFIG(shortcut)
        actSelectAll->setText(QCoreApplication::translate("MainWindow", "\345\205\250\351\200\211(&A)", nullptr));
#if QT_CONFIG(shortcut)
        actSelectAll->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+A", nullptr));
#endif // QT_CONFIG(shortcut)
        actLine->setText(QCoreApplication::translate("MainWindow", "\346\230\276\347\244\272\350\241\214\345\217\267(&L)", nullptr));
#if QT_CONFIG(shortcut)
        actLine->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+L", nullptr));
#endif // QT_CONFIG(shortcut)
        actAbout->setText(QCoreApplication::translate("MainWindow", "\345\205\263\344\272\216(&A)", nullptr));
        actionFontColor->setText(QCoreApplication::translate("MainWindow", "\345\255\227\344\275\223\351\242\234\350\211\262", nullptr));
        actFontBackgroundcolor->setText(QCoreApplication::translate("MainWindow", "\345\255\227\344\275\223\350\203\214\346\231\257\351\242\234\350\211\262", nullptr));
        actEditorBackgroundColor->setText(QCoreApplication::translate("MainWindow", "\347\274\226\350\276\221\345\231\250\350\203\214\346\231\257\351\242\234\350\211\262", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindow", "\346\226\207\344\273\266(&F)", nullptr));
        menu_E->setTitle(QCoreApplication::translate("MainWindow", "\347\274\226\350\276\221(&E)", nullptr));
        menu_O->setTitle(QCoreApplication::translate("MainWindow", "\346\240\274\345\274\217(&O)", nullptr));
        menu_V->setTitle(QCoreApplication::translate("MainWindow", "\346\237\245\347\234\213(&V)", nullptr));
        menu_H->setTitle(QCoreApplication::translate("MainWindow", "\345\270\256\345\212\251(&H)", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("MainWindow", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
