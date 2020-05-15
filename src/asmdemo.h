#ifndef ASMDEMO_H
#define ASMDEMO_H

#include <QDialog>

namespace Ui {
class ASMdemo;
}

class ASMdemo : public QDialog
{
    Q_OBJECT

public:
    explicit ASMdemo(QWidget *parent = nullptr);
    ~ASMdemo();

private:
    Ui::ASMdemo *ui;
};

#endif // ASMDEMO_H
