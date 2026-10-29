#ifndef RED_H
#define RED_H

#include <string>
#include <map>
#include <vector>
#include "Enrutador.h"

using namespace std;

class Red {
private:
    map<string, Enrutador> enrutadores; // Guarda los enrutadores

    //Archivo cargado actualmente (" " si no hay). Cada cambio se guarda en el
    string rutaArchivo;
    void autoGuardar() const;  //Reescribe rutaArchivo con la red actual

    // Costos minimos desde origen a todos los alcanzables (solo usa map).
    //PARTE 2
    // se agrego parametro 'previo': guarda el anterior  de cada destino para poder reconstruir el camino
    map<string, int> calcularCostos(const string& origen , map<string, string>* previo = 0) const;

public:
    Red();

    bool agregarEnrutador(const string& nombre);
    bool eliminarEnrutador(const string& nombre);

    bool agregarEnlace(const string& a, const string& b, int costo);
    bool eliminarEnlace(const string& a, const string& b);

    void mostrarTablas() const;

    // PARTE 2
    void recalcularTablas();   // actualiza la tabla de cada enrutador

    // Camino minimo origen / destino. Devuelve false si no existe ruta.
    bool obtenerCamino(const string& origen, const string& destino, vector<string>& camino, int& costo) const;

    // Archivos de texto
    bool cargarDesdeArchivo(const string& ruta);
    bool guardarEnArchivo(const string& ruta) const;
    void limpiar();
};

#endif
