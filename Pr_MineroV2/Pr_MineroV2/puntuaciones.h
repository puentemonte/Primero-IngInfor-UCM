#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

// n�mero total de minas que se pueden recorrer
const int NUM_TOTAL_MINAS = 5;
// tama�o inicial de 
const int TAM_INICIAL = 2;
// variables globales
const int A = 10;
const int B = 2;
typedef struct {
	int idMina, numMovimientos, numGemas, numDinamitas, ptosMina;
	// ptosMina = ancho * alto + A * numGemas - numMovimientos - B * numDinamitas
}tDatosMina;
typedef struct {
	string nombre;
	int punt_total;
	int minasRecorridas;
	tDatosMina vMinasRecorridas[NUM_TOTAL_MINAS];
}tPuntuacionJugador;
typedef struct {
	int capacidad, num_jugadores;
	tPuntuacionJugador* array_clasificacion;
}tPuntuaciones;

// carga las puntuaciones de puntuaciones.txt en el array din�mico
bool cargar_Marcador(tPuntuaciones& marcador);

// guarda en puntuaciones.txt la informaci�n del array din�mico
bool guardar_Marcador(tPuntuaciones& marcador);

// muestra las minas recorridas de una persona, ordenadas por nivel
void mostrar_Minas_Usuario(const tPuntuaciones& marcador, int cont);

// muestra los jugadores y sus puntuaciones totales, ordenadas por orden alfab�tico
void mostrar_Alfabetico(const tPuntuaciones& marcador);

//muestra datos de todos los usuarios, ordenados alfab�ticamente y las minas crecientemente
void mostrar_Datos_Usuario(const tPuntuaciones& marcador);

// inicializa el array din�mico
void inicializar_Marcador(tPuntuaciones& marcador);

// duplica el tama�o del array
void aumentar_Capacidad(tPuntuaciones& marcador);

// libera memoria din�mica
void destruir(tPuntuaciones& marcador);

// busca un nombre en el array din�mico, devuelve true si lo encuentra y la pos
// si no lo encuentra devuelve la pos donde deber�a estar (final?)
bool buscar(const string& nombre, const tPuntuaciones& marcador, int& pos);

// inserta ordenadamente en pos un nuevo jugador
void insertar(tPuntuaciones& marcador, string const& nombre, int pos);