#ifndef LOGS_H
#define LOGS_H
#include <fstream>
#include <iostream>
using namespace std;
class Logs
{
public:
    Logs();
    ~Logs();
    void setText(string texto);
private:
    ofstream archivo;
};

#endif // LOGS_H
