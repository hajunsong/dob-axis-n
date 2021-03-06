#ifndef DOB_UI_H
#define DOB_UI_H

#include <QMainWindow>

namespace Ui {
class DOB_ui;
}

class DOB_ui : public QMainWindow
{
    Q_OBJECT

public:
    explicit DOB_ui(QWidget *parent = nullptr);
    ~DOB_ui();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::DOB_ui *ui;
};

#endif // DOB_UI_H
