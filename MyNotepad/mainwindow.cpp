#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aboutdialog.h"
#include "finddialog.h"
#include "replacedialog.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QColorDialog>
#include <QFontDialog>
#include <QFileInfo>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    textChanged = false;
    on_actNew_triggered();

    // 初始化状态栏长度标签
    statusLabel.setMaximumWidth(180);
    statusLabel.setText(QString("length: %1    lines: %2").arg(0).arg(1));
    ui->statusbar->addPermanentWidget(&statusLabel);

    // 初始化状态栏光标标签
    statusCursorLabel.setMaximumWidth(180);
    statusCursorLabel.setText(QString("ln: %1    col: %2").arg(0).arg(1));
    ui->statusbar->addPermanentWidget(&statusCursorLabel);

    // 添加作者标签
    QLabel *authorLab = new QLabel(this);
    authorLab->setText(tr("HZL"));
    ui->statusbar->addPermanentWidget(authorLab);

    // 禁用初始操作按钮
    ui->actCopy->setEnabled(false);
    ui->actCut->setEnabled(false);
    ui->actUndo->setEnabled(false);
    ui->actRedo->setEnabled(false);
    ui->actPaste->setEnabled(false);

    // 初始化换行模式
    auto currWrapMode = ui->textEdit->lineWrapMode();
    if (currWrapMode == QTextEdit::NoWrap) {
        ui->textEdit->setLineWrapMode(QPlainTextEdit::WidgetWidth);
        ui->actWrap->setChecked(false);
    } else {
        ui->textEdit->setLineWrapMode(QPlainTextEdit::NoWrap);
        ui->actWrap->setChecked(true);
    }

    ui->actToolBar->setChecked(true);
    ui->actStatusBar->setChecked(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actAbout_triggered()
{
    AboutDialog aboutDlg;
    aboutDlg.exec();
}

void MainWindow::on_actFind_triggered()
{
    FindDialog findDlg(this, ui->textEdit);
    findDlg.exec();
}

void MainWindow::on_actReplace_triggered()
{
    ReplaceDialog replaceDlg(this, ui->textEdit);
    replaceDlg.exec();
}

void MainWindow::on_actNew_triggered()
{
    if (!userEditConfirmed()) return;

    filePath.clear();
    ui->textEdit->clear();
    setWindowTitle(tr("文本文件编辑器"));
    textChanged = false;
}

void MainWindow::on_actOpen_triggered()
{
    if (!userEditConfirmed()) return;

    const QString filter = tr("Text files (*.txt);; All(*.*)");
    QString fileNm = QFileDialog::getOpenFileName(this, "打开文件", ".", filter);
    QFile targetFile(fileNm);

    if (!targetFile.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "提示", "打开文件失败");
        return;
    }

    filePath = fileNm;
    QTextStream readStream(&targetFile);
    const QString fileContent = readStream.readAll();
    ui->textEdit->setPlainText(fileContent);
    targetFile.close();

    setWindowTitle(QFileInfo(fileNm).absoluteFilePath());
    textChanged = false;
}

void MainWindow::on_actSave_triggered()
{
    if (filePath.isEmpty()) {
        const QString filter = tr("Text files (*.txt)");
        QString saveNm = QFileDialog::getSaveFileName(this, "保存文件", ".", filter);
        QFile saveFile(saveNm);

        if (!saveFile.open(QFile::WriteOnly | QFile::Text)) {
            QMessageBox::warning(this, "警告", "保存文件失败");
            return;
        }
        saveFile.close();
        filePath = saveNm;
    }

    QFile saveFile(filePath);
    if (!saveFile.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "警告", "保存文件失败");
        return;
    }

    QTextStream writeStream(&saveFile);
    writeStream << ui->textEdit->toPlainText();
    saveFile.flush();
    saveFile.close();

    setWindowTitle(QFileInfo(filePath).absoluteFilePath());
    textChanged = false;
}

void MainWindow::on_actSaveAs_triggered()
{
    const QString filter = tr("Text files (*.txt)");
    QString saveNm = QFileDialog::getSaveFileName(this, "保存文件", ".", filter);
    if (saveNm.isEmpty()) return;

    QFile saveFile(saveNm);
    if (!saveFile.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "警告", "保存文件失败");
        return;
    }

    filePath = saveNm;
    QTextStream writeStream(&saveFile);
    writeStream << ui->textEdit->toPlainText();
    saveFile.flush();
    saveFile.close();

    setWindowTitle(QFileInfo(filePath).absoluteFilePath());
    textChanged = false;
}

