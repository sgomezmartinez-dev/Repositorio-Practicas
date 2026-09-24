#ifndef EJERCICIO_LZ78_H
#define EJERCICIO_LZ78_H
struct ErrorLZ78 {
    int codigo;
    const char* mensaje;
};
const int ERR_TEXTO_NULO        = 1;
const int ERR_TEXTO_VACIO       = 2;
const int ERR_CAPACIDAD         = 3;
const int ERR_PARES_NULOS       = 4;
const int ERR_PREFIJO_INEXIST   = 5;
const int ERR_INDICE_FUERA      = 6;
const int ERR_TERMINADOR        = 7;
const int ERR_VERIFICACION      = 8;
// Cada entrada del diccionario es un par (prefijo, caracter)
struct Entry {
    int indice;
    char caracter;
};
// Diccionario: solo datos
struct Diccionario {
    Entry* datos;
    int tam;
    int capacidad;
};
//  Funciones  diccionario
void dicInicializar(Diccionario& d, int capInicial = 16);
void dicLiberar(Diccionario& d);
int dicBuscar(const Diccionario& d, int indice, char caracter);
int dicAgregar(Diccionario& d, int indice, char caracter);
const Entry& dicObtener(const Diccionario& d, int i);
int dicLongitudFrase(const Diccionario& d, int i);
int dicEscribirFrase(const Diccionario& d, int i, char* destino);
// Compresion Y descompresion
Entry* comprimirLZ78(const char* texto, int& cantidad);
char* descomprimirLZ78(const Entry* pares, int cantidad);
void verificarTexto(const char* original, const char* reconstruido);
void imprimirPares(const Entry* pares, int cantidad);
#endif