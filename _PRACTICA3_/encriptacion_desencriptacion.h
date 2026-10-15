#ifndef ENCRIPTACION_DESENCRIPTACION_H
#define ENCRIPTACION_DESENCRIPTACION_H

unsigned char rotarIzquierda(unsigned char byte, int n);
unsigned char rotarDerecha(unsigned char byte, int n);
unsigned char* encriptar(const unsigned char* datos, int longitud, int n, unsigned char K);
unsigned char* desencriptar(const unsigned char* datos, int longitud, int n, unsigned char K);
void imprimirHex(const unsigned char* datos, int longitud);
void verificarBytes(const unsigned char* a, const unsigned char* b, int longitud);

#endif

