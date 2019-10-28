#include <iostream>
#include <clocale>
#include "TestarArquivoTexto.h"

//int main() {
//	string a;
//	
//	cin >> a;
//	return testarArquivoTexto();
//}

// Testa o funcionamento dos m�todos da classe ArquivoTexto.
int testarArquivoTexto() {
	setlocale(LC_ALL, "pt-BR");

	ArquivoTexto arquivoTexto;
	string texto1[] = { "�gua", "Fogo", "Terra", "Ar", "Hist�ria", "Computa��o" };
	string texto2[] = { "Amor", "", "Esses s�o os cinco elementos." };

	//escrever("Palavras.txt", arquivoTexto, texto1, 6); 
	//exibir("----- CRIA��O -----", "Palavras.txt", arquivoTexto);

	exibir("----- Investidores -----", "Investidores.txt", arquivoTexto);

	/*adicionar("Palavras.txt", arquivoTexto, texto2, 3);
	exibir("----- ATUALIZA��O -----", "Palavras.txt", arquivoTexto);

	arquivoTextoComTamanhoFixo();*/
	cout << endl << endl;
	return 0;
} 

/* Cria um arquivo texto no diret�rio atual. Os par�metros s�o:

	1. nomeArquivo: nome do arquivo texto;
	2. arquivoTexto: objeto ArquivoTexto;
	3. texto: vetor de objetos string com o conte�do a ser escrito no arquivo;
	4: tamanho: tamanho do vetor de objetos string que ser� escrito no arquivo.
*/
void escrever(string nomeArquivo, ArquivoTexto &arquivoTexto, string texto[], size_t tamanho) {
	arquivoTexto.abrir(nomeArquivo, ESCRITA);

	// Escreve o conte�do do array no arquivo.
	for (size_t pos = 0; pos < tamanho; pos++)
		arquivoTexto.escrever(texto[pos]);

	arquivoTexto.fechar();
} 

/* Adiciona novas linhas de texto no arquivo do diret�rio atual. Os par�metros s�o:

	1. nomeArquivo: nome do arquivo texto;
	2. arquivoTexto: objeto ArquivoTexto;
	3. texto: vetor de objetos string com o conte�do a ser escrito no arquivo;
	4: tamanho: tamanho do vetor de objetos string que ser� escrito no arquivo.
*/
void adicionar(string nomeArquivo, ArquivoTexto &arquivoTexto, string texto[], size_t tamanho) {
	arquivoTexto.abrir(nomeArquivo, ACRESCENTAR);

	// Escreve o conte�do do array no arquivo.
	for (size_t pos = 0; pos < tamanho; pos++)
		arquivoTexto.escrever(texto[pos]);

	arquivoTexto.fechar();
} 

/* Abre e exibe o arquivo texto no console. Os par�metros s�o:

	1. msg: mensagem de texto referente ao conte�do a ser exibido;
	2. nomeArquivo: nome do arquivo texto;
	3. arquivoTexto: objeto ArquivoTexto.
	*/
void exibir(string msg, string nomeArquivo, ArquivoTexto &arquivoTexto) {
	arquivoTexto.abrir(nomeArquivo, LEITURA);

	cout << msg << "\nArquivo: " << arquivoTexto.getNomeArquivo() << "\n\n" << arquivoTexto.ler() << "\n\n";

	arquivoTexto.fechar();
}

/* Exemplifica como realizar um acesso aleat�rio (relativo) com arquivo texto em que todas as 
 * linhas possuem o mesmo comprimento (n�mero de caracteres).
 */
void arquivoTextoComTamanhoFixo() {
	/* Neste exemplo, o tamanho padr�o da linha inclui 5 d�gitos e os caracteres de controle LF/CR.
	   Este caracteres s�o introduzidos no fim de cada linha de texto. Eles correspondem a tecla ENTER.
	*/
	const int TAMANHO_PADRAO_DA_LINHA = 7;

	ArquivoTexto arquivoTexto;
	string numeros[] = { "00123", "00456", "00789", "01321", "01654", "01987" };
	string linhas[6];

	escrever("N�meros.txt", arquivoTexto, numeros, 6);
	exibir("----- CRIA��O -----", "N�meros.txt", arquivoTexto);

	arquivoTexto.abrir("N�meros.txt", LEITURA);

	cout << "----- Conte�do invertido do arquivo N�meros.txt -----\n\n";
	for (int lin = _countof(linhas) - 1; lin >= 0; lin--)
	{
		/* O par�metro passado para a fun��o lerLinha da classe ArquivoTexto � calculado
		   passando o deslocamento (a partir do in�cio zero) em bytes de cada linha de texto. 
		   Este deslocamento � calculado com base no TAMANHO_PADRAO_DA_LINHA.
		*/
		linhas[lin] = arquivoTexto.lerLinha(lin * TAMANHO_PADRAO_DA_LINHA);
		cout << "Linha " << (lin + 1) << ": " << linhas[lin] << endl;
	}
	arquivoTexto.fechar();
}