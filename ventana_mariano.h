#ifndef VENTANA_MARIANO_H
#define VENTANA_MARIANO_H
#include <QMainWindow>
#include "persona.h"

namespace Ui {
class ventana_Mariano;
}
class ventana_Mariano : public QMainWindow
{
    Q_OBJECT

public:
    explicit ventana_Mariano(QWidget *parent = nullptr);
    ~ventana_Mariano();

private slots:
    void siPasa();
    void noPasa();
    void actualizarLabelConPersona();

private:
    Ui::ventana_Mariano *ui;
    Persona Persona;
};

#endif // VENTANA_MARIANO_H
