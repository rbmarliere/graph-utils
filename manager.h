#include <iostream>
#include <sstream>
#include <fstream>
#include <string.h>
#include "graph.h"
#define VERSION 0.2

using namespace std;

class Manager {
	private:
		Graph* graph; // singleton

		ofstream& printLine(ofstream &output, char c) {
			int i = 0;

			output << "\n";
			while (i < 33) {
				output << c;
				i++;
			}
			output << "\n";

			return output;
		}

		ofstream& printHeader(ofstream &output) {
			output << "#################################\n";
		    output << "#### graph-utils v" << VERSION << " REPORT ####\n";
		    output << "#################################";
		    printLine(output, '=');

		    return output;
		}

		ofstream& printGraphInfo(ofstream &output) {
			output << "INFORMAÇÕES DO GRAFO\n\n";
		    output << "Número de nós: " << graph->getNumNodes() << "\n";
		    output << "Número de arestas: " << graph->getNumEdges() << "\n";
		    output << "É conexo? " << graph->isConnected() << "\n";
		    output << "É completo? " << graph->isComplete() << "\n";

		    output << "É regular? ";
		    int r = graph->isRegular();
		    if (r != 0) {
		    	output << r << "-regular\n";
		    } else {
		    	output << "0\n";
		    }

		    output << "Grau médio dos nós: " << graph->getDegreeAverage() << "";
		    printLine(output, '=');

		    return output;
		}

		ofstream& printNodeInfo(ofstream &output) {
			output << "INFORMAÇÕES DOS NÓS\n";
			output << "    Sintaxe: [d, n(d), f(d)], onde:\n";
			output << "        d representa o grau\n";
			output << "        n(d) o número de nós com este grau\n";
			output << "        f(d) a distribuição empírica do grau\n\n";

			int d = 0;
		    while (d <= graph->getMaxDegree()) {
		    	int num_nodes_by_d = graph->getNumNodesByDegree(d);
		    	double f = (double) num_nodes_by_d / (double) graph->getNumNodes();

		    	if (num_nodes_by_d != 0 && f != 0) {
		    		output << "[" << d << ", " << num_nodes_by_d << ", " << f << "]\n";
		    	}

		    	d++;
		    }

		    return output;
		}

		ofstream& printEachNodeInfo(ofstream &output) {
			Node* i = graph->getRoot();

		    while (true) {
		    	if (i == nullptr) {
		    		break;
		    	}

		    	printLine(output, '-');

		    	output << "Nó: " << i->getValue() << "\n";
		    	output << "Grau: " << i->getDegree() << "\n";
		    	output << "É ponto de articulação? " << graph->isCutVertex(i) << "\n";

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
		    }

		    printLine(output, '=');

		    return output;
		}

		ofstream& printComponentsInfo(ofstream &output) {
			printLine(output, '@');
			printLine(output, '=');
			output << "INFORMAÇÕES DAS COMPONENTES CONEXAS\n\n";
			output << "Número de nós da maior componente: " << graph->getBiggestComp()->getGraph()->getNumNodes() << "\n";
			output << "Número de nós da menor componente: " << graph->getSmallestComp()->getGraph()->getNumNodes();
			printLine(output, '=');

			Graph* graphBackup = this->graph; // guarda singleton

			int count = 0;
			Component* c = graphBackup->getComponents();
			while (c != nullptr) {
				count++;
				output << "COMPONENTE " << count;

				printLine(output, '=');
				this->graph = c->getGraph();

			    printGraphInfo(output);
			    printNodeInfo(output);
			    printEachNodeInfo(output);

				c = c->getNext();
			}

			this->graph = graphBackup; // restaura

			return output;
		}

	public:
		void exportGraph(Graph* graph, char* path) {
			ofstream output (path);
			if (!output.is_open()) {
				std::string errMsg("Error opening file \"");
		    	throw errMsg + path + "\"";
		    }

		    printHeader(output);
		    printGraphInfo(output);
		    printNodeInfo(output);
		    printEachNodeInfo(output);
		    printComponentsInfo(output);
		    printLine(output, '#');

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

			    if (countLn != 0) {
			    	iss >> v1 >> v2;

					Node* n1 = graph->insertNode(v1, 0);
					Node* n2 = graph->insertNode(v2, 0);

					graph->insertEdge(n1, n2);
			    }

				countLn++;
			}

			input.close();

			graph->loadComponents();

			this->graph = graph;

			return graph;
		}
};