void MainWindow::on_textEdit_textChanged()
{
    if (!textChanged) {
        setWindowTitle("*" + windowTitle());
        textChanged = true;
    }

    const int txtLen = ui->textEdit->toPlainText().length();
    const int lineCnt = ui->textEdit->document()->lineCount();
    statusLabel.setText(QString("length: %1    lines: %2").arg(txtLen).arg(lineCnt));
}

bool MainWindow::userEditConfirmed()
{
    if (!textChanged) return true;

    const QString docPath = filePath.isEmpty() ? "无标题.txt" : filePath;
    QMessageBox confirmMsg(this);
    confirmMsg.setIcon(QMessageBox::Question);
    confirmMsg.setWindowTitle("保存提示");
    confirmMsg.setText(QString("是否将更改保存到\n\"%1\" ?").arg(docPath));
    confirmMsg.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

    switch (confirmMsg.exec()) {
    case QMessageBox::Yes:
        on_actSave_triggered();
        break;
    case QMessageBox::No:
        textChanged = false;
        break;
    case QMessageBox::Cancel:
        return false;
    }
    return true;
}

void MainWindow::on_actUndo_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_actCut_triggered()
{
    ui->textEdit->cut();
    ui->actPaste->setEnabled(true);
}

void MainWindow::on_actCopy_triggered()
{
    ui->textEdit->copy();
    ui->actPaste->setEnabled(true);
}

void MainWindow::on_actPaste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_actRedo_triggered()
{
    ui->textEdit->redo();
}

void MainWindow::on_textEdit_undoAvailable(bool available)
{
    ui->actUndo->setEnabled(available);
}

void MainWindow::on_textEdit_copyAvailable(bool available)
{
    ui->actCopy->setEnabled(available);
    ui->actCut->setEnabled(available);
}

void MainWindow::on_textEdit_redoAvailable(bool available)
{
    ui->actRedo->setEnabled(available);
}

void MainWindow::on_actionFontColor_triggered()
{
    QColor selectedCol = QColorDialog::getColor(Qt::black, this, "选择颜色");
    if (selectedCol.isValid()) {
        ui->textEdit->setStyleSheet(QString("QPlainTextEdit {color: %1}").arg(selectedCol.name()));
    }
}

void MainWindow::on_actEditorBackgroundColor_triggered()
{
    QColor selectedCol = QColorDialog::getColor(Qt::black, this, "选择颜色");
    if (selectedCol.isValid()) {
        ui->textEdit->setStyleSheet(QString("QPlainTextEdit {background-color: %1}").arg(selectedCol.name()));
    }
}

void MainWindow::on_actWrap_triggered()
{
    auto currWrapMode = ui->textEdit->lineWrapMode();
    if (currWrapMode == QTextEdit::NoWrap) {
        ui->textEdit->setLineWrapMode(QPlainTextEdit::WidgetWidth);
        ui->actWrap->setChecked(true);
    } else {
        ui->textEdit->setLineWrapMode(QPlainTextEdit::NoWrap);
        ui->actWrap->setChecked(false);
    }
}

void MainWindow::on_actFont_triggered()
{
    bool isOk = false;
    QFont selectedFont = QFontDialog::getFont(&isOk, this);
    if (isOk) ui->textEdit->setFont(selectedFont);
}

void MainWindow::on_actStatusBar_triggered()
{
    const bool isVis = ui->statusbar->isVisible();
    ui->statusbar->setVisible(!isVis);
    ui->actStatusBar->setChecked(!isVis);
}

void MainWindow::on_actToolBar_triggered()
{
    const bool isVis = ui->toolBar->isVisible();
    ui->toolBar->setVisible(!isVis);
    ui->actToolBar->setChecked(!isVis);
}

void MainWindow::on_actSelectAll_triggered()
{
    ui->textEdit->selectAll();
}

void MainWindow::on_actExit_triggered()
{
    if (userEditConfirmed()) exit(0);
}

void MainWindow::on_textEdit_cursorPositionChanged()
{
    int colIdx = 0, lineIdx = 0, lastNLPos = -1;
    const int currPos = ui->textEdit->textCursor().position();
    const QString plainTxt = ui->textEdit->toPlainText();

    for (int i = 0; i < currPos; ++i) {
        if (plainTxt[i] == '\n') {
            lineIdx++;
            lastNLPos = i;
        }
    }

    colIdx = currPos - (lastNLPos + 1);
    statusCursorLabel.setText(QString("ln: %1    col: %2").arg(lineIdx + 1).arg(colIdx + 1));
}
