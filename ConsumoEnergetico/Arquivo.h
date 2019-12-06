// Cria operações para um arquivo binário usando os serviços de um arquivo com acesso aleatório.
#ifndef ARQUIVO_BINARIOX
#define ARQUIVO_BINARIOX

#include <fstream>
#include <string>

using namespace std;

template<class T>
class Arquivo {

protected:

	// Obtém a referência do Arquivo.
	fstream& getArquivo();

public:
	/* Abre o arquivo com o nome especificado em nomeArquivo para escrita e leitura de dados.
	* Se o arquivo não existir ele será criado.
	* Retorna true se o arquivo foi aberto com sucesso e false caso contrário.
	*/
	virtual bool abrir(string nomeArquivo);

	// Fecha o arquivo.
	virtual void fechar();
	
	// Reposiciona o arquivo para o inicio
	void reposicionarArquivo();

	// Obtém o nome do arquivo.
	virtual string getNomeArquivo();

	// Obtém o tamanho do arquivo em bytes.
	virtual unsigned long tamanhoArquivo();

	// Obtém o número de registros do arquivo.
	virtual unsigned int numeroRegistros() = 0;

	// Obtém o tamanho do registro em bytes.
	virtual unsigned int tamanhoRegistro() = 0;

	virtual void escreverObjeto(T objeto) = 0;

	virtual T* lerObjeto(int numeroRegistro) = 0;

private:
	string nomeArquivo;
	fstream arquivoBinario; // Arquivo binário para escrita e leitura de dados. 
};
#endif