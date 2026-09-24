#include "encriptacion_desencriptacion.h"
#include <iostream>
using namespace std;
void validarParametrosED(const unsigned char* datos, int longitud, int n) {
    if (datos == nullptr)
        throw "El arreglo de datos es nulo";
    if (longitud <= 0)
        throw "La longitud debe ser mayor que 0";
    if (n <= 0 || n >= 8)
        throw "n debe estar entre 1 y 7";
}
unsigned char rotarIzquierda(unsigned char byte, int n) {
    if (n <= 0 || n >= 8)
        throw "n debe estar entre 1 y 7";
    return (unsigned char)((byte << n) | (byte >> (8 - n)));
}
unsigned char rotarDerecha(unsigned char byte, int n) {
    if (n <= 0 || n >= 8)
        throw "n debe estar entre 1 y 7";
    return (unsigned char)((byte >> n) | (byte << (8 - n)));
}
unsigned char* encriptar(const unsigned char* datos, int longitud, int n, unsigned char K) {
    validarParametrosED(datos, longitud, n);

    unsigned char* salida = new unsigned char[longitud];
    for (int i = 0; i < longitud; i++) {
        unsigned char b = rotarIzquierda(datos[i], n);
        salida[i] = b ^ K;
    }
    return salida;
}
unsigned char* desencriptar(const unsigned char* datos, int longitud, int n, unsigned char K) {
    validarParametrosED(datos, longitud, n);

    unsigned char* salida = new unsigned char[longitud];
    for (int i = 0; i < longitud; i++) {
        unsigned char b = datos[i] ^ K;
        salida[i] = rotarDerecha(b, n);
    }
    return salida;
}
void verificarBytes(const unsigned char* a, const unsigned char* b, int longitud) {
    if (a == nullptr || b == nullptr)
        throw "Arreglo nulo en la verificacion";
    for (int i = 0; i < longitud; i++) {
        if (a[i] != b[i])
            throw "Los datos recuperados NO son identicos a los originales";
    }
}
void imprimirHex(const unsigned char* datos, int longitud) {
    const char* hex = "0123456789ABCDEF";
    for (int i = 0; i < longitud; i++) {
        cout << hex[datos[i] >> 4] << hex[datos[i] & 0x0F] << ' ';
    }
    cout << endl;
}

