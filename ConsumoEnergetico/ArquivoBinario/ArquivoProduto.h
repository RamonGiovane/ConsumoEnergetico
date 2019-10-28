/* Cria uma classe proxy para fornecer opera��es para um arquivo bin�rio usando os servi�os de um arquivo com 
   acesso aleat�rio. Uma classe proxy � usada para ocultar do cliente da classe os membros privados da 
   classe implementada pelo proxy. Neste exemplo, a classe proxy ArquivoProduto � usada para implementar os
   servi�os declarados na interface da classe ArquivoBinario. Como um dos princ�pios da boa engenharia de software
   � ocultar do cliente os detalhes de implementa��o, o cliente da classe ArquivoProduto n�o ter� acesso a 
   implementa��o da classe ArquivoBinario, porque o arquivo de cabe�alho desta classe n�o � inclu�do no 
   arquivo de cabe�alho da classe ArquivoProduto e o c�digo cliente s� receber� o c�digo compilado da classe
   ArquivoBinario.
*/
#ifndef ARQUIVO_PRODUTO
#define ARQUIVO_PRODUTO

#include <fstream>
#include "Produto.h"

/* Declara��o de classe antecipada necess�rio para definir o ponteiro arqBin. Um ponteiro ou uma refer�ncia n�o 
   exige o arquivo de cabe�alho da classe, apenas a declara��o abaixo.
*/
class ArquivoBinario;

/* Como a classe string no C++ utiliza mem�ria din�mica para alocar os seus caracteres, � necess�rio usar
   um array de caracteres para assegurar o tamanho fixo das strings literais que ser�o escritas e lidas
   no arquivo de acesso aleat�rio, e consequentemente o tamanho fixo dos registros.

   Para usar essa classe ser� necess�rio criar uma estrutura para acomodar os campos (vari�veis de inst�ncia) 
   dos objetos que ser�o gravados e lidos do arquivo. Esta estrutura � utilizada nos m�todos 
   escreverObjeto e lerObjeto de cada classe de arquivo, neste exemplo, da classe ArquivoProduto.
*/
struct RegistroProduto {
	char nome[TAMANHO_STRING];
	int quantidade;
	float preco;
};

class ArquivoProduto {
public:
	// Cria um objeto para manipular o arquivo bin�rio com acesso aleat�rio.
	ArquivoProduto();

	/* Cria um objeto para manipular o arquivo bin�rio com acesso aleat�rio cujo nome de arquivo est� 
	 * especificado em nomeArquivo. Em seguida, abre o arquivo para leitura e escrita.
	 */
	ArquivoProduto(string nomeArquivo);

	// Exclui o objeto arquivo bin�rio.
	~ArquivoProduto();

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
	void escreverObjeto(Produto produto);

	/* L� os dados de um registro do arquivo e armazena-os no objeto Produto.
	 * Retorna o objeto Produto. Em caso de erro retorna NULL.
	 */
	Produto* lerObjeto(unsigned int numeroRegistro);

	/* Exclui um registro do arquivo. O primeiro registro � o n�mero zero (0).
	 * Retorna true se o registro foi exclu�do com sucesso e false caso contr�rio.
	 */
	bool excluirRegistro(unsigned int numeroRegistro);

	/* Pesquisa o nome de um produto no arquivo. Em caso de sucesso retorna o n�mero do registro
	 * onde o produto est� armazenado, caso contr�rio, retorna -1.
	*/
	int pesquisarProduto(string nome);

private:
	ArquivoBinario *arqBin; 
};
#endif
