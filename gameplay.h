#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <QWidget>
#include <QLabel>
#include<QPushButton>

namespace Ui {
class gameplay;
}

class gameplay : public QWidget
{
    Q_OBJECT

public:
    explicit gameplay(QWidget *parent = nullptr);
    ~gameplay();
    QLabel* getLabelNPC();
    QPushButton* getBotonSiguiente_NPC();

private:
    Ui::gameplay *ui;
};

#endif // GAMEPLAY_H
