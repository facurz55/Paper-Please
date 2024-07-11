#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <QWidget>

namespace Ui {
class gameplay;
}

class gameplay : public QWidget
{
    Q_OBJECT

public:
    explicit gameplay(QWidget *parent = nullptr);
    ~gameplay();

private:
    Ui::gameplay *ui;
};

#endif // GAMEPLAY_H
