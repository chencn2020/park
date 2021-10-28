#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "new_window.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_button_0_clicked();

    void on_button_1_clicked();

    void on_button_2_clicked();

    void on_button_3_clicked();

    void on_button_4_clicked();

    void on_button_5_clicked();

    void on_button_6_clicked();

    void on_button_7_clicked();

    void on_button_8_clicked();

    void on_button_9_clicked();

    void on_button_point_clicked();

    void on_button_plus_clicked();

    void on_button_min_clicked();

    void on_button_mult_clicked();

    void on_button_divid_clicked();

    void on_button_equ_clicked();

    void on_button_DEL_clicked();

    void on_button_AC_clicked();

    void on_button_Ans_clicked();

    void on_button_left_bracket_clicked();

    void on_button_right_bracket_clicked();

    void on_pushButton_clicked();

    void on_button_square_clicked();

    void on_button_reci_clicked();

    void add_calculate_expression(QString a);

    void set_show_line(QString a);

    void on_button_HIS_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    QString calculate_expression;
    new_window *new_win;
    double ANS;
    bool isAns;
    bool isWrong;
    bool isBinary;
};
#endif // MAINWINDOW_H
