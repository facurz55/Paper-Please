#ifndef PUNTOS_H
#define PUNTOS_H
#include <QString>
#include "multas.h"

class puntos
{
public:
    puntos();
    void setUpMultas(multas * newMultas);
    void puntaje(QString  );//puntajes negativo de verificacion equivocada
    void puntaje2(QString  );//puntajes positivo de verificacion positiva

    int obtener_puntos() ;//getter
    void puntuacion_asignada1();//asignacion de puntos en dificultad 100 facil
    void puntuacion2_asignada2();//asignacion de puntos en dificultad 50 normal
    void puntuacion3_asignada3();//asignacion de puntos en dificultad 0  dificil
    void setPunto(int newPunto);
    void fallo_nivel_2(QString,QString,QString,QString);
    void fallo_nivel_3(int,QString,QString);
    void fallo_nivel_4(int,QString,QString,QString,QString);

private:
    int punto;//variable de puntos
    multas *multa3;
};

#endif // PUNTOS_H
