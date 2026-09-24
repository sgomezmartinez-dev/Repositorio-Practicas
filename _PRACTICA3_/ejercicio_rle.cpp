#include "ejercicio_rle.h"
#include <cctype>
std::string RLECompresion(const std::string& strTexto) {
    // Excepción 1: Cadena vacía (Lanza un const char*)
    if (strTexto.empty()) {
        throw " !!! ERROR ¡¡¡ CADENA DE ENTRADA INVALIDA , NO PUEDE ESTAR VACIA ";
    }

    // Excepción 2: Contiene números (Lanza un std::string)
    for (char c : strTexto) {
        if (std::isdigit(c)) {
            throw std::string("!!! ERROR ¡¡¡ CADENA DE ENTRADA INVALIDA , NO PUEDE CONTENER VALORES NUMERICOS  ");
        }
    }

    std::string result = "";
    int j = 1;

    for (size_t i = 0; i < strTexto.length(); i++) {
        if (i + 1 < strTexto.length() && strTexto[i] == strTexto[i + 1]) {
            j++;
        } else {
            result += std::to_string(j) + strTexto[i];
            j = 1;
        }
    }

    return result;
}
std::string RLEDescompresion(const std::string& strTexto) {
    // Excepción 3: Formato inválido (Lanza un código entero de error, ej: 707)
    if (strTexto.empty() || !std::isdigit(strTexto[0])) {
        throw 707;
    }

    std::string resultado = "";
    std::string acumulador = "";

    for (size_t i = 0; i < strTexto.length(); i++) {
        char c = strTexto[i];
        if (std::isdigit(c)) {
            acumulador += c;
        } else {
            if (acumulador.empty()) {
                throw 707;
            }
            int i = std::stoi(acumulador);
            resultado.append(i, c);
            acumulador = "";
        }
    }

    return resultado;
}