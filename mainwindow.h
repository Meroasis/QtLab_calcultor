#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStack>
#include <QKeyEvent>
#include <QMap>
#include <QPushButton>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QStack<QString> operands;
    QString op1;

    QString opcode;
    QStack<QString> opcodes;//操作符
    QMap<int,QPushButton*> btnNums;

    QString calculation(bool *ok = NULL);

private slots:
    void btnNumClicked();
    void btnbinaryOperatorClicked();
    void btnUnaryOperatorClicked();
    void on_btnDot_clicked();

    void on_btnBack_clicked();

    void on_btnC_clicked();


    void on_btnEqu_clicked();

    void on_btnCE_clicked();

    virtual void keyPressEvent(QKeyEvent *event);

    void on_btnPlusOrSub_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
