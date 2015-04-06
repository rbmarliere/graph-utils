#include <iostream>
#include <cstring>
#include "manager.h"

using namespace std;

int main(int argc, char* argv[])
{
	Manager manager;

	// checa se usuario inseriu quantidade certa de parametros
	if (argc != 5) {
		cout << "usage: graph-utils -i <input file> -o <output file>\n";
		return 0;
	}

	// path para ambos os parametros
	char* input;
	char* output;

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
		FILE* inputFile = manager.openFile(input);
		// Graph* inputGraph = manager.createGraphFromFile(inputFile);

		// Manager::write output

		// fclose(inputFile);
		// fclose(outputFile);
	} catch (std::string msg) {
		cout << "Error: " << msg;
	}

	return 1;
}