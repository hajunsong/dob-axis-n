#ifndef DOB_H
#define DOB_H

#include <QMainWindow>

namespace Ui {
class DOB;
}

class DOB : public QMainWindow
{
    Q_OBJECT

public:
    explicit DOB(QWidget *parent = nullptr);
    ~DOB();

private:
    Ui::DOB *ui;
};

#endif // DOB_H
