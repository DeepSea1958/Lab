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
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QLabel *titleLabel;
    QStackedWidget *stackedWidget;
    QWidget *chatPage;
    QGridLayout *gridLayout_3;
    QHBoxLayout *horizontalLayout;
    QTextEdit *roomTextEdit;
    QListWidget *userListWidget;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *sayLineEdit;
    QPushButton *sayButton;
    QPushButton *logoutButton;
    QWidget *loginPage;
    QFrame *loginFrame;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *serverEdit;
    QLineEdit *usernameEdit;
    QSpacerItem *verticalSpacer;
    QPushButton *loginButton;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(442, 324);
        MainWindow->setStyleSheet(QString::fromUtf8("/* ======================\n"
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
"   \346\240\207\351\242\230\n"
"====================== */\n"
"QLabel#titleLabel {\n"
"    font-size: 18px;\n"
"    font-weight: bold;\n"
"    color: #2c3e50;\n"
"}\n"
"\n"
"/* ======================\n"
"   \347\231\273\345\275\225\345\215\241\347\211\207\345\214\272\345\237\237\n"
"====================== */\n"
"QFrame#loginFrame {\n"
"    background-color: #ffffff;\n"
"    border-radius: 10px;\n"
"    border: 1px solid #dcdfe6;\n"
"}\n"
"\n"
"/* \347\231\273\345\275\225\346\240\207\347\255\276 */\n"
"QLabel {\n"
"    color: #606266;\n"
"}\n"
"\n"
"/* \350\276\223\345\205\245\346\241\206\347\273\237\344\270\200\346\240\267\345\274\217 */\n"
"QLineEdit {\n"
"    height: 30px;\n"
"    padding: 4px "
                        "8px;\n"
"    border-radius: 5px;\n"
"    border: 1px solid #dcdfe6;\n"
"    background-color: #ffffff;\n"
"}\n"
"\n"
"QLineEdit:focus {\n"
"    border: 1px solid #409eff;\n"
"}\n"
"\n"
"/* ======================\n"
"   \346\214\211\351\222\256\346\240\267\345\274\217\n"
"====================== */\n"
"QPushButton {\n"
"    height: 32px;\n"
"    padding: 0 15px;\n"
"    border-radius: 6px;\n"
"    background-color: #409eff;\n"
"    color: #ffffff;\n"
"    border: none;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #66b1ff;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #337ecc;\n"
"}\n"
"\n"
"/* \351\200\200\345\207\272\346\214\211\351\222\256\345\274\261\345\214\226\345\244\204\347\220\206 */\n"
"QPushButton#pushButton_2 {\n"
"    background-color: #f56c6c;\n"
"}\n"
"\n"
"QPushButton#pushButton_2:hover {\n"
"    background-color: #f78989;\n"
"}\n"
"\n"
"/* ======================\n"
"   \350\201\212\345\244\251\347\225\214\351\235\242\n"
"====================== */\n"
"\n"
"/* \350\201"
                        "\212\345\244\251\346\230\276\347\244\272\345\214\272 */\n"
"QTextEdit {\n"
"    border: 1px solid #dcdfe6;\n"
"    border-radius: 6px;\n"
"    padding: 6px;\n"
"    background-color: #ffffff;\n"
"}\n"
"\n"
"/* \347\224\250\346\210\267\345\210\227\350\241\250 */\n"
"QListWidget {\n"
"    border: 1px solid #dcdfe6;\n"
"    border-radius: 6px;\n"
"    background-color: #ffffff;\n"
"}\n"
"\n"
"QListWidget::item {\n"
"    height: 28px;\n"
"    padding-left: 6px;\n"
"}\n"
"\n"
"QListWidget::item:selected {\n"
"    background-color: #ecf5ff;\n"
"    color: #409eff;\n"
"}\n"
"\n"
"/* ======================\n"
"   \350\276\223\345\205\245\345\214\272\n"
"====================== */\n"
"QLineEdit#lineEdit {\n"
"    border-radius: 6px;\n"
"}\n"
"\n"
"/* ======================\n"
"   \346\273\232\345\212\250\346\235\241\347\276\216\345\214\226\357\274\210\345\217\257\351\200\211\344\275\206\346\216\250\350\215\220\357\274\211\n"
"====================== */\n"
"QScrollBar:vertical {\n"
"    width: 8px;\n"
"    background: tra"
                        "nsparent;\n"
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
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        titleLabel = new QLabel(centralwidget);
        titleLabel->setObjectName("titleLabel");

        verticalLayout->addWidget(titleLabel);

        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        chatPage = new QWidget();
        chatPage->setObjectName("chatPage");
        gridLayout_3 = new QGridLayout(chatPage);
        gridLayout_3->setObjectName("gridLayout_3");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        roomTextEdit = new QTextEdit(chatPage);
        roomTextEdit->setObjectName("roomTextEdit");

        horizontalLayout->addWidget(roomTextEdit);

        userListWidget = new QListWidget(chatPage);
        userListWidget->setObjectName("userListWidget");
        userListWidget->setMaximumSize(QSize(120, 16777215));

        horizontalLayout->addWidget(userListWidget);


        gridLayout_3->addLayout(horizontalLayout, 0, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        sayLineEdit = new QLineEdit(chatPage);
        sayLineEdit->setObjectName("sayLineEdit");

        horizontalLayout_2->addWidget(sayLineEdit);

        sayButton = new QPushButton(chatPage);
        sayButton->setObjectName("sayButton");

        horizontalLayout_2->addWidget(sayButton);

        logoutButton = new QPushButton(chatPage);
        logoutButton->setObjectName("logoutButton");

        horizontalLayout_2->addWidget(logoutButton);


        gridLayout_3->addLayout(horizontalLayout_2, 1, 0, 1, 1);

        stackedWidget->addWidget(chatPage);
        loginPage = new QWidget();
        loginPage->setObjectName("loginPage");
        loginFrame = new QFrame(loginPage);
        loginFrame->setObjectName("loginFrame");
        loginFrame->setGeometry(QRect(90, 70, 231, 117));
        loginFrame->setFrameShape(QFrame::Shape::StyledPanel);
        loginFrame->setFrameShadow(QFrame::Shadow::Raised);
        gridLayout_2 = new QGridLayout(loginFrame);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        label_2 = new QLabel(loginFrame);
        label_2->setObjectName("label_2");

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        label_3 = new QLabel(loginFrame);
        label_3->setObjectName("label_3");

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        serverEdit = new QLineEdit(loginFrame);
        serverEdit->setObjectName("serverEdit");

        gridLayout->addWidget(serverEdit, 0, 1, 1, 1);

        usernameEdit = new QLineEdit(loginFrame);
        usernameEdit->setObjectName("usernameEdit");

        gridLayout->addWidget(usernameEdit, 1, 1, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 10, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        gridLayout_2->addItem(verticalSpacer, 1, 0, 1, 1);

        loginButton = new QPushButton(loginFrame);
        loginButton->setObjectName("loginButton");

        gridLayout_2->addWidget(loginButton, 2, 0, 1, 1);

        stackedWidget->addWidget(loginPage);

        verticalLayout->addWidget(stackedWidget);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\350\201\212\345\244\251\345\256\244\345\256\242\346\210\267\347\253\257", nullptr));
        titleLabel->setText(QCoreApplication::translate("MainWindow", "\346\261\244\347\246\217\351\253\230\347\232\204\350\201\212\345\244\251\345\256\244", nullptr));
        sayButton->setText(QCoreApplication::translate("MainWindow", "\345\217\221\351\200\201", nullptr));
        logoutButton->setText(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\346\234\215\345\212\241\345\231\250\345\234\260\345\235\200\357\274\232", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\346\230\265\347\247\260\357\274\232", nullptr));
        serverEdit->setText(QCoreApplication::translate("MainWindow", "127.0.0.1", nullptr));
        usernameEdit->setText(QCoreApplication::translate("MainWindow", "tfg", nullptr));
        loginButton->setText(QCoreApplication::translate("MainWindow", "\347\231\273\345\275\225\350\201\212\345\244\251\345\256\244", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
