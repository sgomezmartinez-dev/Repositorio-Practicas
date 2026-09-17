#include <iostream>
using namespace std;
#include <iostream>
/*Problema 1:Se necesita un programa que permita determinar la mínima combinación de billetes y monedas para
una cantidad de dinero determinada. Los billetes en circulación son de $50.000, $20.000, $10.000, $5.000, $2.000
y $1.000, y las monedas son de $500, $200, $100 y $50. Hacer un programa que entregue el número de billetes y monedas
de cada denominación para completar la cantidad deseada. Si por medio de los billetes y monedas disponibles no se puede
lograr la cantidad deseada, el sistema deberá decir lo que resta para lograrla. Use arreglos y ciclos para realizar el programa.
Ejemplo: si se ingresa 47810, el programa debe imprimir:
50000 : 0
20000: 2
10000 : 0
5000: 1
2000 : 1
1000: 0
500 : 1
200: 1
100 : 1
50: 0
Faltante: 10

Problema 3:Haga una función que compare 2 cadenas de caracteres y retorno un valor lógico verdadero si son
iguales y falso en caso contrario, no olvide también tener en cuenta la longitud de las cadenas. Escriba un programa
de prueba.

Problema 5:Haga una función que reciba un numero entero (int) y lo convierta a cadena de caracteres. Use
parámetros por referencia para retornar la cadena. Escriba un programa de prueba.
Ejemplo: si recibe un int con valor 123, la cadena que se retorne debe ser “123”.

Problema 7: Escriba un programa que reciba una cadena de caracteres y elimine los caracteres repetidos.
Ejemplo: se recibe bananas debe mostrar bans.
Nota: la salida del programa debe ser: Original: bananas. Sin repetidos: bans.

Problema 9: Escriba un programa que reciba una cadena de caracteres y elimine los caracteres repetidos.
Ejemplo: se recibe bananas debe mostrar bans.
Nota: la salida del programa debe ser: Original: bananas. Sin repetidos: bans.

Problema 11:MEDIO Escriba un programa que permita manejar las reservas de asientos en una sala de cine, los asientos de
la sala de cine están organizados en 15 filas con 20 asientos cada una. El programa debe mostrar una representación
de la sala que indique que asientos están disponibles y cuales se encuentran reservados. Además debe permitir
realizar reservas o cancelaciones al ingresar la fila (letras A-O) y el número del asiento (números 1-20).
Nota: un ejemplo de visualización de una sección de la sala es el siguiente:
+ + + +
- - + +
- - - -
Donde + representa los asientos reservados y - representa los asientos disponibles.

Problema 13: Se tiene una fotografía digitalizada de una porción de la galaxia NGC 1300 que está ubicada a
61.000.000 de años luz del planeta Tierra. La representación digital de la imagen está constituida por una matriz
de números enteros; en la cual, cada uno representa la cantidad de luz en ese punto de la imagen, así:

Se puede determinar si el elemento ai,j de la matriz representa una estrella si se cumple que:

ai,j + ai,j−1 + ai,j+1 + ai−1,j + ai+1,j / 5 > 6 (1)
Elabore y pruebe una función que reciba un puntero a la matriz de enteros como argumento y que retorne el número
de estrellas encontradas en la imagen. Ignore las posibles estrellas que puedan existir en los bordes de la matriz.

Problema 15: Elabore un programa que permita hallar la intersección entre un par de rectángulos. Represente
los rectángulos como arreglos de 4 datos de la siguiente manera:
Los primeros 2 datos corresponden a las coordenadas de la esquina superior izquierda del rectángulo (x,y)
como se observa en la Figura 5.
Los siguientes 2 datos representan el ancho y la altura del rectángulo como se observa en la Figura 5.

Implemente una función que reciba 2 arreglos que representen los rectángulos A y B, y por referencia retorne un
rectángulo C (con la misma estructura descrita anteriormente) que corresponda a la intersección de A y B como se
observa en la Figura 6.Elabore un programa que permita hallar la intersección entre un par de rectángulos. Represente
los rectángulos como arreglos de 4 datos de la siguiente manera:
Los primeros 2 datos corresponden a las coordenadas de la esquina superior izquierda del rectángulo (x,y)
como se observa en la Figura 5.
Los siguientes 2 datos representan el ancho y la altura del rectángulo como se observa en la Figura 5.

Figura 5: Parámetros del rectángulo.

Implemente una función que reciba 2 arreglos que representen los rectángulos A y B, y por referencia retorne un
rectángulo C (con la misma estructura descrita anteriormente) que corresponda a la intersección de A y B como se
observa en la Figura 6.
*/















































    /*
    case 3: {
        char cad1[100];
        char cad2[100];
        cout << "Ingrese la primera cadena:" << endl;
        cin >> cad1;
        cout << "Ingrese la segunda cadena:" << endl;
        cin >> cad2;
        bool iguales = problema3(cad1, cad2);
        cout << "Resultado: " << (iguales ? "Las cadenas son iguales" : "Las cadenas son diferentes") << endl;
    }
    break;

    case 5: {
        int numero;
        char resultado[20];
        cout << "Ingrese un numero entero:" << endl;
        cin >> numero;
        problema5(numero, resultado);
        cout << "La cadena resultante es: \"" << resultado << "\"" << endl;
    }
    break;

    case 7: {
        char original[200];
        char resultado[200];
        cout << "Ingrese una cadena (sin espacios):" << endl;
        cin >> original;
        problema7(original, resultado);
        cout<<"Resultado: " << resultado << endl;
    }
    break;

    case 9: {
        char numeros[200];
        int n;
        cout << "Ingrese la cadena numerica:" << endl;
        cin >> numeros;
        cout << "Ingrese el valor de n:" << endl;
        cin >> n;
        long long suma = problema9(numeros, n);
        cout << "Original: " << numeros << "." << endl;
        cout << "Suma: " << suma << endl;
    }
    break;

    case 11: {

    }
    break;

    case 13: {
        const int FILAS13 = 6, COLS13 = 8;
        int imagen[FILAS13][COLS13] = {
            {0, 3, 4, 0, 0, 0, 6, 8},
            {5, 13, 6, 0, 0, 0, 2, 3},
            {2, 6, 2, 7, 3, 0, 10, 0},
            {0, 0, 4, 15, 4, 1, 6, 0},
            {0, 0, 7, 12, 6, 9, 10, 4},
            {5, 0, 6, 10, 6, 4, 8, 0}
        };
        // Se pasa la direccion del primer elemento de la matriz (puntero)
        int estrellas = problema13(&imagen[0][0], FILAS13, COLS13);
        cout << "Numero de estrellas encontradas: " << estrellas << endl;
    }
    break;

    case 15: {

    }
    break;

    case 17: {

    }
    break;
    }

    return 0;
}
*/