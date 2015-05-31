#ifndef GRAPH
#define GRAPH

// pré-declarações
class Node;
class Component;
class Graph;


/**
 * CLASSE EDGE
 * Representa as arestas do grafo na forma de nós encadeados.
 */
class Edge
{
	private:
        Node* node; /* nó referenciado */
        Edge* next; /* próximo elemento da lista de arestas */
    public:
		Edge(Node* n);
		void setNext(Edge* e);
		Edge* getNext();
		void setNode(Node* n);
		Node* getNode();
};


/**
 * CLASSE NODE
 * Representa um vértice de um grafo.
 */
class Node
{
    private:
        int value; /* valor do nó */
        int degree; /* grau do nó */
        Node* nextInGraph; /* ponteiro para próximo nó do grafo */
        Edge* edges; /* ponteiro para o primeiro elemento da lista de arestas */
        bool visited; /* flag que determina se o nó já foi visitado */

    public:
		Node(int value, int degree);

        /**
         * verifica se o nó já foi visitado
         * @return valor do atributo visited
         */
		bool wasVisited();

        /**
         * marca o nó como visitado setando visited = true
         */
		void visit();

        /**
         * marca o nó como não visitado setando visited = false
         */
		void flush();


		int getValue();
		void setValue(int value);
		int getDegree();
		void setDegree(int degree);
		Node* getNextInGraph();
		void setNextInGraph(Node* n);
		Edge* getEdges();

        /**
         * referencia a primeira aresta do nó, ou seja, determina n quando atributo edges = nullptr
         * @param n nó que será a primeira aresta da lista
         */
		void setEdgeRoot(Node* n);

        /**
         * anexa ao final da lista encadeada de arestas do nó self o nó @param n
         * @param n próximo nó da lista de arestas
         */
		void insertEdge(Node* n);
		void removeEdge(Node* n);

        /**
         * verifica se o nó self possui aresta com @param n
         */
		bool hasEdgeWith(Node* n);
		Edge* getLastEdge();
};


/**
 * CLASSE COMPONENT
 * Representa as componentes conexas de um grafo, na forma de uma lista encadeada de (sub)grafos 
 */
class Component
{
    private:
        Graph* graph; /* grafo que representa a componente */
        Component* next; /* próxima componente do grafo */

    public:
		Component(Graph* c);
		void setGraph(Graph* c);
		Graph* getGraph();
		void setNext(Component* n);
		Component* getNext();
};


/**
 * CLASSE GRAPH
 * Representa um grafo e possui todas as funcionalidades requisitadas, utilizando-se de todas as outras classes
 */
class Graph
{
    private:
        Node* root; /* nó raíz do grafo, o primeiro a ser inserido */
        Component* components; /* ponteiro para a primeira componente conexa da lista */
        int num_nodes; /* quantidade de nós */
        int num_edges; /* quantidade de arestas */

    public:
		Graph();
		void insertComponent(Graph* g); /* anexa o grafo @param g ao final da lista de componentes */
		Component* getComponents(); /* retorna a primeira componente da lista */
		Component* getBiggestComp(); /* retorna a componente de maior número de vértices */
		Component* getSmallestComp(); /* retorna a componente de menor número de vértices */
		Node* getRoot();
		void setNumNodes(int num);
		int getNumNodes();
		void setNumEdges(int num);
		int getNumEdges();
		int getMaxDegree(); /* retorna o valor do maior grau do grafo */
		double getDegreeAverage(); /* retorna a média dos valores dos graus do grafo */
		int getNumNodesByDegree(int degree); /* retorna a quantidade de nós com o grau @param degree*/
		Node* insertNode(int value, int degree); /* insere nó alimentando o construtor da classe Node com os @params */
		void removeNode(Node* n);
		void insertEdge(Node* source, Node* dest); /* insere no grafo a aresta source -> dest */
		void removeEdge(Node* source, Node* dest);
		bool isRegularByDegree(int degree); /* retorna verdadeiro se o grafo é 'degree'-regular */
		int isRegular(); /* verifica, para cada grau i entre 0 e maxDegree (de forma decremental), se o grafo é i-regular. retorna i na primeira ocorrência */
		bool isComplete(); /* verifica se o grafo é completo */
		bool areAdjacent(Node* source, Node* dest); /* verifica se os @params são adjacentes */
		void depthFirstSearch(Node* searchRoot); /* realiza o algoritmo de busca em profundidade marcando os nós como visitados, a partir de @param searchRoot */
		bool isConnected(); /* verifica se o grafo é conexo */
		void loadComponents(); /* algoritmo recursivo que utiliza a funcao depthFirstSearch() para montar um grafo com os nós que foram visitados e acrescentá-lo na lista das componentes do grafo, sendo chamado novamente para o grafo dos nós não visitados */
		bool nodesInSameComponent(Node* n1, Node* n2); /* verifica se os @params estão na mesma componente conexa */
		bool isBridge(Node* n1, Node* n2); /* verifica se a aresta representada por @params é ponte */
		bool isCutVertex(Node* n); /* verifica se @param é nó de articulação */
		void flushNodes(); /* marca todos os nós como não visitados */
		Graph* transpose(); /* retorna o grafo transposto (todas as arestas são invertidas) */
		Node* getNodeByValue(int value); /* retorna o nó cujo valor é @param value */
};

#endif