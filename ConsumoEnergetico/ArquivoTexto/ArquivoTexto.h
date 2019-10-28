// Esta classe fornece os métodos básicos para manipular um arquivo texto em disco.
#ifndef ARQUIVO_TEXTO
#define ARQUIVO_TEXTO

#include <fstream>
#include <string>

using namespace std;

/* Define os tipos de acesso que podem ser usados para acessar o arquivo. Os modos disponíveis são:

   ACRESCENTAR: abre o arquivo somente para acrescentar dados no fim do arquivo;
   ESCRITA: abre o arquivo somente para a escrita de dados;
   LEITURA: abre o arquivo somente para a leitura de seu conteúdo.
*/
enum TipoDeAcesso { ACRESCENTAR, ESCRITA, LEITURA };

#define TAMANHO_LINHA 180

class ArquivoTexto {
public: 
	// Fecha o arquivo texto antes do objeto ser removido da memória.
	~ArquivoTexto();

	/* Abre um arquivo texto identificado pelo parâmetro nomeArquivo.
	 * O modo de abertura do arquivo deve ser especificado por uma das constantes de TipoDeAcesso.
	 * Se o arquivo não existir ele será criado. Se o modo for ESCRITA e o arquivo já existir em disco, 
	 * todo o seu conteúdo será excluído.
	 * Retorna true se o arquivo foi aberto com sucesso e false caso contrário.
	 */
	bool abrir(string nomeArquivo, TipoDeAcesso modo);

	/* Escreve no arquivo texto o conteúdo do objeto string armazenado no parâmetro conteudo.
	 * A escrita sempre ocorre no fim do arquivo.
	 * Retorna true se a operação foi realizada com sucesso e false caso contrário.
	 */
	bool escrever(string conteudo);

	/* Lê o conteúdo do arquivo texto.
	 * Retorna um objeto string com todo o conteúdo do arquivo texto.
	 * Em caso de erro retorna um objeto string com o valor literal "NULL".
	 */
	string ler();

	/* Lê o conteúdo de uma linha de texto do arquivo identificada por numeroLinha.
	 * A primeira linha de texto é de número zero (0).
	 * Retorna um objeto string com o conteúdo da linha de texto.
	 * Em caso de erro retorna um objeto string com o valor literal "NULL".
	 *
	 * ATENÇÃO: Este método só irá recuperar a linha de texto correta do arquivo se todas  
	 *          as linhas de texto possuírem o mesmo tamanho (comprimento), em bytes.
	 */
	string lerLinha(int numeroLinha);

	// Fecha o arquivo texto.
	void fechar();

	// Obtém o nome do arquivo texto.
	string getNomeArquivo();

private:
	string nomeArquivo, texto;
	ifstream inputFile;
	ofstream outputFile;
}; 
#endif 