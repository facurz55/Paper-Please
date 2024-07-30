#include "puntos.h"
#include <QDebug>

///saquenlo cuando mariano tenga su parte de npc

puntos::puntos() {

}

void puntos::setUpMultas(multas *newMultas)
{
    multa3 = newMultas;
}

void puntos::puntaje(QString npc){
    if(npc=="aldeano")
    {
        punto=punto-15;
    }
    if(npc=="refugiado político")
    {
        punto=punto-25;
    }
    if(npc=="diplomático")
    {
        punto=punto-25;
        multa3->incrementar();
    }
    if(npc=="revolucionario")
    {
        punto=punto-25;
        multa3->incrementar();
    }
}
void puntos::puntaje2(QString npc){
    if(npc=="aldeano")
    {
        punto=punto+10;
    }
    if(npc=="refugiado político")
    {
        punto=punto+15;
    }
    if(npc=="diplomático")
    {
        punto=punto+25;
    }

}
    int puntos::obtener_puntos()
    {
        return punto;
    }
    void puntos::puntuacion_asignada1(){
        punto=100;
    }
    void puntos::puntuacion2_asignada2(){
        punto=50;
    }
    void puntos::puntuacion3_asignada3(){
        punto=0;
    }

