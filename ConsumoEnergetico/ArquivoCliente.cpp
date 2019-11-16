#include "ArquivoHistorico.h"


#include "ArquivoCliente.h"
#include "ArquivoBinario\ArquivoBinario.h"
#include "ArquivoCliente.h"
#include "Constantes.h"
#include <iostream>
#include <io.h>

// Cria um objeto para manipular o arquivo bin�rio com acesso aleat�rio.
ArquivoCliente::ArquivoCliente() {
	arqBin = new ArquivoBinario();
}

/* Cria um objeto para manipular o arquivo bin�rio com acesso aleat�rio cujo nome de arquivo est�
* especificado em nomeArquivo. Em seguida, abre o arquivo para leitura e escrita.
*/
ArquivoCliente::ArquivoCliente(string nomeArquivo) {
	arqBin = new ArquivoBinario();
	arqBin->abrir(nomeArquivo);
}

// Exclui o objeto arquivo bin�rio.
ArquivoCliente::~ArquivoCliente() {
	fechar();
	delete arqBin;
}

/* Abre o arquivo com o nome especificado em nomeArquivo para escrita e leitura de dados.
* Retorna true se o arquivo foi aberto com sucesso e false caso contr�rio.
*/
bool ArquivoCliente::abrir(string nomeArquivo) {
	if (!arqBin->getArquivoBinario().is_open())
		return arqBin->abrir(nomeArquivo);
	return true;
}

// Fecha o arquivo.
void ArquivoCliente::fechar() {
	arqBin->fechar();
}

// Obt�m o nome do arquivo.
string ArquivoCliente::getNomeArquivo() {
	return arqBin->getNomeArquivo();
}

// Obt�m o tamanho do arquivo em bytes.
unsigned long ArquivoCliente::tamanhoArquivo() {
	return arqBin->tamanhoArquivo();
}

// Obt�m o n�mero de registros do arquivo.
unsigned int ArquivoCliente::numeroRegistros() {
	return tamanhoArquivo() / tamanhoRegistro();
}

/* Obt�m o tamanho do registro em bytes.
* 20 bytes da descri��o do cliente com 20 caracteres (1 byte por caractere);
*  4 bytes da quantidade;
*  4 bytes do pre�o.
*/
unsigned int ArquivoCliente::tamanhoRegistro() {
	return (TAMANHO_NOMES * sizeof(char) * 4) + (TAMANHO_CODIGOS * sizeof(char) * 2);
}

// Escreve o objeto Cliente como um registro do arquivo.
void ArquivoCliente::escreverObjeto(Cliente cliente) {
	RegistroCliente registro;

	// Copiando os atributos do objeto Cliente para a estrutura RegistroCliente.
	strncpy_s(registro.nome, TAMANHO_NOMES, cliente.getNome().c_str(), cliente.getNome().length());
	strncpy_s(registro.bairro, TAMANHO_NOMES, cliente.getBairro().c_str(), cliente.getBairro().length());
	strncpy_s(registro.CEP, TAMANHO_CODIGOS, cliente.getCEP().c_str(), cliente.getCEP().length());
	strncpy_s(registro.cidade, TAMANHO_NOMES, cliente.getCidade().c_str(), cliente.getCidade().length());
	strncpy_s(registro.rua, TAMANHO_NOMES, cliente.getRua().c_str(), cliente.getRua().length());
	strncpy_s(registro.numero, TAMANHO_CODIGOS, cliente.getNumero().c_str(), cliente.getNumero().length());

	// Posiciona no fim do arquivo.
	arqBin->getArquivoBinario().seekp(0, ios::end);

	// Escreve os dados do cliente no arquivo usando a estrutura RegistroCliente.
	arqBin->getArquivoBinario().write(reinterpret_cast<const char *>(&registro), tamanhoRegistro());
}

/* L� os dados de um registro do arquivo e armazena-os no objeto Cliente.
* Retorna o objeto Cliente. Em caso de erro retorna NULL.
*/
Cliente* ArquivoCliente::lerObjeto(unsigned int numeroRegistro) {
	RegistroCliente registro;

	// Posiciona no registro a ser lido.
	arqBin->getArquivoBinario().seekg(numeroRegistro * tamanhoRegistro());

	// L� o registro e armazena os dados no objeto cliente.
	arqBin->getArquivoBinario().read(reinterpret_cast<char *>(&registro), tamanhoRegistro());

	/* Se a leitura n�o falhar o objeto Cliente ser� retornado com os dados lidos do arquivo.
	Cria um objeto Cliente com os dados recuperados do arquivo e armazenados na estrutura registro.
	*/
	if (arqBin->getArquivoBinario())
		return new Cliente(registro.numero, registro.nome, registro.rua, registro.bairro, registro.CEP, registro.cidade);
	else return NULL;
}

/* Exclui um registro do arquivo. O primeiro registro � o n�mero zero (0).
* Retorna true se o registro foi exclu�do com sucesso e false caso contr�rio.
*/
bool ArquivoCliente::excluirRegistro(unsigned int numeroRegistro) {
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
int ArquivoCliente::pesquisarCliente(string numeroCliente) {
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
