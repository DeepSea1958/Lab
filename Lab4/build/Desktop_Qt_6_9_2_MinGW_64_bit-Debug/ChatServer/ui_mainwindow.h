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
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QPlainTextEdit *logEditor;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *startStopButton;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(426, 359);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        groupBox->setStyleSheet(QString::fromUtf8("/* ======================\n"
"   \345\205\250\345\261\200\345\237\272\347\241\200\346\240\267\345\274\217\n"
"====================== */\n"
"QWidget {\n"
"    background-color: #f5f7fa;\n"
"    font-family: \"Microsoft YaHei\";\n"
"    font-size: 14px;\n"
"    color: #333333;\n"
"}\n"
"\n"
"/* ======================\n"
"   \345\210\206\347\273\204\346\241\206\357\274\210\346\234\215\345\212\241\345\231\250\346\227\245\345\277\227\357\274\211\n"
"====================== */\n"
"QGroupBox {\n"
"    background-color: #ffffff;\n"
"    border: 1px solid #dcdfe6;\n"
"    border-radius: 8px;\n"
"    margin-top: 20px;\n"
"    font-weight: bold;\n"
"}\n"
"\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    subcontrol-position: top left;\n"
"    padding: 0 6px;\n"
"    color: #2c3e50;\n"
"}\n"
"\n"
"/* ======================\n"
"   \346\227\245\345\277\227\350\276\223\345\207\272\345\214\272\n"
"====================== */\n"
"QPlainTextEdit {\n"
"    border: none;\n"
"    background-color: #ffffff;\n"
"    pa"
                        "dding: 8px;\n"
"    font-family: Consolas, \"Courier New\", monospace;\n"
"    font-size: 13px;\n"
"    color: #303133;\n"
"}\n"
"\n"
"/* ======================\n"
"   \345\220\257\345\212\250 / \345\201\234\346\255\242\346\214\211\351\222\256\n"
"====================== */\n"
"QPushButton#startStopButton {\n"
"    height: 34px;\n"
"    min-width: 120px;\n"
"    border-radius: 6px;\n"
"    background-color: #67c23a;\n"
"    color: #ffffff;\n"
"    font-weight: bold;\n"
"    border: none;\n"
"}\n"
"\n"
"QPushButton#startStopButton:hover {\n"
"    background-color: #85ce61;\n"
"}\n"
"\n"
"QPushButton#startStopButton:pressed {\n"
"    background-color: #5daf34;\n"
"}\n"
"\n"
"/* \345\201\234\346\255\242\347\212\266\346\200\201\357\274\210\344\275\240\345\234\250\344\273\243\347\240\201\351\207\214 setProperty \346\210\226 setText \346\227\266\345\210\207\346\215\242\357\274\211 */\n"
"QPushButton#startStopButton[stopped=\"true\"] {\n"
"    background-color: #f56c6c;\n"
"}\n"
"\n"
"QPushButton#startStopButton[stopp"
                        "ed=\"true\"]:hover {\n"
"    background-color: #f78989;\n"
"}\n"
"\n"
"/* ======================\n"
"   \346\273\232\345\212\250\346\235\241\357\274\210\346\227\245\345\277\227\347\224\250\357\274\211\n"
"====================== */\n"
"QScrollBar:vertical {\n"
"    width: 8px;\n"
"    background: transparent;\n"
"}\n"
"\n"
"QScrollBar::handle:vertical {\n"
"    background: #c0c4cc;\n"
"    border-radius: 4px;\n"
"}\n"
"\n"
"QScrollBar::handle:vertical:hover {\n"
"    background: #909399;\n"
"}\n"
"\n"
"QScrollBar::add-line,\n"
"QScrollBar::sub-line {\n"
"    height: 0px;\n"
"}\n"
""));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName("verticalLayout");
        logEditor = new QPlainTextEdit(groupBox);
        logEditor->setObjectName("logEditor");

        verticalLayout->addWidget(logEditor);


        gridLayout->addWidget(groupBox, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        startStopButton = new QPushButton(centralwidget);
        startStopButton->setObjectName("startStopButton");

        horizontalLayout->addWidget(startStopButton);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\346\234\215\345\212\241\345\231\250", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "\346\234\215\345\212\241\345\231\250\346\227\245\345\277\227", nullptr));
        startStopButton->setText(QCoreApplication::translate("MainWindow", "\345\220\257\345\212\250\346\234\215\345\212\241\345\231\250", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
