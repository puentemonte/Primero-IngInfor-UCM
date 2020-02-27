// Autora: Estibaliz Zubimendi Solaguren
// email: estizubi@ucm.es
// Compilador y S.O. utilizado: VS 2019
// Nombre del problema:

#include <iostream>
#include <fstream>

using namespace std;

const int N = 100;
typedef int tLista[N];

void resolver(tLista lista, int total) {

	for (int i = 0; i < total; ++i) {

		int menor = i;

		for (int j = i + 1; j < total; ++j) {
			if (lista[j] < lista[menor])
				menor = j;
		}
		if (menor > i) {
			int tmp;
			tmp = lista[i];
			lista[i] = lista[menor];
			lista[menor] = tmp;
		}
	}

}

void resuelveCaso() {

	tLista lista;
	int num, i = 0;

	cin >> num;
	while (num != 0) {
		lista[i] = num;
		++i;
		cin >> num;
	}

	resolver(lista, i);

	for (int j = 0; j < i; ++j) {
		cout << lista[j] << " ";
	}
	cout << endl;

}

int main() {

#ifndef DOMJUDGE
	std::ifstream in("sample-02.1.in");
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