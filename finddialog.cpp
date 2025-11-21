#include "finddialog.h"
#include "ui_finddialog.h"
#include <QMessageBox>

FindDialog::FindDialog(QWidget *parent, QPlainTextEdit *textEdit)
    : QDialog(parent)
    , ui(new Ui::FindDialog)
{
    ui->setupUi(this);
    pTextEdit = textEdit;
    ui->rbDown->setChecked(true);
}

FindDialog::~FindDialog()
{
    delete ui;
}

void FindDialog::on_btFindNext_clicked()
{
    const QString findStr = ui->findText->text();
    if (findStr.isEmpty() || !pTextEdit) return;

    const QString fullText = pTextEdit->toPlainText();
    QTextCursor currCursor = pTextEdit->textCursor();
    int matchPos = -1;
    const Qt::CaseSensitivity caseSense = ui->cbCaseSensitive->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive;

    // 向下查找
    if (ui->rbDown->isChecked()) {
        matchPos = fullText.indexOf(findStr, currCursor.position(), caseSense);
        if (matchPos >= 0) {
            currCursor.setPosition(matchPos);
            currCursor.setPosition(matchPos + findStr.length(), QTextCursor::KeepAnchor);
            pTextEdit->setTextCursor(currCursor);
        }
    }
    // 向上查找
    else if (ui->rbUp->isChecked()) {
        matchPos = fullText.lastIndexOf(findStr, currCursor.position() - fullText.length() - 1, caseSense);
        if (matchPos >= 0) {
            currCursor.setPosition(matchPos + findStr.length());
            currCursor.setPosition(matchPos, QTextCursor::KeepAnchor);
            pTextEdit->setTextCursor(currCursor);
        }
    }

    // 未找到匹配内容
    if (matchPos < 0) {
        QMessageBox infoMsg(this);
        infoMsg.setWindowTitle("提示");
        infoMsg.setText(QString("找不到 \"%1\"").arg(findStr));
        infoMsg.setIcon(QMessageBox::Information);
        infoMsg.setStandardButtons(QMessageBox::Ok);
        infoMsg.exec();
    }
}

void FindDialog::on_btCancel_clicked()
{
    accept();
}
