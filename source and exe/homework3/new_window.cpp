#include "new_window.h"
#include "ui_new_window.h"

new_window::new_window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::new_window)
{
    ui->setupUi(this);
    this->setWindowTitle("历史记录");
    QFont font;
    font.setPointSize(10);
    ui->textEdit->setFont(font);
    ui->textEdit->setReadOnly(true);
}

new_window::~new_window()
{
    delete ui;
}

void new_window::add_items(QString t)
{
    ui->textEdit->append(t);
}
