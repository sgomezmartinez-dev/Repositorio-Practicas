#ifndef ENRUTADOR_H
#define ENRUTADOR_H

#include <string>
#include <map>

using namespace std;

class Enrutador {
private:
    string nombre;
    map<string, int> vecinos;      // vecino directo: costo del enlace
    map<string, int> tablaCostos;  // destino: costo del mejor camino

public:
    Enrutador(const string& nombre = ""); //Inicializa el objeto  al crearlo

    string getNombre() const;
    const map<string, int>& getVecinos() const;

    void agregarVecino(const string& destino, int costo);
    void eliminarVecino(const string& destino);

    void actualizarTabla(const map<string, int>& nueva);
    int getCostoA(const string& destino) const;   // -1 si no hay ruta
    void mostrarTabla() const;
};

#endif

