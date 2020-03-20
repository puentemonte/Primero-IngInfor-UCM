// Autor/a: Estibaliz Zubimendi Solaguren
// email: estizubi@ucm.es
// Compilador y S.O. utilizado: Microsoft Visual Studio 2019
// Nombre del problema: Búscando a...

#include <iostream>
#include <fstream>

using namespace std;

const int tamMatriz = 40;
typedef int tElem[tamMatriz][tamMatriz];
typedef struct {
	tElem elem;
	int f, c;
}tMatriz;

bool comprobarPatron(const tMatriz &m, const tMatriz &p, int x, int y) {
	/*
	 función que dada la imagen, 
	 el patrón y un posición de la imagen, 
	 compruebe si el patrón aparece a partir de la posición dada
	*/	
	int i = 0, j = 0, k, l;
	bool encontrado = true;

	while (encontrado && i < p.f) {
		k = i;
		j = 0;
		while (encontrado && j < p.c) {
			l = j;
			if (p.elem[i][j] != m.elem[k + x][l + y])
				encontrado = false;
			else
				++j;
		}
		++i;
	}
	return encontrado;
}

bool resolver(const tMatriz &m, const tMatriz &p, int &fila, int &columna) {

	bool encontrado = false;
	int i = 0, j = 0;

	while(!encontrado && i <= (m.f - p.f)){
		j = 0;
		while (!encontrado && j <= (m.c - p.c)) {
			if (comprobarPatron(m, p, i, j))
				encontrado = true;
			++j;
		}
		++i;
	}
	fila = i - 1;
	columna = j - 1;
	return encontrado;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	tMatriz m, patron;
	//coordenadas de dónde se encuentra el patrón
	int x, y;

	// leer los datos de la entrada
	cin >> m.f >> m.c;

	if (!std::cin)  // fin de la entrada
		return false;

	for (int i = 0; i < m.f; ++i) {
		for (int j = 0; j < m.c; ++j) {
			cin >> m.elem[i][j];
		}
	}
	cin >> patron.f >> patron.c;
	for (int i = 0; i < patron.f; ++i) {
		for (int j = 0; j < patron.c; ++j) {
			cin >> patron.elem[i][j];
		}
	}

	bool sol = resolver(m, patron, x, y);

	// escribir sol
	if (sol)
		cout << x << " " << y << "\n";
	else
		cout << "NO\n";

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("sample-09.1.in");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	std::ofstream out("datos.out");
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