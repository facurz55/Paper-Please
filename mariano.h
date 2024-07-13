#ifndef MARIANO_H
#define MARIANO_H

#include <QWidget>

namespace Ui {
class Mariano;
}

class Mariano : public QWidget
{
    Q_OBJECT

public:
    explicit Mariano(QWidget *parent = nullptr);
    ~Mariano();

private:
    Ui::Mariano *ui;
};

#endif // MARIANO_H
