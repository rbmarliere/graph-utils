#include <cstddef>

class Node
{
    private:
        int value, degree;
        Node* nextInGraph;
        Node* nextInEdges;

    public:
        Node(int value, int degree) {
            this->value = value;
            this->degree = degree;
            nextInGraph = nextInEdges = NULL;
        }

        int getValue() {
            return value;
        }

        void setValue(int value) {
            this->value = value;
        }

        int getDegree() {
            return degree;
        }

        void setDegree(int degree) {
            this->degree = degree;
        }

        Node* getNextInGraph() {
            return nextInGraph;
        }

        void setNextInGraph(Node* n) {
            this->nextInGraph = n;
        }

        Node* getNextInEdges() {
            return nextInEdges;
        }

        void setNextInEdges(Node* n) {
            this->nextInEdges = n;
        }

        void insertEdge(Node* n) {
            Node* i = this;
            while (true) {
                if (i == n) {
                    break;
                }

                if (i->getNextInEdges() == NULL) {
                    i->setNextInEdges(n);
                    break;
                }
            }
        }

        void removeEdge(Node* n) {
            Node* i = this;
            while (true) {
                if (i->getNextInEdges() == NULL) {
                    break;
                }

                if (i->getNextInEdges() == n) {
                    i->setNextInEdges(n->getNextInEdges());
                    break;
                }

                i = i->getNextInEdges();
            }
        }

        bool hasEdgeWith(Node* node) {
            Node* i = this;
            while(i->getNextInEdges() != NULL) {
                if (i == node) {
                    return true;
                }

                i = i->getNextInEdges();
            }

            return false;
        }
};

class Graph
{
    private:
        Node* root;
        int num_nodes, num_edges;
    public:
        Graph() {
            root = new Node(0, 0);
            num_nodes = num_edges = 0;
        }

        Node* getRoot() {
            return root;
        }

        // escrever um grafo em um arquivo texto com as seguintes informações do grafo: número de vértices, número de arestas, grau médio, e distribuição empírica do grau dos vértices, que consiste na frequência relativa dos graus. Ou seja, f(d) = n(d)/n, onde f(d) é a frequência relativa do grau d que é dada pelo número de vértices com grau d (dado por n(d)) divido pelo número total de vértices do grafo (dado por n) :

        int getNumNodes() {
            return num_nodes;
        }

        int getNumEdges() {
            return num_edges;
        }

        int getDegreeFrequency(int degree) {
            return getNumNodesByDegree(degree) / num_nodes;
        }

        double getDegreeAverage() {
            Node* i = root;
            int sumDegrees = 0;
            while (true) {
                sumDegrees += i->getDegree();

                if (i->getNextInGraph() == NULL) {
                    break;
                }

                i = i->getNextInGraph();
            }

            return sumDegrees / num_nodes;
        }

        int getNumNodesByDegree(int degree) {
            Node* i = root;
            int count = 0;
            while (true) {
                if (i->getNextInGraph() == NULL) {
                    break;
                }

                if (i->getDegree() == degree) {
                    count++;
                }

                i = i->getNextInGraph();
            }
        }

        // demais funcionalidades:

        void insertNode(Node* n) {
            Node* i = root;
            while (true) {
                if (i == n) {
                    break;
                }

                if (i->getNextInGraph() == NULL) {
                    i->setNextInGraph(n);
                    break;
                }

                i = i->getNextInGraph();
            }
        }

        void removeNode(Node* n) {
            Node* i = root;
            while (true) {
                if (i->getNextInGraph() == NULL) {
                    break;
                }

                if (i->getNextInGraph() == n) {
                    i->setNextInGraph(n->getNextInGraph());
                    break;
                }

                i = i->getNextInGraph();
            }
        }

        void insertEdge(Node* source, Node* dest) {
            source->insertEdge(dest);
            dest->insertEdge(source);

            source->setDegree(source->getDegree()+1);
            dest->setDegree(dest->getDegree()+1);
        }

        void removeEdge(Node* source, Node* dest) {
            source->removeEdge(dest);
            dest->removeEdge(source);

            source->setDegree(source->getDegree()-1);
            dest->setDegree(dest->getDegree()-1);
        }

        int getDegree(Node* node) {
            return node->getDegree();
        }

        bool isRegular(int degree);

        bool isComplete();

        bool areAdjacent(Node* source, Node* dest) {
            return source->hasEdgeWith(dest);
        }

        bool isConnected();

        bool nodesInSameComponent(Node* n1, Node* n2); // class Component? ou apenas outra instancia de Graph?

        bool isArticulationPoint(Node* n);

        bool isBridge(Node* n1, Node* n2);

        // + 10  - Obtenha os componentes conexos do grafo. Quantos componentes conexos tem o grafo? Qual ́e o tamanho do maior e do menor componente conexo?
};
