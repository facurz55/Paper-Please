#ifndef PUNTOS_H
#define PUNTOS_H
#include <QString>
class puntos
{
public:
    puntos();
    void puntaje(QString  );//puntajes negativo de verificacion equivocada
    void puntaje2(QString  );//puntajes positivo de verificacion positiva

    int obtener_puntos() const;//getter
    void puntuacion_asignada1();//asignacion de puntos en dificultad 100 facil
    void puntuacion2_asignada2();//asignacion de puntos en dificultad 50 normal
    void puntuacion3_asignada3();//asignacion de puntos en dificultad 0  dificil

    int punto;//variable de puntos
};

#endif // PUNTOS_H
