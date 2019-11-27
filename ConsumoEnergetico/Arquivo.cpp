#include <iostream>
#include "Arquivo.h"

/* Abre o arquivo com o nome especificado em nomeArquivo para escrita e leitura de dados.
* Se o arquivo n�o existir ele ser� criado.
* Retorna true se o arquivo foi aberto com sucesso e false caso contr�rio.
*/
bool Arquivo::abrir(string nomeArquivo) {
	this->nomeArquivo = nomeArquivo;

	// Abre o arquivo bin�rio para escrita (acrescenta toda sa�da no fim do arquivo) e leitura de dados.
	Arquivo.open(nomeArquivo, ios::app | ios::in | ios::binary);

	if (Arquivo) return true;
	return false;
}

// Fecha o arquivo.
void Arquivo::fechar() {
	if (Arquivo.is_open()) Arquivo.close();
}

// Obt�m a refer�ncia do Arquivo.
fstream& Arquivo::getArquivo() {
	return Arquivo;
}

// Obt�m o nome do arquivo.
string Arquivo::getNomeArquivoBinario() {
	return nomeArquivo;
}

// Obt�m o tamanho do arquivo em bytes.
unsigned long Arquivo::tamanhoArquivo() {
	// Obt�m a posi��o inicial do arquivo.
	Arquivo.seekp(0, ios::beg);
	unsigned long inicio = static_cast<unsigned long>(Arquivo.tellp());

	// Obt�m a posi��o final do arquivo.
	Arquivo.seekp(0, ios::end);
	unsigned long fim = static_cast<unsigned long>(Arquivo.tellp());

	// Calcula o tamanho do arquivo.
	return fim - inicio;
}
