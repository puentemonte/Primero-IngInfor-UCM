#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int mxEsp = 20;
const int mxCons = 200;

typedef struct {
	int codigo;
	string nombre;
}tEspecialidad;
typedef struct {
	int codigo, num_consultas;
	string fecha;
}tConsulta;
// array dinámico de especialidades
typedef struct {
	tEspecialidad* array_dinamico;
	int tam, capacidad;
}tListaEspecialidades;

// array de datos dinámicos
typedef tConsulta* tPtrConsultas;
typedef tPtrConsultas tListaConsultas[mxCons];
// array aux
typedef tConsulta tArrayAux[mxCons];

void inicializar(tListaEspecialidades& lista) {
	lista.capacidad = mxEsp;
	lista.tam = 0;
	lista.array_dinamico = new tEspecialidad[mxEsp];
}

void ordenarPorFecha(tListaConsultas& lista, int total) {
	int pos;
	tConsulta* tmp = NULL;
	for (int i = 1; i < total; ++i) {
		pos = i;
		while ((pos > 0) && lista[pos - 1]->fecha > lista[pos]->fecha) {
			tmp = lista[pos];
			lista[pos] = lista[pos - 1];
			lista[pos - 1] = tmp;
			--pos;
		}
	}
}

bool buscarNombre(const tListaEspecialidades& especialidades, int &pos, int codigo) {
	// buscamos pos de código
	int ini = 0, fin = especialidades.tam - 1, mitad;
	bool encontrada = false;
	while ((ini <= fin) && !encontrada) {
		mitad = (ini + fin) / 2;
		if (codigo == especialidades.array_dinamico[mitad].codigo)
			encontrada = true;
		else if (codigo < especialidades.array_dinamico[mitad].codigo)
			fin = mitad - 1;
		else
			ini = mitad + 1;
	}
	if (encontrada)
		pos = mitad;
	else
		pos = ini;
	return encontrada;
}

void solve() {
	tListaEspecialidades lista_especialidades;
	tListaConsultas lista_consultas;
	tArrayAux array_aux;
	// inicializamos el array dinámico
	inicializar(lista_especialidades);

	// primero leemos las consultas
	int contador = 0;
	cin >> array_aux[contador].codigo;
	while (array_aux[contador].codigo != -1) {
		cin >> array_aux[contador].fecha >> array_aux[contador].num_consultas;
		++contador;
		cin >> array_aux[contador].codigo;
	}
	// inicializamos el array de datos dinámicos
	for (int i = 0; i < contador; ++i) {
		lista_consultas[i] = &array_aux[i];
	}

	// luego leemos las especialidades
	cin >> lista_especialidades.array_dinamico[lista_especialidades.tam].codigo;
	while (lista_especialidades.array_dinamico[lista_especialidades.tam].codigo != -1) {
		getline(cin, lista_especialidades.array_dinamico[lista_especialidades.tam].nombre);
		++lista_especialidades.tam;
		cin >> lista_especialidades.array_dinamico[lista_especialidades.tam].codigo;
	}

	// primero ordenamos
	ordenarPorFecha(lista_consultas, contador);

	int pos;
	string respuesta;
	for (int i = 0; i < contador; ++i) {
		cout << lista_consultas[i]->fecha;
		// realizamos una búsqueda binaria sobre un array ordenado
		if (buscarNombre(lista_especialidades, pos, lista_consultas[i]->codigo))
			cout << lista_especialidades.array_dinamico[pos].nombre << " " << lista_consultas[i]->num_consultas;
		else
			cout << " Especialidad inexistente";
		cout << "\n";
	}
}

int main() {
#ifndef DOMJUDGE
	std::ifstream in("sample-18.1.in");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	std::ofstream out("datos.out");
	auto coutbuf = std::cout.rdbuf(out.rdbuf());

#endif

	solve();

	// para dejar todo como estaba al principio
#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	std::cout.rdbuf(coutbuf);
	system("PAUSE");
#endif
	return 0;
}