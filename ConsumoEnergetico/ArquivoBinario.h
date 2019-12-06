// Cria operações para um arquivo binário usando os serviços de um arquivo com acesso aleatório.
#ifndef ARQUIVO_BINARIO
#define ARQUIVO_BINARIO

#include <fstream>
#include <string>

using namespace std;

class ArquivoBinario {

public:

	inline ArquivoBinario(){}

	inline ArquivoBinario(string nomeArquivo) {
		this->nomeArquivo = nomeArquivo;
		abrir(nomeArquivo);
	}

	inline ~ArquivoBinario() {
		fechar();
	}

	/* Abre o arquivo com o nome especificado em nomeArquivo para escrita e leitura de dados.
	 * Se o arquivo não existir ele será criado.
	 * Retorna true se o arquivo foi aberto com sucesso e false caso contrário.
	 */
	virtual bool abrir(string nomeArquivo);
	
	// Obtém o número de registros do arquivo.
	unsigned int numeroRegistros();

	// Fecha o arquivo.
	virtual void fechar();

	// Obtém o nome do arquivo.
	virtual string getNomeArquivo();

protected:
	// Reposiciona o arquivo para o inicio
	virtual void reposicionarArquivo();

	// Obtém a referência do arquivoBinario.
	virtual fstream& getArquivoBinario();

	// Obtém o tamanho do arquivo em bytes.
	virtual unsigned long tamanhoArquivo();

	// Obtém o tamanho do registro em bytes.
	virtual unsigned int tamanhoRegistro() = 0;

private:
	string nomeArquivo;
	fstream arquivoBinario; // Arquivo binário para escrita e leitura de dados. 
};
#endif