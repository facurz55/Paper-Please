#include "condiciones.h"

condiciones::condiciones() {
    NPC = new Persona();  // Inicializar el puntero
    generarCondicionesNivel1();
}

condiciones::~condiciones() {
    delete NPC;  // Limpiar la memoria
}

int condiciones::generarNumero(){
    int min = 1;
    int max = 5;

    return QRandomGenerator::global()->bounded(min, max + 1); // max + 1 porque bounded excluye el límite superior
}

int condiciones::generarNumero2(){
    int min = 1;
    int max = 7;

    return QRandomGenerator::global()->bounded(min, max + 1); // max + 1 porque bounded excluye el límite superior
}

void condiciones::generarCondicionesNivel1(){
    int numeroIF = generarNumero();

    if(numeroIF == 1){
        nacionalidad = NPC->obtenerNacionalidad();
    }else{
        nacionalidad = "CUALQUIERA";
    }

    if(numeroIF == 2){
        fecha = NPC->obtenerFecha();
    }else{
        fecha = "CUALQUIERA";
    }

    if(numeroIF == 3){
        tipoVisita = NPC->getPersonaVisa();
    }else{
        tipoVisita = "CUALQUIERA";
    }

    if(numeroIF == 4){
        estancia = NPC->obtenerEstancia();
    }else{
        estancia = "CUALQUIERA";
    }

    if(numeroIF == 5){
        estCivil = NPC->getPersonaEstCivil();
    }else{
        estCivil = "CUALQUIERA";
    }
}

QString condiciones::obtenerEstancia(){
    return estancia;
}

QString condiciones::obtenerEstCivil(){
    return estCivil;
}

QString condiciones::obtenerFecha(){
    return fecha;
}

QString condiciones::obtenerNacionalidad(){
    return nacionalidad;
}

QString condiciones::obtenerTipoVisita(){
    return tipoVisita;
}
