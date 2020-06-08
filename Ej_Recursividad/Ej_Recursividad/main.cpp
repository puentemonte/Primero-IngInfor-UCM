/*
  Estibaliz Zubimendi Solaguren
  Códigos correspondientes a las explicaciones de ejercicios recursivos en clase
*/

#include <iostream>
#include <string>
using namespace std;

typedef struct {
    int cont = 0;
    int array[100];
}tLista;

typedef struct {
    int numero = 0, pot = 1;
}tSol;

////////////////////////////////////////
// Ejercicios recursivos con números.
////////////////////////////////////////

// Calcula en número de dígitos que tiene un número
int numDigitos(unsigned long long int n);

// Suma los dígitos de un número
int suma(int n);

// Suma de todos los número que van desde 1 hasta n
int sumatorio(int n);

// Invierte un número a
tSol invertir(int n);

////////////////////////////////////////
// Ejercicios recursivos con listas.
// Recorridos lineales
////////////////////////////////////////

// Mostrar la lista según su orden
void mostrarDirecto(tLista lista, int pos);

// Mostrar la lista en orden inverso
void mostrarInverso(tLista lista, int pos);

// Mostrar los elementos que están en índices pares
void mostrarIndexpares(tLista lista, int pos);

// Sumar los elementos de una lista
int sumar(tLista lista, int pos);

// Mostrar los números pares de una lista
void mostrarPares(tLista lista, int pos);

////////////////////////////////////////
// Ejercicios recursivos con listas.
// Búsquedas lineales
////////////////////////////////////////

// Dice si todos los elementos de la lista son iguales
bool iguales(const tLista& l, int pos);

// Cuantos hay iguales al primero empezando desde el inicio
int cuantosIguales(const tLista& l);
int cuantosIguales2(const tLista& l, int pos, int num);

int main() {
    int uno;
    cout << "Uno: ";
    cin >> uno;
    cout << uno << " tiene " << numDigitos(uno) << " digitos\n";

    system("PAUSE");
    system("cls");

    int dos;
    cout << "Dos: ";
    cin >> dos;
    cout << "la suma de las cifras de " << dos << " es " << suma(dos) << "\n";

    system("PAUSE");
    system("cls");

    int tres;
    cout << "Tres: ";
    cin >> tres;
    cout << "el sumatorio desde 1 hasta " << tres << " es " << sumatorio(tres) << "\n";

    system("PAUSE");
    system("cls");

    tSol cuatro;
    int aux;
    cout << "Cuatro: ";
    cin >> aux;
    cuatro = invertir(aux);
    cout << aux << " invertido es " << cuatro.numero << "\n";

    system("PAUSE");
    system("cls");

    tLista cinco;
    cout << "Numero de elementos: ";
    cin >> cinco.cont;
    for (int i = 0; i < cinco.cont; ++i)
        cin >> cinco.array[i];
    system("PAUSE");
    system("cls");
    cout << "Mostrando lista directamente: ";
    mostrarDirecto(cinco, 0);
    cout << "\n";
    cout << "Mostrando lista inversamente: ";
    mostrarInverso(cinco, 0);
    cout << "\n";
    cout << "Mostrando elementos en indices pares: ";
    mostrarIndexpares(cinco, 0);
    cout << "\n";
    cout << "La suma de los elementos de la lista: " << sumar(cinco, 0) << "\n";
    cout << "Mostrando los elementos pares: ";
    mostrarPares(cinco, 0);
    cout << "\n";
    cout << "Todos los elementos de las lista son iguales? " << iguales(cinco, 0) << "\n";
    cout << "Elementos iguales al primero: " << cuantosIguales(cinco) << "\n";

    return 0;
}

int cuantosIguales2(const tLista& l, int pos, int num) {
    int sol = 0;
    if (pos == l.cont)
        sol = 0;
    else {
        if ((l.array[pos] == num)) {
            sol = 1 + cuantosIguales2(l, pos + 1, num);
        }
    }
    return sol;
}

int cuantosIguales(const tLista& l) {
    int sol = 0;
    if (l.cont == 0 || l.cont == 1)
        sol = 0;
    else
        sol = cuantosIguales2(l, 1, l.array[0]);
    return sol;
}

bool iguales(const tLista& l, int pos) {
    bool same = true;
    if (pos < l.cont) {
        if (l.array[pos] != l.array[pos - 1]) {
            same = false;
        } 
        iguales(l, pos + 1);
    }
    return same;
}

void mostrarPares(tLista lista, int pos) {
    if (pos < lista.cont) {
        if (lista.array[pos] % 2 == 0)
            cout << lista.array[pos] << " ";
        mostrarPares(lista, pos + 1);
    }
}

int sumar(tLista lista, int pos) {
    int suma = 0;
    if (pos < lista.cont) {
        suma = lista.array[pos] + sumar(lista, pos + 1);
    }
    return suma;
}

void mostrarIndexpares(tLista lista, int pos) {
    if (pos < lista.cont) {
        if (pos % 2 == 0)
            cout << lista.array[pos] << " ";
        mostrarIndexpares(lista, pos + 1);
    }
}

void mostrarInverso(tLista lista, int pos) {
    if (pos < lista.cont) {
        mostrarInverso(lista, pos + 1);
        cout << lista.array[pos] << " ";
    }
}

void mostrarDirecto(tLista lista, int pos) {
    if (pos < lista.cont) {
        cout << lista.array[pos] << " ";
        mostrarDirecto(lista, pos + 1);
    }
}

tSol invertir(int n) {
    tSol sol;
    if (n < 10) {
        sol.numero = n;
        sol.pot = 1;
    }
    else {
        sol = invertir(n / 10);
        sol.pot *= 10;
        sol.numero = sol.numero + (sol.pot * (n % 10));
    }
    return sol;
}

int sumatorio(int n) {
    int sol = 0;
    if (n == 1)
        sol = 1;
    else {
        sol = n + sumatorio(n - 1);
    }
    return sol;
}

int suma(int n) {
    int sol = 0;
    if (n < 10)
        sol = n;
    else {
        sol = n%10 + suma(n / 10);
    }
    return sol;
}

int numDigitos(unsigned long long int n) {
    int sol = 0;
    if (n < 10)
        sol = 1;
    else {
        sol = 1 + numDigitos(n / 10);
    }
    return sol;
}