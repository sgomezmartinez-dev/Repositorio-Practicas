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
struct Entry {
    int indice;
    char caracter;
};
class Diccionario {
private:
    Entry* datos;
    int tam;
    int capacidad;

    void redimensionar();
public:
    Diccionario(int capInicial = 16);
    ~Diccionario();
    Diccionario(const Diccionario&) = delete;
    Diccionario& operator=(const Diccionario&) = delete;

    int buscar(int indice, char caracter) const;
    int agregar(int indice, char caracter);
    const Entry& obtener(int i) const;
    int tamanio() const;
    int longitudFrase(int i) const;
    int escribirFrase(int i, char* destino) const;
};
Entry* comprimirLZ78(const char* texto, int& cantidad);
char* descomprimirLZ78(const Entry* pares, int cantidad);
void verificarTexto(const char* original, const char* reconstruido);
void imprimirPares(const Entry* pares, int cantidad);
#endif