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
typedef struct {
	char c = ' ';
	bool sol = false;
}tCasilla;
typedef tCasilla tArray[MAX][MAX];
typedef struct {
	tArray matriz;
	int f, c;
}tMatriz;
const int NUM_DIRECCIONES = 8;
const pair<int, int>dirs8[NUM_DIRECCIONES] = { {1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1},{0,-1},{1,-1} };

istream& operator>>(istream& in, tMatriz& m) {
	char aux;

	in >> m.f >> m.c;
	in.get(aux);
	for (int i = 0; i < m.f; ++i) {
		for (int j = 0; j < m.c; ++j) {
			in.get(m.matriz[i][j].c);
		}
		in.get(aux);
	}
	return in;
}

ostream& operator<<(ostream& out, tMatriz& m) {
	for (int i = 0; i < m.c; ++i) {
		out << " -";
	}
	out << "\n";
	for (int i = 0; i < m.f; ++i) {
		for (int j = 0; j < m.c; ++j) {
			if (m.matriz[i][j].sol)
				out << m.matriz[i][j].c << " ";
			else
				out << "  ";
		}
		out << "\n";
	}
	for (int i = 0; i < m.c; ++i) {
		out << " -";
	}
	out << "\n";
	return out;
}

bool dentroPlano(const tMatriz& m, int x, int y) {
	return (x >= 0 && x < m.f && y >= 0 && y < m.c);
}

bool encontrarPalabra(tMatriz& m, string palabra, int x, int y) {
	bool dir = false;
	int d = 0;
	while (d < NUM_DIRECCIONES && !dir) {
		// buscamos la dirección correcta
		if (dentroPlano(m, x + dirs8[d].first, y + dirs8[d].second)) {
			int destinoX = x + dirs8[d].first;
			int destinoY = y + dirs8[d].second;
			if (m.matriz[destinoX][destinoY].c == palabra[1])
				dir = true;
			else
				++d;
		}
	}
	int ind = 0;
	// suponemos que hemos encontrado la palabra
	bool encontrada = true;
	if (dir) {
		while (ind < palabra.length() && encontrada) {
			int destinoX = x + (ind * dirs8[d].first);
			int destinoY = y + (ind * dirs8[d].second);
			if (m.matriz[destinoX][destinoY].c != palabra[ind])
				encontrada = false;
			else
				++ind;
		}
		if (encontrada) {
			// ahora ponemos sol = true en los tCaracteres que forman la palabra
			for (int i = 0; i < palabra.length(); ++i)
				m.matriz[x + (i * dirs8[d].first)][y + (i * dirs8[d].second)].sol = true;
		}

	}
	
	return encontrada;
}

void resolver(tMatriz& m, string palabra) {
	bool encontrada = false;
	int i = 0, j = 0;
	while (!encontrada && i < m.f) {
		while (!encontrada && j < m.c) {
			// buscamos la primera letra
			if (palabra[0] == m.matriz[i][j].c)
				encontrada = encontrarPalabra(m, palabra, i, j);
			++j;
		}
		++i;
	}
}

void resuelveCaso() {
	tMatriz m;
	int n;
	string palabra;
	char aux;

	// lectura de matriz
	cin >> m;
	// cada palabra se procesa en cada momento
	cin >> n;
	for (int i = 0; i < n; ++i) {
		cin.get(aux);
		getline(cin, palabra);
		resolver(m, palabra);
	}
	cout << m;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("sample-13.in");
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