// Autor/a: Estibaliz Zubimendi Solaguren
// email: estizubi@ucm.es
// Compilador y S.O. utilizado: Visual Studio 2019
// Nombre del problema: Número de digitos de un número
#include <iostream>
#include <fstream>

using namespace std;

int numDig(unsigned long long int n) {
	if (n < 10)
		return 1;
	else
		return 1 + numDig(n / 10);
}

bool resolver() {
	unsigned long long n;
	cin >> n;
	if (!cin)
		return false;
	cout << numDig(n) << "\n";
	return true;
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("casos.in");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
    std::ofstream out("datos.out");
    auto coutbuf = std::cout.rdbuf(out.rdbuf());

#endif

    while (resolver());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    std::cout.rdbuf(coutbuf);
    system("PAUSE");
#endif
    return 0;
}