#include <iostream>
#include <sstream>
#include <fstream>
#include <string.h>
#include "graph.h"

using namespace std;

class Manager {
	// classe responsável pela leitura/escrita de arquivos e montagem do grafo

	public:
		void exportGraph(Graph* graph, char* path) {
			ofstream output (path);
			if (!output.is_open()) {
				std::string errMsg("Error opening file \"");
		    	throw errMsg + path + "\"";
		    }
		}

		Graph* createGraph(char* path) {
			ifstream input (path);
			if (!input.is_open()) {
				std::string errMsg("Error opening file \"");
		    	throw errMsg + path + "\"";
		    }

			Graph* graph;
			int v1 = 0, v2 = 0, num_nodes = 0, countLn = 0;
			string line;
			while (std::getline(input, line))
			{
			    istringstream iss(line);

			    if (countLn == 0) {
			    	iss >> num_nodes;
			    	graph->setNumNodes(num_nodes);
			    	cout << num_nodes << "\n";
			    } else {
			    	iss >> v1 >> v2;
			    	cout << v1 << " " << v2 << "\n";
			    	Node* n1 = new Node(v1, 0);
					Node* n2 = new Node(v2, 0);

					graph->insertNode(n1);
					graph->insertNode(n2);
					graph->insertEdge(n1, n2);
			    }

				countLn++;
			}

			graph->setNumEdges(countLn);

			return graph;
		}
};