// Autor/a: Estibaliz Zubimendi Solaguren
// email: estizubi@ucm.es
// Compilador: Visual Studio 2019
// Nombre del problema: Práctica minero v2
#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;

// número total de minas que se pueden recorrer
const int NUM_TOTAL_MINAS = 5;
// tamaño inicial del array dinámico
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
// utilizamos la búsqueda binaria ya que tenemos un array ordenado, busca por id
bool buscarMina(tPuntuaciones& marcador, int& pos_mina, int id_mina, int pos_jugador);

// carga las puntuaciones de puntuaciones.txt en el array dinámico
bool cargar_Marcador(tPuntuaciones& marcador);

// vuelca en puntuaciones.txt toda la información del marcador
bool guardar_Marcador(tPuntuaciones& marcador);

// muestra las minas recorridas de una persona, ordenadas por nivel
void mostrar_Minas_Usuario(const tPuntuaciones& marcador, int cont);

// muestra los jugadores y sus puntuaciones totales, ordenadas por orden alfabético
void mostrar_Alfabetico(const tPuntuaciones& marcador);

// muestra datos de todos los usuarios, ordenados alfabéticamente y las minas crecientemente
void mostrar_Datos_Usuario(const tPuntuaciones& marcador);

// inicializa el array dinámico
void inicializar_Marcador(tPuntuaciones& marcador);

// duplica el tamaño del array
void aumentar_Capacidad(tPuntuaciones& marcador);

// libera memoria dinámica
// destruye el array dinámico
void destruir(tPuntuaciones& marcador);

// busca un jugador por nombre y devuelve si lo ha encontrado o no y su posición
// si no lo ha encontrado entonces devuelve dónde debería estar
bool buscar(const string& nombre, const tPuntuaciones& marcador, int& pos);

// inserta ordenadamente en pos un nuevo jugador
void insertar(tPuntuaciones& marcador, string const& nombre, int pos);