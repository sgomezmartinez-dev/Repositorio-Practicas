#include <iostream>
#include <string>
#include "Red.h"

using namespace std;

int main() {
    Red red;
    int opcion;

    // Enrutadores iniciales
    red.agregarEnrutador("A");
    red.agregarEnrutador("B");
    red.agregarEnrutador("C");
    red.agregarEnrutador("D");

    do {
        cout << "\n|******* SIMULADOR DE RED DE ENRUTADORES *******|\n" << endl;
        cout << "1.Mostrar tablas de costos " << endl;
        cout << "2.Agregar enrutador " << endl;
        cout << "3.Eliminar enrutador " << endl;
        cout << "4.Agregar enlace " << endl;
        cout << "5.Eliminar enlace " << endl;
        cout << "0. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 2: {
            string nombre;
            cout << "Nombre del nuevo enrutador: ";
            cin >> nombre;
            if (red.agregarEnrutador(nombre))
                cout << "Enrutador " << nombre << " agregado." << endl;
            else
                cout << "No se pudo agregar (el nombre ya existe)." << endl;
            break;
        }
        case 3: {
            string nombre;
            cout << "Nombre del enrutador a eliminar: ";
            cin >> nombre;
            if (red.eliminarEnrutador(nombre))
                cout << "Enrutador " << nombre << " eliminado." << endl;
            else
                cout << "No se pudo eliminar (no existe)." << endl;
            break;
        }
        case 4: {
            string a, b;
            int costo;
            cout << "Enrutador origen: ";
            cin >> a;
            cout << "Enrutador destino: ";
            cin >> b;
            cout << "Costo del enlace: ";
            cin >> costo;
            if (red.agregarEnlace(a, b, costo))
                cout << "Enlace " << a << " - " << b << " agregado." << endl;
            else
                cout << "No se pudo agregar (revise que existan, sean distintos y el costo sea mayor a 0)." << endl;
            break;
        }
        case 5: {
            string a, b;
            cout << "Enrutador origen: ";
            cin >> a;
            cout << "Enrutador destino: ";
            cin >> b;
            if (red.eliminarEnlace(a, b))
                cout << "Enlace " << a << " - " << b << " eliminado." << endl;
            else
                cout << "No se pudo eliminar (algun enrutador no existe)." << endl;
            break;
        }
        case 1:
            red.mostrarTablas();
            break;
        case 0:
            break;
        default:
            cout << "Opcion no valida." << endl;
        }

    } while (opcion != 0);

    cout << "Programa finalizado." << endl;
    return 0;
}