// Implementa os serviços da classe ArquivoTexto.
#include <iostream>
#include <cstring>
#include "ArquivoTexto.h"

// Fecha o arquivo texto antes do objeto ser removido da memória.
ArquivoTexto::~ArquivoTexto() {
	fechar();
}

/* Abre um arquivo texto identificado pelo parâmetro nomeArquivo.
 * O modo de abertura do arquivo deve ser especificado por uma das constantes de TipoDeAcesso.
 * Se o arquivo não existir ele será criado. Se o modo for ESCRITA e o arquivo já existir em disco,
 * todo o seu conteúdo será excluído.
 * Retorna true se o arquivo foi aberto com sucesso e false caso contrário.
 */
bool ArquivoTexto::abrir(string nomeArquivo, TipoDeAcesso modo) {
	this->nomeArquivo = nomeArquivo;

	// Abre o arquivo segundo o modo de abertura.
	switch (modo) {
	case ACRESCENTAR: outputFile.open(nomeArquivo, ios::app);
		if (outputFile.is_open()) return true;
		break;

	case ESCRITA: outputFile.open(nomeArquivo, ios::out);
		if (outputFile.is_open()) return true;
		break;

	case LEITURA: inputFile.open(nomeArquivo, ios::in);
		/* O teste abaixo verifica se foi retornado um ponteiro válido, diferente de nulo, se sim o teste é true indicando que o arquivo foi aberto com sucesso.
			 Caso contrário, um ponteiro nulo indica que houve erro ao tentar abrir o arquivo.
		 */
		if (inputFile) return true;
	}
	return false;
} // abrir()

/* Escreve no arquivo texto o conteúdo do objeto string armazenado no parâmetro conteudo.
 * A escrita do conteudo sempre ocorre no fim do arquivo.
 * Retorna true se a operação foi realizada com sucesso e false caso contrário.
 */
bool ArquivoTexto::escrever(string conteudo) {
	/* Escreve no arquivo se ele estiver aberto.
	 * Posiciona o ponteiro de posição de arquivo no fim e escreve o conteúdo.
	 */
	if (outputFile.is_open()) {
		outputFile.seekp(0, ios::end);
		outputFile << conteudo << endl;
		return true;
	}
	return false;
} // escrever()

/* Lê o conteúdo do arquivo texto.
 * Retorna um objeto string com todo o conteúdo do arquivo texto.
 * Em caso de erro retorna um objeto string com o valor literal "NULL".
 */
string ArquivoTexto::ler() {
	char linha[TAMANHO_LINHA];

	// Verifica se ocorreu erro ao acessar o arquivo.
	if (!inputFile) return "NULL";

	// Lê o conteúdo do arquivo até atingir o fim do arquivo.
	do { // Lê o conteúdo de uma linha limitada a TAMANHO_LINHA caracteres ou até encontrar o caractere nova linha ('\n'). 
		inputFile.getline(linha, TAMANHO_LINHA);

		texto.append(linha);
		texto.append("\n");

	} while (!inputFile.eof()); //Verifica se chegou ao fim do arquivo.
	return texto;
} // ler()

/* Lê o conteúdo de uma linha de texto do arquivo identificada por numeroLinha.
 * A primeira linha de texto é de número zero (0).
 * Retorna um objeto string com o conteúdo da linha de texto.
 * Em caso de erro retorna um objeto string com o valor literal "NULL".
 *
 * ATENÇÃO: Este método só irá recuperar a linha de texto correta do arquivo se todas
 *          as linhas de texto possuírem o mesmo tamanho (comprimento), em bytes.
 */
string ArquivoTexto::lerLinha(int numeroLinha) {
	char linha[TAMANHO_LINHA];

	// Verifica se ocorreu erro ao acessar o arquivo.
	if (!inputFile) return "NULL";

	// Lê o conteúdo do arquivo até atingir o fim do arquivo.
	if (numeroLinha >= 0) {
		inputFile.seekg(numeroLinha);
		inputFile.getline(linha, TAMANHO_LINHA);
	}
	return linha;
} // lerLinha()

// Fecha o arquivo texto.
void ArquivoTexto::fechar() {
	// Fecha o arquivo se estiver aberto.
	if (inputFile.is_open()) inputFile.close();
	if (outputFile.is_open()) outputFile.close();
	texto.clear();
}

// Obtém o nome do arquivo texto.
string ArquivoTexto::getNomeArquivo() {
	return nomeArquivo;
}