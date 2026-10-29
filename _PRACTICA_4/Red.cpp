#include "Red.h"
#include <iostream>
#include <fstream>
#include <sstream>

Red::Red() {}

//Guarda la red actual en el archivo cargado
void Red::autoGuardar() const {
    if (rutaArchivo.empty())
        return;                              // no hay archivo cargado
    if (!guardarEnArchivo(rutaArchivo))
        cout << "Aviso: no se pudo actualizar el archivo " << rutaArchivo << endl;
}

// PARTE 2
void Red::limpiar() {
    enrutadores.clear();
}
// PARTE 1

bool Red::agregarEnrutador(const string& nombre) {
    if (nombre.empty() || enrutadores.count(nombre))
        return false;
    enrutadores[nombre] = Enrutador(nombre);
    recalcularTablas();   //actualiza las tablas al recibir cambios
    autoGuardar();   // Evidencia  el cambio en el archivo
    return true;
}

bool Red::eliminarEnrutador(const string& nombre) {
    map<string, Enrutador>::iterator it = enrutadores.find(nombre);
    if (it == enrutadores.end())
        return false;

    // quitar este enrutador de la lista de vecinos de los demas
    for (map<string, Enrutador>::iterator r = enrutadores.begin();
         r != enrutadores.end(); ++r) {
        r->second.eliminarVecino(nombre);
    }
    enrutadores.erase(it);
    recalcularTablas();
    autoGuardar();
    return true;
}

bool Red::agregarEnlace(const string& a, const string& b, int costo) {
    if (a == b || costo <= 0)
        return false;
    map<string, Enrutador>::iterator ra = enrutadores.find(a);
    map<string, Enrutador>::iterator rb = enrutadores.find(b);
    if (ra == enrutadores.end() || rb == enrutadores.end())
        return false;

    ra->second.agregarVecino(b, costo);   // enlace bidireccional
    rb->second.agregarVecino(a, costo);
    recalcularTablas();
    autoGuardar();
    return true;
}

bool Red::eliminarEnlace(const string& a, const string& b) {
    map<string, Enrutador>::iterator ra = enrutadores.find(a);
    map<string, Enrutador>::iterator rb = enrutadores.find(b);
    if (ra == enrutadores.end() || rb == enrutadores.end())
        return false;

    ra->second.eliminarVecino(b);
    rb->second.eliminarVecino(a);
    recalcularTablas();
    autoGuardar();
    return true;
}

// PARTE 1 y 2

// Añadidura del parametro previo
map<string, int> Red::calcularCostos(const string& origen, map<string, string>* previo)
    const { map<string, int> dist;

    dist[origen] = 0;

    // Se repite como maximo (n-1) veces: un camino minimo tiene a lo sumo n-1 enlaces
    for (size_t i = 1; i < enrutadores.size(); ++i) {
        bool huboCambio = false;

        for (map<string, Enrutador>::const_iterator r = enrutadores.begin();
             r != enrutadores.end(); ++r) {

            if (!dist.count(r -> first))
                continue;   // aun no se llega a este enrutador

            const map<string, int>& vecinos = r -> second.getVecinos();
            for (map<string, int>::const_iterator v = vecinos.begin();
                 v != vecinos.end(); ++v) {
                int nuevoCosto = dist[r -> first] + v -> second;
                if (!dist.count(v -> first) || nuevoCosto < dist[v -> first]) {
                    dist[v -> first] = nuevoCosto;
                    if (previo)   // Parametro previo
                        (*previo)[v -> first] = r -> first;  // llegamos a v desde r
                    huboCambio = true;
                }
            }
        }
        if (!huboCambio)
            break;   // ya no mejora nada
    }
    return dist;
}

// PARTE 2
void Red::recalcularTablas() {
    for (map<string, Enrutador>::iterator r = enrutadores.begin();
         r != enrutadores.end(); ++r) {
        r->second.actualizarTabla(calcularCostos(r->first));
    }
}

