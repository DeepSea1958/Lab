/********************************************************************************
** Form generated from reading UI file 'finddialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FINDDIALOG_H
#define UI_FINDDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_FindDialog
{
public:
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *findText;
    QHBoxLayout *horizontalLayout_3;
    QCheckBox *cbCaseSensitive;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QRadioButton *rbUp;
    QRadioButton *rbDown;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_2;
    QPushButton *btFindNext;
    QPushButton *btCancel;

    void setupUi(QDialog *FindDialog)
    {
        if (FindDialog->objectName().isEmpty())
            FindDialog->setObjectName("FindDialog");
        FindDialog->resize(431, 284);
        horizontalLayout_4 = new QHBoxLayout(FindDialog);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label = new QLabel(FindDialog);
        label->setObjectName("label");

        horizontalLayout_2->addWidget(label);

        findText = new QLineEdit(FindDialog);
        findText->setObjectName("findText");

        horizontalLayout_2->addWidget(findText);


        verticalLayout_3->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        cbCaseSensitive = new QCheckBox(FindDialog);
        cbCaseSensitive->setObjectName("cbCaseSensitive");

        horizontalLayout_3->addWidget(cbCaseSensitive);

        groupBox = new QGroupBox(FindDialog);
        groupBox->setObjectName("groupBox");
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setObjectName("horizontalLayout");
        rbUp = new QRadioButton(groupBox);
        rbUp->setObjectName("rbUp");

        horizontalLayout->addWidget(rbUp);

        rbDown = new QRadioButton(groupBox);
        rbDown->setObjectName("rbDown");

        horizontalLayout->addWidget(rbDown);


        horizontalLayout_3->addWidget(groupBox);


        verticalLayout_3->addLayout(horizontalLayout_3);


        horizontalLayout_4->addLayout(verticalLayout_3);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        btFindNext = new QPushButton(FindDialog);
        btFindNext->setObjectName("btFindNext");

        verticalLayout_2->addWidget(btFindNext);

        btCancel = new QPushButton(FindDialog);
        btCancel->setObjectName("btCancel");

        verticalLayout_2->addWidget(btCancel);


        horizontalLayout_4->addLayout(verticalLayout_2);


        retranslateUi(FindDialog);

        QMetaObject::connectSlotsByName(FindDialog);
    } // setupUi

    void retranslateUi(QDialog *FindDialog)
    {
        FindDialog->setWindowTitle(QCoreApplication::translate("FindDialog", "\346\237\245\346\211\276", nullptr));
        label->setText(QCoreApplication::translate("FindDialog", "\346\237\245\346\211\276\347\233\256\346\240\207", nullptr));
        cbCaseSensitive->setText(QCoreApplication::translate("FindDialog", "\345\214\272\345\210\206\345\244\247\345\260\217\345\206\231", nullptr));
        groupBox->setTitle(QCoreApplication::translate("FindDialog", "\346\226\271\345\220\221", nullptr));
        rbUp->setText(QCoreApplication::translate("FindDialog", "\345\220\221\344\270\212(&U)", nullptr));
        rbDown->setText(QCoreApplication::translate("FindDialog", "\345\220\221\344\270\213(&D)", nullptr));
        btFindNext->setText(QCoreApplication::translate("FindDialog", "\346\237\245\346\211\276\344\270\213\344\270\200\344\270\252", nullptr));
        btCancel->setText(QCoreApplication::translate("FindDialog", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FindDialog: public Ui_FindDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FINDDIALOG_H
