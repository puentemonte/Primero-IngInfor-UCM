#include <iostream>
#include <fstream>

using namespace std;

const int N = 100;
typedef struct {
	int fila, col;
	int elem[N][N];
}tMatriz;

bool esPunto(const tMatriz& m, int numFila, int numCol) {

	bool esPunto = false, mayorFila = true, menorFila = true, mayorCol = true, menorCol = true;
	int i = 0, j = 0;

	while (i < m.col && mayorFila) {
		mayorFila = m.elem[numFila][numCol] >= m.elem[numFila][i];
		++i;
	}
	i = 0;
	while (i < m.col && menorFila) {
		menorFila = m.elem[numFila][numCol] <= m.elem[numFila][i];
		++i;
	}

	while (j < m.fila && mayorCol) {
		mayorCol = m.elem[numFila][numCol] >= m.elem[j][numCol];
		++j;
	}
	j = 0;
	while (j < m.fila && menorCol) {
		menorCol = m.elem[numFila][numCol] <= m.elem[j][numCol];
		++j;
	}

	if((mayorFila && menorCol) || (menorFila && mayorCol))
		esPunto = true;

	return esPunto;
}

// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
bool resolver(const tMatriz &m) {

	bool encontrado = false;
	int i = 0, j = 0;

	while (i < m.fila && !encontrado) {
		j = 0;
		while (j < m.col && !encontrado) {
			encontrado = esPunto(m, i, j);
			++j;
		}
		++i;
	}
	

	return encontrado;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	tMatriz m;

	// leer los datos de la entrada
	cin >> m.fila >> m.col;
	//caso especial
	if (m.fila == 0 && m.col == 0)
		return false;
	for (int i = 0; i < m.fila; ++i) {
		for (int j = 0; j < m.col; ++j) {
			cin >> m.elem[i][j];
		}
	}

	bool sol = resolver(m);

	// escribir sol
	if (sol)
		cout << "SI\n";
	else if (!sol)
		cout << "NO\n";

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("sample-10.1.in");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	std::ofstream out("salida.out");
	auto coutbuf = std::cout.rdbuf(out.rdbuf());
#endif

	while (resuelveCaso());

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	system("PAUSE");
#endif
	return 0;
}