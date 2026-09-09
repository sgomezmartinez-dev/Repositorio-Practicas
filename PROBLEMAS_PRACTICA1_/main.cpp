#include <iostream>

using namespace std;

/* PROBLEMA 2:Se necesita un programa que permita determinar la mínima combinación de billetes
 y monedas para una cantidad de dinero determinada. Los billetes en circulación son de $50.000,
 $20.000, $10.000, $5.000, $2.000 y $1.000, y las monedas son de $500, $200, $100 y $50
Hacer un programa que entregue el número de billetes y monedas de cada denominación para completar la cantidad deseada.
Si por medio de los billetes y monedas disponibles no se puede lograr la cantidad deseada, el sistema deberá decir lo que resta para lograrla.
 Ej: si se ingresa 47810, el programa debe imprimir:
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

PROBLEMA 4: Escriba un programa para leer dos números enteros con el siguiente signicado: el
valor del primer número representa una hora del día en un reloj de 24 horas, de modo que 1245

representa las doce y cuarenta y cinco de la tarde. El segundo entero representa un tiempo de du-
ración de la misma manera, por lo que 345 representa tres horas y 45 minutos. El programa debe

sumar esta duración primer número, y el resultado será impreso en la misma notación, en este caso
1630, que es el tiempo de 3 horas y 45 minutos después de 12:45.
Nota: el formato de salida debe ser: La hora es 1630.
Otra nota: se debe imprimir un mensaje como el siguiente cuando uno de los datos ingresados en
inválido: 1560 es un tiempo invalido.


PROBLEMA 6:Escriba un programa que encuentre el valor aproximado del número de euler en base
a la siguiente suma infita:
e =1 / 0! + 1 / 1! + 1 /2! + 1 /3! + 1 / 4! + 1 / 5! + ... (2)

El usuario debe ingresar el número de elementos usados en la aproximación.
Ej: si se ingresa 3 e =
1/0! +1/1! +1/2! = 2,5
Nota: el formato de salida debe ser: e es aproximadamente: 2.5


PROBLEMA 8:Escriba un programa que reciba 3 números a, b, c, y calcule la suma de todos los
múltiplos de a y b que sean menores a c. Tenga en cuenta no sumar 2 veces los múltiplos comunes.
Ej: para a=3, b=5 y c=10. Se sumarían 3+6+9+5=23
Para a=5, b=7 y c=36. Se sumarían 5+10+15+20+25+30+35+7+14+21+28 = 210.
Nota: el formato de salida debe ser:
m11 + m12 + m13 + . . . + m21 + m22 + m23. . . = sumatoria.
m11 representa el primer múltiplo de a y así sucesivamente. m21 representa el primer múltiplo de b
y así sucesivamente.

PROBLEMA 10:Escriba un programa que reciba un número n e imprima el enésimo número primo.
Ej: Si recibe 4 el programa debe imprimir 7.
Nota: la salida del programa debe ser: El primo numero 4 es: 7.

PROBLEMA 12:Escriba un programa que calcula el máximo factor primo de un número.
Ej: Si se recibe 33 el programa debe imprimir 11.
Nota: la salida del programa debe ser: El mayor factor primo de 33 es: 11.

PROBLEMA 14:Un número palíndromo es igual de derecha a izquierda y de izquierda a derecha,
Ej: 969. escriba un programa que calcule el número palíndromo más grande que se puede obtener
como una multiplicación de números de 3 dígitos.
Ej: una de las posibles respuestas es: 143*777=111111.
Nota: la salida del programa debe ser: 143*777=111111

PROBLEMA 16:Un número palíndromo es igual de derecha a izquierda y de izquierda a derecha,
Ej: 969. escriba un programa que calcule el número palíndromo más grande que se puede obtener
como una multiplicación de números de 3 dígitos.
Ej: una de las posibles respuestas es: 143*777=111111.
Nota: la salida del programa debe ser: 143*777=111111

*/

void problema2 (int dinero){
     int A = 50000 ,B = 20000 ,C = 10000 , D = 5000 , E = 2000 , F = 1000 ,G = 500 , H=  200 , I = 100 , J = 50;
     int restante = dinero;
     int OPA =  restante  / A ;
     restante = restante % A;
     int OPB =  restante  / B ;
     restante = restante % B;
     int OPC =  restante  / C ;
     restante = restante % C;
     int OPD =  restante  / D ;
     restante = restante % D;
     int OPE =  restante  / E ;
     restante = restante % E;
     int OPF =  restante  / F ;
     restante = restante % F;
     int OPG =  restante  / G ;
     restante = restante % G;
     int OPH =  restante  / H ;
     restante = restante % H;
     int OPI =  restante  / I ;
     restante = restante % I;
     int OPJ =  restante  / J ;
     restante = restante % J;
     cout<< "50000:" << OPA <<  endl;
     cout<< "20000:" << OPB<< endl;
     cout<< "10000:" << OPC << endl;
     cout<< "5000:" << OPD << endl;
     cout<< "2000:" << OPE << endl;
     cout<< "1000:" << OPF <<  endl;
     cout<< "500:" << OPG << endl;
     cout<< "200:" << OPH << endl;
     cout<< "100:" << OPI <<  endl;
     cout<< "50:" << OPJ <<  endl;

     if (restante > 0 ) {
         int faltante = restante;
         cout << "Faltante: " << faltante << endl;
     }


}

