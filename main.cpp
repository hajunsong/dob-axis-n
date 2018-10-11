#include "dob.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DOB w;
    w.show();

    return a.exec();
}
