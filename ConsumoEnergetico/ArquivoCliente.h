#ifndef ARQUIVO_CLIENTE_H
#define ARQUIVO_CLIENTE_H
#include "ArquivoBinario\ArquivoBinario.h"
#include "Cliente.h"
#include <string>
#include "Constantes.h"

using namespace std;
struct RegistroCliente {
	char nome[TAMANHO_NOMES];
	char rua[TAMANHO_NOMES];
	char bairro[TAMANHO_NOMES];
	char cidade[TAMANHO_NOMES];
	char CEP[TAMANHO_CODIGOS];
	char CPF[TAMANHO_CODIGOS];
	char numero[TAMANHO_CODIGOS];
};

class ArquivoCliente
{
public:
	// Cria um objeto para manipular o arquivo binário com acesso aleatório.
	ArquivoCliente();

	/* Cria um objeto para manipular o arquivo binário com acesso aleatório cujo nome de arquivo está
	* especificado em nomeArquivo. Em seguida, abre o arquivo para leitura e escrita.
	*/
	ArquivoCliente(string nomeArquivo);

	// Exclui o objeto arquivo binário.
	~ArquivoCliente();

	/* Abre o arquivo com o nome especificado em nomeArquivo para escrita e leitura de dados.
	* Retorna true se o arquivo foi aberto com sucesso e false caso contrário.
	*/
	bool abrir(string nomeArquivo);

	// Fecha o arquivo.
	void fechar();

	// Obtém o nome do arquivo.
	string getNomeArquivo();

	// Obtém o tamanho do arquivo em bytes.
	unsigned long tamanhoArquivo();

	// Obtém o número de registros do arquivo.
	unsigned int numeroRegistros();

	// Obtém o tamanho do registro em bytes.
	unsigned int tamanhoRegistro();

	// Escreve o objeto Cliente como um registro do arquivo.
	void escreverObjeto(Cliente cliente);

	/* Lê os dados de um registro do arquivo e armazena-os no objeto Cliente.
	* Retorna o objeto Cliente. Em caso de erro retorna NULL.
	*/
	Cliente* lerObjeto(unsigned int numeroRegistro);

	/* Exclui um registro do arquivo. O primeiro registro é o número zero (0).
	* Retorna true se o registro foi excluído com sucesso e false caso contrário.
	*/
	bool excluirRegistro(unsigned int numeroRegistro);

	


	/* Pesquisa o número de um cliente no arquivo. Em caso de sucesso retorna o número do registro
	* onde o cliente está armazenado, caso contrário, retorna -1.
	*/
	int pesquisarCliente(string numero);

private:
	ArquivoBinario *arqBin;
};

#endif // !ARQUIVO_CLIENTE_H