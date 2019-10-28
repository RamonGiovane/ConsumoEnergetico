#include <iostream>
#include <io.h>
#include "ArquivoBinario.h"
#include "ArquivoProduto.h"

// Cria um objeto para manipular o arquivo bin�rio com acesso aleat�rio.
ArquivoProduto::ArquivoProduto() {
	arqBin = new ArquivoBinario();
}

/* Cria um objeto para manipular o arquivo bin�rio com acesso aleat�rio cujo nome de arquivo est�
 * especificado em nomeArquivo. Em seguida, abre o arquivo para leitura e escrita.
 */
ArquivoProduto::ArquivoProduto(string nomeArquivo) {
	arqBin = new ArquivoBinario();
	arqBin->abrir(nomeArquivo);
}

// Exclui o objeto arquivo bin�rio.
ArquivoProduto::~ArquivoProduto() {
	delete arqBin;
}

/* Abre o arquivo com o nome especificado em nomeArquivo para escrita e leitura de dados.
* Retorna true se o arquivo foi aberto com sucesso e false caso contr�rio.
*/
bool ArquivoProduto::abrir(string nomeArquivo) {
	if (!arqBin->getArquivoBinario().is_open())
		return arqBin->abrir(nomeArquivo);
	return true;
}

// Fecha o arquivo.
void ArquivoProduto::fechar() {
	arqBin->fechar();
}

// Obt�m o nome do arquivo.
string ArquivoProduto::getNomeArquivo() {
	return arqBin->getNomeArquivo();
}

// Obt�m o tamanho do arquivo em bytes.
unsigned long ArquivoProduto::tamanhoArquivo() {
	return arqBin->tamanhoArquivo();
}

// Obt�m o n�mero de registros do arquivo.
unsigned int ArquivoProduto::numeroRegistros() {
	return tamanhoArquivo() / tamanhoRegistro();
}

/* Obt�m o tamanho do registro em bytes.
 * 20 bytes da descri��o do produto com 20 caracteres (1 byte por caractere);
 *  4 bytes da quantidade;
 *  4 bytes do pre�o.
 */
unsigned int ArquivoProduto::tamanhoRegistro() {
	return TAMANHO_STRING * sizeof(char) + sizeof(int) + sizeof(float);
}

// Escreve o objeto Produto como um registro do arquivo.
void ArquivoProduto::escreverObjeto(Produto produto) {
	RegistroProduto registro;

	// Copiando os atributos do objeto Produto para a estrutura RegistroProduto.
	strncpy_s(registro.nome, TAMANHO_STRING, produto.getNome().c_str(), produto.getNome().length());
	registro.quantidade = produto.getQuantidade();
	registro.preco = produto.getPreco();

	// Posiciona no fim do arquivo.
	arqBin->getArquivoBinario().seekp(0, ios::end);

	// Escreve os dados do produto no arquivo usando a estrutura RegistroProduto.
	arqBin->getArquivoBinario().write(reinterpret_cast<const char *>(&registro), tamanhoRegistro());
}

/* L� os dados de um registro do arquivo e armazena-os no objeto Produto.
 * Retorna o objeto Produto. Em caso de erro retorna NULL.
 */
Produto* ArquivoProduto::lerObjeto(unsigned int numeroRegistro) {
	RegistroProduto registro;

	// Posiciona no registro a ser lido.
	arqBin->getArquivoBinario().seekg(numeroRegistro * tamanhoRegistro());

	// L� o registro e armazena os dados no objeto produto.
	arqBin->getArquivoBinario().read(reinterpret_cast<char *>(&registro), tamanhoRegistro());

	/* Se a leitura n�o falhar o objeto Produto ser� retornado com os dados lidos do arquivo.
	   Cria um objeto Produto com os dados recuperados do arquivo e armazenados na estrutura registro.
	 */
	if (arqBin->getArquivoBinario())
		return new Produto(registro.nome, registro.quantidade, registro.preco);
	else return NULL;
}

/* Exclui um registro do arquivo. O primeiro registro � o n�mero zero (0).
 * Retorna true se o registro foi exclu�do com sucesso e false caso contr�rio.
 */
bool ArquivoProduto::excluirRegistro(unsigned int numeroRegistro) {
	// Obt�m o n�mero de registros do arquivo.
	unsigned registros = numeroRegistros();

	// Verifica se o n�mero do registro � v�lido.
	if (numeroRegistro >= 0 && numeroRegistro < registros) {
		// Cria um novo arquivo que receber� o conte�do do arquivo atual sem o registro a ser exclu�do.
		ArquivoProduto arquivo("Produto.tmp");

		// Copia todos os registros do arquivo Produto.dat para Produto.tmp.
		for (unsigned reg = 0; reg < registros; reg++) 
			if (reg != numeroRegistro) 
				arquivo.escreverObjeto(*lerObjeto(reg));

		// Fecha os arquivos para que possam ser removido e renomeado.
		arquivo.fechar();
		fechar();

		// Remove o arquivo com o registro a ser exclu�do e renomeia o novo arquivo.
		_unlink("Produto.dat");
		rename("Produto.tmp", "Produto.dat");

		// Reabre o arquivo "Produto.dat".
		abrir("Produto.dat");
		return true;
	}
	return false;
}

/* Pesquisa o nome de um produto no arquivo. Em caso de sucesso retorna o n�mero do registro
 * onde o produto est� armazenado, caso contr�rio, retorna -1.
 */
int ArquivoProduto::pesquisarProduto(string nome) {
	Produto *produto;

	// Obt�m o n�mero de registros do arquivo.
	unsigned registros = numeroRegistros();

	// Percorre o arquivo a procura do nome do produto.
	for (unsigned reg = 0; reg < registros; reg++) {
		// Recupera o produto do aquivo.
		produto = lerObjeto(reg);

		// Verifica se � o nome procurado.
		if (!_stricmp(nome.c_str(), produto->getNome().c_str()))
			return reg;
	}
	return -1;
}