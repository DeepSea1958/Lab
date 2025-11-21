#include "codeedit.h"
#include <QPainter>
#include <QTextBlock>

CodeEditor::CodeEditor(QWidget *parent)
    : QPlainTextEdit(parent)
{
    lineNumberArea = new LineNumberArea(this);

    // 连接信号槽
    connect(this, &CodeEditor::blockCountChanged, this, &CodeEditor::updateLineNumberAreaWidth);
    connect(this, &CodeEditor::updateRequest, this, &CodeEditor::updateLineNumberArea);
    connect(this, &CodeEditor::cursorPositionChanged, this, &CodeEditor::highlightCurrentLine);

    updateLineNumberAreaWidth(0);
    highlightCurrentLine();
}

int CodeEditor::lineNumberAreaWidth()
{
    int digitCount = 1;
    const int maxBlock = qMax(1, blockCount());

    // 计算需要的数字位数
    for (int tempMax = maxBlock; tempMax >= 10; tempMax /= 10) {
        ++digitCount;
    }

    // 计算行号区域宽度（预留间距+数字宽度）
    const int digitWidth = fontMetrics().horizontalAdvance(QLatin1Char('9'));
    return 3 + digitWidth * digitCount;
}

void CodeEditor::updateLineNumberAreaWidth(int /* newBlockCount */)
{
    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}

void CodeEditor::updateLineNumberArea(const QRect &rect, int dy)
{
    if (dy != 0) {
        lineNumberArea->scroll(0, dy);
    } else {
        lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());
    }

    // 若当前区域包含视图端口，更新行号宽度
    if (rect.contains(viewport()->rect())) {
        updateLineNumberAreaWidth(0);
    }
}

void CodeEditor::resizeEvent(QResizeEvent *e)
{
    QPlainTextEdit::resizeEvent(e);
    const QRect contentRect = contentsRect();
    lineNumberArea->setGeometry(QRect(contentRect.left(), contentRect.top(),
                                      lineNumberAreaWidth(), contentRect.height()));
}

void CodeEditor::highlightCurrentLine()
{
    QList<QTextEdit::ExtraSelection> extraSelList;

    if (!isReadOnly()) {
        QTextEdit::ExtraSelection currLineSel;
        // 设置当前行高亮颜色（浅黄色）
        const QColor highlightColor = QColor(Qt::yellow).lighter(160);

        currLineSel.format.setBackground(highlightColor);
        currLineSel.format.setProperty(QTextFormat::FullWidthSelection, true);
        currLineSel.cursor = textCursor();
        currLineSel.cursor.clearSelection();
        extraSelList.append(currLineSel);
    }

    setExtraSelections(extraSelList);
}

void CodeEditor::lineNumberAreaPaintEvent(QPaintEvent *event)
{
    QPainter painter(lineNumberArea);
    painter.fillRect(event->rect(), Qt::white);

    QTextBlock currBlock = firstVisibleBlock();
    int blockIdx = currBlock.blockNumber();
    int blockTop = qRound(blockBoundingGeometry(currBlock).translated(contentOffset()).top());
    int blockBottom = blockTop + qRound(blockBoundingRect(currBlock).height());

    // 遍历可见块并绘制行号
    while (currBlock.isValid() && blockTop <= event->rect().bottom()) {
        if (currBlock.isVisible() && blockBottom >= event->rect().top()) {
            const QString lineNumText = QString::number(blockIdx + 1);
            painter.setPen(Qt::black);
            painter.drawText(0, blockTop, lineNumberArea->width(), fontMetrics().height(),
                             Qt::AlignRight, lineNumText);
        }

        currBlock = currBlock.next();
        blockTop = blockBottom;
        blockBottom = blockTop + qRound(blockBoundingRect(currBlock).height());
        ++blockIdx;
    }
}
