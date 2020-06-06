// Autor/a: Estibaliz Zubimendi Solaguren
// email: estizubi@ucm.es
// Compilador: Visual Studio 2019
// Nombre del problema: Práctica minero v2
#pragma once
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <iomanip>
#include <string>
#include <utility>
#include <conio.h>
using namespace std;

const int MAX = 50;
typedef enum { LIBRE, TIERRA, GEMA, PIEDRA, MURO, DINAMITA, SALIDA, MINERO, VACIO } tCasilla;
typedef tCasilla tPlano[MAX][MAX];
typedef struct {
	tPlano plano;
	//posición en la que se encuentra el minero
	int filaMinero, columnaMinero;
	int nFilas, nColumnas;
}tMina;
typedef char tPlanoCaracteres[3 * MAX][3 * MAX];
typedef int tPlanoColores[3 * MAX][3 * MAX];

//transforma un carácter en un valor del tipo enumerado tElemento
tCasilla char2elem(char c);

//lee el plano de la mina del fichero y lo guarda en memoria, actualiza la pos del minero
void cargar_mina(ifstream& fichero, tMina& mina);

//muestra por pantalla el plano en escala 1:1
void dibujar1_1(const tMina& mina);
//muestra por pantalla el plano en escala 3:1
void dibujar1_3(const tMina& mina);
// función auxiliar para no repetir mucho código en dibujar1_3
// con 2 for asigna el color adecuado a cada casilla
void plano_colores_aux(tPlanoColores& plano_colores, int color, int i, int j);
//dibuja las casillas aumentadas tres veces. Lla casilla sirve para actualizar 
//el plano de caracteres y colores en las coordenadas i, j
void dibuja3x3(tCasilla casilla, tPlanoCaracteres& caracteres, tPlanoColores& colores, int i, int j);

//asignar color al fondo
void colorFondo(int color);

// para los elementos que tienen el mismo color de fondo, les asigna un char y el color
void caracter_color(tCasilla casilla, char& caracter, int& numColor);

//comprueba si una posición está dentro del plano
bool dentroPlano(const tMina& mina, int x, int y);
