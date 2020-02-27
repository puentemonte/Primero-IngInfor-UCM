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

	bool inter = true;
	int i = 0;
	while ((i < total - 1) && inter) {
		inter = false;
		for (int j = total - 1; j > i; --j) {
			if (lista[j] < lista[j - 1]) {
				int tmp;
				tmp = lista[j];
				lista[j] = lista[j - 1];
				lista[j - 1] = tmp;
				inter = true;
			}
		}
		if (inter)
			++i;
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
	std::ifstream in("sample-03.1.in");
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
	return 0;
}