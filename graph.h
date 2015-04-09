o disso #include <cstddef>
#include <iostream>
#include <stack>
class Node;
class Edge
{
    private:
        Node* node;
        Edge* next;
    public:
        Edge(Node* n) {
            node = n;
            next = nullptr;
        }

        void setNext(Edge* e) {
            this->next = e;
        }

        Edge* getNext() {
            return this->next;
        }

        Node* getNode() {
            return this->node;
        }
};

class Node
{
    private:
        int value, degree;
        Node* nextInGraph;
        Edge* edges;
        bool visited;

    public:
        Node(int value, int degree) {
            visited = false;
            this->value = value;
            this->degree = degree;
            nextInGraph = nullptr;
            edges = nullptr;
        }

        bool wasVisited() {
            return visited;
        }

        void visit() {
            this->visited = true;
        }

        void flush() {
            this->visited = false;
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

        Edge* getEdges() {
            return this->edges;
        }

        void setEdgeRoot(Node* n) {
            Edge* e = new Edge(n);
            this->edges = e;
        }

        void insertEdge(Node* n) {//insere aresta
            if (edges == nullptr) {
                this->setEdgeRoot(n);
                degree++;
            } else {
                Edge* i = getEdges();
                while (true) {
                    if (i->getNode()->getValue() == n->getValue()) {
                        break;
                    }

                    if (i->getNext() == nullptr) {
                        Edge* e = new Edge(n);
                        i->setNext(e);
                        degree++;
                        break;
                    }

                    i = i->getNext();
                }
            }
        }

        void removeEdge(Node* n) {//remove aresta
            Edge* i = edges;
            while (true) {
                if (i == nullptr) {
                    break;
                }

                if (i->getNext() == nullptr && i->getNode()->getValue() == n->getValue()) {
                    this->edges = nullptr;
                    degree--;
                    break;
                }

                if (i->getNext()->getNode()->getValue() == n->getValue()) {
                    i->setNext(i->getNext()->getNext());
                    degree--;
                    break;
                }

                i = i->getNext();
            }
        }

        bool hasEdgeWith(Node* n) {//verifica se e nós são adjacentes
            Edge* i = getEdges();
            while(true) {
                if (i == nullptr) {
                    break;
                }

                if (i->getNode()->getValue() == n->getValue()) {
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

        double getDegreeAverage() {//média de graus do grafo
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

        Node* insertNode(int value, int degree) {
            Node* n = new Node(value, degree);
            if (root == nullptr) {
                root = n;
            } else {
                Node* i = root;
                while (true) {
                    if (i->getValue() == n->getValue()) {
                        return i;
                    }

                    if (i->getNextInGraph() == nullptr) {
                        i->setNextInGraph(n);
                        break;
                    }

                    i = i->getNextInGraph();
                }
            }

            return n;
        }

        void removeNode(Node* n) {
            if (n->getValue() == root->getValue()) {
                root = n->getNextInGraph();
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

            num_edges++;
        }

        void removeEdge(Node* source, Node* dest) {
            source->removeEdge(dest);
            dest->removeEdge(source);

            num_edges--;
        }

        int getDegree(Node* node) {
            return node->getDegree();
        }

        bool isRegular(int degree){//acho que não pode passar o grau não, tem que pegar um nó e ver o grau dele, ai grava numa variavel e vai fazendo com todos os nós, se der alguma alteração retorna falso.
            Node* n = root;
            int i = degree;
            while (n!= nullptr){
                if (n -> getDegree() != i)
                    return false;
                else
                    n = n-> getNextInGraph();
           }
            return true;
        }

        bool isComplete(){//checa se o número de graus do grafo é n*(n-1), se for retorna verdadeiro se não for retorna falso
            Node* n = root;
            int i = 0;
            while(n!= nullptr){
                i = i + n->getDegree();
                n = n->getNextInGraph();
            }
            if (i == getNumNodes() * (getNumNodes() - 1))
                return true;
            else
                return false;
        }



        bool areAdjacent(Node* source, Node* dest) {
            return source->hasEdgeWith(dest);
        }

        bool isConnected()
        {
            std::stack<Node*> nodesInProgress;

            this->flushNodes();

            nodesInProgress.push(this->getRoot());

            while (!nodesInProgress.empty()) {
                nodesInProgress.top()->visit();
                Edge* edge  = nodesInProgress.top()->getEdges();
                if(edge == nullptr)
                {
                    nodesInProgress.pop();
                }
                else
                {
                    bool foundVisitedNode = false;
                    while (edge != nullptr && foundVisitedNode){
                        if (edge->getNode()->wasVisited() == false){
                            foundVisitedNode = true;
                        }
                        else
                        {
                            edge = edge->getNext();
                        }
                    }
                    if (!foundVisitedNode) {
                        nodesInProgress.pop();
                    }
                    else
                    {
                        nodesInProgress.push(edge->getNode());
                    }
                }
            }

            Node* root = this->getRoot();
            while(root != nullptr){
                if(root->wasVisited() == false)
                {
                    return false;
                }
                root = root->getNextInGraph();
            }



            return true;
        }

        bool nodesInSameComponent(Node* n1, Node* n2)
        {
            std::stack<Node*> nodesInProgress;

            this->flushNodes();

            nodesInProgress.push(n1);

            while (!nodesInProgress.empty()) {
                nodesInProgress.top()->visit();
                if(nodesInProgress.top()->getValue() == n2->getValue())
                {
                    return true;
                }
                Edge* edge  = nodesInProgress.top()->getEdges();
                if(edge == nullptr)
                {
                    nodesInProgress.pop();
                }
                else
                {
                    bool foundVisitedNode = false;
                    while (edge != nullptr && foundVisitedNode){
                        if (edge->getNode()->wasVisited() == false){
                            foundVisitedNode = true;
                        }
                        else
                        {
                            edge = edge->getNext();
                        }
                    }
                    if (!foundVisitedNode) {
                        nodesInProgress.pop();
                    }
                    else
                    {
                        nodesInProgress.push(edge->getNode());
                    }
                }
            }
            return false;
        }


        bool isArticulationPoint(Node* n){//coloca todos os nós adjacentes ao nó em um vetor, remove o nó, ve se todos continuam na mesma componente conexa, readiciona o nó e retorna o resultado
            Node* a[];
            int i = 0;
            Node* x,y = n;
            x->nextInEdge();
            while (x != nullptr){//passa pra vetor
                a[i]=x*;
                i++;
                x->nextInEdge();
            }
            i = 0;
            removeNode(n)
            while(a[i+1] != nullptr){
                if(nodesInSameComponent(a[i], a[i+1])!= true){
                    insertNode(y);
                    return false;
                }
                else
                    insertNode(y);
                    return true;

            }

        }


        bool isBridge(Node* n1, Node* n2){//remove a aresta e checa se os 2 nós delas permanecem conectados, depois refaz a aresta e retorna o resultado
            bool i = true;
            this->removeEdge(n1,n2);
            if (nodesInSameComponent(n1,n2)) {
                i = false;
            }
            this->insertEdge(n1,n2);

            return i;
        }


        //Obtenha os componentes conexos do grafo. Quantos componentes conexos tem o grafo? Qual ́e o tamanho do maior e do menor componente conexo?
        void connectedComponents()
        {
            int greater = 0;
            int lesser;

            bool allVisited = false;

            std::stack<Node*> nodesInProgress;

            this->flushNodes();

            nodesInProgress.push(this->getRoot());

            while (!allVisited) {

                int count = 0;

                while (!nodesInProgress.empty()) {
                    nodesInProgress.top()->visit();
                    printf("%d",nodesInProgress.top()->getValue());
                    Edge* edge  = nodesInProgress.top()->getEdges();
                    if(edge == nullptr)
                    {
                        nodesInProgress.pop();
                    }
                    else
                    {
                        bool foundVisitedNode = false;
                        while (edge != nullptr && foundVisitedNode){
                            if (edge->getNode()->wasVisited() == false){
                                foundVisitedNode = true;
                            }
                            else
                            {
                                edge = edge->getNext();
                            }
                        }
                        if (!foundVisitedNode) {
                            nodesInProgress.pop();
                        }
                        else
                        {
                            nodesInProgress.push(edge->getNode());
                        }
                    }
                }

                Node* root = this->getRoot();
                while(root != nullptr){
                    if(root->wasVisited() == false)
                    {
                        //return false;
                    }
                    root = root->getNextInGraph();
                }

            }

        }


        void flushNodes() {
            if (root == nullptr) {
                return;
            }

            Node* i = root;
            while (true) {
                if (i == nullptr) {
                    break;
                }

                i->flush();

                i = i->getNextInGraph();
            }
        }
};
