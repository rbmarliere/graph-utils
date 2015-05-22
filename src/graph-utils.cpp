#include <iostream>
#include <cstring>
#include <ctime>
#include "../lib/manager.hpp"

using namespace std;

int main(int argc, char* argv[])
{
	unsigned long int start_s = clock();

	Manager manager;

	// verifica se usuario inseriu quantidade certa de parametros
	if (argc != 5) {
		cout << "usage: graph-utils -i <input file> -o <output file>\n";
		return 0;
	}

	// path para ambos os parametros
	char* input = nullptr;
	char* output = nullptr;

	// parser dos parametros
	for (int i=1; i<argc; i++) {
		if (i+1 != argc) {
			if (strcmp(argv[i], "-i") == 0) {
				input = argv[i+1];
			} else if (strcmp(argv[i], "-o") == 0) {
				output = argv[i+1];
			}
		}
	}

	try {
		Graph* graph = manager.createGraph(input);

		manager.exportGraph(graph, output);

		cout << "dumped to " << output << "\n";
	} catch (string msg) {
		cout << "error: " << msg;
	}

	unsigned long int stop_s = clock();
	cout << "time: " << (stop_s - start_s) / double(CLOCKS_PER_SEC)*1000 << "ms\n";

	return 1;
}