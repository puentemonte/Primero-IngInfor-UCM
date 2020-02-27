// Autora: Estibaliz Zubimendi Solaguren
// email: estizubi@ucm.es
// Compilador y S.O. utilizado: VS 2019
// Nombre del problema: El burro y las alforjas
// he utilizado el método de inserción con intercambios

#include <iostream>
#include <fstream>

using namespace std;

const int N = 1000;
typedef int tLista[N];

int resolver(tLista &lista, int total, int burrosTotal) {

	int numBurros = 0, ind = 0;

	//algoritmo de ordenación por inserción con intercambios
	for (int i = 0; i < total - 1; i++) {

		for (int j = i + 1; j < total; j++) {

			if (lista[j] < lista[i]) {
				int tmp;
				tmp = lista[i];
				lista[i] = lista[j];
				lista[j] = tmp;
			}
		}
	}

	while (ind < total - 1 && numBurros < burrosTotal) {
		if (lista[ind] == lista[ind + 1]) {
			++numBurros;
			++ind;
		}
		++ind;
	}
	return numBurros;
}

void resuelveCaso() {

	tLista lista;
	int numBurros = 0, numSacos = 0;

	cin >> numBurros >> numSacos;

	for (int i = 0; i < numSacos; ++i) {
		cin >> lista[i];
	}

	int sol = resolver(lista, numSacos, numBurros);
	cout << sol << "\n";
}

int main() {

	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("sample-04.2.in");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	std::ofstream out("datos.out");
	auto coutbuf = std::cout.rdbuf(out.rdbuf());
#endif

	int numCasos;
	std::cin >> numCasos;
	for (int i = 0; i < numCasos; ++i)
		resuelveCaso();

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	std::cout.rdbuf(coutbuf);
	system("PAUSE");
#endif
	return 0;
}