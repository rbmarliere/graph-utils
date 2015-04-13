#include <cstddef>
#include <iostream>
#include <stack>

using namespace std;

class Node;
class Component;
class Graph;
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

        void setNode(Node* n) {
            this->node = n;
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

        Edge* getEdges() {
            return this->edges;
        }

        void setEdgeRoot(Node* n) {
            Edge* e = new Edge(n);
            this->edges = e;
        }

        void insertEdge(Node* n) {
            if (edges == nullptr) {
                this->setEdgeRoot(n);
                degree++;
            } else {
                Edge* i = this->getEdges();
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

        void removeEdge(Node* n) {
            if (edges->getNode()->getValue() == n->getValue()) {
                this->edges = edges->getNext();
                degree--;
            } else {
                Edge* i = edges;
                while (i != nullptr) {
                    Edge* nxt = i->getNext();

                    if (nxt != nullptr && nxt->getNode()->getValue() == n->getValue()) {
                        i->setNext(nxt->getNext());
                        degree--;
                    }

                    i = i->getNext();
                }
            }
        }

        bool hasEdgeWith(Node* n) {
            Edge* i = this->getEdges();
            while (true) {
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

        Edge* getLastEdge() {
            Edge* i = this->getEdges();

            while (i->getNext() != nullptr) {
                i = i->getNext();
            }

            return i;
        }
};

class Component {
    private:
        Graph* graph;
        Component* next;

    public:
        Component(Graph* c) {
            graph = c;
            next = nullptr;
        }

        void setGraph(Graph* c) {
            graph = c;
        }

        Graph* getGraph() {
            return this->graph;
        }

        void setNext(Component* n) {
            next = n;
        }

        Component* getNext() {
            return this->next;
        }
};

class Graph
{
    private:
        Node* root;
        Component* components;
        int num_nodes, num_edges;
    public:
        Graph() {
            root = nullptr;
            components = nullptr;
            num_nodes = num_edges = 0;
        }

        void insertComponent(Graph* g) {
            Component* newComp = new Component(g);
            if (components == nullptr) {
                components = newComp;
            } else {
                Component* c = this->getComponents();
                while (true) {
                    if (c->getNext() == nullptr) {
                        c->setNext(newComp);
                        break;
                    }

                    c = c->getNext();
                }
            }
        }

        Component* getComponents() {
            return this->components;
        }

        Component* getBiggestComp() {
            int max = 0;
            Component* returnValue = nullptr;
            Component* c = this->getComponents();
            while (c != nullptr) {
                int aux = c->getGraph()->getNumNodes();
                if (aux > max) {
                    max = aux;
                    returnValue = c;
                }

                c = c->getNext();
            }

            return returnValue;
        }

        Component* getSmallestComp() {
            Component* returnValue = nullptr;
            Component* c = this->getComponents();
            int count = 0, min = 0;
            while (c != nullptr) {
                if (count == 0) {
                    min = c->getGraph()->getNumNodes();
                    returnValue = c;
                    count++;
                }

                int aux = c->getGraph()->getNumNodes();
                if (aux < min) {
                    min = aux;
                    returnValue = c;
                }

                c = c->getNext();
            }

            return returnValue;
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

        int getMaxDegree() {
            Node* i = root;
            int max = 0;
            while (true) {
                int d = i->getDegree();
                if (d > max) {
                    max = d;
                }

                if (i->getNextInGraph() == nullptr) {
                    break;
                }

                i = i->getNextInGraph();
            }

            return max;
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

            double returnValue = (double) sumDegrees / (double) num_nodes;

            return returnValue;
        }

        int getNumNodesByDegree(int degree) {
            Node* i = root;
            int count = 0;
            while (true) {
                if (i->getDegree() == degree) {
                    count++;
                }

                if (i->getNextInGraph() == nullptr) {
                    break;
                }

                i = i->getNextInGraph();
            }

            return count;
        }

        Node* insertNode(int value, int degree) {
            Node* n = new Node(value, degree);
            if (root == nullptr) {
                root = n;
                num_nodes++;
            } else {
                Node* i = root;
                while (true) {
                    if (i->getValue() == n->getValue()) {
                        return i;
                    }

                    if (i->getNextInGraph() == nullptr) {
                        i->setNextInGraph(n);
                        num_nodes++;
                        break;
                    }

                    i = i->getNextInGraph();
                }
            }

            return n;
        }

        void removeNode(Node* n) { //?
            if (n->getValue() == root->getValue()) {
                root = n->getNextInGraph();
                num_nodes--;
            } else {
                Node* i = root;
                while (true) {
                    if (i->getNextInGraph() == nullptr) {
                        break;
                    }

                    if (i->getNextInGraph() == n) {
                        i->setNextInGraph(n->getNextInGraph());
                        num_nodes--;
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

        bool isRegularByDegree(int degree){
            Node* n = root;
            int i = degree;
            while (n!= nullptr){
                if (n->getDegree() != i)
                    return false;
                else
                    n = n->getNextInGraph();
           }
            return true;
        }

        int isRegular() {
            int d = 0;
            while (d <= this->getMaxDegree()) {
                if (this->isRegularByDegree(d) == true) {
                    return d;
                }

                d++;
            }

            return 0;
        }

        bool isComplete() {
            Node* n = root;
            int i = 0;

            while(n!= nullptr){
                i = i + n->getDegree();
                n = n->getNextInGraph();
            }

            if (i == this->getNumNodes() * (this->getNumNodes() - 1)) {
                return true;
            } else {
                return false;
            }
        }

        bool areAdjacent(Node* source, Node* dest) {
            return source->hasEdgeWith(dest);
        }

        void depthFirstSearch() {
            this->flushNodes();

            stack<Node*> nodesInProgress;
            nodesInProgress.push(this->getRoot());

            while (!nodesInProgress.empty()) {
                Node* top = nodesInProgress.top();
                nodesInProgress.pop();

                top->visit();

                Edge* edge  = top->getEdges();
                while (edge != nullptr) {
                    if (!edge->getNode()->wasVisited()) {
                        nodesInProgress.push(edge->getNode());
                    }

                    edge = edge->getNext();
                }
            }
        }

        bool isConnected() {
            this->depthFirstSearch();

            Node* root = this->getRoot();
            while (root != nullptr){
                if (!root->wasVisited()) {
                    return false;
                }
                root = root->getNextInGraph();
            }

            return true;
        }

        void loadComponents() {
            this->depthFirstSearch();

            Graph* component1 = new Graph();
            Graph* component2 = new Graph();
            Node* n = this->getRoot();
            while (n != nullptr) {
                if (n->wasVisited() == true) {
                    Node* newNode1 = component1->insertNode(n->getValue(), 0);

                    Edge* e = n->getEdges();
                    while (e != nullptr) {
                        Node* newNode2 = component1->insertNode(e->getNode()->getValue(), 0);
                        component1->insertEdge(newNode1, newNode2);

                        e = e->getNext();
                    }
                } else {
                    Node* newNode1 = component2->insertNode(n->getValue(), 0);

                    Edge* e = n->getEdges();
                    while (e != nullptr) {
                        Node* newNode2 = component2->insertNode(e->getNode()->getValue(), 0);
                        component2->insertEdge(newNode1, newNode2);

                        e = e->getNext();
                    }
                }

                n = n->getNextInGraph();
            }

            if (component1->getRoot() != nullptr) {
                this->insertComponent(component1);
            }

            if (component2->getRoot() != nullptr) {
                component2->loadComponents();
            }

            Component* c = component2->getComponents();
            while (c != nullptr) {
                this->insertComponent(c->getGraph());

                c = c->getNext();
            }
        }

        bool nodesInSameComponent(Node* n1, Node* n2) {
            this->flushNodes();

            stack<Node*> nodesInProgress;
            nodesInProgress.push(n1);

            while (!nodesInProgress.empty()) {
                Node* top = nodesInProgress.top();
                nodesInProgress.pop();

                top->visit();

                Edge* edge  = top->getEdges();
                while (edge != nullptr) {
                    if (edge->getNode()->getValue() == n2->getValue()) {
                        return true;
                    }

                    if (!edge->getNode()->wasVisited()) {
                        nodesInProgress.push(edge->getNode());
                    }

                    edge = edge->getNext();
                }
            }

            return false;
        }

        bool isBridge(Node* n1, Node* n2) {
            if (this->areAdjacent(n1, n2)) {
                this->removeEdge(n1, n2);
                bool nodesStillConnected = this->nodesInSameComponent(n1, n2);
                this->insertEdge(n1, n2);
                if (nodesStillConnected) {
                    return false;
                }
                return true;
            } else {
                return false;
            }
        }

        bool isCutVertex(Node* n){ //?
            bool returnValue = false;

            if (this->getRoot() == nullptr) {
                return returnValue;
            }

            Edge* e = n->getEdges();
            Edge* lastEdge = n->getLastEdge(); // grava ultima aresta para parar o loop a seguir
            while (true) {
                this->removeEdge(e->getNode(), n);

                bool areInSameComponent = this->nodesInSameComponent(n, e->getNode());

                this->insertEdge(n, e->getNode());

                if (!areInSameComponent) {
                    returnValue = true;
                    break;
                }

                if (e->getNode()->getValue() == lastEdge->getNode()->getValue()) {
                    break;
                }

                e = e->getNext();
            }

            return returnValue;
        }

        void flushNodes() {
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