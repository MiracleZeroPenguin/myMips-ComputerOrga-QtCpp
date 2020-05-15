#ifndef COPYRIGHT_H
#define COPYRIGHT_H

#include <QDialog>

namespace Ui {
class Copyright;
}

class Copyright : public QDialog
{
    Q_OBJECT

public:
    explicit Copyright(QWidget *parent = nullptr);
    ~Copyright();

private:
    Ui::Copyright *ui;
};

#endif // COPYRIGHT_H
