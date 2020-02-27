// Autora: Estibaliz Zubimendi Solaguren
// email: estizubi@ucm.es
// Compilador y S.O. utilizado: VS 2019
// Nombre del problema:

#include <iostream>
#include <fstream>

using namespace std;

const int N = 100;
typedef int tElemento[N][N];
typedef struct {
	int fila, col;
	tElemento elem;
}tMatriz;

void resolver(tMatriz m, int total) {

}

void resuelveCaso() {

	tMatriz m;
	int num, i, j = 0;

	cin >> num;
	while (num != 0) {
		m.elem[i][j] = num;
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
	std::ifstream in("datos.in");
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