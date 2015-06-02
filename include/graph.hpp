#ifndef GRAPH
#define GRAPH

#include <vector>

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
		int weight; /* peso da aresta (número aleatório entre 1 e 50) */
        Node* node; /* nó referenciado */
        Node* parent; /* endereço para o nó que possui esta aresta (o nó em questão tem aresta com this->node) */
        Edge* next; /* próximo elemento da lista de arestas */
        bool direction; /* flag que identifica se uma aresta está saindo (true) de um vértice ou não */
    public:
		Edge(Node* n, int weight, bool direction);
        int getWeight() const;
		void setNext(Edge* e);
		Edge* getNext();
		void setParent(Node* n);
		Node* getParent();
		void setNode(Node* n);
		Node* getNode();
		void setDirection(bool d);
		bool getDirection();
        bool operator <(const Edge& e2) const; /* sobreescreve o operador de maior para ordenação */
};

bool edgePtrCmp(const Edge* e1, const Edge* e2); /* função auxiliar para comparação de dois ponteiros, utilizado na ordenação de arestas de um grafo */

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
		void setEdgeRoot(Node* n, int weight, bool direction);

        /**
         * anexa ao final da lista encadeada de arestas do nó self o nó @param n
         * @param n próximo nó da lista de arestas
         * @return bool indica se aresta foi inserida ou não
         */
		bool insertEdge(Node* n, int weight, bool direction);
		Edge* removeEdge(Node* n); /* retorna a aresta removida */

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
        bool digraph; /* se true, trata-se de um digrafo */

    public:
		Graph(bool isDigraph);
		void insertComponent(Graph* g); /* anexa o grafo @param g ao final da lista de componentes */
		Component* getComponents(); /* retorna a primeira componente da lista */
		Component* getBiggestComp(); /* retorna a componente de maior número de vértices */
		Component* getSmallestComp(); /* retorna a componente de menor número de vértices */
		Node* getRoot();
		void setNumNodes(int num);
		int getNumNodes();
		void setNumEdges(int num);
		int getNumEdges();
		void setDigraph(bool flag);
		bool isDigraph();
		Node* getHighestDegreeNode(); /* retorna o nó com maior grau do grafo */
		Node* getLowestDegreeNode(); /* retorna o nó com menor grau do grafo */
		double getDegreeAverage(); /* retorna a média dos valores dos graus do grafo */
		int getNumNodesByDegree(int degree); /* retorna a quantidade de nós com o grau @param degree*/
		Node* insertNode(int value, int degree); /* insere nó alimentando o construtor da classe Node com os @params */
		void removeNode(Node* n);
		void insertEdge(Node* source, Node* dest, int weight); /* insere no grafo a aresta source -> dest */
		Edge* removeEdge(Node* source, Node* dest); /* remove a aresta entre source e dest, retornando-a */
		bool isRegularByDegree(int degree); /* retorna verdadeiro se o grafo é 'degree'-regular */
		int isRegular(); /* verifica, para cada grau i entre 0 e maxDegree (de forma decremental), se o grafo é i-regular. retorna i na primeira ocorrência */
		bool isComplete(); /* verifica se o grafo é completo */
		bool areAdjacent(Node* source, Node* dest); /* verifica se os @params são adjacentes */
		void depthFirstSearch(Node* searchRoot); /* realiza o algoritmo de busca em profundidade marcando os nós como visitados, a partir de @param searchRoot */
		bool isConnected(); /* verifica se o grafo é conexo */
		void loadComponents(); /* algoritmo recursivo que utiliza a funcao depthFirstSearch() para montar um grafo com os nós que foram visitados e acrescentá-lo na lista das componentes do grafo, sendo chamado novamente para o grafo dos nós não visitados */
		bool nodesInSameComponent(Node* n1, Node* n2); /* verifica se os @params estão na mesma componente conexa */
		bool nodeIsReachable(Node* n1, Node* n2); /* verifica se existe caminho de n1 para n2 */
		bool isBridge(Node* n1, Node* n2); /* verifica se a aresta representada por @params é ponte */
		bool isCutVertex(Node* n); /* verifica se @param é nó de articulação */
		void flushNodes(); /* marca todos os nós como não visitados */
		Graph* transpose(); /* retorna o grafo transposto (todas as arestas são invertidas) */
		Node* getNodeByValue(int value); /* retorna o nó cujo valor é @param value */
		Graph* getMST_Prim(); /* retorna a árvore geradora mínima usando o algoritmo de Prim */
		Graph* getMST_Kruskal(); /* retorna a árvore geradora mínima usando o algoritmo de Kruskal */
		Graph* getMaxClique(); /* retorna a clique máxima */
        Graph* checkSubsetsBy(int factor); /* verifica subconjuntos de this removendo combinações de nós factor a factor, retornando um subgrafo completo ou nullptr */
        std::vector<Edge*> getSortedEdges(); /* carrega um vetor ordenado de arestas, de forma crescente através dos pesos */
        std::vector<Node*> getTransitiveClosureOf(Node* n, bool direct); /* retorna o fecho transitivo (direto ou indireto, a depender do @param direct) do nó @param n */
        void removeAllEdges(); /* remove todas as arestas de todos os nós de um grafo */
        Graph* copy(); /* copia this e retorna */
        bool hasCycle(); /* verifica se o grafo possui ciclo, retornando true no primeiro ciclo encontrado */
};

#endif