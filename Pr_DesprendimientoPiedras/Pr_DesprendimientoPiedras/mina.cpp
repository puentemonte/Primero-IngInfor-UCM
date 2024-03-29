// Autor/a: Estibaliz Zubimendi Solaguren
// email: estizubi@ucm.es
// Compilador y S.O. utilizado: Microsoft Visual Studio 2019
// Nombre del problema: Desprendimiento piedras
#include "mina.h"
using namespace std;

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

ostream& operator<< (ostream& out, tElemento const& e) {
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

void cargar_mina(istream& fichero, tMina& mina) {

	char c, aux;

	//leemos el plano de la mina
	fichero >> mina.fila >> mina.col;
	//para el "\n"
	fichero.get(aux);
	for (int i = 0; i < mina.fila; ++i) {
		for (int j = 0; j < mina.col; ++j) {
			fichero.get(c);
			mina.plano[i][j] = char2elem(c);
			//posici�n minero
			if (mina.plano[i][j] == MINERO) {
				mina.filaMinero = i;
				mina.colMinero = j;
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
	int l = 0;
	for (int i = 0; i < mina.fila; ++i) {
		//imprimir la misma fila 3 veces
		l = 0;
		for (int k = l; k < 3; ++k) {
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

bool dentroPlano(const tMina& mina, int x, int y) {
	return (x >= 0 && x <= mina.fila && y >= 0 && y <= mina.col);
}