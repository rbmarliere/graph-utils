#include <iostream>
#include <string.h>
#include "graph.h"

class Manager {
	// classe responsável pela leitura/escrita de arquivos e montagem do grafo

	public:
		void exportGraph(Graph* graph, FILE* file);

		Graph* createGraphFromFile(FILE* file);

		FILE* openFile(char* path) {
		    FILE* file;
		    file = fopen(path, "r");

		    if (file == NULL) {
		    	std::string errMsg("Error opening file \"");
		    	throw errMsg + path + "\"";
		    }

		    return file;
		}
};