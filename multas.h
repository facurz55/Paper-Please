#ifndef MULTAS_H
#define MULTAS_H

class multas
{
public:
    multas();
    void incrementar();
    int obtenerMultas() const;
    void setMultas(int m);
private:
    int multa;
};

#endif // MULTAS_H
