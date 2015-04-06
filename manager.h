#include <iostream>
#include <string.h>
#include "graph.h"

class Manager {
	// classe responsável pela leitura/escrita de arquivos e montagem do grafo

	public:
		void exportGraph(Graph* graph, FILE* file);

		Graph* createGraphFromFILE(FILE* file);

		FILE* readFile(char* path) {
		    FILE* file;
		    file = fopen(path, "r");

		    if (file == NULL) {
		    	throw "Error opening file.";
		    }

		    return file;
		}
};