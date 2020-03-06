// Autora: Estibaliz Zubimendi Solaguren
// email: estizubi@ucm.es
// Compilador y S.O. utilizado: VS 2019
// Nombre del problema:

#include <iostream>
#include <fstream>

using namespace std;

const int N = 100;
typedef struct {
	int fila, col;
	int elem[N][N];

}tMatriz;

istream& operator>>(istream& in, tMatriz& m) {
	in >> m.fila >> m.col;
	for (int i = 0; i < m.fila; ++i) {
		for (int j = 0; j < m.col; ++j) {
			in >> m.elem[i][j];
		}
	}
	return in;
}

ostream& operator<<(ostream& out, tMatriz& m) {
	for (int i = 0; i < m.fila; ++i) {
		for (int j = 0; j < m.col; ++j) {
			out << m.elem[i][j] << " ";
		}
		out << endl;
	}
	return out;
}

tMatriz operator*(const tMatriz& m1, const tMatriz& m2) {
	tMatriz mResul;

	//inicializamos la matriz resultado
	mResul.fila = m1.fila;
	mResul.col = m2.col;

	//coger una fila y multiplicarla por todas las columnas
	//a su vez coger todos los elementos de esa fila y columnas y multiplicarlos
	for(int i = 0; i < m1.fila; ++i){
		for (int j = 0; j < m2.col; ++j) {
			int aux = 0;
			for (int k = 0; k < m1.col; ++k) {
				aux += m1.elem[i][k] * m2.elem[k][j];
			}
			mResul.elem[i][j] = aux;
		}
	}

	return mResul;
}

tMatriz resolver(const tMatriz &m1, const tMatriz &m2) {
	return m1 * m2;
}

bool resuelveCaso() {

	tMatriz m1, m2, sol;
	//lectura de datos
	cin >> m1 >> m2;
	//final de lectura
	if (!std::cin) 
		return false;
	
	sol = resolver(m1, m2);

	cout << sol << endl;

	return true;

}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("sample-07.1.in");
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