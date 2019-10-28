// Cria operações para um arquivo binário usando os serviços de um arquivo com acesso aleatório.
#ifndef ARQUIVO_BINARIO
#define ARQUIVO_BINARIO

#include <fstream>
#include <string>

using namespace std;

class ArquivoBinario {
public:
	/* Abre o arquivo com o nome especificado em nomeArquivo para escrita e leitura de dados.
	 * Se o arquivo não existir ele será criado.
	 * Retorna true se o arquivo foi aberto com sucesso e false caso contrário.
	 */
	bool abrir(string nomeArquivo);

	// Fecha o arquivo.
	void fechar();

	// Obtém o nome do arquivo.
	string getNomeArquivo();

	// Obtém a referência do arquivoBinario.
	fstream& getArquivoBinario();

	// Obtém o tamanho do arquivo em bytes.
	unsigned long tamanhoArquivo();

private:
	string nomeArquivo;
	fstream arquivoBinario; // Arquivo binário para escrita e leitura de dados. 
};
#endif