#ifndef TESTAR_ARQUIVO_TEXTO
#define TESTAR_ARQUIVO_TEXTO

#include "ArquivoTexto.h"

/* Cria um arquivo texto no diretório atual. Os parâmetros são:

	1. nomeArquivo: nome do arquivo texto;
	2. arquivoTexto: objeto ArquivoTexto;
	3. texto: vetor de objetos string com o conteúdo a ser escrito no arquivo;
	4: tamanho: tamanho do vetor de objetos string que será escrito no arquivo.
*/
void escrever(string nomeArquivo, ArquivoTexto &arquivoTexto, string texto[], size_t tamanho);

/* Adiciona novas linhas de texto no arquivo do diretório atual. Os parâmetros são:

	1. nomeArquivo: nome do arquivo texto;
	2. arquivoTexto: objeto ArquivoTexto;
	3. texto: vetor de objetos string com o conteúdo a ser escrito no arquivo;
	4: tamanho: tamanho do vetor de objetos string que será escrito no arquivo.
*/
void adicionar(string nomeArquivo, ArquivoTexto &arquivoTexto, string texto[], size_t tamanho);

/* Abre e exibe o arquivo texto no console. Os parâmetros são:

	1. msg: mensagem de texto referente ao conteúdo a ser exibido;
	2. nomeArquivo: nome do arquivo texto;
	3. arquivoTexto: objeto ArquivoTexto.
*/
void exibir(string msg, string nomeArquivo, ArquivoTexto &arquivoTexto);

/* Exemplifica como realizar um acesso aleatório (relativo) com arquivo texto em que todas as
 * linhas possuem o mesmo comprimento (número de caracteres).
 */
void arquivoTextoComTamanhoFixo();

// Testa o funcionamento dos métodos da classe ArquivoTexto.
int testarArquivoTexto();
#endif