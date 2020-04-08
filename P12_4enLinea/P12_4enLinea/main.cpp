#include <iostream>
#include <fstream>

using namespace std;

const int COL = 7;
const int FILA = 6;
typedef int tArray[COL];
typedef char tMatriz[FILA][COL];

void resolver(const tMatriz &m, const tArray &columnas) {
	
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	int nMov, aux, n;
	tArray columnas;
	tMatriz m;

	// inicializamos columnas
	for (int i = 0; i < COL; ++i) {
		columnas[i] = 5;
	}
	// inicializamos la matriz
	for (int i = 0; i < FILA; ++i) {
		for (int j = 0; j < COL; ++j) {
			m[i][j] = 'F';
		}
	}

	cin >> nMov;
	if (nMov == 0)
		return false;
	aux = nMov / 2;
	while (aux > 0) {
		cin >> n;
		m[columnas[n]][n] = 'A';
		--columnas[n];
		cin >> n;
		m[columnas[n]][n] = 'B';
		--columnas[n];
		--aux;
	}
	// por si el número de fichas no es par, necesito que lea un movimiento más de A
	if (nMov % 2 != 0) {
		cin >> n;
		m[columnas[n]][n] = 'A';
		++columnas[n];
	}

	for (int i = 0; i < FILA; ++i) {
		for (int j = 0; j < COL; ++j) {
			cout << m[i][j] << " ";
		}
		cout << "\n";
	}

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("sample-12.in");
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