#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "math.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->btnNum0,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    connect(ui->btnNum1,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    connect(ui->btnNum2,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    connect(ui->btnNum3,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    connect(ui->btnNum4,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    connect(ui->btnNum5,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    connect(ui->btnNum6,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    connect(ui->btnNum7,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    connect(ui->btnNum8,SIGNAL(clicked()),this,SLOT(btnNumClicked()));
    connect(ui->btnNum9,SIGNAL(clicked()),this,SLOT(btnNumClicked()));

    connect(ui->btnDivide,SIGNAL(clicked()),this,SLOT(btnBinaryOperatorClicked()));
    connect(ui->btnMultiply,SIGNAL(clicked()),this,SLOT(btnBinaryOperatorClicked()));
    connect(ui->btnPlus,SIGNAL(clicked()),this,SLOT(btnBinaryOperatorClicked()));
    connect(ui->btnMinus,SIGNAL(clicked()),this,SLOT(btnBinaryOperatorClicked()));

    connect(ui->btnPercentage,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));
    connect(ui->btnInverse,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));
    connect(ui->btnSquare,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));
    connect(ui->btnSqrt,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::calculation(bool *ok)
{
    double result = 0;
    bool hasError = false;

    if (operands.size() >= 2 && !opcodes.isEmpty())
    {
        double operand1 = operands[0].toDouble();
        double operand2 = operands[1].toDouble();
        QString op = opcodes[0];

        // 执行相应运算
        if (op == "+") {
            result = operand1 + operand2;
        }
        else if (op == "-") {
            result = operand1 - operand2;
        }
        else if (op == "×") {
            result = operand1 * operand2;
        }
        else if (op == "÷") {
            if (operand2 == 0) {
                hasError = true;
            } else {
                result = operand1 / operand2;
            }
        }

        // 清除已计算的操作数和运算符，保存结果作为新的操作数
        operands.clear();
        opcodes.clear();
        operands.push_back(QString::number(result));
    }

    if (hasError) {
        return "错误";
    }
    return operands.isEmpty() ? "0" : operands[0];
}

// 数字按钮点击事件
void MainWindow::btnNumClicked()
{
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if (!btn) return;

    QString digit = btn->text();

    // 处理 leading zero 问题
    if (operand == "0" && digit == "0") {
        return; // 避免多个0开头
    }
    if (operand == "0" && digit != "0") {
        operand.clear(); // 替换初始0
    }

    // 限制输入长度，防止显示溢出
    if (operand.length() < 15) {
        operand += digit;
        ui->display->setText(operand);
    }
}

// 小数点按钮点击事件
void MainWindow::on_btnPriod_clicked()
{
    if (operand.isEmpty()) {
        operand = "0."; // 空输入时直接输入.显示0.
    } else if (!operand.contains(".")) {
        operand += ".";
    }
    ui->display->setText(operand);
}

// 删除按钮点击事件
void MainWindow::on_btnDel_clicked()
{
    if (!operand.isEmpty()) {
        operand.chop(1); // 移除最后一个字符
        // 如果删除后为空，显示0
        ui->display->setText(operand.isEmpty() ? "0" : operand);
    }
}

// CE按钮（清除当前输入）
void MainWindow::on_btnClearAlll_clicked()
{
    operand.clear();
    ui->display->setText("0");
}

// C按钮（清除所有）
void MainWindow::on_btnClear_clicked()
{
    operand.clear();
    operands.clear();
    opcodes.clear();
    ui->display->setText("0");
}

// 二元运算符点击事件（+、-、×、÷）
void MainWindow::btnBinaryOperatorClicked()
{
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if (!btn) return;

    QString opcode = btn->text();

    // 如果有当前输入，加入操作数列表
    if (!operand.isEmpty()) {
        operands.push_back(operand);
        operand.clear();
    }

    // 如果已有运算符，先计算再加入新运算符
    if (!opcodes.isEmpty() && operands.size() >= 2) {
        QString result = calculation();
        ui->display->setText(result);
    }

    // 加入新运算符（确保操作数列表有值时才添加）
    if (!operands.isEmpty()) {
        opcodes.push_back(opcode);
    }
}

// 一元运算符点击事件（%、1/x、x²、√x）
void MainWindow::btnUnaryOperatorClicked()
{
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if (!btn) return;

    QString op = btn->text();
    double result = 0;
    bool hasError = false;

    // 如果没有当前输入，使用显示框的值
    if (operand.isEmpty()) {
        operand = ui->display->text();
    }

    if (!operand.isEmpty() && operand != "错误") {
        result = operand.toDouble();

        if (op == "%") {
            result /= 100.0; // 百分比运算
        }
        else if (op == "1/x") {
            if (result == 0) {
                hasError = true;
            } else {
                result = 1 / result; // 倒数运算
            }
        }
        else if (op == "x^2") {
            result *= result; // 平方运算
        }
        else if (op == "x^(1/2)") {
            if (result < 0) {
                hasError = true;
            } else {
                result = sqrt(result); // 平方根运算
            }
        }

        operand.clear();
        if (hasError) {
            ui->display->setText("错误");
        } else {
            QString resStr = QString::number(result);
            // 移除多余的小数点和零
            if (resStr.contains(".") && resStr.right(1) == "0") {
                resStr = resStr.left(resStr.length() - 1);
            }
            ui->display->setText(resStr);
            operands.clear();
            operands.push_back(resStr);
        }
    }
}

// 等号按钮点击事件
void MainWindow::on_btnEqual_clicked()
{
    if (!operand.isEmpty()) {
        operands.push_back(operand);
        operand.clear();
    }

    if (operands.size() >= 2 && !opcodes.isEmpty()) {
        QString result = calculation();
        ui->display->setText(result);
    }
}

// 正负号转换按钮点击事件
void MainWindow::on_btnSign_clicked()
{
    if (operand.isEmpty()) {
        // 如果没有当前输入，取显示框的值处理
        operand = ui->display->text();
        if (operand == "0" || operand == "错误") {
            return;
        }
    }

    // 处理正负号转换
    if (operand.startsWith("-")) {
        operand.remove(0, 1); // 移除负号
    } else {
        operand = "-" + operand; // 添加负号
    }

    ui->display->setText(operand);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_0)
       ui->btnNum0->animateClick();
    if(event->key() == Qt::Key_1)
        ui->btnNum1->animateClick();
    if(event->key() == Qt::Key_2)
        ui->btnNum2->animateClick();
    if(event->key() == Qt::Key_3)
        ui->btnNum3->animateClick();
    if(event->key() == Qt::Key_4)
        ui->btnNum4->animateClick();
    if(event->key() == Qt::Key_5)
        ui->btnNum5->animateClick();
    if(event->key() == Qt::Key_6)
        ui->btnNum6->animateClick();
    if(event->key() == Qt::Key_7)
        ui->btnNum7->animateClick();
    if(event->key() == Qt::Key_8)
        ui->btnNum8->animateClick();
    if(event->key() == Qt::Key_9)
        ui->btnNum9->animateClick();
    if(event->key() == Qt::Key_Plus)
        ui->btnPlus->animateClick();
    if(event->key() == Qt::Key_Minus)
        ui->btnMinus->animateClick();
    if(event->key() == Qt::Key_Asterisk)
        ui->btnMultiply->animateClick();
    if(event->key() == Qt::Key_Slash)
        ui->btnDivide->animateClick();
    if(event->key() == Qt::Key_Equal)
        ui->btnEqual->animateClick();
    if(event->key() == Qt::Key_Backspace)
        ui->btnDel->animateClick();
    if(event->key() == Qt::Key_Period)
        ui->btnPriod->animateClick();
}
