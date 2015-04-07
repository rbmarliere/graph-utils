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
		    output << "graph-utils v" << VERSION << "\n";
		    output << "############# REPORT #############\n\n";
		    output << " -------------------------------- \n";
		    output << "Número de nós: " << graph->getNumNodes() << "\n";
		    output << "Número de arestas: " << graph->getNumEdges() << "\n";
		    output << " -------------------------------- \n";

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

		    	Node* j = i->getNextInEdges();
		    	if (j != nullptr) {
		    		output << "Primeira aresta com: " << j->getValue() << "\n";
		    		output << "Segunda aresta com: " << j->getNextInEdges()->getValue() << "\n";
		    		output << "Terceira aresta com: " << j->getNextInEdges()->getNextInEdges()->getValue() << "\n";
		    		output << "Quarta aresta com: " << j->getNextInEdges()->getNextInEdges()->getNextInEdges()->getValue() << "\n";
			    	// bool hasEdges = false;
			    	// while (true) {
			    	// 	cout << j->getValue();
			    	// 	if (j == nullptr) {
			    	// 		break;
			    	// 	}

			    	// 	if (!hasEdges) {
				    // 		output << "Possui arestas com: ";
				    // 		hasEdges = true;
				    // 	}

			    	// 	output << j->getValue() << ", ";

			    	// 	j = j->getNextInEdges();
			    	// }
			    }

		    	i = i->getNextInGraph();

		    	output << "\n @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ \n";
		    }

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

			    	Node* n1 = new Node(v1, 0);
					Node* n2 = new Node(v2, 0);

					graph->insertNode(n1);
					graph->insertNode(n2);
					graph->insertEdge(n1, n2);
			    }

				countLn++;
			}

			input.close();

			graph->setNumEdges(countLn-1);

			return graph;
		}
};