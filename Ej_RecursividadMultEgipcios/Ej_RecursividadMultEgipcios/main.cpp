#include <iostream>
#include <fstream>

using namespace std;

int prod(int a, int b) {
	// Inicializamos s
	int s = 0;
	// Casos recursivos
	if (a == 0 || b == 0)
		s = 0;
	if (a == 1)
		s = b;
	if (b == 1)
		s = a;
	// Casos recursivos
	if ((b > 1) && ((b % 2) == 0))
		s = prod(2 * a, b / 2);
	else if ((b > 1) && ((b % 2) != 0))
		s = prod(2 * a, b / 2) + a;
	return s;
}

bool resuelveCaso() {
	int n1, n2, sol;
	cin >> n1;
	if (!cin)
		return false;
	cin >> n2;
	sol = prod(n1, n2);
	cout << sol << "\n";
}

int main() {
	std::ifstream in("datos.in");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
	std::ofstream out("datos.out");
	auto coutbuf = std::cout.rdbuf(out.rdbuf());

	while (resuelveCaso());

	std::cin.rdbuf(cinbuf);
	std::cout.rdbuf(coutbuf);
	system("PAUSE");

	return 0;
}