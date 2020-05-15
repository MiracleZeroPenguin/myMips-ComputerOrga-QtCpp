#ifndef MACHINEDEMO_H
#define MACHINEDEMO_H

#include <QDialog>

namespace Ui {
class Machinedemo;
}

class Machinedemo : public QDialog
{
    Q_OBJECT

public:
    explicit Machinedemo(QWidget *parent = nullptr);
    ~Machinedemo();

private slots:
    void on_checkcoe_clicked(bool checked);

    void on_checkseg_clicked(bool checked);

private:
    Ui::Machinedemo *ui;
};

#endif // MACHINEDEMO_H
