#include "ArquivoHistorico.h"
#include "ArquivoCliente.h"
#include "ArquivoBinario.h"
#include "ArquivoCliente.h"
#include "Constantes.h"
#include <iostream>
#include <io.h>



ArquivoCliente::ArquivoCliente() {}

ArquivoCliente::ArquivoCliente(string nomeArquivo) : ArquivoBinario(nomeArquivo) {}

/* Obtém o tamanho do registro em bytes.
* 20 bytes da descrição do cliente com 20 caracteres (1 byte por caractere);
*  4 bytes da quantidade;
*  4 bytes do preço.
*/
unsigned int ArquivoCliente::tamanhoRegistro() {
	return (TAMANHO_NOMES * sizeof(char) * 4) + (TAMANHO_CODIGOS * sizeof(char) * 3);
}

// Escreve o objeto Cliente como um registro do arquivo.
void ArquivoCliente::escreverObjeto(Cliente cliente) {
	RegistroCliente registro;

	// Copiando os atributos do objeto Cliente para a estrutura RegistroCliente.
	strncpy_s(registro.nome, cliente.getNome().c_str(), _TRUNCATE);
	strncpy_s(registro.bairro, cliente.getBairro().c_str(), _TRUNCATE);
	strncpy_s(registro.CEP, TAMANHO_CODIGOS, cliente.getCEP().c_str(), cliente.getCEP().length());
	strncpy_s(registro.CPF, TAMANHO_CODIGOS, cliente.getCEP().c_str(), cliente.getCEP().length());
	strncpy_s(registro.cidade, TAMANHO_NOMES, cliente.getCidade().c_str(), cliente.getCidade().length());
	strncpy_s(registro.rua, TAMANHO_NOMES, cliente.getRua().c_str(), cliente.getRua().length());
	strncpy_s(registro.numero, TAMANHO_CODIGOS, cliente.getNumero().c_str(), cliente.getNumero().length());

	// Posiciona no fim do arquivo.
	getArquivoBinario().seekp(0, ios::end);

	// Escreve os dados do cliente no arquivo usando a estrutura RegistroCliente.
	getArquivoBinario().write(reinterpret_cast<const char *>(&registro), tamanhoRegistro());
}

/* Lê os dados de um registro do arquivo e armazena-os no objeto Cliente.
* Retorna o objeto Cliente. Em caso de erro retorna NULL.
*/
Cliente* ArquivoCliente::lerObjeto(unsigned int numeroRegistro) {
	RegistroCliente registro;

	// Posiciona no registro a ser lido.
	getArquivoBinario().seekg(numeroRegistro * tamanhoRegistro());

	// Lê o registro e armazena os dados no objeto cliente.
	getArquivoBinario().read(reinterpret_cast<char *>(&registro), tamanhoRegistro());

	/* Se a leitura não falhar o objeto Cliente será retornado com os dados lidos do arquivo.
	Cria um objeto Cliente com os dados recuperados do arquivo e armazenados na estrutura registro.
	*/
	if (getArquivoBinario())
		return new Cliente(registro.numero, registro.nome, registro.CPF, registro.rua, registro.bairro, registro.CEP, registro.cidade);
	else return NULL;
}


/* Pesquisa o número de um cliente no arquivo. Em caso de sucesso retorna o número do registro
* onde o cliente está armazenado, caso contrário, retorna -1.
*/
int ArquivoCliente::pesquisarCliente(string numeroCliente) {
	Cliente *cliente;

	// Obtém o número de registros do arquivo.
	unsigned registros = numeroRegistros();

	// Percorre o arquivo a procura do nome do cliente.
	for (unsigned reg = 0; reg < registros; reg++) {
		// Recupera o cliente do aquivo.
		cliente = lerObjeto(reg);

		// Verifica se é o número procurado.
		if (!_stricmp(numeroCliente.c_str(), cliente->getNumero().c_str()))
			return reg;
	}
	return -1;
}
