#include "Enrutador.h"
#include <iostream>

Enrutador::Enrutador(const string& nombre) : nombre(nombre) {
    tablaCostos[nombre] = 0;   // el costo hacia si mismo es 0
}

string Enrutador::getNombre() const {
    return nombre;
}

const map<string, int>& Enrutador::getVecinos() const {
    return vecinos;
}

void Enrutador::agregarVecino(const string& destino, int costo) {
    vecinos[destino] = costo;        // si ya existia, actualiza el costo
    tablaCostos[destino] = costo;    // tabla inicial: solo enlaces directos
}

void Enrutador::eliminarVecino(const string& destino) {
    vecinos.erase(destino);
    tablaCostos.erase(destino);
}

void Enrutador::actualizarTabla(const map<string, int>& nueva) {
    tablaCostos = nueva;
}

int Enrutador::getCostoA(const string& destino) const {
    map<string, int>::const_iterator it = tablaCostos.find(destino);
    if (it == tablaCostos.end())
        return -1;
    return it->second;
}

void Enrutador::mostrarTabla() const {
    cout << "Tabla de " << nombre << ":" << endl;
    for (map<string, int>::const_iterator it = tablaCostos.begin();
         it != tablaCostos.end(); ++it) {
        cout << "  -> " << it->first << " : " << it->second << endl;
    }
}