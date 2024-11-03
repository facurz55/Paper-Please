#include "multas.h"


multas::multas()
{
    multa = 0;
}

void multas::incrementar()
{
    multa += 1;
}
int multas::obtenerMultas() const
{
    return multa;
}

void multas::setMultas(int m){
    multa = m;
}
