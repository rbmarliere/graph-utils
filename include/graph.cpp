#include <cstddef>
#include <iostream>
#include <stack>
#include "graph.hpp"
#include <algorithm>

using namespace std;

Edge::Edge(Node* n) {
    weight = 1 + (rand() % 50);
    node = n;
    next = nullptr;
}

int Edge::getWeight() const {
    return this->weight;
}

void Edge::setNext(Edge* e) {
    this->next = e;
}

Edge* Edge::getNext() {
    return this->next;
}

void Edge::setNode(Node* n) {
    this->node = n;
}

Node* Edge::getNode() {
    return this->node;
}

bool Edge::operator <(const Edge& e2) const {
    return this->getWeight() < e2.getWeight();
}

bool edgePtrCmp(const Edge* e1, const Edge* e2) {
    return *e1 < *e2;
}

Node::Node(int value, int degree) {
    visited = false;
    this->value = value;
    this->degree = degree;
    nextInGraph = nullptr;
    edges = nullptr;
}

bool Node::wasVisited() {
    return visited;
}

void Node::visit() {
    this->visited = true;
}

void Node::flush() {
    this->visited = false;
}

int Node::getValue() {
    return value;
}

void Node::setValue(int value) {
    this->value = value;
}

int Node::getDegree() {
    return degree;
}

void Node::setDegree(int degree) {
    this->degree = degree;
}

Node* Node::getNextInGraph() {
    return nextInGraph;
}

void Node::setNextInGraph(Node* n) {
    this->nextInGraph = n;
}

Edge* Node::getEdges() {
    return this->edges;
}

void Node::setEdgeRoot(Node* n) {
    Edge* e = new Edge(n);
    this->edges = e;
}

