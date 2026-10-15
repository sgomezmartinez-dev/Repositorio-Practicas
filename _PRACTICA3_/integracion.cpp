#include "integracion.h"
#include "ejercicio_lz78.h"
#include "ejercicio_rle.h"
#include "encriptacion_desencriptacion.h"
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

const int BYTES_POR_PAR = 5;   // 4 bytes del indice + 1 byte del caracter

// Archivos
char* leerArchivo(const char* ruta, int& longitud) {
    ifstream f(ruta, ios::binary);
    if (!f.is_open())
        throw "No se pudo abrir el archivo de entrada";

    f.seekg(0, ios::end); //Mueve el cursor de lectura a una posición del archivo.
    longitud = (int)f.tellg(); // Devuelve la posición actual del cursor de lectura
    f.seekg(0, ios::beg);
    if (longitud <= 0)
        throw 101;                         // codigo: archivo vacio

    char* buf = new char[longitud + 1];    // memoria dinamica: tamano desconocido
    f.read(buf, longitud);
    buf[longitud] = '\0';
    return buf;
}

void escribirArchivo(const char* ruta, const char* datos, int longitud) {
    ofstream f(ruta, ios::binary);
    if (!f.is_open())
        throw "No se pudo abrir el archivo de salida";
    f.write(datos, longitud);
}


static unsigned char* paresABytes(const Entry* pares, int cantidad) {
    unsigned char* b = new unsigned char[cantidad * BYTES_POR_PAR];
    for (int i = 0; i < cantidad; i++) {
        unsigned int v = (unsigned int)pares[i].indice;
        b[i * 5 + 0] = (unsigned char)(v & 0xFF);
        b[i * 5 + 1] = (unsigned char)((v >> 8) & 0xFF);
        b[i * 5 + 2] = (unsigned char)((v >> 16) & 0xFF);
        b[i * 5 + 3] = (unsigned char)((v >> 24) & 0xFF);
        b[i * 5 + 4] = (unsigned char)pares[i].caracter;
    }
    return b;
}

static Entry* bytesAPares(const unsigned char* b, int longitud, int& cantidad) {
    if (longitud % BYTES_POR_PAR != 0)
        throw "Datos LZ78 corruptos: longitud no multiplo de 5";
    cantidad = longitud / BYTES_POR_PAR;
    Entry* pares = new Entry[cantidad];
    for (int i = 0; i < cantidad; i++) {
        unsigned int v = (unsigned int)b[i * 5]
                         | ((unsigned int)b[i * 5 + 1] << 8)
                         | ((unsigned int)b[i * 5 + 2] << 16)
                         | ((unsigned int)b[i * 5 + 3] << 24);
        pares[i].indice = (int)v;
        pares[i].caracter = (char)b[i * 5 + 4];
    }
    return pares;
}

// Seleccion de metodo
unsigned char* comprimirTexto(int metodo, const char* texto, int& longitud) {
    if (metodo == 1) {                       // LZ78
        int ¿cantidad = 0;
        Entry* pares = comprimirLZ78(texto, cantidad);
        unsigned char* bytes = paresABytes(pares, cantidad);
        delete[] pares;
        longitud = cantidad * BYTES_POR_PAR;
        return bytes;
    }
    if (metodo == 2)                         // RLE
        return rleComprimirBytes(texto, longitud);

    throw string("Metodo de compresion invalido");
}

char* descomprimirBytes(int metodo, const unsigned char* datos, int longitud) {
    if (metodo == 1) {
        int cantidad = 0;
        Entry* pares = bytesAPares(datos, longitud, cantidad);
        char* out = nullptr;
        try {
            out = descomprimirLZ78(pares, cantidad);
        } catch (...) {
            delete[] pares;
            throw;
        }
        delete[] pares;
        return out;
    }
    if (metodo == 2)
        return rleDescomprimirBytes(datos, longitud);

    throw string("Metodo de descompresion invalido");
}

//  Flujo completo
void ejecutarIntegracion() {
    int metodo = 0, n = 0, k = 0;
    char rutaEntrada[256], rutaSalida[256];

    cout << "Metodo (1 = LZ78, 2 = RLE): ";
    cin >> metodo;
    cout << "Archivo de entrada: ";
    cin >> rutaEntrada;
    cout << "Archivo de salida: ";
    cin >> rutaSalida;
    cout << "Rotacion n (0 < n < 8): ";
    cin >> n;
    cout << "Clave K (0 - 255): ";
    cin >> k;

    if (n < 1 || n > 7)
        throw "La rotacion n debe estar entre 1 y 7";
    if (k < 0 || k > 255)
        throw "La clave K debe estar entre 0 y 255";
    unsigned char K = (unsigned char)k;

    char* original = nullptr;
    unsigned char* comprimido = nullptr;
    unsigned char* cifrado = nullptr;
    unsigned char* descifrado = nullptr;
    char* final = nullptr;
    char* releido = nullptr;

    try {
        int lenOrig = 0, lenComp = 0, lenSalida = 0, lenReleido = 0;

        // 1-2. Leer y comprimir
        original = leerArchivo(rutaEntrada, lenOrig);
        comprimido = comprimirTexto(metodo, original, lenComp);
        cout << "Original: " << lenOrig << " bytes | Comprimido: " << lenComp << " bytes\n";

        // 3. Encriptar
        cifrado = encriptar(comprimido, lenComp, n, K);
        cout << "Encriptado (hex): ";
        imprimirHex(cifrado, lenComp);

        // 4. Desencriptar y descomprimir
        descifrado = desencriptar(cifrado, lenComp, n, K);
        final = descomprimirBytes(metodo, descifrado, lenComp);

        // 5. Escribir y verificar contra el original
        lenSalida = (int)strlen(final);
        escribirArchivo(rutaSalida, final, lenSalida);

        releido = leerArchivo(rutaSalida, lenReleido);
        if (lenReleido != lenOrig || memcmp(original, releido, lenOrig) != 0)
            throw ErrorLZ78{ERR_VERIFICACION, "El texto final NO coincide con el original"};

        cout << "Verificacion: el archivo de salida es IDENTICO al original\n";
    } catch (...) {
        delete[] original; delete[] comprimido; delete[] cifrado;
        delete[] descifrado; delete[] final; delete[] releido;
        throw;
    }
    delete[] original; delete[] comprimido; delete[] cifrado;
    delete[] descifrado; delete[] final; delete[] releido;
}