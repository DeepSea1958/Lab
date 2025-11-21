#include "replacedialog.h"
#include "ui_replacedialog.h"
#include <QMessageBox>

ReplaceDialog::ReplaceDialog(QWidget *parent, QPlainTextEdit *textEdit)
    : QDialog(parent)
    , ui(new Ui::ReplaceDialog)
{
    ui->setupUi(this);
    pTextEdit = textEdit;
    ui->rbDown->setChecked(true);
}

ReplaceDialog::~ReplaceDialog()
{
    delete ui;
}

void ReplaceDialog::on_btReplaceAll_clicked()
{
    const QString searchStr = ui->searchText->text();
    const QString replaceStr = ui->targetText->text();

    if (pTextEdit && !searchStr.isEmpty() && !replaceStr.isEmpty()) {
        QString fullText = pTextEdit->toPlainText();
        const Qt::CaseSensitivity caseSense = ui->cbCaseSensitive->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive;

        fullText.replace(searchStr, replaceStr, caseSense);
        pTextEdit->setPlainText(fullText);
    }
}

void ReplaceDialog::on_btFindNext_clicked()
{
    const QString searchStr = ui->searchText->text();
    if (searchStr.isEmpty() || !pTextEdit) return;

    const QString fullText = pTextEdit->toPlainText();
    QTextCursor currCursor = pTextEdit->textCursor();
    int matchPos = -1;
    const Qt::CaseSensitivity caseSense = ui->cbCaseSensitive->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive;

    // 向下查找
    if (ui->rbDown->isChecked()) {
        matchPos = fullText.indexOf(searchStr, currCursor.position(), caseSense);
        if (matchPos >= 0) {
            currCursor.setPosition(matchPos);
            currCursor.setPosition(matchPos + searchStr.length(), QTextCursor::KeepAnchor);
            pTextEdit->setTextCursor(currCursor);
        }
    }
    // 向上查找
    else if (ui->rbUp->isChecked()) {
        matchPos = fullText.lastIndexOf(searchStr, currCursor.position() - fullText.length() - 1, caseSense);
        if (matchPos >= 0) {
            currCursor.setPosition(matchPos + searchStr.length());
            currCursor.setPosition(matchPos, QTextCursor::KeepAnchor);
            pTextEdit->setTextCursor(currCursor);
        }
    }

    // 未找到匹配内容
    if (matchPos < 0) {
        QMessageBox infoMsg(this);
        infoMsg.setWindowTitle("提示");
        infoMsg.setText(QString("找不到 \"%1\"").arg(searchStr));
        infoMsg.setIcon(QMessageBox::Information);
        infoMsg.setStandardButtons(QMessageBox::Ok);
        infoMsg.exec();
    }
}


void ReplaceDialog::on_btCancel_clicked()
{
    accept();
}

void ReplaceDialog::on_btReplace_clicked()
{
    const QString searchStr = ui->searchText->text();
    const QString replaceStr = ui->targetText->text();

    if (pTextEdit && !searchStr.isEmpty() && !replaceStr.isEmpty()) {
        const QString selectedTxt = pTextEdit->textCursor().selectedText();
        if (selectedTxt == searchStr) {
            pTextEdit->insertPlainText(replaceStr);
        }
        on_btFindNext_clicked();
    }
}
