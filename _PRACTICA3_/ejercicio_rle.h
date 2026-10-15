#ifndef EJERCICIO_RLE_H
#define EJERCICIO_RLE_H
#include <string>
std::string RLECompresion(const std::string& strTexto);
std::string RLEDescompresion(const std::string& strTexto);
unsigned char* rleComprimirBytes(const char* texto, int& longitud);
char* rleDescomprimirBytes(const unsigned char* datos, int longitud);
#endif
