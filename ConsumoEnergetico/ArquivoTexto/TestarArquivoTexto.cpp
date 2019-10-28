#include <iostream>
#include <clocale>
#include "TestarArquivoTexto.h"

//int main() {
//	string a;
//	
//	cin >> a;
//	return testarArquivoTexto();
//}

// Testa o funcionamento dos métodos da classe ArquivoTexto.
int testarArquivoTexto() {
	setlocale(LC_ALL, "pt-BR");

	ArquivoTexto arquivoTexto;
	string texto1[] = { "Água", "Fogo", "Terra", "Ar", "História", "Computação" };
	string texto2[] = { "Amor", "", "Esses são os cinco elementos." };

	//escrever("Palavras.txt", arquivoTexto, texto1, 6); 
	//exibir("----- CRIAÇÃO -----", "Palavras.txt", arquivoTexto);

	exibir("----- Investidores -----", "Investidores.txt", arquivoTexto);

	/*adicionar("Palavras.txt", arquivoTexto, texto2, 3);
	exibir("----- ATUALIZAÇÃO -----", "Palavras.txt", arquivoTexto);

	arquivoTextoComTamanhoFixo();*/
	cout << endl << endl;
	return 0;
} 

/* Cria um arquivo texto no diretório atual. Os parâmetros são:

	1. nomeArquivo: nome do arquivo texto;
	2. arquivoTexto: objeto ArquivoTexto;
	3. texto: vetor de objetos string com o conteúdo a ser escrito no arquivo;
	4: tamanho: tamanho do vetor de objetos string que será escrito no arquivo.
*/
void escrever(string nomeArquivo, ArquivoTexto &arquivoTexto, string texto[], size_t tamanho) {
	arquivoTexto.abrir(nomeArquivo, ESCRITA);

	// Escreve o conteúdo do array no arquivo.
	for (size_t pos = 0; pos < tamanho; pos++)
		arquivoTexto.escrever(texto[pos]);

	arquivoTexto.fechar();
} 

/* Adiciona novas linhas de texto no arquivo do diretório atual. Os parâmetros são:

	1. nomeArquivo: nome do arquivo texto;
	2. arquivoTexto: objeto ArquivoTexto;
	3. texto: vetor de objetos string com o conteúdo a ser escrito no arquivo;
	4: tamanho: tamanho do vetor de objetos string que será escrito no arquivo.
*/
void adicionar(string nomeArquivo, ArquivoTexto &arquivoTexto, string texto[], size_t tamanho) {
	arquivoTexto.abrir(nomeArquivo, ACRESCENTAR);

	// Escreve o conteúdo do array no arquivo.
	for (size_t pos = 0; pos < tamanho; pos++)
		arquivoTexto.escrever(texto[pos]);

	arquivoTexto.fechar();
} 

/* Abre e exibe o arquivo texto no console. Os parâmetros são:

	1. msg: mensagem de texto referente ao conteúdo a ser exibido;
	2. nomeArquivo: nome do arquivo texto;
	3. arquivoTexto: objeto ArquivoTexto.
	*/
void exibir(string msg, string nomeArquivo, ArquivoTexto &arquivoTexto) {
	arquivoTexto.abrir(nomeArquivo, LEITURA);

	cout << msg << "\nArquivo: " << arquivoTexto.getNomeArquivo() << "\n\n" << arquivoTexto.ler() << "\n\n";

	arquivoTexto.fechar();
}

/* Exemplifica como realizar um acesso aleatório (relativo) com arquivo texto em que todas as 
 * linhas possuem o mesmo comprimento (número de caracteres).
 */
void arquivoTextoComTamanhoFixo() {
	/* Neste exemplo, o tamanho padrão da linha inclui 5 dígitos e os caracteres de controle LF/CR.
	   Este caracteres são introduzidos no fim de cada linha de texto. Eles correspondem a tecla ENTER.
	*/
	const int TAMANHO_PADRAO_DA_LINHA = 7;

	ArquivoTexto arquivoTexto;
	string numeros[] = { "00123", "00456", "00789", "01321", "01654", "01987" };
	string linhas[6];

	escrever("Números.txt", arquivoTexto, numeros, 6);
	exibir("----- CRIAÇÃO -----", "Números.txt", arquivoTexto);

	arquivoTexto.abrir("Números.txt", LEITURA);

	cout << "----- Conteúdo invertido do arquivo Números.txt -----\n\n";
	for (int lin = _countof(linhas) - 1; lin >= 0; lin--)
	{
		/* O parâmetro passado para a função lerLinha da classe ArquivoTexto é calculado
		   passando o deslocamento (a partir do início zero) em bytes de cada linha de texto. 
		   Este deslocamento é calculado com base no TAMANHO_PADRAO_DA_LINHA.
		*/
		linhas[lin] = arquivoTexto.lerLinha(lin * TAMANHO_PADRAO_DA_LINHA);
		cout << "Linha " << (lin + 1) << ": " << linhas[lin] << endl;
	}
	arquivoTexto.fechar();
}