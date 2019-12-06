// Cria opera��es para um arquivo bin�rio usando os servi�os de um arquivo com acesso aleat�rio.
#ifndef ARQUIVO_BINARIOX
#define ARQUIVO_BINARIOX

#include <fstream>
#include <string>

using namespace std;

template<class T>
class Arquivo {

protected:

	// Obt�m a refer�ncia do Arquivo.
	fstream& getArquivo();

public:
	/* Abre o arquivo com o nome especificado em nomeArquivo para escrita e leitura de dados.
	* Se o arquivo n�o existir ele ser� criado.
	* Retorna true se o arquivo foi aberto com sucesso e false caso contr�rio.
	*/
	virtual bool abrir(string nomeArquivo);

	// Fecha o arquivo.
	virtual void fechar();
	
	// Reposiciona o arquivo para o inicio
	void reposicionarArquivo();

	// Obt�m o nome do arquivo.
	virtual string getNomeArquivo();

	// Obt�m o tamanho do arquivo em bytes.
	virtual unsigned long tamanhoArquivo();

	// Obt�m o n�mero de registros do arquivo.
	virtual unsigned int numeroRegistros() = 0;

	// Obt�m o tamanho do registro em bytes.
	virtual unsigned int tamanhoRegistro() = 0;

	virtual void escreverObjeto(T objeto) = 0;

	virtual T* lerObjeto(int numeroRegistro) = 0;

private:
	string nomeArquivo;
	fstream arquivoBinario; // Arquivo bin�rio para escrita e leitura de dados. 
};
#endif