// Autora: Estibaliz Zubimendi Solaguren
// email: estizubi@ucm.es
// Compilador y S.O. utilizado: VS 2019
// Nombre del problema: Máxima cota de un mapa topográfico

#include <iostream>
#include <fstream>

using namespace std;

const int N = 100;
typedef struct {
	int f, c;
	int tAlturas[N][N];
}tMatriz;

typedef struct {
	int x = 0, y = 0;
}tCoord;

void resolver(const tMatriz &m, int &posx, int &posy) {
	//encontrar el mayor
	//como estamos buscando un elemento y no recorriendo: utilizar while

	//el primer mayor es el primer elemento de la matriz
	int mayor = m.tAlturas[posx][posy];
	for (int i = 0; i < m.f; ++i) {
		for (int j = 0; j < m.c; ++j) {
			if (m.tAlturas[i][j] > mayor) {
				posx = i;
				posy = j;
				mayor = m.tAlturas[i][j];
			}
		}
	}
}

bool resuelveCaso() {
	tMatriz m;
	tCoord coordenada;

	// leer los datos de la entrada

	cin >> m.f >> m.c;

	for (int i = 0; i < m.f; ++i) {
		for (int j = 0; j < m.c; ++j) {
			cin >> m.tAlturas[i][j];
		}
	}
	if (!std::cin)  // fin de la entrada
		return false;

	resolver(m, coordenada.x, coordenada.y);

	// escribir sol
	cout << m.tAlturas[coordenada.x][coordenada.y] << " " 
		<< coordenada.x << " " << coordenada.y << "\n";

	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("sample-06.1.in");
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