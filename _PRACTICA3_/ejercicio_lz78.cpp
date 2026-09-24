#include "ejercicio_lz78.h"
#include <iostream>
#include <cstring>
using namespace std;
void lanzarError(int codigo, const char* mensaje) {
    throw ErrorLZ78{codigo, mensaje};
}
// 1 DICCIONARIO
void dicInicializar(Diccionario& d, int capInicial) {
    if (capInicial < 1)
        lanzarError(ERR_CAPACIDAD, "La capacidad inicial debe ser >= 1");
    d.datos = new Entry[capInicial];
    d.tam = 1;                    // la posicion 0 es la frase vacia
    d.capacidad = capInicial;
    d.datos[0].indice = 0;
    d.datos[0].caracter = '\0';
}
void dicLiberar(Diccionario& d) {
    delete[] d.datos;
    d.datos = nullptr;
    d.tam = 0;
    d.capacidad = 0;
}
void dicRedimensionar78(Diccionario& d) {
    int nuevaCap = d.capacidad * 2;
    Entry* nuevo = new Entry[nuevaCap];
    for (int i = 0; i < d.tam; i++)
        nuevo[i] = d.datos[i];
    delete[] d.datos;
    d.datos = nuevo;
    d.capacidad = nuevaCap;
}
int dicBuscar(const Diccionario& d, int indice, char caracter) {
    for (int i = 1; i < d.tam; i++) {
        if (d.datos[i].indice == indice && d.datos[i].caracter == caracter)
            return i;
    }
    return -1;
}
int dicAgregar(Diccionario& d, int indice, char caracter) {
    if (indice < 0 || indice >= d.tam)
        lanzarError(ERR_PREFIJO_INEXIST, "Prefijo inexistente en el diccionario");
    if (d.tam == d.capacidad)
        dicRedimensionar78(d);
    d.datos[d.tam].indice = indice;
    d.datos[d.tam].caracter = caracter;
    return d.tam++;
}
const Entry& dicObtener(const Diccionario& d, int i) {
    if (i < 0 || i >= d.tam)
        lanzarError(ERR_INDICE_FUERA, "Indice fuera del diccionario");
    return d.datos[i];
}
int dicLongitudFrase(const Diccionario& d, int i) {
    dicObtener(d, i);             // valida el indice
    int largo = 0;
    while (i != 0) {
        largo++;
        i = d.datos[i].indice;
    }
    return largo;
}
int dicEscribirFrase(const Diccionario& d, int i, char* destino) {
    int largo = dicLongitudFrase(d, i);
    int pos = largo - 1;
    while (i != 0) {
        destino[pos--] = d.datos[i].caracter;
        i = d.datos[i].indice;
    }
    return largo;
}
// 2 COMPRESION
Entry* comprimirLZ78(const char* texto, int& cantidad) {
    if (texto == nullptr)
        lanzarError(ERR_TEXTO_NULO, "El texto es nulo");
    if (texto[0] == '\0')
        lanzarError(ERR_TEXTO_VACIO, "El texto esta vacio");

    int n = (int)strlen(texto); // longitud del texto n
    Diccionario dic;
    dicInicializar(dic, 16);
    Entry* salida = nullptr;
    try {
        salida = new Entry[n + 1];

        cantidad = 0; //recorre caracter c
        int prefijo = 0;
        for (int i = 0; texto[i] != '\0'; i++) {
            char c = texto[i];
            int idx = dicBuscar(dic, prefijo, c); // busca en si la combinación ya existe

            if (idx != -1) { // si ya existe
                prefijo = idx;// actualiza
            } else { // sino
                salida[cantidad].indice = prefijo; // Se guarda el nuevo cracter en salida que contiene el prefijo anterior
                salida[cantidad].caracter = c; // guarda el caracter actual c
                cantidad++;
                dicAgregar(dic, prefijo, c);
                prefijo = 0;
            }
        }
        if (prefijo != 0) {
            salida[cantidad].indice = prefijo;
            salida[cantidad].caracter = '\0';
            cantidad++; //Para no perder esta información, se emite un último token apuntando a ese prefijo y acompañado del carácter nulo \0
        }
    } catch (...) {
        // Si algo falla, se libera todo y se relanza la misma excepcion
        delete[] salida;
        dicLiberar(dic);
        throw;
    }

    dicLiberar(dic);
    return salida;
}
// 2 DESCOMPRESION
void asegurarCapacidad78(char*& buf, int& cap, int necesario) { //gestor de memoria dinámica
    if (necesario <= cap) return;
    int nuevaCap = cap * 2;
    if (nuevaCap < necesario) nuevaCap = necesario;
    char* nuevo = new char[nuevaCap];
    memcpy(nuevo, buf, cap); //copiar un bloque de memoria de un lugar a otro byte por byte
    delete[] buf;
    buf = nuevo;
    cap = nuevaCap;
}
char* descomprimirLZ78(const Entry* pares, int cantidad) {
    if (pares == nullptr || cantidad <= 0)
        lanzarError(ERR_PARES_NULOS, "No hay pares para descomprimir");

    Diccionario dic;
    dicInicializar(dic, 16);
    int cap = 64; // capacidad inical
    int len = 0;
    char* out = nullptr;

    try {
        out = new char[cap];

        for (int k = 0; k < cantidad; k++) { // recorre cada par del arreglo comprimido
            int prefijo = pares[k].indice;
            char c = pares[k].caracter;
            if (prefijo < 0 || prefijo >= dic.tam)
                lanzarError(ERR_INDICE_FUERA, "Par invalido: el indice no existe en el diccionario");

            int lp = dicLongitudFrase(dic, prefijo);
            int extra = (c != '\0') ? 1 : 0;
            asegurarCapacidad78(out, cap, len + lp + extra + 1);

            dicEscribirFrase(dic, prefijo, out + len);
            len += lp;

            if (c != '\0') {
                out[len++] = c;
                dicAgregar(dic, prefijo, c);
            } else if (k != cantidad - 1) {
                lanzarError(ERR_TERMINADOR, "Terminador '\\0' antes del ultimo par");
            }
        }
        out[len] = '\0';
    } catch (...) {
        delete[] out;
        dicLiberar(dic);
        throw;
    }

    dicLiberar(dic);
    return out;
}
// 3 Verificacion y salida
void verificarTexto(const char* original, const char* reconstruido) {
    if (original == nullptr || reconstruido == nullptr)
        lanzarError(ERR_TEXTO_NULO, "Texto nulo en la verificacion");
    if (strcmp(original, reconstruido) != 0)
        lanzarError(ERR_VERIFICACION, "El texto reconstruido NO es identico al original");
}

void imprimirPares(const Entry* pares, int cantidad) {
    cout << "Salida (indice, caracter):\n";
    for (int i = 0; i < cantidad; i++) {
        cout << "(" << pares[i].indice << ", ";
        if (pares[i].caracter == '\0') cout << "\\0";
        else cout << pares[i].caracter;
        cout << ")\n";
    }
}