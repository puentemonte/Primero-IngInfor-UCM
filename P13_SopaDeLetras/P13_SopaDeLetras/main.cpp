// Autor/a: Estibaliz Zubimendi Solaguren
// email: estizubi@ucm.es
// Compilador y S.O. utilizado: VS 2019
// Nombre del problema: Sopa de letras
#include <iostream>
#include <fstream>
#include <string>
#include <utility>

using namespace std;
const int MAX = 50;
typedef tCasilla tArray[MAX][MAX];
typedef struct {
	tArray matriz;
	int f, c;
}tMatriz;
typedef struct {
	char c;
	bool sol;
}tCasilla;
const int NUM_DIRECCIONES = 8;
const pair<int, int>dirs8[NUM_DIRECCIONES] = { {1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1},{0,-1},{1,-1} };

istream& operator>>(istream& in, tMatriz& m) {
	in >> m.f >> m.c;
	for (int i = 0; i < m.f; ++i) {
		for (int j = 0; j < m.c; ++j) {
			in.get(m.matriz[i][j]);
		}
	}
	return in;
}

ostream& operator<<(ostream& out, tMatriz& m) {
	for (int i = 0; i < m.f; ++i) {
		for (int j = 0; j < m.c; ++j) {
			out << m.matriz[i][j] << " ";
		}
		out << "\n";
	}
	return out;
}

void resolver(const tMatriz &m) {

}

void resuelveCaso() {
	tMatriz m;
	int p;
	// lectura de matriz
	cin >> m;
	// cada palabra se procesa en cada momento
	cin >> p;
	for (int i = 0; i < p; ++i) {

	}
		resolver(m);
	
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("sample-13.1.in");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	std::ofstream out("datos.out");
	auto coutbuf = std::cout.rdbuf(out.rdbuf());
#endif

	int numCasos;
	cin >> numCasos;
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