class Node
{
    private:
        int value, degree;
        double weight;
        Node *next;

    public:
        Node(int value, int degree, double weight) {
            this->value = value;
            this->degree = degree;
            this->weight = weight;
            next = NULL;
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

        double getWeight() {
            return weight;
        }

        void setWeight(double weight) {
            this->weight = weight;
        }

        Node* getNext() {
            return next;
        }

        void setNext(Node *next) {
            this->next = next;
        }

        bool hasEdge(Node* node) { // ?
            i = this;
            while(i->getNext() != NULL) {
                if (i == node) {
                    return true;
                }

                i = i->getNext();
            }

            return false;
        }
};

class Graph
{
    private:
        Node *root;
        int num_nodes, num_edges;
    public:
        Graph() {
            root = new No(NULL);
            num_nodes = 0;
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

        double getDegreeAverage();

        int getNumNodesByDegree(int degree);

        void exportGraph(File* file);

        // demais funcionalidades:

        // void insertNode();
        // void removeNode();
        void insertEdge(Node* root, Node* source, Node* dest, double weight); // ao final, source.degree++ && dest.degree++
        void removeEdge(Node* source, Node* dest);

        int getDegree(Node* node) {
            return node->getDegree();
        }

        bool isRegular(int degree);
        bool isComplete();
        bool areAdjacent(Node* source, Node* dest) {
            return source->hasEdge(dest);
        }
        bool isConnected();
        bool nodesInSameComponent(Node* n1, Node* n2); // class Component: será que vale a pena?
        bool isArticulationPoint(Node* n);
        bool isBridge(Node* n1, Node* n2); // class Edge?

        // + 10  - Obtenha os componentes conexos do grafo. Quantos componentes conexos tem o grafo? Qual ́e o tamanho do maior e do menor componente conexo?
};