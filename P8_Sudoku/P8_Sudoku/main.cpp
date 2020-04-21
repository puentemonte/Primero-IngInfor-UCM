// Autor/a: Estibaliz Zubimendi Solaguren
// email: estizubi@ucm.es
// Compilador y S.O. utilizado: Microsoft Visual Studio 2019
// Nombre del problema: Sudokus correctos

#include <iostream>
#include <fstream>

using namespace std;

const int DIM = 9;
typedef int tMatriz[DIM][DIM];
typedef struct {
	int x, y;
}tCoord;
typedef bool tElem[DIM];
typedef struct {
	int numElem;
	tElem elemento;
}tConjunto;

tConjunto creaCjto() {
	tConjunto c;

	c.numElem = 0;
	for (int i = 0; i < DIM; ++i)
		c.elemento[i] = false;
	
	return c;
}

bool compruebaFilas(const tMatriz& m, tConjunto &filas) {
	bool repes = false;
	int i = 0, j = 0;

	while (!repes && i < DIM) {
		filas = creaCjto();
		j = 0;
		while (!repes && j < DIM) {
			//si filas.elemento[m[i][j] - 1] == true (el número ya está)
			if (filas.elemento[m[i][j] - 1])
				repes = true;
			else {
				++filas.numElem;
				filas.elemento[m[i][j] - 1] = true;
			}
			++j;
		}
		++i;
	}
	return !repes;
}
bool compruebaColumnas(const tMatriz& m, tConjunto &columnas) {
	bool repes = false;
	int i = 0, j = 0;

	while (!repes && i < DIM) {
		columnas = creaCjto();
		j = 0;
		while (!repes && j < DIM) {
			if (columnas.elemento[m[j][i] - 1])
				repes = true;
			else {
				++columnas.numElem;
				columnas.elemento[m[j][i] - 1] = true;
			}
			++j;
		}
		++i;
	}
	return !repes;
}
bool comprueba3x3(const tMatriz& m, tConjunto &subMatriz) {
	bool repes = false;
	int i = 0, j = 0, k, l;

	while (!repes && i < DIM) {
		while (!repes && j < DIM) {
			subMatriz = creaCjto();
			k = i;
			while (!repes && k <= i + 2) {
				l = j;
				while (!repes && l <= j + 2) {
					if (subMatriz.elemento[m[k][l] - 1])
						repes = true;
					else {
						++subMatriz.numElem;
						subMatriz.elemento[m[k][l] - 1] = true;
					}
					++l;
				}
				++k;
			}
			j += 3;
		}
		i += 3;
	}

	return !repes;
}

bool resolver(const tMatriz& m) {
	bool resuelto = true;
	tConjunto c;

	resuelto = compruebaFilas(m, c);
	if (resuelto)
		resuelto = compruebaColumnas(m, c);
	if (resuelto)
		resuelto = comprueba3x3(m, c);

	return resuelto;
}

void resuelveCaso() {
	tMatriz m;

	for (int i = 0; i < DIM; ++i) {
		for (int j = 0; j < DIM; ++j) {
			cin >> m[i][j];
		}
	}

	bool sol = resolver(m);

	if (sol)
		cout << "SI\n";
	else
		cout << "NO\n";
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("sample-08.2.in");
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