void Node::insertEdge(Node* n) {
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

void Node::removeEdge(Node* n) {
    if (edges != nullptr) {
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
}

bool Node::hasEdgeWith(Node* n) {
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

Edge* Node::getLastEdge() {
    Edge* i = this->getEdges();

    if (i != nullptr) {
        while (i->getNext() != nullptr) {
            i = i->getNext();
        }

        return i;
    } else {
        return nullptr;
    }
}

Component::Component(Graph* c) {
    graph = c;
    next = nullptr;
}

void Component::setGraph(Graph* c) {
    graph = c;
}

Graph* Component::getGraph() {
    return this->graph;
}

void Component::setNext(Component* n) {
    next = n;
}

Component* Component::getNext() {
    return this->next;
}

Graph::Graph() {
    root = nullptr;
    components = nullptr;
    num_nodes = num_edges = 0;
}

void Graph::insertComponent(Graph* g) {
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

Component* Graph::getComponents() {
    return this->components;
}

Component* Graph::getBiggestComp() {
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

Component* Graph::getSmallestComp() {
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

Node* Graph::getRoot() {
    return root;
}

void Graph::setNumNodes(int num) {
    this->num_nodes = num;
}

int Graph::getNumNodes() {
    return num_nodes;
}

void Graph::setNumEdges(int num) {
    this->num_edges = num;
}

int Graph::getNumEdges() {
    return num_edges;
}

Node* Graph::getHighestDegreeNode() {
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

    return i;
}

Node* Graph::getLowestDegreeNode() {
    Node* i = root;
    int min = 0;
    while (true) {
        int d = i->getDegree();
        if (d < min) {
            min = d;
        }

        if (i->getNextInGraph() == nullptr) {
            break;
        }

        i = i->getNextInGraph();
    }

    return i;
}

double Graph::getDegreeAverage() {
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

int Graph::getNumNodesByDegree(int degree) {
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

Node* Graph::insertNode(int value, int degree) {
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

void Graph::removeNode(Node* n) {
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

void Graph::insertEdge(Node* source, Node* dest) {
    source->insertEdge(dest);
    num_edges++;
}

void Graph::removeEdge(Node* source, Node* dest) {
    source->removeEdge(dest);
    num_edges--;
}

bool Graph::isRegularByDegree(int degree){
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

int Graph::isRegular() {
    int d = this->getHighestDegreeNode()->getDegree();
    while (d >= 0) {
        if (this->isRegularByDegree(d) == true) {
            return d;
        }

        d--;
    }

    return 0;
}

bool Graph::isComplete() {
    Node* n = root;
    int i = 0;

    while (n != nullptr) {
        i += n->getDegree();
        n = n->getNextInGraph();
    }

    if (i == this->getNumNodes() * (this->getNumNodes() - 1)) {
        return true;
    } else {
        return false;
    }
}

bool Graph::areAdjacent(Node* source, Node* dest) {
    return source->hasEdgeWith(dest);
}

void Graph::depthFirstSearch(Node* searchRoot) {
    this->flushNodes();

    stack<Node*> nodesInProgress;
    nodesInProgress.push(searchRoot);

    while (!nodesInProgress.empty()) {
        Node* top = nodesInProgress.top();
        nodesInProgress.pop();

        top->visit();

        Edge* edge = top->getEdges();
        while (edge != nullptr) {
            if (!edge->getNode()->wasVisited()) {
                nodesInProgress.push(edge->getNode());
            }

            edge = edge->getNext();
        }
    }
}

bool Graph::isConnected() {
    if (this->getComponents() != nullptr && this->getComponents()->getNext() != nullptr) {
        // possui mais de uma componente conexa
        return false;
    } else {
        return true;
    }
}

void Graph::loadComponents() {
    this->depthFirstSearch(this->getRoot());

    Graph* toBeChecked = new Graph();
    Graph* gT = this->transpose();
    Node* n = this->getRoot();
    while (n != nullptr) {
        if (n->wasVisited() == true) {
            Graph* component = new Graph();
            Node* n_in_gT = gT->getNodeByValue(n->getValue());
            gT->depthFirstSearch(n_in_gT);

            Node* gT_n = gT->getRoot();
            while (gT_n != nullptr) {
                if (gT_n->wasVisited() == true) {
                    // se o nó foi visitado no grafo transposto, então faz parte de uma componente conexa
                    Node* newNode1 = component->insertNode(gT_n->getValue(), 0);

                    Edge* e = gT_n->getEdges();
                    while (e != nullptr) {
                        Node* newNode2 = component->insertNode(e->getNode()->getValue(), 0);
                        component->insertEdge(newNode2, newNode1);

                        e = e->getNext();
                    }
                } else {
                    // senão é anexado ao subgrafo que será posteriormente analisado na chamada recursiva deste método
                    Node* newNode1 = toBeChecked->insertNode(gT_n->getValue(), 0);

                    Edge* e = gT_n->getEdges();
                    while (e != nullptr) {
                        if (e->getNode()->wasVisited() == false) {
                            Node* newNode2 = toBeChecked->insertNode(e->getNode()->getValue(), 0);
                            toBeChecked->insertEdge(newNode2, newNode1);
                        }

                        e = e->getNext();
                    }
                }

                gT_n = gT_n->getNextInGraph();
            }

            if (component->getRoot() != nullptr) {
                this->insertComponent(component);
            }

            break;
        }

        n = n->getNextInGraph();
    }

    if (toBeChecked->getRoot() != nullptr) {
        toBeChecked->loadComponents();
    }

    Component* c = toBeChecked->getComponents();
    while (c != nullptr) {
        this->insertComponent(c->getGraph());

        c = c->getNext();
    }
}

bool Graph::nodesInSameComponent(Node* n1, Node* n2) {
    return this->nodeIsReachable(n1, n2) && this->nodeIsReachable(n2, n1);
}

bool Graph::nodeIsReachable(Node* n1, Node* n2) {
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

bool Graph::isBridge(Node* n1, Node* n2) {
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

bool Graph::isCutVertex(Node* n) {
    bool returnValue = false;

    if (this->getRoot() == nullptr) {
        return returnValue;
    }

    Edge* e = n->getEdges();
    Edge* lastEdge = n->getLastEdge(); // grava ultima aresta para parar o loop a seguir
    while (e != nullptr) {
        this->removeEdge(n, e->getNode());

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

void Graph::flushNodes() {
    Node* i = root;
    while (true) {
        if (i == nullptr) {
            break;
        }

        i->flush();

        i = i->getNextInGraph();
    }
}

Graph* Graph::transpose() {
    Graph* gT = new Graph();

    Node* i = this->getRoot();
    while (i != nullptr) {
        Node* n1 = gT->insertNode(i->getValue(), 0);
        Edge* e = i->getEdges();
        while (e != nullptr) {
            Node* n2 = gT->insertNode(e->getNode()->getValue(), 0);
            gT->insertEdge(n2, n1);
            e = e->getNext();
        }
        i = i->getNextInGraph();
    }

    return gT;
}

Node* Graph::getNodeByValue(int value) {
    Node* i = this->getRoot();
    while (i != nullptr) {
        if (i->getValue() == value) {
            return i;
        }
        i = i->getNextInGraph();
    }

    return nullptr;
}

Graph* Graph::getMST_Prim() {
    return 0;
}

Graph* Graph::getMST_Kruskal() {
    return 0;
}

Graph* Graph::getMaxClique() {
    Node* i = this->getHighestDegreeNode(); // pega nó de maior grau
    int highestDegree = i->getDegree();
    int lowestDegree = this->getLowestDegreeNode()->getDegree();
    this->depthFirstSearch(i); // visita todos os nós alcançáveis a partir dele

    Graph* initial = new Graph(); // monta o grafo correspondente
    while (i != nullptr) {
        if (i->wasVisited() == true) {
            Node* newNode1 = initial->insertNode(i->getValue(), 0);

            Edge* e = i->getEdges();
            while (e != nullptr) {
                if (e->getNode()->wasVisited() == true) {
                    Node* newNode2 = initial->insertNode(e->getNode()->getValue(), 0);
                    initial->insertEdge(newNode1, newNode2);
                }

                e = e->getNext();
            }
        }

        i = i->getNextInGraph();
    }

    if (initial->isComplete()) {
        return initial;
    }

    for (int i = highestDegree; i == lowestDegree; i--) {
        int combination_factor = highestDegree - i;
        Graph* clique = initial->checkSubsetsBy(combination_factor);

        if (clique != nullptr) {
            return clique;
        }
    }

    return nullptr;
}

Graph* Graph::checkSubsetsBy(int factor) {
    return 0;
}

vector<Edge*> Graph::getSortedEdges() {
    vector<Edge*> edges;

    Node* i = this->getRoot();
    while (i != nullptr) {
        Edge* e = i->getEdges();
        while (e != nullptr) {
            edges.push_back(e);
            e = e->getNext();
        }
        i = i->getNextInGraph();
    }

    sort(edges.begin(), edges.end(), edgePtrCmp);

    return edges;
}

vector<Node*> Graph::getTransitiveClosureOf(Node* n, bool direct) {
    vector<Node*> closure;

    Graph* g;
    Node* _n;
    if (direct == true) {
        g = this;
        _n = n;
    } else {
        g = this->transpose();
        _n = g->getNodeByValue(n->getValue());
    }

    g->depthFirstSearch(_n);

    Node* i = g->getRoot();
    while (i != nullptr) {
        if (i->wasVisited() == true) {
            closure.push_back(i);
        }
        i = i->getNextInGraph();
    }

    return closure;
}
