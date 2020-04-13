#include "mina.h"

tCasilla char2elem(char c) {

	tCasilla elem;

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
	case ' ':
		elem = LIBRE;
	}
	return elem;
};

void cargar_mina(ifstream& fichero, tMina& mina) {

	char c, aux;

	//leemos el plano de la mina
	fichero >> mina.nFilas >> mina.nColumnas;
	//para el "\n"
	fichero.get(aux);
	for (int i = 0; i < mina.nFilas; ++i) {
		for (int j = 0; j < mina.nColumnas; ++j) {
			fichero.get(c);
			mina.plano[i][j] = char2elem(c);
			//posición minero
			if (mina.plano[i][j] == MINERO) {
				mina.filaMinero = i;
				mina.columnaMinero = j;
			}
		}
		fichero.get(aux);
	}
}

void caracter_color(tCasilla casilla, char& caracter, int& numColor) {
	switch (casilla) {
	// solo se tienen en cuenta estas cuatro casillas ya que repiten caracteres
	case TIERRA:
		caracter = '.';
		numColor = 4;
		break;
	case PIEDRA:
		caracter = '@';
		numColor = 4;
		break;
	case MURO:
		caracter = 'X';
		numColor = 4;
		break;
	case LIBRE:
		caracter = ' ';
		numColor = 4;
	}
}

void colorFondo(int color) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, 15 | (color << 4));
}

void dibujar1_1(const tMina& mina) {

	char plano_caracteres[MAX][MAX];
	int plano_colores[MAX][MAX];

	for (int i = 0; i < mina.nFilas; ++i) {
		for (int j = 0; j < mina.nColumnas; ++j) {
			switch (mina.plano[i][j]) {
			// en todos los cuatro casos siguientes hay que llamar a caracter_color
			case TIERRA:
			case PIEDRA:
			case MURO:
			case LIBRE:
				caracter_color(mina.plano[i][j], plano_caracteres[i][j], plano_colores[i][j]);
				break;
			case GEMA:
				plano_caracteres[i][j] = 'G';
				plano_colores[i][j] = 2;
				break;
			case DINAMITA:
				plano_caracteres[i][j] = 'D';
				plano_colores[i][j] = 9;
				break;
			case SALIDA:
				plano_caracteres[i][j] = 'S';
				plano_colores[i][j] = 1;
				break;
			case MINERO:
				plano_caracteres[i][j] = 'M';
				plano_colores[i][j] = 7;
			}
		}
	}
	system("cls");
	for (int i = 0; i < mina.nFilas; ++i) {
		for (int j = 0; j < mina.nColumnas; ++j) {
			colorFondo(plano_colores[i][j]);
			cout << setw(2) << plano_caracteres[i][j];
			colorFondo(0);
		}
		cout << "\n";
	}
}

void dibuja3x3(tCasilla casilla, tPlanoCaracteres& caracteres, tPlanoColores& colores, int i, int j) {
	for (int k = 0; k < 3; ++k) {
		for (int l = 0; l < 3; ++l) {
			caracter_color(casilla, caracteres[i * 3 + k][j * 3 + l], colores[i * 3 + k][j * 3 + l]);
		}
	}
}

