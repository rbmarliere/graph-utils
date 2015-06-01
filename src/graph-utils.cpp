#include <iostream>
#include <cstring>
#include <ctime>
#include "../include/manager.hpp"

using namespace std;

void printHelp() {
	cout << "usage: graph-utils -i <input file> -o <output file> <-d *>\n";
	cout << "* -d for digraphs (optional)\n";
}

/**
 * Função principal do programa responsável por
 * fazer o parsing dos argumentos e chamar o Manager
 *
 * @param  argc quantidade de argumentos inseridos
 * @param  argv argumentos propriamente ditos
 */
int main(int argc, char* argv[])
{
	unsigned long int start_s = clock(); // grava o tempo atual do relógio para medir ao final da execução

	// path para ambos os parametros (nome e caminho dos arquivos)
	char* input = nullptr;
	char* output = nullptr;
	bool digraph = false;

	// parser dos parametros
	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-i") == 0) {
			input = argv[i+1];
		} else if (strcmp(argv[i], "-o") == 0) {
			output = argv[i+1];
		} else if (strcmp(argv[i], "-d") == 0) {
			digraph = true;
		} else if (strcmp(argv[i], "-h") == 0) {
			printHelp();
			return 0;
		}
	}

	if (argc < 5 || input == nullptr || output == nullptr) {
		printHelp();
		return 0;
	}

	try {
		Manager manager; // objeto Manager responsável por processar os dados
		manager.importGraph(input, digraph);
		manager.exportGraph(output);
	} catch (string msg) {
		cout << "error: " << msg;
	}

	unsigned long int stop_s = clock(); // tempo final
	int milliseconds = (stop_s - start_s) / double(CLOCKS_PER_SEC)*1000; // calcula o tempo final - tempo inicial para obter o tempo de processamento total
	int seconds = (int) (milliseconds / 1000) % 60 ;
	int minutes = (int) ((milliseconds / (1000*60)) % 60);
	cout << "time: " << minutes << "m" << seconds << "s\n";

	return 1;
}