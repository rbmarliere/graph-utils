#include "graph.h"

class Manager {
	// classe responsável pela leitura/escrita de arquivos e montagem do grafo

	void exportGraph(Graph* graph, File* file);

	Graph* createGraphFromFile(File* file);

	File* readFile(char* path);
}