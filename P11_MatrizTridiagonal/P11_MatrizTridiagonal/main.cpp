// Autor/a: Estibaliz Zubimendi
// email: estizubi@ucm.es
// Compilador y S.O. utilizado: Microsoft Visual Studio 2019
// Nombre del problema: Matriz tridiagonal

#include <iostream>
#include <fstream>

using namespace std;

const  int  NUM_DIRECCIONES = 4;
const  pair <int, int > dirs4[NUM_DIRECCIONES] = { {-1,0},{1,0},{0,1},{0,-1} };
const int DIM = 50;
typedef long int tArray[DIM][DIM];
typedef struct {
	tArray elemento;
	int nFilas;
}tMatriz;

int resolver(const tMatriz& m, int& sumaMax) {
	int fila = 0;
	//inicializamos sumaMax al primer elemento (más los elemetos colindantes)
	sumaMax = m.elemento[0][0];
	sumaMax += m.elemento[dirs4[1].first][dirs4[1].second];
	sumaMax += m.elemento[dirs4[2].first][dirs4[2].second];

	//lo hacemos para todos los elementos menos para el último de la diagonal principal
	for (int i = 1; i < m.nFilas - 1; ++i) {
		int tmp = m.elemento[i][i];
		for (int j = 0; j < NUM_DIRECCIONES; ++j) {
			tmp += m.elemento[i + dirs4[j].first][i + dirs4[j].second];
		}
		if (tmp > sumaMax) {
			sumaMax = tmp;
			fila = i;
		}
	}
	
	//último elemento
	int last = m.elemento[m.nFilas - 1][m.nFilas - 1];
	last += m.elemento[(m.nFilas - 1) + dirs4[0].first][(m.nFilas - 1) + dirs4[0].second];
	last += m.elemento[(m.nFilas - 1) + dirs4[3].first][(m.nFilas - 1) + dirs4[3].second];
	if (last > sumaMax) {
		sumaMax = last;
		fila = m.nFilas - 1;
	}
	
	return fila;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	tMatriz m;
	// leer los datos de la entrada
	cin >> m.nFilas;
	if (!cin)  // fin de la entrada
		return false;

	//en caso de ser una matriz 1x1
	if (m.nFilas == 1) {
		cin >> m.elemento[0][0];
		cout << 0 << " " << m.elemento[0][0] << "\n";
		return true;
	}

	//diagonal principal
	for (int i = 0; i < m.nFilas; ++i) {
		cin >> m.elemento[i][i];
	}
	//diagonal superior
	for (int i = 0; i < m.nFilas - 1; ++i) {
		cin >> m.elemento[i][i + 1];
	}
	//diagonal inferior
	for(int i = 0; i < m.nFilas - 1; ++i){
		cin >> m.elemento[i + 1][i];
	}

	int sumaMax;
	int fila = resolver(m, sumaMax);

	// escribir sol
	cout << fila << " " << sumaMax << "\n";
	return true;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("sample-11.2.in");
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