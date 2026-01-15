#ifndef PRIVATECHATWIDGET_H
#define PRIVATECHATWIDGET_H

#include <QWidget>
#include <QMouseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class PrivateChatWidget; }
QT_END_NAMESPACE

class PrivateChatWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PrivateChatWidget(const QString &targetName,
                               QWidget *parent = nullptr);
    ~PrivateChatWidget();

    QString target() const { return m_target; }
    void appendMessage(const QString &sender, const QString &text);

signals:
    void sendPrivateMessage(const QString &receiver, const QString &text);
    void windowClosed(const QString &target);   // 关闭时通知主窗口清指针

private slots:
    void on_sendButton_clicked();

protected:
    void mousePressEvent(QMouseEvent *e) override;
    void mouseMoveEvent(QMouseEvent *e) override;

private:
    Ui::PrivateChatWidget *ui;
    QString m_target;
    QPoint  m_dragPos;
};

#endif // PRIVATECHATWIDGET_H
