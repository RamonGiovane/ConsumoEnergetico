#include "ArquivoHistorico.h"
#include "ArquivoX.h"
#include "Arquivo.h"
#include "Constantes.h"
#include <iostream>
#include <io.h>


/* Abre o arquivo com o nome especificado em nomeArquivo para escrita e leitura de dados.
* Retorna true se o arquivo foi aberto com sucesso e false caso contr�rio.
*/
template<class Cliente>
bool ArquivoX<Cliente>::abrir(string nomeArquivo) {
	if (!getArquivoBinario().is_open())
		return abrir(nomeArquivo);
	return true;
}

// Fecha o arquivo.
template<class Cliente>
void ArquivoX<Cliente>::fechar() {
	fechar();
}

// Obt�m o nome do arquivo.
template<class Cliente>
string ArquivoX<Cliente>::getNomeArquivo() {
	return getNomeArquivo();
}

// Obt�m o tamanho do arquivo em bytes.
template<class Cliente>
unsigned long ArquivoX<Cliente>::tamanhoArquivo() {
	return tamanhoArquivo();
}

// Obt�m o n�mero de registros do arquivo.
template<class Cliente>
unsigned int ArquivoX<Cliente>::numeroRegistros() {
	return tamanhoArquivo() / tamanhoRegistro();
}

/* Obt�m o tamanho do registro em bytes.
* 20 bytes da descri��o do cliente com 20 caracteres (1 byte por caractere);
*  4 bytes da quantidade;
*  4 bytes do pre�o.
*/
template<class Cliente>
unsigned int ArquivoX<Cliente>::tamanhoRegistro() {
	return (TAMANHO_NOMES * sizeof(char) * 4) + (TAMANHO_CODIGOS * sizeof(char) * 3);
}

// Escreve o objeto Cliente como um registro do arquivo.
template<class Cliente>
void ArquivoX<Cliente>::escreverObjeto(Cliente cliente) {
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

/* L� os dados de um registro do arquivo e armazena-os no objeto Cliente.
* Retorna o objeto Cliente. Em caso de erro retorna NULL.
*/
template<class Cliente>
Cliente* ArquivoX<Cliente>::lerObjeto(unsigned int numeroRegistro) {
	RegistroCliente registro;

	// Posiciona no registro a ser lido.
	getArquivoBinario().seekg(numeroRegistro * tamanhoRegistro());

	// L� o registro e armazena os dados no objeto cliente.
	getArquivoBinario().read(reinterpret_cast<char *>(&registro), tamanhoRegistro());

	/* Se a leitura n�o falhar o objeto Cliente ser� retornado com os dados lidos do arquivo.
	Cria um objeto Cliente com os dados recuperados do arquivo e armazenados na estrutura registro.
	*/
	if (getArquivoBinario())
		return new Cliente(registro.numero, registro.nome, registro.CPF, registro.rua, registro.bairro, registro.CEP, registro.cidade);
	else return NULL;
}

/* Exclui um registro do arquivo. O primeiro registro � o n�mero zero (0).
* Retorna true se o registro foi exclu�do com sucesso e false caso contr�rio.
*/
template<class Cliente>
bool ArquivoX<Cliente>::excluirRegistro(unsigned int numeroRegistro) {
	// Obt�m o n�mero de registros do arquivo.
	unsigned registros = numeroRegistros();

	// Verifica se o n�mero do registro � v�lido.
	if (numeroRegistro >= 0 && numeroRegistro < registros) {
		// Cria um novo arquivo que receber� o conte�do do arquivo atual sem o registro a ser exclu�do.
		ArquivoCliente arquivo(FILE_CLIENTE_TMP);

		// Copia todos os registros do arquivo Cliente.dat para Cliente.tmp.
		for (unsigned reg = 0; reg < registros; reg++)
			if (reg != numeroRegistro)
				arquivo.escreverObjeto(*lerObjeto(reg));

		// Fecha os arquivos para que possam ser removido e renomeado.
		arquivo.fechar();
		fechar();

		// Remove o arquivo com o registro a ser exclu�do e renomeia o novo arquivo.
		_unlink(FILE_CLIENTE_DAT);
		rename(FILE_CLIENTE_TMP, FILE_CLIENTE_DAT);

		// Reabre o arquivo "Cliente.dat".
		abrir(FILE_CLIENTE_DAT);
		return true;
	}
	return false;
}

/* Pesquisa o n�mero de um cliente no arquivo. Em caso de sucesso retorna o n�mero do registro
* onde o cliente est� armazenado, caso contr�rio, retorna -1.
*/
template<class Cliente>
int ArquivoX<Cliente>::pesquisarCliente(string numeroCliente) {
	Cliente *cliente;

	// Obt�m o n�mero de registros do arquivo.
	unsigned registros = numeroRegistros();

	// Percorre o arquivo a procura do nome do cliente.
	for (unsigned reg = 0; reg < registros; reg++) {
		// Recupera o cliente do aquivo.
		cliente = lerObjeto(reg);

		// Verifica se � o n�mero procurado.
		if (!_stricmp(numeroCliente.c_str(), cliente->getNumero().c_str()))
			return reg;
	}
	return -1;
}
