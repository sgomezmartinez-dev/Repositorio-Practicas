#ifndef INTEGRACION_H
#define INTEGRACION_H

char* leerArchivo(const char* ruta, int& longitud);
void escribirArchivo(const char* ruta, const char* datos, int longitud);

unsigned char* comprimirTexto(int metodo, const char* texto, int& longitud);
char* descomprimirBytes(int metodo, const unsigned char* datos, int longitud);

void ejecutarIntegracion();

#endif
