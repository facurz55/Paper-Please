#include "puntos.h"
#include "menu.h"

///saquenlo cuando mariano tenga su parte de npc

puntos::puntos() {}
void puntos::puntaje(QString npc){
    if(npc=="aldeano")
    {
        punto=punto-15;
    }
    if(npc=="Refugiado político")
    {
        punto=punto-25;
    }
    if(npc=="Diplomático")
    {
        punto=punto-25;
    }
    if(npc=="Revolucionario")
    {
        punto=punto-25;
    }
}
void puntos::puntaje2(QString npc){
    if(npc=="aldeano")
    {
        punto=punto+10;
    }
    if(npc=="Refugiado político")
    {
        punto=punto+15;
    }
    if(npc=="Diplomático")
    {
        punto=punto+25;
    }
}
    int puntos::obtener_puntos() const
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

