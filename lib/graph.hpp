class Node;
class Component;
class Graph;
class Edge
{
    public:
		Edge(Node* n);
		void setNext(Edge* e);
		Edge* getNext();
		void setNode(Node* n);
		Node* getNode();
};

class Node
{
    public:
		Node(int value, int degree);
		bool wasVisited();
		void visit();
		void flush();
		int getValue();
		void setValue(int value);
		int getDegree();
		void setDegree(int degree);
		Node* getNextInGraph();
		void setNextInGraph(Node* n);
		Edge* getEdges();
		void setEdgeRoot(Node* n);
		void insertEdge(Node* n);
		void removeEdge(Node* n);
		bool hasEdgeWith(Node* n);
		Edge* getLastEdge();
};

class Component
{
    public:
		Component(Graph* c);
		void setGraph(Graph* c);
		Graph* getGraph();
		void setNext(Component* n);
		Component* getNext();
};

class Graph
{
    public:
		Graph();
		void insertComponent(Graph* g);
		Component* getComponents();
		Component* getBiggestComp();
		Component* getSmallestComp();
		Node* getRoot();
		void setNumNodes(int num);
		int getNumNodes();
		void setNumEdges(int num);
		int getNumEdges();
		int getMaxDegree();
		double getDegreeAverage();
		int getNumNodesByDegree(int degree);
		Node* insertNode(int value, int degree);
		void removeNode(Node* n);
		void insertEdge(Node* source, Node* dest);
		void removeEdge(Node* source, Node* dest);
		int getDegree(Node* node);
		bool isRegularByDegree(int degree);
		int isRegular();
		bool isComplete();
		bool areAdjacent(Node* source, Node* dest);
		void depthFirstSearch();
		bool isConnected();
		void loadComponents();
		bool nodesInSameComponent(Node* n1, Node* n2);
		bool isBridge(Node* n1, Node* n2);
		bool isCutVertex(Node* n);
		void flushNodes();
};