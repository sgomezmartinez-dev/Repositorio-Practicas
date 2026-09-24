#include "ejercicio_lz78.h"
#include <iostream>
#include <cstring>
using namespace std;
static void lanzarError(int codigo, const char* mensaje) {
    throw ErrorLZ78{codigo, mensaje};
}
template <typename T>
struct GuardaArreglo {
    T*& puntero;
    bool activo;
    GuardaArreglo(T*& p) : puntero(p), activo(true) {}
    ~GuardaArreglo() { if (activo) delete[] puntero; }
    void soltar() { activo = false; }
};
Diccionario::Diccionario(int capInicial) : datos(nullptr), tam(1), capacidad(capInicial) {
    if (capInicial < 1)
        lanzarError(ERR_CAPACIDAD, "La capacidad inicial debe ser >= 1");
    datos = new Entry[capacidad];
    datos[0].indice = 0;
    datos[0].caracter = '\0';
}
Diccionario::~Diccionario() {
    delete[] datos;
}
void Diccionario::redimensionar() {
    int nuevaCap = capacidad * 2;
    Entry* nuevo = new Entry[nuevaCap];
    for (int i = 0; i < tam; i++)
        nuevo[i] = datos[i];
    delete[] datos;
    datos = nuevo;
    capacidad = nuevaCap;
}
int Diccionario::buscar(int indice, char caracter) const {
    for (int i = 1; i < tam; i++) {
        if (datos[i].indice == indice && datos[i].caracter == caracter)
            return i;
    }
    return -1;
}
int Diccionario::agregar(int indice, char caracter) {
    if (indice < 0 || indice >= tam)
        lanzarError(ERR_PREFIJO_INEXIST, "Prefijo inexistente en el diccionario");
    if (tam == capacidad)
        redimensionar();
    datos[tam].indice = indice;
    datos[tam].caracter = caracter;
    return tam++;
}
const Entry& Diccionario::obtener(int i) const {
    if (i < 0 || i >= tam)
        lanzarError(ERR_INDICE_FUERA, "Indice fuera del diccionario");
    return datos[i];
}
int Diccionario::tamanio() const {
    return tam;
}
int Diccionario::longitudFrase(int i) const {
    obtener(i);
    int largo = 0;
    while (i != 0) {
        largo++;
        i = datos[i].indice;
    }
    return largo;
}
int Diccionario::escribirFrase(int i, char* destino) const {
    int largo = longitudFrase(i);
    int pos = largo - 1;
    while (i != 0) {
        destino[pos--] = datos[i].caracter;
        i = datos[i].indice;
    }
    return largo;
}
// ================= Compresion =================
Entry* comprimirLZ78(const char* texto, int& cantidad) {
    if (texto == nullptr)
        lanzarError(ERR_TEXTO_NULO, "El texto es nulo");
    if (texto[0] == '\0')
        lanzarError(ERR_TEXTO_VACIO, "El texto esta vacio");
    int n = (int)strlen(texto);
    Diccionario dic;
    Entry* salida = new Entry[n + 1];
    GuardaArreglo<Entry> guarda(salida);
    cantidad = 0;
    int prefijo = 0;
    for (int i = 0; texto[i] != '\0'; i++) {
        char c = texto[i];
        int idx = dic.buscar(prefijo, c);

        if (idx != -1) {
            prefijo = idx;
        } else {
            salida[cantidad].indice = prefijo;
            salida[cantidad].caracter = c;
            cantidad++;
            dic.agregar(prefijo, c);
            prefijo = 0;
        }
    }
    if (prefijo != 0) {
        salida[cantidad].indice = prefijo;
        salida[cantidad].caracter = '\0';
        cantidad++;
    }

    guarda.soltar();
    return salida;
}
// ================= Descompresion =================
static void asegurarCapacidad(char*& buf, int& cap, int necesario) {
    if (necesario <= cap) return;
    int nuevaCap = cap * 2;
    if (nuevaCap < necesario) nuevaCap = necesario;
    char* nuevo = new char[nuevaCap];
    memcpy(nuevo, buf, cap);
    delete[] buf;
    buf = nuevo;
    cap = nuevaCap;
}
char* descomprimirLZ78(const Entry* pares, int cantidad) {
    if (pares == nullptr || cantidad <= 0)
        lanzarError(ERR_PARES_NULOS, "No hay pares para descomprimir");
    Diccionario dic;
    int cap = 64;
    int len = 0;
    char* out = new char[cap];
    GuardaArreglo<char> guarda(out);
    for (int k = 0; k < cantidad; k++) {
        int prefijo = pares[k].indice;
        char c = pares[k].caracter;
        if (prefijo < 0 || prefijo >= dic.tamanio())
            lanzarError(ERR_INDICE_FUERA, "Par invalido: el indice no existe en el diccionario");
        int lp = dic.longitudFrase(prefijo);
        int extra = (c != '\0') ? 1 : 0;
        asegurarCapacidad(out, cap, len + lp + extra + 1);
        dic.escribirFrase(prefijo, out + len);
        len += lp;
        if (c != '\0') {
            out[len++] = c;
            dic.agregar(prefijo, c);
        } else if (k != cantidad - 1) {
            lanzarError(ERR_TERMINADOR, "Terminador '\\0' antes del ultimo par");
        }
    }
    out[len] = '\0';
    guarda.soltar();
    return out;
}
// ================= Verificacion y salida =================
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