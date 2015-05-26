#include <iostream>
#include <iomanip>
#include <thread>
#include <unistd.h>
#include <sstream>
#include <fstream>
#include <string.h>
#include "manager.hpp"

using namespace std;

ofstream& Manager::printLine(ofstream &output, char c) {
    int i = 0;

    output << "\n";
    while (i < 33) {
        output << c;
        i++;
    }
    output << "\n";

    return output;
}

ofstream& Manager::printHeader(ofstream &output) {
    output << "#################################\n";
    output << "#### graph-utils v" << VERSION << " REPORT ####\n";
    output << "#################################";
    printLine(output, '=');

    return output;
}

ofstream& Manager::printGraphInfo(ofstream &output) {
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

ofstream& Manager::printNodeInfo(ofstream &output) {
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

ofstream& Manager::printEachNodeInfo(ofstream &output) {
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

ofstream& Manager::printComponentsInfo(ofstream &output) {
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

int Manager::countLines(char* path) {
    ifstream count (path);
    if (!count.is_open()) {
        std::string errMsg("error opening file \"");
        throw errMsg + path + "\"";
    }

    int countLn = 0;
    string line;
    while (getline(count, line)) {
        countLn++;
    }
    count.close();

    return countLn;
}

void Manager::exportGraph(Graph* graph, char* path) {
    ofstream output (path);
    if (!output.is_open()) {
        std::string errMsg("error opening file \"");
        throw errMsg + path + "\"";
    }

    cout << "exporting graph: \n";

    printHeader(output);
    printGraphInfo(output);
    printNodeInfo(output);
    printEachNodeInfo(output);
    if (graph->getComponents()->getNext() != nullptr) {
        printComponentsInfo(output);
    }
    printLine(output, '#');

    cout << "done\n";

    cout << "dumped to " << path << "\n";

    output.close();
}

Graph* Manager::importGraph(char* path) {
    ifstream input (path);
    if (!input.is_open()) {
        std::string errMsg("error opening file \"");
        throw errMsg + path + "\"";
    }

    cout << "importing graph from ";

    Graph* graph = new Graph();
    int v1 = 0, v2 = 0, num_nodes = 0, i = 0;
    int lines = this->countLines(path);
    cout << path << " (" << lines << " lines): \n";
    string line;

    while (getline(input, line)) {
        istringstream iss(line);

        if (i != 0) {
            iss >> v1 >> v2;

            Node* n1 = graph->insertNode(v1, 0);
            Node* n2 = graph->insertNode(v2, 0);

            graph->insertEdge(n1, n2);
        }

        i++;
    }
    input.close();

    cout << "done\n";

    cout << "loading connected components: \n";
    graph->loadComponents();
    cout << "done\n";

    this->graph = graph;

    return graph;
}
