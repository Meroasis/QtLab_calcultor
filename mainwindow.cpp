#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    btnNums = {{Qt::Key_0,ui->btnNum0},
               {Qt::Key_1,ui->btnNum1},
               {Qt::Key_2,ui->btnNum2},
               {Qt::Key_3,ui->btnNum3},
               {Qt::Key_4,ui->btnNum4},
               {Qt::Key_5,ui->btnNum5},
               {Qt::Key_6,ui->btnNum6},
               {Qt::Key_7,ui->btnNum7},
               {Qt::Key_8,ui->btnNum8},
               {Qt::Key_9,ui->btnNum9},
               {Qt::Key_Plus,ui->btnPlus},
               {Qt::Key_Minus,ui->btnSub},
               {Qt::Key_Asterisk,ui->btnMul},
               {Qt::Key_Slash,ui->btnDiv},
               {Qt::Key_Period,ui->btnDot},
               {Qt::Key_Percent,ui->btnPercentage},
               {Qt::Key_Equal,ui->btnEqu},
               {Qt::Key_Backspace,ui->btnBack}
               };


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

    connect(ui->btnMul,SIGNAL(clicked()),this,SLOT(btnbinaryOperatorClicked()));
    connect(ui->btnSub,SIGNAL(clicked()),this,SLOT(btnbinaryOperatorClicked()));
    connect(ui->btnPlus,SIGNAL(clicked()),this,SLOT(btnbinaryOperatorClicked()));
    connect(ui->btnDiv,SIGNAL(clicked()),this,SLOT(btnbinaryOperatorClicked()));

    connect(ui->btnPercentage,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));
    connect(ui->btnRevert,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));
    connect(ui->btnSqure,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));
    connect(ui->btnSqrt,SIGNAL(clicked()),this,SLOT(btnUnaryOperatorClicked()));


}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::calculation(bool *ok)
{
    double result = operands.top().toDouble();
    if(operands.size() == 2 && opcodes.size()>0){
        //取数
        double operand1 = operands.front().toDouble();
        operands.pop_front();
        double operand2 = operands.front().toDouble();
        operands.pop_front();
        //取操作符
        QString calOpcode = opcodes.front();
        opcodes.pop_front();
        if(calOpcode == "+"){
            result = operand1 + operand2;
        }else if(calOpcode == "-"){
            result = operand1 - operand2;
        }else if(calOpcode == "÷"){
            if (operand2 == 0)
            {
                QMessageBox::critical(this, tr("Error"), tr("Cannot divide by zero."));
                return "";
            }
            result = operand1 / operand2;
        }else if(calOpcode == "×"){
            result = operand1 * operand2;
        }
        operands.push_back(QString::number(result));
        ui->statusbar->showMessage("success");
    }else
       ui->statusbar->showMessage(QString("oprands is %1,opcode is %2").arg(operands.size()).arg(opcodes.size()));

    return QString::number(result);
}




void MainWindow::btnNumClicked()
{
   /* QString digit = qobject_cast<QPushButton *>(sender())->text();

    // if(digit=='0'&& op1 == "0")digit = "";
    // if(op1 == "0" && digit != "0")op1 = "";

    op1 += digit;
    ui->Output->setText(op1)*/;
    //ui->statusbar->showMessage(str);
   QPushButton *button = qobject_cast<QPushButton*>(sender());
   if (!button) return;

   QString digit = button->text();
   op1 += digit;
   ui->Output->setText(op1);
}



void MainWindow::on_btnDot_clicked()
{
    if(!op1.contains("."))
       op1 += qobject_cast<QPushButton *>(sender())->text();
    ui->Output->setText(op1);
}


void MainWindow::on_btnBack_clicked()
{
    op1 = op1.left(op1.length()-1);
    ui->Output->setText(op1);
}



void MainWindow::on_btnC_clicked()
{
    op1.clear();
    operands.clear();
    opcodes.clear();
    ui->Output->setText(op1);
}
void MainWindow::on_btnCE_clicked()
{
    op1.clear();
    ui->Output->setText(op1);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    foreach(auto btnKey, btnNums.keys()){
        if(event->key() == btnKey)
            btnNums[btnKey]->animateClick();
    }

}

void MainWindow::on_btnEqu_clicked()
{

    if(op1 != ""){
        operands.push_back(op1);
        op1 = " ";

    }
    QString result = calculation();
    ui->Output->setText(result);

}

void MainWindow::btnbinaryOperatorClicked()
{
    QString opcode = qobject_cast<QPushButton *>(sender())->text();


    if(op1 != ""){
        operands.push_back(op1);
        op1 = " ";

        opcodes.push_back(opcode);
        QString result = calculation();
        ui->Output->setText(result);
    }


}

void MainWindow::btnUnaryOperatorClicked()
{
    if(op1 != ""){
        double result = op1.toDouble();
        op1 = "";
        QString CulOp = qobject_cast<QPushButton*>(sender())->text();
        if(CulOp == "%"){
            result /= 100.0;
        }else if(CulOp == "1/x"){
            result = 1 / result;
        }else if(CulOp == "x^2"){
            result *= result;
        }else if(CulOp == "√"){
            result = sqrt(result);
        }
        ui->Output->setText(QString::number(result));


    }
}




void MainWindow::on_btnPlusOrSub_clicked()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (!button) return;
    if(op1 != ""){
        double value = op1.toDouble();
        value = -value;
        op1 = QString::number(value);
        ui->Output->setText(op1);
    }
}

