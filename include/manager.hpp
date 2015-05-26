#ifndef MANAGER
#define MANAGER
#define VERSION 0.2
#include "graph.hpp"

class Manager
{
	private:
		Graph* graph;
		bool stopThread;

		std::ofstream& printLine(std::ofstream &output, char c);
		std::ofstream& printHeader(std::ofstream &output);
		std::ofstream& printGraphInfo(std::ofstream &output);
		std::ofstream& printNodeInfo(std::ofstream &output);
		std::ofstream& printEachNodeInfo(std::ofstream &output);
		std::ofstream& printComponentsInfo(std::ofstream &output);
		int countLines(char* path);
	public:
		void exportGraph(Graph* graph, char* path);
		Graph* importGraph(char* path);
};

#endif