void dibujar1_3(const tMina& mina) {
	tPlanoCaracteres plano_caracteres;
	tPlanoColores plano_colores;

	for (int i = 0; i < mina.nFilas; ++i) {
		for (int j = 0; j < mina.nColumnas; ++j) {
			switch (mina.plano[i][j]) {
			case LIBRE:
			case PIEDRA:
			case TIERRA:
			case MURO:
				dibuja3x3(mina.plano[i][j], plano_caracteres, plano_colores, i, j);
				break;
			case GEMA:
				//primero actualizamos el carácter
				plano_caracteres[i * 3][j * 3] = 'G';
				plano_caracteres[i * 3][j * 3 + 1] = 'E';
				plano_caracteres[i * 3][j * 3 + 2] = 'M';
				plano_caracteres[i * 3 + 1][j * 3] = 'E';
				plano_caracteres[i * 3 + 1][j * 3 + 1] = 'E';
				plano_caracteres[i * 3 + 1][j * 3 + 2] = 'A';
				plano_caracteres[i * 3 + 2][j * 3] = 'M';
				plano_caracteres[i * 3 + 2][j * 3 + 1] = 'A';
				plano_caracteres[i * 3 + 2][j * 3 + 2] = 'M';
				//ahora el color
				plano_colores[i * 3][j * 3] = 2;
				plano_colores[i * 3][j * 3 + 1] = 2;
				plano_colores[i * 3][j * 3 + 2] = 2;
				plano_colores[i * 3 + 1][j * 3] = 2;
				plano_colores[i * 3 + 1][j * 3 + 1] = 2;
				plano_colores[i * 3 + 1][j * 3 + 2] = 2;
				plano_colores[i * 3 + 2][j * 3] = 2;
				plano_colores[i * 3 + 2][j * 3 + 1] = 2;
				plano_colores[i * 3 + 2][j * 3 + 2] = 2;
				break;
			case DINAMITA:
				plano_caracteres[i * 3][j * 3] = 'D';
				plano_caracteres[i * 3][j * 3 + 1] = 'I';
				plano_caracteres[i * 3][j * 3 + 2] = 'N';
				plano_caracteres[i * 3 + 1][j * 3] = 'A';
				plano_caracteres[i * 3 + 1][j * 3 + 1] = 'M';
				plano_caracteres[i * 3 + 1][j * 3 + 2] = 'I';
				plano_caracteres[i * 3 + 2][j * 3] = 'T';
				plano_caracteres[i * 3 + 2][j * 3 + 1] = 'A';
				plano_caracteres[i * 3 + 2][j * 3 + 2] = '!';
				plano_colores[i * 3][j * 3] = 9;
				plano_colores[i * 3][j * 3 + 1] = 9;
				plano_colores[i * 3][j * 3 + 2] = 9;
				plano_colores[i * 3 + 1][j * 3] = 9;
				plano_colores[i * 3 + 1][j * 3 + 1] = 9;
				plano_colores[i * 3 + 1][j * 3 + 2] = 9;
				plano_colores[i * 3 + 2][j * 3] = 9;
				plano_colores[i * 3 + 2][j * 3 + 1] = 9;
				plano_colores[i * 3 + 2][j * 3 + 2] = 9;
				break;
			case SALIDA:
				plano_caracteres[i * 3][j * 3] = 'S';
				plano_caracteres[i * 3][j * 3 + 1] = 'A';
				plano_caracteres[i * 3][j * 3 + 2] = 'L';
				plano_caracteres[i * 3 + 1][j * 3] = 'I';
				plano_caracteres[i * 3 + 1][j * 3 + 1] = 'D';
				plano_caracteres[i * 3 + 1][j * 3 + 2] = 'A';
				plano_caracteres[i * 3 + 2][j * 3] = 'E';
				plano_caracteres[i * 3 + 2][j * 3 + 1] = 'S';
				plano_caracteres[i * 3 + 2][j * 3 + 2] = 'C';
				plano_colores[i * 3][j * 3] = 1;
				plano_colores[i * 3][j * 3 + 1] = 1;
				plano_colores[i * 3][j * 3 + 2] = 1;
				plano_colores[i * 3 + 1][j * 3] = 1;
				plano_colores[i * 3 + 1][j * 3 + 1] = 1;
				plano_colores[i * 3 + 1][j * 3 + 2] = 1;
				plano_colores[i * 3 + 2][j * 3] = 1;
				plano_colores[i * 3 + 2][j * 3 + 1] = 1;
				plano_colores[i * 3 + 2][j * 3 + 2] = 1;
				break;
			case MINERO:
				plano_caracteres[i * 3][j * 3] = 'M';
				plano_caracteres[i * 3][j * 3 + 1] = 'I';
				plano_caracteres[i * 3][j * 3 + 2] = '-';
				plano_caracteres[i * 3 + 1][j * 3] = '-';
				plano_caracteres[i * 3 + 1][j * 3 + 1] = 'N';
				plano_caracteres[i * 3 + 1][j * 3 + 2] = 'E';
				plano_caracteres[i * 3 + 2][j * 3] = 'R';
				plano_caracteres[i * 3 + 2][j * 3 + 1] = 'O';
				plano_caracteres[i * 3 + 2][j * 3 + 2] = '!';
				plano_colores[i * 3][j * 3] = 7;
				plano_colores[i * 3][j * 3 + 1] = 7;
				plano_colores[i * 3][j * 3 + 2] = 7;
				plano_colores[i * 3 + 1][j * 3] = 7;
				plano_colores[i * 3 + 1][j * 3 + 1] = 7;
				plano_colores[i * 3 + 1][j * 3 + 2] = 7;
				plano_colores[i * 3 + 2][j * 3] = 7;
				plano_colores[i * 3 + 2][j * 3 + 1] = 7;
				plano_colores[i * 3 + 2][j * 3 + 2] = 7;
			}
		}
	}

	system("cls");
	for (int i = 0; i < mina.nFilas * 3; ++i) {
		for (int j = 0; j < mina.nColumnas * 3; ++j) {
			colorFondo(plano_colores[i][j]);
			cout << setw(2) << plano_caracteres[i][j];
			colorFondo(0);
		}
		cout << "\n";
	}
}

bool dentroPlano(const tMina& mina, int x, int y) {
	return (x >= 0 && x < mina.nFilas && y >= 0 && y < mina.nColumnas);
}