// Autor/a: Estibaliz Zubimendi Solaguren
// email: estizubi@ucm.es
// Compilador y S.O. utilizado: Microsoft Visual Studio 2019
// Nombre del problema: Desprendimiento piedras
#pragma once
#include <iostream>
#include <fstream>
#include <istream>
#include <utility>
using namespace std;

typedef enum tElemento { TIERRA, PIEDRA, MURO, GEMA, SALIDA, LIBRE, MINERO };
const int DIM = 50;
typedef tElemento tPlano[DIM][DIM];
typedef struct {
	tPlano plano;
	int fila = 0, col = 0, filaMinero = 0, colMinero = 0;
}tMina;

//transforma un carácter en un valor del tipo enumerado tElemento
tElemento char2elem(char c);

//para escribir los valores del tipo enumerado
ostream& operator<< (ostream& out, tElemento const& e);

//lee el plano de la mina del fichero y lo guarda en memoria, actualiza la pos del minero
void cargar_mina(istream& fichero, tMina& mina);

//muestra por pantalla el plano en escala 1:1
void dibujar1_1(tMina const& mina);
//muestra por pantalla el plano en escala 3:1
void dibujar3_1(tMina const& mina);

//comprueba si una posición está dentro del plano
bool dentroPlano(const tMina& mina, int x, int y);