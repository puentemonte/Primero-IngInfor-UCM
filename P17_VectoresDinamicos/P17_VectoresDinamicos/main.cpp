// Autor/a: Estibaliz Zubimendi Solaguren
// email: estizubi@ucm.es
// Compilador: Visual Studio 2019
// Nombre problema: Vectores dinámicos
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;
const int TAM_INICIAL = 3;
typedef struct {
	string nombre;
	int unidades;
}tObj;
typedef struct {
	tObj* arrayDinam;
	// tam = número de elementos
	// capacidad = capacidad total
	int tam, capacidad;
}tLista;

bool encontrado(const tLista& lista, string& nombre, int& pos) {
	// utilizamos selección con intercambios para buscar el elemento
	// devolvemos true si lo ha encontrado y la posición por parámetro
	bool encontrado = false;
	int i = 0;
	while (!encontrado && i < lista.tam) {
		if (lista.arrayDinam[i].nombre == nombre)
			encontrado = true;
		else
			++i;
	}
	pos = i;
	return encontrado;
}

void visualizar(const tLista& lista) {
	// por cada elemento que hay en el array dinámico, visualizamos el nombre y unidades
	for (int i = 0; i < lista.tam; ++i) {
		cout << lista.arrayDinam[i].nombre << " " << lista.arrayDinam[i].unidades << endl;
	}
	cout << "---\n";
}

void ampliar(tLista& lista) {
	// creamos un puntero auxiliar y lo inicializamos a null
	tObj* aux = nullptr;
	// ese aux va a apuntar a un array con tamaño doble del array que teníamos
	aux = new tObj[2 * lista.capacidad];
	// ahora copia todos los elementos que había en el array antiguo
	for (int i = 0; i < lista.tam; ++i) {
		aux[i] = lista.arrayDinam[i];
	}
	// liberamos memoria
	delete[]lista.arrayDinam;
	// volvemos a pasar la información de aux a lista
	lista.arrayDinam = aux;
	// aumentamos la capacidad
	lista.capacidad *= 2;
	// aux vuelve a apuntar a null
	aux = nullptr;
}

void resuelveCaso() {
	tLista lista;
	// inicializamos
	lista.capacidad = TAM_INICIAL;
	lista.tam = 0;
	lista.arrayDinam = new tObj[TAM_INICIAL];
	char a, aux;
	string nombre;
	int pos = 0;
	cin >> a;
	// si leemos F, se finaliza el programa
	while (a != 'F') {
		// visualizamos el array que tenemos
		if (a == 'L')
			visualizar(lista);
		else {
			int num = 0;
			cin >> nombre >> num;
			if (encontrado(lista, nombre, pos)) {
				// aumentamos las unidades de un producto existente
				if (a == 'A')
					lista.arrayDinam[pos].unidades += num;
				// restamos las unidades de un producto existente
				//else if (a == 'R') {
				//	// si las unidades que le vamos a restar son mayores de las que hay, ponemos a 0
				//	if (lista.arrayDinam[pos].unidades < num)
				//		lista.arrayDinam[pos].unidades = 0;
				//	else
				//		// restamos la cantidad en caso contrario
				//		lista.arrayDinam[pos].unidades -= num;
				//	
				//}
				else
					lista.arrayDinam[pos].unidades = max(lista.arrayDinam[pos].unidades - num, 0);
			}
			// si el objeto no existe y le estamos sumando lo añadimos al array
			else if (!encontrado(lista, nombre, pos) && a == 'A'){
				// si el array se ha llenado, hay que aumentar su capacidad
				if (lista.tam == lista.capacidad - 1)
					ampliar(lista);
				// le asignamos un nombre y unas unidades al nuevo objeto
				lista.arrayDinam[lista.tam].nombre = nombre;
				lista.arrayDinam[lista.tam].unidades = num;
				// el número de elementos de la lista aumenta por uno
				++lista.tam;
			}
		}
		// salto de línea
		cin.get(aux);
		cin >> a;
	}
	// liberamos la memoria
	delete[] lista.arrayDinam;
	// el puntero ahora apunta a una dirección nula
	lista.arrayDinam = nullptr;
}

int main() {
	// ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
	std::ifstream in("sample-17.1.in");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	std::ofstream out("datos.out");
	auto coutbuf = std::cout.rdbuf(out.rdbuf());
#endif

	resuelveCaso();

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	std::cout.rdbuf(coutbuf);
	system("PAUSE");
#endif
	return 0;
}