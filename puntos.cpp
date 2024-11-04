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
void  puntos::fallo_nivel_2(QString residencia,QString origen,QString npc,QString proposito_del_viaje){
    if((residencia=="bolivia")&& (origen=="boliviano/a")){
        puntaje(npc);
    }
    if((origen=="paraguayo/a") && (proposito_del_viaje=="turismo")){
        puntaje(npc);
    }
    if((origen=="brasileño/a") && (proposito_del_viaje=="visita familiar")){
        puntaje(npc);
    }
}
void puntos::fallo_nivel_3(int cantidad_acompanante,QString npc,QString origen){
    if((origen=="boliviano/a") && (cantidad_acompanante!=0)){
        puntaje(npc);
    }
    if(cantidad_acompanante>=5){
        puntaje(npc);
    }
    if((cantidad_acompanante>=4)&& (origen=="brasileño/a")){
        puntaje(npc);
    }
    if((cantidad_acompanante<=2)&& (origen=="paraguayo/a")){
        puntaje(npc);
    }
}
void puntos::fallo_nivel_4(int peso_maleta,QString tipo_maleta,QString ocupacion,QString npc ,QString residencia){
    if((peso_maleta<=15) && (tipo_maleta!="liviana")){
        puntaje(npc);
    }
    if((peso_maleta<=25)&& (peso_maleta>15) && (tipo_maleta!="media")){
        puntaje(npc);
    }
    if((peso_maleta<=40)&& (peso_maleta>26) && (tipo_maleta!="pesada")){
        puntaje(npc);
    }
    if((peso_maleta>20) && (residencia=="Bolivia")){
        puntaje(npc);
    }
    if((tipo_maleta=="pesada") && (residencia=="Paraguay")){
        puntaje(npc);
    }
    if((residencia=="Argentina") && (ocupacion=="piquetero")){
        puntaje(npc);
    }
    if((residencia=="Brasil") && (ocupacion=="futbolista")){
        puntaje(npc);
    }
    if((residencia=="Paraguay")&& (ocupacion=="ingeniero")){
        puntaje(npc);
    }
    if((residencia=="Bolivia")&& (ocupacion=="camionero")){
        puntaje(npc);
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

void puntos::setPunto(int newPunto)
{
    punto = newPunto;
}

