#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "calculate.h"
#include "iostream"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->theAnsLcd->setDecMode(); // 设置十进制显示结果
    ui->theAnsLcd->display(0); // 初始化
    new_win = new new_window; // 历史记录窗口
    calculate_expression = "";
    isAns = false;
    isWrong = false; // 运算式是否出错
    ANS = 0; // 记录答案
    isBinary = false; // 是否转换成二进制
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

}

void MainWindow::on_button_0_clicked()
{
    set_show_line("0");
    add_calculate_expression("0");
}

void MainWindow::on_button_1_clicked()
{
    set_show_line("1");
    add_calculate_expression("1");
}

void MainWindow::on_button_2_clicked()
{
    set_show_line("2");
    add_calculate_expression("2");
}

void MainWindow::on_button_3_clicked()
{
    set_show_line("3");
    add_calculate_expression("3");
}

void MainWindow::on_button_4_clicked()
{
    set_show_line("4");
    add_calculate_expression("4");
}

void MainWindow::on_button_5_clicked()
{
    set_show_line("5");
    add_calculate_expression("5");
}

void MainWindow::on_button_6_clicked()
{
    set_show_line("6");
    add_calculate_expression("6");
}

void MainWindow::on_button_7_clicked()
{
    set_show_line("7");
    add_calculate_expression("7");
}

void MainWindow::on_button_8_clicked()
{
    set_show_line("8");
    add_calculate_expression("8");
}

void MainWindow::on_button_9_clicked()
{
    set_show_line("9");
    add_calculate_expression("9");
}

void MainWindow::on_button_point_clicked()
{
    set_show_line(".");
    add_calculate_expression(".");
}

void MainWindow::on_button_plus_clicked()
{
    set_show_line("+");
    add_calculate_expression("+");
}

void MainWindow::on_button_min_clicked()
{
    set_show_line("-");
    add_calculate_expression("-");
}

void MainWindow::on_button_mult_clicked()
{
    set_show_line("×");
    add_calculate_expression("*");
}

void MainWindow::on_button_divid_clicked()
{
    set_show_line("÷");
    add_calculate_expression("/");
}

void MainWindow::on_button_equ_clicked()
{
    calculate *cal = new calculate();

    // 使用正则表达式解析平方，将2@转换成2*2
    QRegExp sqr("((\\d+)|([(][^@]*[)])|(\\d+\\.\\d*))@");
    while((sqr.indexIn(calculate_expression, 0)) != -1){
        calculate_expression.replace(sqr,"((\\1)*(\\1))");
    }

    // 使用正则表达式解析倒数，将2！转换成1/2
    QRegExp reci("((\\d+)|([(][^!]*[)])|(\\d+\\.\\d*))!");
    while((reci.indexIn(calculate_expression, 0)) != -1){
        calculate_expression.replace(reci,"(1/\\1)");
    }

    std::cout << calculate_expression.toLatin1().data() << std::endl;
    int res = cal->setCal(calculate_expression.toLatin1().data()); // 将计算式传入函数

    QString tem_ = ui->input_line->toHtml(); // 存放历史记录
    tem_ = tem_.left(tem_.length() - 18);

    if(res == 1){
        double tem = cal->get_result(); // 得到结果，如果为nan，说明输入的是类似()形式
        if(QString::number(tem) == "nan") {
            ui->input_line->setText("ERROR: 运算式输入不合法");
            new_win->add_items(tem_ + " ERROR: 运算式输入不合法");
            isWrong = true;
        }
        else {
            isAns = true;
            ANS = tem; // 将ANS赋值
            ui->theAnsLcd->display(ANS);  // 显示结果
            calculate_expression = "";

            add_calculate_expression(QString::number(ANS));
            new_win->add_items(tem_ + " = " + QString::number(ANS) + "</p></body></html>"); // 添加到历史记录种
        }
    } else if (res == -1) { //错误类型1
        new_win->add_items(tem_ + " ERROR: 小数点输入有误，请检查输入");
        ui->input_line->setText("ERROR: 小数点输入有误，请检查输入");
        isWrong = true;
    } else if (res == -2){ // 错误类型2
        new_win->add_items(tem_ + " ERROR: 运算式输入不合法");
        ui->input_line->setText("ERROR: 运算式输入不合法");
        isWrong = true;
    } else if(res == -3){ // 错误类型3
        new_win->add_items(tem_ + " ERROR: 除数出现0");
        ui->input_line->setText("ERROR: 除数出现0");
        isWrong = true;
    }
}

void MainWindow::on_button_DEL_clicked() // 回退
{
    QString tem = ui->input_line->toHtml();
    tem = tem.left(tem.length() - 19);
    if(tem.endsWith("</span")){
        int index = tem.lastIndexOf("<span style=\" vertical-align:super;\">");
        tem.remove(index, tem.length() - index);
    }
    ui->input_line->setText(tem + "</p></body></html>");
    calculate_expression = calculate_expression.left(calculate_expression.length() - 1);
}

void MainWindow::on_button_AC_clicked() // 清空
{
    ui->input_line->clear();
    calculate_expression = "";
    isAns = false;
}


void MainWindow::on_button_Ans_clicked() // 上一次的正确计算结果
{
    QString tem = ui->input_line->toHtml();
    tem = tem.left(tem.length() - 18);
    ui->input_line->setText(tem + "Ans</p></body></html>");
    add_calculate_expression(QString::number(ANS));
}

void MainWindow::on_button_left_bracket_clicked()
{
    set_show_line("(");
    QString tem = calculate_expression;
    // 允许计算2(3+4)和(2+3)(4+5)算术式
    if(tem.endsWith(")") || (tem.length() && tem[tem.length() - 1].isDigit())) add_calculate_expression("*");
    add_calculate_expression("(");
}

void MainWindow::on_button_right_bracket_clicked()
{
    set_show_line(")");
    add_calculate_expression(")");
}


void MainWindow::on_button_square_clicked()
{
    set_show_line("<span style=\" vertical-align:super;\">2</span>");
    add_calculate_expression("@"); // 平方，用符号@表示
}

void MainWindow::on_button_reci_clicked()
{
    set_show_line("<span style=\" vertical-align:super;\">-1</span>");
    add_calculate_expression("!"); // 倒数，用符号！表示
}

void MainWindow:: add_calculate_expression(QString a)
{
    calculate_expression += a;
}

void MainWindow:: set_show_line(QString a)
{
    if(isAns) {
        ui->input_line->setText("Ans");
        isAns = false;
    }

    if(isWrong){
        ui->input_line->clear();
        isWrong = false;
        calculate_expression = "";
    }

    QString tem = ui->input_line->toHtml(); // 显示计算式
    tem = tem.left(tem.length() - 18);
    ui->input_line->setText(tem + a + "</p></body></html>");

}

void MainWindow::on_button_HIS_clicked()
{
    new_win->show(); // 显示历史记录
}

void MainWindow::on_pushButton_3_clicked() // 转换成二进制
{
    // 重复点击可在二进制和十进制之间转换
    if(!isBinary){
        calculate *cal = new calculate();
        int i = 0;
        char A[15];
        for(int j = 0; j < 15; j++) A[j] = '5';
        cal->toBinary(ANS, A); // 调用函数

        QString s ="";
        while(A[i] != '5') {
            s += A[i++];
        }
        ui->theAnsLcd->display(s.toUtf8().data());
        isBinary = true;
    } else {
        ui->theAnsLcd->display(ANS);
        isBinary = false;
    }

}
