#include <iostream>
#include <fstream>
#include <istream>
#include "mina.h"
using namespace std;

void resuelveCaso() {
	int escala, entradafichero;
	tMina mina;

	cin >> escala >> entradafichero;
	cargar_mina(cin, mina);

	if (escala == 1)
		dibujar1_1(mina);
	else
		dibujar3_1(mina);
	cout << endl;
}

int main() {
#ifndef DOMJUDGE
	std::ifstream in("sample-PR_01.1.in");
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

tElemento char2elem(char c) {

	tElemento elem;

	switch (c)
	{
	case 'J':
		elem = MINERO;
		break;

	case 'T':
		elem = TIERRA;
		break;

	case 'P':
		elem = PIEDRA;
		break;

	case 'M':
		elem = MURO;
		break;

	case 'G':
		elem = GEMA;
		break;

	case 'S':
		elem = SALIDA;
		break;
	case '-':
		elem = LIBRE;
	}
	return elem;
};

std::ostream& operator<< (std::ostream& out, tElemento const& e) {
	switch (e) {
	case TIERRA:
		out << ".";
		break;
	case PIEDRA:
		out << "@";
		break;
	case MURO:
		out << "X";
		break;
	case MINERO:
		out << "M";
		break;
	case GEMA:
		out << "G";
		break;
	case SALIDA:
		out << "S";
		break;
	case LIBRE:
		out << "-";
	}
	return out;
}

void cargar_mina(std::istream& fichero, tMina& mina) {

	char c, aux;

	//leemos el plano de la mina
	fichero >> mina.fila >> mina.col;
	//para el "\n"
	fichero.get(aux);
	for (int i = 0; i < mina.fila; ++i) {
		for (int j = 0; j < mina.col; ++j) {
			fichero.get(c);
			mina.plano[i][j] = char2elem(c);
			//posición minero
			if (mina.plano[i][j] == 'J') {
				mina.fila = i;
				mina.col = j;
			}
		}
		fichero.get(aux);
	}
}

void dibujar1_1(tMina const& mina) {

	for (int i = 0; i < mina.fila; ++i) {
		for (int j = 0; j < mina.col; ++j) {
			switch (mina.plano[i][j]) {
			case TIERRA:
				cout << TIERRA;
				break;
			case PIEDRA:
				cout << PIEDRA;
				break;
			case MURO:
				cout << MURO;
				break;
			case GEMA:
				cout << GEMA;
				break;
			case SALIDA:
				cout << SALIDA;
				break;
			case LIBRE:
				cout << LIBRE;
				break;
			case MINERO:
				cout << MINERO;
			}
		}
		cout << "\n";
	}
}

void dibujar3_1(tMina const& mina) {
	int k = 0;
	for (int i = 0; i < mina.fila; ++i) {
		//imprimir la misma fila 3 veces
		k = 0;
		for (k < 3; ++k) {
			for (int j = 0; j < mina.col; ++j) {
				switch (mina.plano[i][j]) {
				case TIERRA:
					cout << TIERRA << TIERRA << TIERRA;
					break;
				case PIEDRA:
					cout << PIEDRA << PIEDRA << PIEDRA;
					break;
				case MURO:
					cout << MURO << MURO << MURO;
					break;
				case GEMA:
					cout << GEMA << GEMA << GEMA;
					break;
				case SALIDA:
					cout << SALIDA << SALIDA << SALIDA;
					break;
				case LIBRE:
					cout << LIBRE << LIBRE << LIBRE;
					break;
				case MINERO:
					cout << MINERO << MINERO << MINERO;
				}
			}
			cout << "\n";
		}
		
	}
}