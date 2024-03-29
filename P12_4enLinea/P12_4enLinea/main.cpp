//Autor/a: Estibaliz Zubimendi Solaguren
//email: estizubi@ucm.es
//Compilador: Visual Studio 2019
//Nombre del problema: 4 en l�nea
#include <iostream>
#include <fstream>

using namespace std;

const int COLUMNA = 7;
const int FILA = 6;
// 1 A
// 2 B
// 0 NADIE
typedef int tMatriz[FILA][COLUMNA];
typedef enum tVeredicto{ A, B, EMPATE };
// array que lleva un contador de cuantas l�neas se han rellenado en cada columna
typedef int tColumna[COLUMNA];

tVeredicto compruebaHorizontal(const tMatriz& m) {
	tVeredicto v = EMPATE;
	bool ganadorA, ganadorB;
	int i = 0, j = 0;
	while (i < FILA && v == EMPATE) {
		j = 0;
		while (j < COLUMNA - 3 && v == EMPATE) {
			ganadorA = m[i][j] == 1 && m[i][j + 1] == 1 && m[i][j + 2] == 1 && m[i][j + 3] == 1;
			if (ganadorA)
				v = A;
			ganadorB = m[i][j] == 2 && m[i][j + 1] == 2 && m[i][j + 2] == 2 && m[i][j + 3] == 2;
			if (ganadorB)
				v = B;
			++j;
		}
		++i;
	}
	return v;
}
tVeredicto compruebaVertical(const tMatriz& m) {
	tVeredicto v = EMPATE;
	bool ganadorA, ganadorB;
	int i = 0, j = 0;
	while (j < COLUMNA && v == EMPATE) {
		i = 0;
		while (i < FILA - 3 && v == EMPATE) {
			ganadorA = m[i][j] == 1 && m[i + 1][j] == 1 && m[i + 2][j] == 1 && m[i + 3][j] == 1;
			if (ganadorA)
				v = A;
			ganadorB = m[i][j] == 2 && m[i + 1][j] == 2 && m[i + 2][j] == 2 && m[i + 3][j] == 2;
			if (ganadorB)
				v = B;
			++i;
		}
		++j;
	}
	return v;
}
tVeredicto comprobarDiagonalIzqDer(const tMatriz& m) {
	tVeredicto v = EMPATE;
	bool ganadorA, ganadorB;
	int i = 0, j = 0;
	while (i < FILA - 3 && v == EMPATE) {
		j = 0;
		while (j < COLUMNA - 3 && v == EMPATE) {
			ganadorA = m[i][j] == 1 && m[i + 1][j + 1] == 1 && m[i + 2][j + 2] == 1 && m[i + 3][j + 3] == 1;
			if (ganadorA)
				v = A;
			ganadorB = m[i][j] == 2 && m[i + 1][j + 1] == 2 && m[i + 2][j + 2] == 2 && m[i + 3][j + 3] == 2;
			if (ganadorB)
				v = B;
			++j;
		}
		++i;
	}
	return v;
}
tVeredicto comprobarDiagonalDerIzq(const tMatriz& m) {
	tVeredicto v = EMPATE;
	bool ganadorA, ganadorB;
	int i = 0, j = COLUMNA - 1;
	while (i < FILA - 3 && v == EMPATE) {
		j = COLUMNA - 1;
		while (j > COLUMNA - 5 && v == EMPATE) {
			ganadorA = m[i][j] == 1 && m[i + 1][j - 1] == 1 && m[i + 2][j - 2] == 1 && m[i + 3][j - 3] == 1;
			if (ganadorA)
				v = A;
			ganadorB = m[i][j] == 2 && m[i + 1][j - 1] == 2 && m[i + 2][j - 2] == 2 && m[i + 3][j - 3] == 2;
			if (ganadorB)
				v = B;
			--j;
		}
		++i;
	}
	return v;
}

tVeredicto resolver(const tMatriz &m) {
	tVeredicto v = EMPATE;
	v = compruebaHorizontal(m);
	if (v == EMPATE)
		v = compruebaVertical(m);
	if (v == EMPATE)
		v = comprobarDiagonalIzqDer(m);
	if (v == EMPATE)
		v = comprobarDiagonalDerIzq(m);
	return v;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuraci�n, y escribiendo la respuesta
bool resuelveCaso() {
	tMatriz m;
	tColumna cont;
	tVeredicto v = EMPATE;

	int n = 0, a = 0, i = 0, b = 0;
	cin >> n;
	if (n == 0)
		return false;

	// inicializamos la matriz
	for (int i = 0; i < FILA; ++i) {
		for (int j = 0; j < COLUMNA; ++j) {
			m[i][j] = 0;
		}
	}
	for (int i = 0; i < COLUMNA; ++i) {
		cont[i] = 0;
	}

	while (i < (n / 2) && v == EMPATE) {
		if (v == EMPATE) {
			cin >> a;
			m[cont[a]][a] = 1;
			++cont[a];
			v = resolver(m);
		}
		if (v == EMPATE) {
			cin >> b;
			m[cont[b]][b] = 2;
			++cont[b];
			v = resolver(m);
		}
		++i;
	}
	if (n % 2 != 0) {
		cin >> a;
		m[cont[a]][a] = 1;
		if(v == EMPATE)
			v = resolver(m);
	}
	if (n != 0) {
		switch (v) {
		case A:
			cout << "Gana A\n";
			break;
		case B:
			cout << "Gana B\n";
			break;
		case EMPATE:
			cout << "Empate\n";
		}
	}

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("sample-12.1.in");
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