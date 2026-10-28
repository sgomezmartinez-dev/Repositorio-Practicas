#ifndef RED_H
#define RED_H

#include <string>
#include <map>
#include "Enrutador.h"

using namespace std;

class Red {
private:
    map<string, Enrutador> enrutadores; // Guarda los enrutadores

    // Costos minimos desde origen a todos los alcanzables (solo usa map)
    map<string, int> calcularCostos(const string& origen) const;

public:
    Red();

    bool agregarEnrutador(const string& nombre);
    bool eliminarEnrutador(const string& nombre);

    bool agregarEnlace(const string& a, const string& b, int costo);
    bool eliminarEnlace(const string& a, const string& b);

    void recalcularTablas();
    void mostrarTablas() const;
};

#endif
