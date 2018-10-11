#include "dob.h"
#include "ui_dob.h"

DOB::DOB(QWidget *parent) : QMainWindow(parent), ui(new Ui::DOB)
{
    ui->setupUi(this);
}

DOB::~DOB()
{
    delete ui;
}
