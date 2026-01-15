#include "privatechatwidget.h"
#include "ui_privatechatwidget.h"
#include "mainwindow.h"
#include <QPushButton>
#include <QTime>
#include <QApplication>

PrivateChatWidget::PrivateChatWidget(const QString &targetName, QWidget *parent)
    : QWidget(parent), ui(new Ui::PrivateChatWidget), m_target(targetName)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint |
                   Qt::WindowCloseButtonHint);
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowTitle(QString("与 %1 的私聊").arg(m_target));
    resize(400, 300);
    ui->targetLabel->setText(m_target);
    ui->msgEdit->setFocus();

    connect(ui->closeButton, &QPushButton::clicked, this, &QWidget::close);
    connect(ui->sendButton,  &QPushButton::clicked,
            this, &PrivateChatWidget::on_sendButton_clicked);
}

PrivateChatWidget::~PrivateChatWidget()
{
    emit windowClosed(m_target);
    delete ui;
}

void PrivateChatWidget::appendMessage(const QString &sender, const QString &text)
{
    QString tm = QTime::currentTime().toString("hh:mm:ss");
    ui->chatBrowser->append(QString("[%1] %2: %3").arg(tm, sender, text));

    // 对方消息交给主窗口落盘（自己发的消息通过信号让主窗口落盘）
    if (sender != "我") {
        MainWindow *mainWin = qobject_cast<MainWindow*>(qApp->activeWindow());
        if (mainWin)
            mainWin->appendPrivateMessage(sender, text, m_target);
    }
}

void PrivateChatWidget::on_sendButton_clicked()
{
    QString txt = ui->msgEdit->text().trimmed();
    if (txt.isEmpty()) return;
    ui->msgEdit->clear();

    // 1. 立即在本地窗口显示“我”
    appendMessage("我", txt);
    // 2. 交给主窗口转发（落盘在主窗口的信号处理中完成）
    emit sendPrivateMessage(m_target, txt);
}

void PrivateChatWidget::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton)
        m_dragPos = e->globalPos() - frameGeometry().topLeft();
}

void PrivateChatWidget::mouseMoveEvent(QMouseEvent *e)
{
    if (e->buttons() & Qt::LeftButton)
        move(e->globalPos() - m_dragPos);
}
