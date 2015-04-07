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
            nextInGraph = nextInEdges = nullptr;
        }
        //recupera o valor do nó
        int getValue() {
            return value;
        }
        //altera o valor do nó
        void setValue(int value) {
            this->value = value;
        }
        //recupera o grau do nó
        int getDegree() {
            return degree;
        }
        //altera o grau do nó
        void setDegree(int degree) {
            this->degree = degree;
        }
        //retorna o próximo nó no grafo
        Node* getNextInGraph() {
            return nextInGraph;
        }
        //altera o proximo nó no grafo
        void setNextInGraph(Node* n) {
            this->nextInGraph = n;
        }
         //retorna o proximo no adjacente
        Node* getNextInEdges() {
            return nextInEdges;
        }
        //altera o proximo nó adjacente
        void setNextInEdges(Node* n) {
            this->nextInEdges = n;
        }
        //insere aresta
        void insertEdge(Node* n) {
            Node* i = this;
            while (true) {
                if (i->getValue() == n->getValue()) {
                    break;
                }

                if (i->getNextInEdges() == nullptr) {
                    i->setNextInEdges(n);
                    break;
                }

                i = i->getNextInEdges();
            }
        }

        void removeEdge(Node* n) {
            Node* i = this;
            while (true) {
                if (i->getNextInEdges() == nullptr) {
                    break;
                }

                if (i->getNextInEdges() == n) {
                    i->setNextInEdges(n->getNextInEdges());
                    break;
                }

                i = i->getNextInEdges();
            }
        }

        bool hasEdgeWith(Node* n) {
            Node* i = this;
            while(i->getNextInEdges() != nullptr) {
                if (i->getValue() == n->getValue()) {
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
            root = nullptr;
            num_nodes = num_edges = 0;
        }

        Node* getRoot() {
            return root;
        }

        void setNumNodes(int num) {
            this->num_nodes = num;
        }

        int getNumNodes() {
            return num_nodes;
        }

        void setNumEdges(int num) {
            this->num_edges = num;
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

                if (i->getNextInGraph() == nullptr) {
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
                if (i->getNextInGraph() == nullptr) {
                    break;
                }

                if (i->getDegree() == degree) {
                    count++;
                }

                i = i->getNextInGraph();
            }

            return count;
        }

        // demais funcionalidades:

        void insertNode(Node* n) {
            if (root == nullptr) {
                root = n;
            } else {
                Node* i = root;
                while (true) {
                    if (i->getValue() == n->getValue()) {
                        break;
                    }

                    if (i->getNextInGraph() == nullptr) {
                        i->setNextInGraph(n);
                        break;
                    }

                    i = i->getNextInGraph();
                }
            }
        }

        void removeNode(Node* n) {
            if (n->getValue() == root->getValue()) {
                root = n->getNextInGraph();
                free(n);
            } else {
                Node* i = root;
                while (true) {
                    if (i->getNextInGraph() == nullptr) {
                        break;
                    }

                    if (i->getNextInGraph() == n) {
                        i->setNextInGraph(n->getNextInGraph());
                        break;
                    }

                    i = i->getNextInGraph();
                }
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

        bool isRegular(int degree){//acho que não pode passar o grau não, tem que pegar um nó e ver o grau dele, ai grava numa variavel e vai fazendo com todos os nós, se der alguma alteração retorna falso.
            Node* n = root;
            int i = degree;
            while (n!= NULL){
                if (n -> getDegree() != i)
                    return false
                else
                    n = n-> getNextInGraph()
           }
            return true;
        }
        bool isComplete(){
            Node* n = root;
            int i = 0;
            while(n!= NULL){
                i = i + n->getDegree();
                n = n->getNextInGraph();
            }
            if (i = getNumNodes * (getNumNodes - 1))
                return true;
            else
                return false;
        }

        //checa se o número de graus do grafo é n*(n-1), se for retorna verdadeiro se não for retorna falso

        bool areAdjacent(Node* source, Node* dest) {
            return source->hasEdgeWith(dest);
        }

        bool isConnected();

        bool nodesInSameComponent(Node* n1, Node* n2); // class Component? ou apenas outra instancia de Graph?
        //verificar se tem caminho de um pro outro.

        bool isArticulationPoint(Node* n);

        bool isBridge(Node* n1, Node* n2);

        // + 10  - Obtenha os componentes conexos do grafo. Quantos componentes conexos tem o grafo? Qual ́e o tamanho do maior e do menor componente conexo?
};
