#include <iostream>
#include <sstream>
#include <fstream>
#include <string.h>
#include "graph.h"
#define VERSION 0.1

using namespace std;

class Manager {
	private:
		ofstream& printHeader(ofstream &output, Graph* graph) {
		    output << "#### graph-utils v" << VERSION << " REPORT ####\n\n";
		    output << "---------------------------------\n";
		    output << "Número de nós: " << graph->getNumNodes() << "\n";
		    output << "Número de arestas: " << graph->getNumEdges() << "\n";
		    output << "É conexo? " << graph->isConnected(graph) << "\n";
		    output << "---------------------------------\n";

		    return output;
		}

		ofstream& printNodeInfo(ofstream &output, Graph* graph) {
			Node* i = graph->getRoot();
		    while (true) {
		    	if (i == nullptr) {
		    		break;
		    	}

		    	output << "Nó: " << i->getValue() << "\n";
		    	output << "Grau: " << i->getDegree() << "\n";

		    	Edge* j = i->getEdges();
		    	if (j != nullptr) {
		    		output << "Possui arestas com: ";
			    	while (true) {
			    		if (j == nullptr) {
			    			break;
			    		}
			    		output << j->getNode()->getValue() << " ";

			    		j = j->getNext();
			    	}
			    }

		    	i = i->getNextInGraph();

		    	output << "\n=================================\n";
		    }

		    output << "\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";

		    return output;
		}
	public:
		void exportGraph(Graph* graph, char* path) {
			ofstream output (path);
			if (!output.is_open()) {
				std::string errMsg("Error opening file \"");
		    	throw errMsg + path + "\"";
		    }

		    printHeader(output, graph);
		    printNodeInfo(output, graph);

		    output.close();
		}

		Graph* createGraph(char* path) {
			ifstream input (path);
			if (!input.is_open()) {
				std::string errMsg("Error opening file \"");
		    	throw errMsg + path + "\"";
		    }

			Graph* graph = new Graph();
			int v1 = 0, v2 = 0, num_nodes = 0, countLn = 0;
			string line;
			while (getline(input, line)) {
			    istringstream iss(line);

			    if (countLn == 0) {
			    	iss >> num_nodes;
			    	graph->setNumNodes(num_nodes);
			    } else {
			    	iss >> v1 >> v2;

					// cout << n1->getValue() << " to " << n2->getValue() << "\n";

					Node* n1 = graph->insertNode(v1, 0);
					Node* n2 = graph->insertNode(v2, 0);
					graph->insertEdge(n1, n2);
			    }

				countLn++;
			}

			input.close();

			graph->setNumEdges(countLn-1);

			return graph;
		}
};