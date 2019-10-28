/* Cria uma classe proxy para fornecer operações para um arquivo binário usando os serviços de um arquivo com 
   acesso aleatório. Uma classe proxy é usada para ocultar do cliente da classe os membros privados da 
   classe implementada pelo proxy. Neste exemplo, a classe proxy ArquivoProduto é usada para implementar os
   serviços declarados na interface da classe ArquivoBinario. Como um dos princípios da boa engenharia de software
   é ocultar do cliente os detalhes de implementação, o cliente da classe ArquivoProduto não terá acesso a 
   implementação da classe ArquivoBinario, porque o arquivo de cabeçalho desta classe não é incluído no 
   arquivo de cabeçalho da classe ArquivoProduto e o código cliente só receberá o código compilado da classe
   ArquivoBinario.
*/
#ifndef ARQUIVO_PRODUTO
#define ARQUIVO_PRODUTO

#include <fstream>
#include "Produto.h"

/* Declaração de classe antecipada necessário para definir o ponteiro arqBin. Um ponteiro ou uma referência não 
   exige o arquivo de cabeçalho da classe, apenas a declaração abaixo.
*/
class ArquivoBinario;

/* Como a classe string no C++ utiliza memória dinâmica para alocar os seus caracteres, é necessário usar
   um array de caracteres para assegurar o tamanho fixo das strings literais que serão escritas e lidas
   no arquivo de acesso aleatório, e consequentemente o tamanho fixo dos registros.

   Para usar essa classe será necessário criar uma estrutura para acomodar os campos (variáveis de instância) 
   dos objetos que serão gravados e lidos do arquivo. Esta estrutura é utilizada nos métodos 
   escreverObjeto e lerObjeto de cada classe de arquivo, neste exemplo, da classe ArquivoProduto.
*/
struct RegistroProduto {
	char nome[TAMANHO_STRING];
	int quantidade;
	float preco;
};

class ArquivoProduto {
public:
	// Cria um objeto para manipular o arquivo binário com acesso aleatório.
	ArquivoProduto();

	/* Cria um objeto para manipular o arquivo binário com acesso aleatório cujo nome de arquivo está 
	 * especificado em nomeArquivo. Em seguida, abre o arquivo para leitura e escrita.
	 */
	ArquivoProduto(string nomeArquivo);

	// Exclui o objeto arquivo binário.
	~ArquivoProduto();

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
	
	// Escreve o objeto Produto como um registro do arquivo.
	void escreverObjeto(Produto produto);

	/* Lê os dados de um registro do arquivo e armazena-os no objeto Produto.
	 * Retorna o objeto Produto. Em caso de erro retorna NULL.
	 */
	Produto* lerObjeto(unsigned int numeroRegistro);

	/* Exclui um registro do arquivo. O primeiro registro é o número zero (0).
	 * Retorna true se o registro foi excluído com sucesso e false caso contrário.
	 */
	bool excluirRegistro(unsigned int numeroRegistro);

	/* Pesquisa o nome de um produto no arquivo. Em caso de sucesso retorna o número do registro
	 * onde o produto está armazenado, caso contrário, retorna -1.
	*/
	int pesquisarProduto(string nome);

private:
	ArquivoBinario *arqBin; 
};
#endif