bool Red::obtenerCamino(const string& origen, const string& destino,vector<string>& camino, int& costo)
    const {
    camino.clear();
    costo = -1;
    if (!enrutadores.count(origen) || !enrutadores.count(destino))
        return false;

    map<string, string> previo;
    map<string, int> dist = calcularCostos(origen, &previo);

    map<string, int>::const_iterator d = dist.find(destino);
    if (d == dist.end())
        return false;   // no hay ruta (SINC)

    // Se reconstruye desde el destino hacia el origen y luego se invierte
    string actual = destino;
    camino.insert(camino.begin(), actual);
    while (actual != origen) {
        actual = previo[actual];
        camino.insert(camino.begin(), actual);   // siempre al inicio
    }
    costo = d -> second;
    return true;
}

// PARTE 1

void Red::mostrarTablas() const {
    if (enrutadores.empty()) {
        cout << "La red esta vacia." << endl;
        return;
    }

    cout << "\t";
    for (map<string, Enrutador>::const_iterator c = enrutadores.begin();
         c != enrutadores.end(); ++c)
        cout << c->first << "\t";
    cout << endl;

    for (map<string, Enrutador>::const_iterator f = enrutadores.begin();
         f != enrutadores.end(); ++f) {
        cout << f->first << "\t";
        for (map<string, Enrutador>::const_iterator c = enrutadores.begin();
             c != enrutadores.end(); ++c) {
            int costo = f->second.getCostoA(c->first);
            if (costo < 0) cout << "SINC\t";
            else           cout << costo << "\t";
        }
        cout << endl;
    }
}

// PARTE 2
bool Red::cargarDesdeArchivo(const string& ruta) {
    ifstream archivo(ruta.c_str());    // en cargarDesdeArchivo
    if (!archivo.is_open())
        return false;

    rutaArchivo = "";   //Durante la carga no se reescribe el archivo
    limpiar();
    string linea;
    int numLinea = 0;
    while (getline(archivo, linea)) {
        ++numLinea;

        istringstream lector (linea);
        string E1, E2, E3; // Enrutadores
        if (!(lector >> E1) || E1[0] == '+')
            continue;                        // linea vacia o comentario

        if (!(lector >> E2)) {                   // un solo dato: enrutador
            agregarEnrutador(E1);
            continue;
        }
        if (!(lector >> E3)) {
            cout << "Linea " << numLinea << ":faltan datos. Use 'A B costo' para un enlace o 'A' para un enrutador." << endl;
            continue;
        }
        int costo = 0;
        istringstream conv(E3);
        if (!(conv >> costo))
            costo = 0;   // no era un numero ,  agregarEnlace lo rechaza costo <= 0
        agregarEnrutador(E1);   // si ya existe, no hace nada
        agregarEnrutador(E2);
        if (!agregarEnlace(E1, E2, costo))
            cout << "Linea " << numLinea << ":enlace no valido. El costo debe ser un numero mayor a 0 y los enrutadores deben ser distintos." << endl;
    }
    archivo.close();
    recalcularTablas();
    rutaArchivo = ruta;   //Cada cambio se guarda en este archivo
    return true;
}

bool Red::guardarEnArchivo(const string& ruta) const {
    ofstream archivo(ruta.c_str());
    if (!archivo.is_open())
        return false;

    archivo << "+ Red de enrutadores" << endl;
    for (map<string, Enrutador>::const_iterator r = enrutadores.begin();
         r != enrutadores.end(); ++r) {
        const map<string, int>& vec = r -> second.getVecinos();
        if (vec.empty())
            archivo << r -> first << endl;     // enrutador aislado
        for (map<string, int>::const_iterator v = vec.begin(); v != vec.end(); ++v) {
            if (r -> first < v -> first)         // cada enlace una sola vez
                archivo << r -> first << " " << v -> first << " " << v -> second << endl;
        }
    }
    archivo.close();
    return true;
}