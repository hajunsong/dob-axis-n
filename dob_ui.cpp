#include "dob_ui.h"
#include "ui_dob_ui.h"

DOB_ui::DOB_ui(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::DOB_ui)
{
    ui->setupUi(this);
}

DOB_ui::~DOB_ui()
{
    delete ui;
}
