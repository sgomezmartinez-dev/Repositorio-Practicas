#include "funciones.h"
#include <iostream>
using namespace std;
void problema1(const int* denominaciones, int tamano, int* dinero) {
    for (int i = 0; i < tamano; i++) {
        int valorDenominacion = *(denominaciones + i);
        int cantidad = *dinero / valorDenominacion;
        cout << valorDenominacion << " : " << cantidad << endl;
        *dinero = *dinero % valorDenominacion;
    }
}

bool problema3(const char* cad1, const char* cad2) {
    int i = 0;
    while (*(cad1 + i) && *(cad2 + i)) {
        if (*(cad1 + i) != *(cad2 + i)) {
            return false;
        }
        i++;
    }
    return (!*(cad1 + i) && !*(cad2 + i));
}

void problema5(const int* numero, char* cadena) {
    int save = *numero;
    if (save == 0) {
        cadena[0] = '0';
        cadena[1] = 0;
        return;
    }
    bool esNegativo = save < 0;
    save = esNegativo ? -save : save;
    int saveCopia = save;
    int longitud = 0;
    while ( saveCopia > 0) {
        longitud++;
        saveCopia /= 10;
    }

    if (esNegativo) {
        longitud++;
    }
    cadena[longitud] = 0;
    int pos = longitud - 1;
    while (save > 0) {
        int digito = save % 10;
        cadena[pos] = 48 + digito;
        save /= 10;
        pos--;
    }

    if (esNegativo) {
        cadena[0] = '-';
    }
}
void problema7(const char* entrada, char* salida) {
    int i = 0;
    int j = 0;
    while (*(entrada + i) != '\0') {
        char caracterActual = *(entrada + i);
        bool existe = false;
        int k = 0;
        while (k < j) {
            if (*(salida + k) == caracterActual) {
                existe = true;
                break;
            }
            k++;
        }

        if (!existe) {
            *(salida + j) = caracterActual;
            j++;
            *(salida + j) = '\0';
        }

        i++;
    }
}


void problema9(const char* cadena, const int* n, int* resultadoSuma) {
    int len = 0;
    while (*(cadena + len) != '\0') {
        len++;
    }

    int tamBloque = *n;
    int residuo = len % tamBloque;
    int cerosAgregar = (residuo == 0) ? 0 : (tamBloque - residuo);

    int sumaTotal = 0;
    int i = 0;
    if (cerosAgregar > 0) {
        int primerNumero = 0;
        int digitosAReer = tamBloque - cerosAgregar;

        for (int k = 0; k < digitosAReer; k++) {
            primerNumero = primerNumero * 10 + (*(cadena + i) - '0');
            i++;
        }
        sumaTotal += primerNumero;
    }
    while (i < len) {
        int numeroBloque = 0;
        for (int k = 0; k < tamBloque && i < len; k++) {
            numeroBloque = numeroBloque * 10 + (*(cadena + i) - '0');
            i++;
        }
        sumaTotal += numeroBloque;
    }
    *resultadoSuma = sumaTotal;
}


