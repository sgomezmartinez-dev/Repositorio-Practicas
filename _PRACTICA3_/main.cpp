#include <iostream>
#include <string>
#include <cstring>
#include "ejercicio_lz78.h"
#include "ejercicio_rle.h"
#include "encriptacion_desencriptacion.h"
using namespace std;
int main() {
    int x = 0;
    cout << "1. LZ78 (comprimir y descomprimir)\n"
         << "2. RLE (comprimir y descomprimir)\n"
         << "3. RLE (descomprimir una cadena, ej: 3A2B)\n"
         << "4. Encriptar y desencriptar texto\n";
    cout << "Ingrese el problema que desea ejecutar ( | 1 | 2 | 3 | 4 | ):" << endl;
    cin >> x;
    char texto[256];
    int n = 0, k = 0, longitud = 0, cantidad = 0;
    unsigned char K = 0;
    const unsigned char* datos = nullptr;
    Entry* pares = nullptr;
    char* rec = nullptr;
    unsigned char* cifrado = nullptr;
    unsigned char* recuperado = nullptr;

    try {
        switch (x) {

        case 1: {   // ===== LZ78 =====
            cout << "Texto a comprimir: ";
            cin.width(256);
            cin >> texto;

            pares = comprimirLZ78(texto, cantidad);
            imprimirPares(pares, cantidad);

            rec = descomprimirLZ78(pares, cantidad);
            cout << "Texto descomprimido: " << rec << endl;

            verificarTexto(texto, rec);
            cout << "Verificacion: los textos son IDENTICOS\n";
            break;
        }

        case 2: {   // ===== RLE (aqui si se permite std::string) =====
            string cadena;
            cout << "Texto a comprimir (sin numeros): ";
            cin >> cadena;

            string comprimido = RLECompresion(cadena);
            cout << "Comprimido: " << comprimido << endl;

            string descomprimido = RLEDecompresion(comprimido);
            cout << "Descomprimido: " << descomprimido << endl;

            if (descomprimido == cadena)
                cout << "Verificacion: los textos son IDENTICOS\n";
            else
                cout << "Verificacion: los textos son DIFERENTES\n";
            break;
        }

        case 3: {   // ===== RLE: solo descomprimir =====
            string cadena;
            cout << "Cadena RLE (ej: 3A2B1C): ";
            cin >> cadena;
            cout << "Descomprimido: " << RLEDecompresion(cadena) << endl;
            break;
        }

        case 4: {   // ===== Encriptacion / desencriptacion =====
            cout << "Texto a encriptar: ";
            cin.width(256);
            cin >> texto;

            cout << "Rotacion n (0 < n < 8): ";
            cin >> n;
            cout << "Clave K (0 - 255): ";
            cin >> k;
            if (k < 0 || k > 255)
                throw "La clave K debe estar entre 0 y 255";
            K = (unsigned char)k;

            longitud = (int)strlen(texto);
            datos = reinterpret_cast<const unsigned char*>(texto);

            cifrado = encriptar(datos, longitud, n, K);
            cout << "Encriptado (hex): ";
            imprimirHex(cifrado, longitud);

            recuperado = desencriptar(cifrado, longitud, n, K);
            cout << "Desencriptado: ";
            cout.write(reinterpret_cast<const char*>(recuperado), longitud);
            cout << endl;

            verificarBytes(datos, recuperado, longitud);
            cout << "Verificacion: los datos son IDENTICOS\n";
            break;
        }

        default:
            cout << "Opcion no valida.\n";
            break;
        }
    }
    catch (const char* msg) {
        cerr << "[Error const char*] " << msg << endl;
    }
    catch (const string& msg) {
        cerr << "[Error string] " << msg << endl;
    }
    catch (int codigo) {
        cerr << "[Error int] Codigo: " << codigo << endl;
    }
    catch (const ErrorLZ78& e) {
        cerr << "[ErrorLZ78] (" << e.codigo << ") " << e.mensaje << endl;
    }
    catch (const ErrorCifrado& e) {
        cerr << "[ErrorCifrado] (" << e.codigo << ") " << e.mensaje << endl;
    }
    catch (...) {
        cerr << "[Error desconocido]" << endl;
    }
    // ---------- Liberar memoria (siempre, haya o no error) ----------
    delete[] pares;
    delete[] rec;
    delete[] cifrado;
    delete[] recuperado;

    return 0;
}