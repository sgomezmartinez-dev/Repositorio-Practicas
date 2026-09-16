#include <iostream>
#include "funciones.h"
using namespace std;
int main() {
    int x = 0;
    cout << "Ingrese el problema que desea ejecutar ( | 1 | 3 | 5 | 7 | 9 | 11 | 13 | 15 | 17 | ):" << endl;
    cin >> x;

    switch (x) {

    case 1: {
        const int denominaciones[10] = {50000, 20000, 10000, 5000, 2000, 1000, 500, 200, 100, 50};
        int dinero = 0;
        cout << "Ingrese la cantidad: ";
        cin >> dinero;
        problema1(denominaciones, 10, &dinero);
        if (dinero > 0) {
            cout << "Faltante: " << dinero << endl;
        }
        break;
    }

    case 3: {
        char cadena1[100];
        char cadena2[100];
        cout << "Ingrese la primera cadena: ";
        cin >> cadena1;
        cout << "Ingrese la segunda cadena: ";
        cin >> cadena2;
        if (problema3(cadena1, cadena2)) {
            cout << "Resultado: Las cadenas SON iguales." << endl;
        } else {
            cout << "Resultado: Las cadenas NO son iguales." << endl;
        }

        break;
    }
    case 5: {
        int numero = 0;
        char resultado[50];
        cout << "Ingrese un numero entero: ";
        cin >> numero;
        problema5(&numero, resultado);
        cout << "Cadena resultante: \"" << resultado << "\"" << endl;
        break;
    }
    case 7: {
        char original[100];
        char sinRepetidos[100] = "";
        cout << "Ingrese la cadena: ";
        cin >> original;
        problema7(original, sinRepetidos);
        cout << "Original: " << original << ". Sin repetidos: " << sinRepetidos << "." << endl;
        break;
    }

    case 9: {
        int n = 0;
        char cadenaNumerica[100];
        int sumaResultante = 0;
        cout << "Ingrese el valor de n: ";
        cin >> n;
        cout << "Ingrese la cadena numerica: ";
        cin >> cadenaNumerica;
        problema9(cadenaNumerica, &n, &sumaResultante);
        cout << "Original: " << cadenaNumerica << "." << endl;
        cout << "Suma: " << sumaResultante << "." << endl;
        break;
    }

    case 11: {
        const int FILAS = 15;
        const int COLS = 20;
        char sala[15 * 20];
        char accionInit = 'I';
        problema11(sala, &FILAS, &COLS, &accionInit, nullptr, nullptr);
        int subOpcion = 0;
        do {
            cout << "\n--- GESTION DE CINE ---" << endl;
            cout << "1. Ver estado de la sala" << endl;
            cout << "2. Reservar asiento (+)" << endl;
            cout << "3. Cancelar reserva (-)" << endl;
            cout << "4. Salir" << endl;
            cout << "Seleccione una opcion: ";
            cin >> subOpcion;

            if (subOpcion == 1) {
                char accionMostrar = 'M';
                problema11(sala, &FILAS, &COLS, &accionMostrar, nullptr, nullptr);
            } else if (subOpcion == 2 || subOpcion == 3) {
                char filaLetra;
                int numAsiento;
                char op = (subOpcion == 2) ? '+' : '-';

                cout << "Ingrese la letra de la fila (A-O): ";
                cin >> filaLetra;
                cout << "Ingrese el numero del asiento (1-20): ";
                cin >> numAsiento;

                problema11(sala, &FILAS, &COLS, &op, &filaLetra, &numAsiento);
            }
        } while (subOpcion != 4);
        break;
    }
    case 15: {
        int rectA[4];
        int rectB[4];
        int rectC[4];
        char c;
        cout << "Ingrese datos del Rectangulo A (x,y,ancho,alto): ";
        cin >> rectA[0] >> c >> rectA[1] >> c >> rectA[2] >> c >> rectA[3];
        cout << "Ingrese datos del Rectangulo B (x,y,ancho,alto): ";
        cin >> rectB[0] >> c >> rectB[1] >> c >> rectB[2] >> c >> rectB[3];
        problema15(rectA, rectB, rectC);
        cout << "Rectangulo interseccion C: {"
             << *(rectC + 0) << ", "
             << *(rectC + 1) << ", "
             << *(rectC + 2) << ", "
             << *(rectC + 3) << "}" << endl;
        break;
    }
    case 17: {
        int limite = 0;
        int sumaResultante = 0;
        cout << "Ingrese un numero N: ";
        cin >> limite;
        problema17(&limite, &sumaResultante);
        cout << "El resultado de la suma es: " << sumaResultante << "." << endl;
        break;
    }

    }

    return 0;
}