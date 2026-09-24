#ifndef ENCRIPTACION_DESENCRIPTACION_H
#define ENCRIPTACION_DESENCRIPTACION_H
struct ErrorCifrado {
    int codigo;
    const char* mensaje;
};
unsigned char rotarIzquierda(unsigned char byte, int n);
unsigned char rotarDerecha(unsigned char byte, int n);
unsigned char* encriptar(const unsigned char* datos, int longitud, int n, unsigned char K);
unsigned char* desencriptar(const unsigned char* datos, int longitud, int n, unsigned char K);
void verificarBytes(const unsigned char* a, const unsigned char* b, int longitud);
void imprimirHex(const unsigned char* datos, int longitud);
#endif
