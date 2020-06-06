// Autor/a: Estibaliz Zubimendi Solaguren
// email: estizubi@ucm.es
// Compilador: Visual Studio 2019
// Nombre del problema: Pr�ctica minero v2
#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

// n�mero total de minas que se pueden recorrer
const int NUM_TOTAL_MINAS = 5;
// tama�o inicial del array din�mico
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

// para gestionar las minas, utilizamos lo mismo que con los jugadores
// utilizamos la b�squeda binaria ya que tenemos un array ordenado, busca por id
bool buscarMina(tPuntuaciones& marcador, int& pos_mina, int id_mina, int pos_jugador);

// carga las puntuaciones de puntuaciones.txt en el array din�mico
bool cargar_Marcador(tPuntuaciones& marcador);

// vuelca en puntuaciones.txt toda la informaci�n del marcador
bool guardar_Marcador(tPuntuaciones& marcador);

// muestra las minas recorridas de una persona, ordenadas por nivel
void mostrar_Minas_Usuario(const tPuntuaciones& marcador, int cont);

// muestra los jugadores y sus puntuaciones totales, ordenadas por orden alfab�tico
void mostrar_Alfabetico(const tPuntuaciones& marcador);

// muestra datos de todos los usuarios, ordenados alfab�ticamente y las minas crecientemente
void mostrar_Datos_Usuario(const tPuntuaciones& marcador);

// inicializa el array din�mico
void inicializar_Marcador(tPuntuaciones& marcador);

// duplica el tama�o del array
void aumentar_Capacidad(tPuntuaciones& marcador);

// libera memoria din�mica
// destruye el array din�mico
void destruir(tPuntuaciones& marcador);

// busca un jugador por nombre y devuelve si lo ha encontrado o no y su posici�n
// si no lo ha encontrado entonces devuelve d�nde deber�a estar
bool buscar(const string& nombre, const tPuntuaciones& marcador, int& pos);

// inserta ordenadamente en pos un nuevo jugador
void insertar(tPuntuaciones& marcador, string const& nombre, int pos);