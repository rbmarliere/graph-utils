#ifndef MANAGER
#define MANAGER
#define VERSION 0.3 /* versão do programa */
#include "graph.hpp"

/**
 * CLASSE MANAGER
 * Responsável pelo processamento dos dados fornecidos pelo usuário e também pelo fornecimento da saída do programa.
 */
class Manager
{
	private:
		Graph* graph; /* grafo gerado no momento da importação via Manager::importGraph(path) */

		/**
		 * imprime uma sequencia de 32 caracteres
		 * @param  output stream onde será feita a impressão
		 * @param  c      caractere a ser impresso
		 */
		void printLine(std::ofstream &output, char c);

		/**
		 * imprime as informações básicas referente ao programa
		 * @param  output stream onde será feita a impressão
		 */
		void printHeader(std::ofstream &output);

		/**
		 * imprime as informações a respeito do atributo graph desta classe
		 * @param  output stream onde será feita a impressão
		 */
		void printGraphInfo(std::ofstream &output);

		/**
		 * imprime as informações gerais acerca de todos os nós do atributo graph desta classe (número de nós com cada grau, distribuição empírica, etc)
		 * @param  output stream onde será feita a impressão
		 */
		void printNodeInfo(std::ofstream &output);

		/**
		 * imprime as informações de cada nó do atributo graph desta classe (como seu grau e suas arestas)
		 * @param  output stream onde será feita a impressão
		 */
		void printEachNodeInfo(std::ofstream &output);

		/**
		 * imprime, utilizando-se de muitos métodos declarados acima, as informações das componentes conexas do atributo graph desta classe
		 * @param  output stream onde será feita a impressão
		 */
		void printComponentsInfo(std::ofstream &output);

		/**
		 * função auxiliar retirada da internet (https://www.ross.click/2011/02/creating-a-progress-bar-in-c-or-any-other-console-app/) para imprimir na tela uma barra de carregamento para ilustrar o processamento do arquivo de input
		 * @param x índice atual
		 * @param n índice final
		 * @param w largura da barra
		 */
		void loadbar(unsigned int x, unsigned int n, unsigned int w);

		/**
		 * função auxiliar para contar o número de linhas de um arquivo
		 * @param  path caminho para o arquivo
		 * @return      número de linhas
		 */
		int countLines(char* path);
	public:
		/**
		 * função fundamental do programa que é responsável por imprimir todas as informações do atributo graph num arquivo de output
		 * @param path caminho para o arquivo de output, especificado pelo usuário via argumento ao programa
		 */
		void exportGraph(char* path);

		/**
		 * função fundamental do programa que é responsável por ler um arquivo de entrada e criar um grafo (ou digrafo) na memória, através do header graph.hpp
		 * @param path caminho para o arquivo de input, especificado pelo usuário via argumento ao programa
		 */
		void importGraph(char* path, bool digraph);
};

#endif