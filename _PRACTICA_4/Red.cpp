#include "Red.h"
#include <iostream>

Red::Red() {}

bool Red::agregarEnrutador(const string& nombre) {
    if (nombre.empty() || enrutadores.count(nombre))
        return false;
    enrutadores[nombre] = Enrutador(nombre);
    return true;
}

bool Red::eliminarEnrutador(const string& nombre) {
    map<string, Enrutador>::iterator it = enrutadores.find(nombre);
    if (it == enrutadores.end())
        return false;

    // quitar este enrutador de la lista de vecinos de los demas
    for (map<string, Enrutador>::iterator r = enrutadores.begin(); // Revisa desde el primero
         r != enrutadores.end(); ++r) {
        r->second.eliminarVecino(nombre);
    }
    enrutadores.erase(it);
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
    return true;
}

bool Red::eliminarEnlace(const string& a, const string& b) {
    map<string, Enrutador>::iterator ra = enrutadores.find(a);
    map<string, Enrutador>::iterator rb = enrutadores.find(b);
    if (ra == enrutadores.end() || rb == enrutadores.end()) //Distinguir si encontro algo o no
        return false;

    ra->second.eliminarVecino(b);
    rb->second.eliminarVecino(a);
    return true;
}
map<string, int> Red::calcularCostos(const string& origen) const {
    map<string, int> dist;
    dist[origen] = 0;

    // Se repite como maximo (n-1) veces: un camino minimo tiene a lo sumo n-1 enlaces
    for (size_t i = 1; i < enrutadores.size(); ++i) {
        bool huboCambio = false;

        // Se revisan todos los enlaces de todos los enrutadores ya alcanzados
        for (map<string, Enrutador>::const_iterator r = enrutadores.begin();
             r != enrutadores.end(); ++r) {

            if (!dist.count(r->first))
                continue;   // aun no se llega a este enrutador

            const map<string, int>& vecinos = r->second.getVecinos();
            for (map<string, int>::const_iterator v = vecinos.begin();
                 v != vecinos.end(); ++v) {
                int nuevoCosto = dist[r->first] + v->second;
                if (!dist.count(v->first) || nuevoCosto < dist[v->first]) {
                    dist[v->first] = nuevoCosto;
                    huboCambio = true;
                }
            }
        }
        if (!huboCambio)
            break;   // ya no mejora nada
    }
    return dist;
}
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