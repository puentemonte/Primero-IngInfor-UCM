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
	char c;
	bool sol;
}tCasilla;
typedef tCasilla tArray[MAX][MAX];
typedef struct {
	tArray matriz;
	int f, c;
}tMatriz;
const int NUM_DIRECCIONES = 8;
const pair<int, int>dirs8[NUM_DIRECCIONES] = { {1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1},{0,-1},{1,-1} };

void inicializar(tMatriz& m) {
	for (int i = 0; i < MAX; ++i) {
		for (int j = 0; j < MAX; ++j) {
			m.matriz[i][j].c = ' ';
			m.matriz[i][j].sol = false;
		}
	}
}

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
	out << " ";
	out << "\n";
	for (int i = 0; i < m.f; ++i) {
		cout << " ";
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
	out << " " << endl;
	return out;
}

bool encuentraPalabra(tMatriz &m, string& palabra, int dir, int i, int j) {
	//  k es el índice de la palabra
	int k = 1;
	bool encontrada = true;
	while (encontrada && k < palabra.length()) {
		char c = m.matriz[i + dirs8[dir].first * k][j + dirs8[dir].second * k].c;
		encontrada = m.matriz[i + dirs8[dir].first * k][j + dirs8[dir].second * k].c == palabra[k];
		++k;
	}
	return encontrada;
}

bool buscaPalabra(tMatriz &m, string &palabra, int i, int j) {
	int dir = 0;
	bool encontrada = false;
	while (dir < NUM_DIRECCIONES && !encontrada) {
		encontrada = encuentraPalabra(m, palabra, dir, i, j);
		++dir;
	}
	// hay que guardar dir restarle el último que se le suma en el bucle
	--dir;
	if (encontrada) {
		for (int k = 0; k < palabra.length(); ++k) {
			m.matriz[i + dirs8[dir].first * k][j + dirs8[dir].second * k].sol = true;
		}
	}
	return encontrada;
}

void resolver(tMatriz &m, string &palabra) {
	bool encontrada = false;
	int i = 0, j = 0;
	while (!encontrada && j < m.c) {
		i = 0;
		while (!encontrada && i < m.f) {
			if (palabra[0] == m.matriz[i][j].c)
				encontrada = buscaPalabra(m, palabra, i, j);
			++i;
		}
		++j;
	}
}

void resuelveCaso() {
	tMatriz m;
	int n;
	string palabra;
	char aux;

	//inicializamos matriz
	inicializar(m);

	// lectura de matriz
	cin >> m;
	if (m.f != 0 && m.c != 0) {
		// cada palabra se procesa en cada momento
		cin >> n;
		cin.get(aux);
		for (int i = 0; i < n; ++i) {
			getline(cin, palabra);
			resolver(m, palabra);
		}
		cout << m << endl;
	}
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