int problema4(int hora, int tiempo){
    int minutosI = hora % 100;
    int horaI = hora / 100;
    int minutosE = tiempo % 100;
    int horaE = tiempo / 100;
    if (horaI < 0 || horaI > 23 || minutosI < 0 || minutosI > 59) {
        cout << hora << " |TIEMPO INVALIDO| " << endl;
        return 0;
    }
    if (horaE < 0 || horaE > 23 || minutosE < 0 || minutosE > 59) {
        cout << tiempo << " |TIEMPO INVALIDO| " << endl;
        return 0;
    }
    int cambio1 = horaI * 60 + minutosI;
    int cambio2 = horaE * 60 + minutosE;
    int total = (cambio1 + cambio2) % 1440;
    int horaF = total / 60;
    int minutosF =  total % 60 ;
    int resultado = horaF * 100 + minutosF;
    cout << "La hora es: " << resultado << endl;
    return 0;

}

double problema6(int n){
    double e = 0;
    double factorial = 1;
    for (int i = 1; i < n; i++){
        factorial = factorial *i;
        e = e + (1.0 / factorial);
    }
    return e;
}

int problema8(int a , int b , int c){
    int sumatoria = 0;
    for (int j = a ; j < c ; j += a){
        sumatoria += j;
        if(j==a){
           cout<<j;
        }
        else if(j > a){
            cout << " + " << j;

        }

    }
    for (int h = b ; h < c ; h += b){
        if (h % a !=0){
            sumatoria += h;
            cout << " + " << h;

        }

    }
    cout << " = " << sumatoria << endl;
    return sumatoria;

}


int problema10(int numero){
    int contador = 0;
    int n = 2;
    while (contador < numero){
        bool esprimo = true;
        for(int t = 2; t < n ; t++){
            if(n % t == 0){
                esprimo = false;
                break;
            }
        }
        if(esprimo){
            contador ++;
        }
        if (contador == numero){
            cout<<"El primo numero "<<numero<< " es: "<<n<< endl;
            return n;
        }
        n++;
    }
    return 0;
    }

int problema12(int n){
    int m = n;
    int divisor = 2;
    int factorPrimo = 1;
    while (n>1){
        if(n % divisor == 0){
            factorPrimo = divisor;
            n =  n / divisor;

        }
        else{
            divisor++;
        }

    }
    cout<<"El mayor factor primo de "<<m<<" es: "<<factorPrimo<< endl;
    return factorPrimo;

}


int problema14(){
    int mayorpalindromo = 0;
    int almacenado = 0;
    int t1 = 0 ,  t2 = 0 , factor1 = 0 , factor2 = 0;
    for (int r = 999; r >= 100; r--){
        for (int s = r; s >= 100; s--){
            int producto = r * s;
            if ( producto <= mayorpalindromo ){
                break;
               }
            t1 = producto;
            t2 = 0;
            while (t1 > 0){
                    t2 = t2*10 + (t1 % 10);
                    t1 /= 10;
                }
                if (producto == t2){
                    mayorpalindromo = producto;
                    factor1 = r;
                    factor2 = s;
                }
        }
    }

 cout << factor1 << " * " << factor2 << " = " <<mayorpalindromo;
    return 0;
}

int problema16(int k){
    int terminos = 0;
    int semillaj = 1;
    int j;
    for (j = 1 ; j<k ;++j){
        int m = 0;
        int n = j;

        while (n != 1){
            m += 1;
            if (n % 2 == 0){
                 n = n/2;
            }
            else{
                n = 3*n + 1;
            }
        }
        ++m;
        if (m >terminos){
            terminos = m ;
            semillaj = j;

        }
    }
    cout<<"La serie mas larga es con la semilla "<< semillaj <<" ,teniendo "<< terminos << " terminos."<< endl;
    int n = semillaj;
    cout<< n ;
    while (n != 1){
        if (n % 2 == 0){
            n = n/2;
        }
        else{
            n = 3*n + 1;
        }
        cout << ", " << n;
    }
    return 0;
}



int main(){
    int x = 0;
    cout << "Ingrese el problema que desea ejecutar ( | 2 | 4 | 6 | 8 | 10 | 12 | 14 | 16 | ): " << endl;
    cin >> x;
    switch (x) {
    case 2:{
        int dinero;
        cout<< "Ingrese la cantidad de dinero que desee:" << endl;
        cin >> dinero;
        problema2(dinero);
    }
    break;
    case 4:{
        int hora;
        int tiempo;
        cout<< "Ingrese una hora (no incluya caracteres especiales)" << endl;
        cin >> hora;
        cout<< "Ingrese un tiempo (no incluya caracteres especiales)" << endl;
        cin >> tiempo;
        problema4(hora , tiempo);

    }
    break;
    case 6:{
        int n;
        cout<< "Ingrese la cantidad del valor aproximado de euler que desea encontrar:" << endl;
        cin >> n;
        cout<< "e es aproximadamente:" << problema6(n)<< endl;
    }
    break;
    case 8:{
        int a;
        int b;
        int c;
        cout<< "Ingrese un numero a:" << endl;
        cin >> a;
        cout<< "Ingrese un numero b:" << endl;
        cin >> b;
        cout<< "Ingrese un numero c:" << endl;
        cin >> c;
        problema8(a,b,c);
    }
    break;
    case 10:{
        int numero;
        cout<< "Ingrese un numero n:" << endl;
        cin >> numero;
        problema10(numero);
    }
    break;
    case 12:{
        int m;
        cout<< "Ingrese  un numero m:" << endl;
        cin >> m;
        problema12(m);
    }
    break;
    case 14:{
        cout<< "FACTOR DE DOS NUMERO PALINDROMOS DE 3 CIFRAS" << endl;
        problema14();
    }
    break;
    case 16:{
        int k;
        cout<< "Ingrese  un numero k:" << endl;
        cin >> k;
        problema16(k);
    }
    break;
    }
    }





































