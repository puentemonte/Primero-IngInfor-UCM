#pragma once
using namespace std;

typedef enum tElemento {TIERRA, PIEDRA, MURO, GEMA, SALIDA, LIBRE, MINERO};
const int DIM = 50;
typedef tElemento tPlano[DIM][DIM];
typedef struct {
	tPlano plano;
	int fila, col, filaMinero, colMinero;
}tMina;

//transforma un carácter en un valor del tipo enumerado tElemento
tElemento char2elem(char c);

//para escribir los valores del tipo enumerado
std::ostream& operator<< (std::ostream& out, tElemento const& e);

//lee el plano de la mina del fichero y lo guarda en memoria, actualiza la pos del minero
void cargar_mina(std::istream& fichero, tMina& mina);

//muestra por pantalla el plano en escala 1:1
void dibujar1_1(tMina const& mina);
//muestra por pantalla el plano en escala 3:1
void dibujar3_1(tMina const& mina);