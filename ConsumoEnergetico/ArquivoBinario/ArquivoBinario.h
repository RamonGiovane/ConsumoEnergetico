// Cria opera��es para um arquivo bin�rio usando os servi�os de um arquivo com acesso aleat�rio.
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
	 * Se o arquivo n�o existir ele ser� criado.
	 * Retorna true se o arquivo foi aberto com sucesso e false caso contr�rio.
	 */
	virtual bool abrir(string nomeArquivo);
	
	// Obt�m o n�mero de registros do arquivo.
	unsigned int numeroRegistros();

	// Fecha o arquivo.
	virtual void fechar();

	// Obt�m o nome do arquivo.
	virtual string getNomeArquivo();

protected:
	// Reposiciona o arquivo para o inicio
	virtual void reposicionarArquivo();

	// Obt�m a refer�ncia do arquivoBinario.
	virtual fstream& getArquivoBinario();

	// Obt�m o tamanho do arquivo em bytes.
	virtual unsigned long tamanhoArquivo();

	// Obt�m o tamanho do registro em bytes.
	virtual unsigned int tamanhoRegistro() = 0;

private:
	string nomeArquivo;
	fstream arquivoBinario; // Arquivo bin�rio para escrita e leitura de dados. 
};
#endif