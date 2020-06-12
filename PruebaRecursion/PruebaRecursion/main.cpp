// Prueba de evaluación del día 12 de junio de 2020
// Alumno/a: Estibaliz Zubimendi Solaguren
// email:  estizubi@ucm.es
// Grupo: B

// Fíjate que hay 3 sitios donde aparece el comentario  "INTRODUCIR CODIGO"
// Debes cambiar los nombres de los ficheros para las distintas pruebas

#include <iostream>
#include <fstream>
using namespace std;

typedef struct {
	int cont = 0;
	int array[100];
}tLista;

// Prototipos

// Traduce (0/1) booleano a (FALSE/TRUE) del tipo string
string bool2string(bool x);

// Prototipo de la función que se debe implementar
bool funcion(const tLista& l, int pos);
// INTRODUCIR CODIGO

int resuelveCaso() {

	tLista l;
	int num = 0;
	cin >> num;
	while (num != -1)
	{
		l.array[l.cont] = num;
		l.cont++;
		cin >> num;
	}

	// Llamada a la función implementada
	// INTRODUCIR CODIGO
	bool cierto;
	// llamamos a la función recursiva
	cierto = funcion(l, l.cont - 1);
	// imprimimos TRUE OR FALSE
	cout << bool2string(cierto) << "\n";

	return 0;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("5.in");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	std::ofstream out("datos.1.1.out");
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

// Implementación de la función recursiva

// INTRODUCIR CODIGO

bool funcion(const tLista& l, int pos) {
	bool cierto = false;
	// primero comprobamos las listas vacías o que solo tienen un elemento
	if (l.cont == 0 || l.cont == 1)
		cierto = false;
	// ahora las que no son vacias
	else {
		// mientras la posición sea mayor que 0 tenemos que utilizar recursividad
		if (pos > 0) {
			// cuando encontremos dos iguales terminamos la recursividad
			if (l.array[pos] == l.array[pos - 1])
				cierto = true;
			// ahora tenemos que comprobar para la posición anterior
			else
				cierto = funcion(l, pos - 1);
		}
	}
	// por último devolvemos cierto
	return cierto;
}

// Traduce (0/1) booleano a (FALSE/TRUE) del tipo string
string bool2string(bool x) {
	if (x)
		return "TRUE";
	else
		return "FALSE";
}