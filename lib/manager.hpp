#include "graph.hpp"
#define VERSION 0.2

class Manager {
	private:
		std::ofstream& printLine(std::ofstream &output, char c);
		std::ofstream& printHeader(std::ofstream &output);
		std::ofstream& printGraphInfo(std::ofstream &output);
		std::ofstream& printNodeInfo(std::ofstream &output);
		std::ofstream& printEachNodeInfo(std::ofstream &output);
		std::ofstream& printComponentsInfo(std::ofstream &output);
		static inline void loadbar(unsigned int x, unsigned int n, unsigned int w = 50);
		void loadbar2();
		int countLines(char* path);
	public:
		void exportGraph(Graph* graph, char* path);
		Graph* createGraph(char* path);
};