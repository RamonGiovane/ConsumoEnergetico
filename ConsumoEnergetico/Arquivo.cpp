#include <iostream>
#include "Arquivo.h"

/* Abre o arquivo com o nome especificado em nomeArquivo para escrita e leitura de dados.
* Se o arquivo não existir ele será criado.
* Retorna true se o arquivo foi aberto com sucesso e false caso contrário.
*/
bool Arquivo::abrir(string nomeArquivo) {
	this->nomeArquivo = nomeArquivo;

	// Abre o arquivo binário para escrita (acrescenta toda saída no fim do arquivo) e leitura de dados.
	Arquivo.open(nomeArquivo, ios::app | ios::in | ios::binary);

	if (Arquivo) return true;
	return false;
}

// Fecha o arquivo.
void Arquivo::fechar() {
	if (Arquivo.is_open()) Arquivo.close();
}

// Obtém a referência do Arquivo.
fstream& Arquivo::getArquivo() {
	return Arquivo;
}

// Obtém o nome do arquivo.
string Arquivo::getNomeArquivoBinario() {
	return nomeArquivo;
}

// Obtém o tamanho do arquivo em bytes.
unsigned long Arquivo::tamanhoArquivo() {
	// Obtém a posição inicial do arquivo.
	Arquivo.seekp(0, ios::beg);
	unsigned long inicio = static_cast<unsigned long>(Arquivo.tellp());

	// Obtém a posição final do arquivo.
	Arquivo.seekp(0, ios::end);
	unsigned long fim = static_cast<unsigned long>(Arquivo.tellp());

	// Calcula o tamanho do arquivo.
	return fim - inicio;
}