void problema11(char* sala, const int* filas, const int* cols, const char* accion, const char* filaLetra, const int* numAsiento) {
    char op = *accion;
    if (op == 'I') {
        for (int f = 0; f < *filas; f++) {
            for (int c = 0; c < *cols; c++) {
                *(sala + f * (*cols) + c) = '-';
            }
        }
        return;
    }
    if (op == 'M') {
        cout << "\n    ";
        for (int c = 1; c <= *cols; c++) {
            cout << (c < 10 ? " " : "") << c << " ";
        }
        cout << "\n";
        for (int f = 0; f < *filas; f++) {
            char letraFila = 'A' + f;
            cout << letraFila << "  ";
            for (int c = 0; c < *cols; c++) {
                cout << " " << *(sala + f * (*cols) + c) << " ";
            }
            cout << "\n";
        }
        cout << endl;
        return;
    }
    if (op == '+' || op == '-') {
        char letra = *filaLetra;
        if (letra >= 'a' && letra <= 'z') {
            letra -= 32;
        }
        int f = letra - 'A';
        int c = *numAsiento - 1;

        if (f < 0 || f >= *filas || c < 0 || c >= *cols) {
            cout << "Error: Fila (A-O) o asiento (1-20) fuera del limite de la sala." << endl;
            return;
        }
        char* asientoPtr = sala + (f * (*cols) + c);

        if (op == '+') {
            if (*asientoPtr == '+') {
                cout << "El asiento " << letra << *numAsiento << " ya esta reservado." << endl;
            } else {
                *asientoPtr = '+';
                cout << "Reserva realizada exitosamente para el asiento " << letra << *numAsiento << "." << endl;
            }
        } else if (op == '-') {
            if (*asientoPtr == '-') {
                cout << "El asiento " << letra << *numAsiento << " se encuentra disponible." << endl;
            } else {
                *asientoPtr = '-';
                cout << "Reserva cancelada exitosamente para el asiento " << letra << *numAsiento << "." << endl;
            }
        }
    }
}

void problema13(const int* imagen, const int* filas, const int* cols, int* numEstrellas) {
    int f = *filas;
    int c = *cols;
    int contador = 0;

    // Se recorre la matriz omitiendo la primera y ultima fila/columna (bordes)
    for (int i = 1; i < f - 1; i++) {
        for (int j = 1; j < c - 1; j++) {
            // Lectura de intensidad del punto central y sus 4 vecinos con aritmetica de punteros 2D
            int centro    = *(imagen + i * c + j);
            int izquierda = *(imagen + i * c + (j - 1));
            int derecha   = *(imagen + i * c + (j + 1));
            int arriba    = *(imagen + (i - 1) * c + j);
            int abajo     = *(imagen + (i + 1) * c + j);

            // Calculo de la suma de intensidades en forma de cruz
            int suma = centro + izquierda + derecha + arriba + abajo;

            // Criterio de estrella: promedio > 6  <=>  suma > 30
            if (suma > 30) {
                contador++;
            }
        }
    }

    *numEstrellas = contador;
}

void problema15(const int* rectA, const int* rectB, int* rectC) {
    int xA = *(rectA + 0);
    int yA = *(rectA + 1);
    int wA = *(rectA + 2);
    int hA = *(rectA + 3);
    int xB = *(rectB + 0);
    int yB = *(rectB + 1);
    int wB = *(rectB + 2);
    int hB = *(rectB + 3);
    int xInicio = (xA > xB) ? xA : xB;
    int xFinA = xA + wA;
    int xFinB = xB + wB;
    int xFin = (xFinA < xFinB) ? xFinA : xFinB;
    int yInicio = (yA > yB) ? yA : yB;
    int yFinA = yA + hA;
    int yFinB = yB + hB;
    int yFin = (yFinA < yFinB) ? yFinA : yFinB;
    if (xInicio < xFin && yInicio < yFin) {
        *(rectC + 0) = xInicio;
        *(rectC + 1) = yInicio;
        *(rectC + 2) = xFin - xInicio;
        *(rectC + 3) = yFin - yInicio;
    } else {
        *(rectC + 0) = 0;
        *(rectC + 1) = 0;
        *(rectC + 2) = 0;
        *(rectC + 3) = 0;
    }
}

void problema17(const int* limite, int* resultadoSuma) {
    int a = *limite;
    int b = 0;
    for (int d = 1; d <= a / 2; d++) {
        if (a % d == 0) {
            b += d;
        }
    }
    int sumaB = 0;
    for (int d = 1; d <= b / 2; d++) {
        if (b % d == 0) {
            sumaB += d;
        }
    }
    if (sumaB == a && a != b) {
        *resultadoSuma = a + b;
    } else {
        *resultadoSuma = 0;
    }
}