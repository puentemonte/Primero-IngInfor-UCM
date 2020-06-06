// Autor/a: Estibaliz Zubimendi Solaguren
// email: estizubi@ucm.es
// Compilador y S.O. utilizado: Visual Studio 2019
// Nombre del problema: Invertir número
// Resuelto con recursividad

#include <iostream>
#include <fstream>

using namespace std;

typedef struct {
    unsigned long long int numero = 0, pot = 1;
}tSol;

// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
tSol invertir(unsigned long long int n) {
    // declaramos la variable que vamos a devolver
    tSol sol;
    // si el número solo tiene una cifra, es decir, es menor que 10
    if (n < 10) {
        // no hay que revertir nada porque es el número en sí
        sol.numero = n;
        // además la potencia es 1 porque es la potencia que necesitamos para calcular el número
        sol.pot = 1;
    }
    // si el número tiene más de una cifra comenzamos con la recursión
    else {
        // tenemos que hacer la división entera de n para quitarle una cifra
        sol = invertir(n / 10);
        // aumentamos la potencia que necesitariamos para calcular el número
        sol.pot *= 10;
        // tenemos que sumar al número la última cifra de n y multiplicarla por 10
        sol.numero += (n % 10) * sol.pot;
        /*
        EXPLICACIÓN:
        si n = 123
        sol.numero al principio está a 0 entonces al principio n % 10 va a ser 3 y sol.pot = 1
        pero según más iteraciones hagamos...
        sol.numero lo vamos a multiplicar por la potencia de 10 necesaria, entonces pasa lo siguiente:
        300 (sol.pot = 100) + 20 (pot = 10) + 1 (pot = 1) = 321, que es 123 invertido
        */
    }
    // finalmente devolvemos la respuesta y se termina la recursividad
    return sol;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int n;
    tSol sol;

    // leer los datos de la entrada
    cin >> n;
    if (!std::cin)  // fin de la entrada
        return false;

    // recursividad
    sol = invertir(n);

    // imprimimos la solución
    cout << sol.numero << endl;

    return true;
}

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("sample-20.1.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
    std::ofstream out("datos.out");
    auto coutbuf = std::cout.rdbuf(out.rdbuf());

#endif

    while (resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    std::cout.rdbuf(coutbuf);
    system("PAUSE");
#endif
    return 0;
}
