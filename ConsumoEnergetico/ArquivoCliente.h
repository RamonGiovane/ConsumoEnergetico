#ifndef ARQUIVO_CLIENTE_H
#define ARQUIVO_CLIENTE_H
#include "ArquivoBinario\ArquivoBinario.h"
#include "Cliente.h"
#include <string>

#define TAMANHO_STRING 70
using namespace std;
struct RegistroCliente {
	char nome[TAMANHO_STRING];
	char rua[TAMANHO_STRING];
	char bairro[TAMANHO_STRING];
	char CEP[TAMANHO_STRING];
	char cidade[TAMANHO_STRING];
	char numero[TAMANHO_STRING];
};



class ArquivoCliente
{
public:
	// Cria um objeto para manipular o arquivo bin�rio com acesso aleat�rio.
	ArquivoCliente();

	/* Cria um objeto para manipular o arquivo bin�rio com acesso aleat�rio cujo nome de arquivo est�
	* especificado em nomeArquivo. Em seguida, abre o arquivo para leitura e escrita.
	*/
	ArquivoCliente(string nomeArquivo);

	// Exclui o objeto arquivo bin�rio.
	~ArquivoCliente();

	/* Abre o arquivo com o nome especificado em nomeArquivo para escrita e leitura de dados.
	* Retorna true se o arquivo foi aberto com sucesso e false caso contr�rio.
	*/
	bool abrir(string nomeArquivo);

	// Fecha o arquivo.
	void fechar();

	// Obt�m o nome do arquivo.
	string getNomeArquivo();

	// Obt�m o tamanho do arquivo em bytes.
	unsigned long tamanhoArquivo();

	// Obt�m o n�mero de registros do arquivo.
	unsigned int numeroRegistros();

	// Obt�m o tamanho do registro em bytes.
	unsigned int tamanhoRegistro();

	// Escreve o objeto Produto como um registro do arquivo.
	void escreverObjeto(Cliente cliente);

	/* L� os dados de um registro do arquivo e armazena-os no objeto Produto.
	* Retorna o objeto Produto. Em caso de erro retorna NULL.
	*/
	Cliente* lerObjeto(unsigned int numeroRegistro);

	/* Exclui um registro do arquivo. O primeiro registro � o n�mero zero (0).
	* Retorna true se o registro foi exclu�do com sucesso e false caso contr�rio.
	*/
	bool excluirRegistro(unsigned int numeroRegistro);

	/* Pesquisa o nome de um cliente no arquivo. Em caso de sucesso retorna o n�mero do registro
	* onde o cliente est� armazenado, caso contr�rio, retorna -1.
	*/
	int pesquisarProduto(string nome);

private:
	ArquivoBinario *arqBin;
};

#endif // !ARQUIVO_CLIENTE_H