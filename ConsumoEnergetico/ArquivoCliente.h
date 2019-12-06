#ifndef ARQUIVO_CLIENTE_H
#define ARQUIVO_CLIENTE_H
#include "ArquivoBinario.h"
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

class ArquivoCliente : public ArquivoBinario
{
public:


	ArquivoCliente();

	ArquivoCliente(string nomeArquivo);

	// Obtém o tamanho do registro em bytes.
	unsigned int tamanhoRegistro();

	// Escreve o objeto Cliente como um registro do arquivo.
	void escreverObjeto(Cliente cliente);

	/* Lê os dados de um registro do arquivo e armazena-os no objeto Cliente.
	* Retorna o objeto Cliente. Em caso de erro retorna NULL.
	*/
	Cliente* lerObjeto(unsigned int numeroRegistro);


	/* Pesquisa o número de um cliente no arquivo. Em caso de sucesso retorna o número do registro
	* onde o cliente está armazenado, caso contrário, retorna -1.
	*/
	int pesquisarCliente(string numero);

};

#endif // !ARQUIVO_CLIENTE_H