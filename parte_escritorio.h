#ifndef PARTE_ESCRITORIO_H
#define PARTE_ESCRITORIO_H

#include <QWidget>

namespace Ui {
class parte_escritorio;
}

class parte_escritorio : public QWidget
{
    Q_OBJECT

public:
    explicit parte_escritorio(QWidget *parent = nullptr);
    ~parte_escritorio();

private:
    Ui::parte_escritorio *ui;
};

#endif // PARTE_ESCRITORIO_H
