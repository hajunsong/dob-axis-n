#include "dob_ui.h"
#include "ui_dob_ui.h"
#include "dob.h"

DOB_ui::DOB_ui(QWidget *parent) : QMainWindow(parent), ui(new Ui::DOB_ui)
{
    ui->setupUi(this);
}

DOB_ui::~DOB_ui()
{
    delete ui;
}

void DOB_ui::on_pushButton_clicked()
{
    uint num_body = 3;
    DOB dob(num_body);
    dob.run();
    ui->label_tot->setText(QString::number(dob.total_time));
    ui->label_ave->setText(QString::number(dob.average_time));
}

void DOB_ui::on_pushButton_2_clicked()
{
    this->close();
}
