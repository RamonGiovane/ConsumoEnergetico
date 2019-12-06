#include <iostream>
#include "ArquivoBinario.h"

 /* Abre o arquivo com o nome especificado em nomeArquivo para escrita e leitura de dados.
  * Se o arquivo não existir ele será criado.
  * Retorna true se o arquivo foi aberto ou se já estava aberto com sucesso e false caso contrário.
  */
bool ArquivoBinario::abrir(string nomeArquivo) {
	
	if (this->nomeArquivo == nomeArquivo && arquivoBinario.is_open()) {
		reposicionarArquivo();
		return arquivoBinario ? true : false;
	}

	this->nomeArquivo = nomeArquivo;

	// Abre o arquivo binário para escrita (acrescenta toda saída no fim do arquivo) e leitura de dados.
	arquivoBinario.open(nomeArquivo, ios::app | ios::in | ios::binary);


	return arquivoBinario ? true : false;
}


// Obtém o número de registros do arquivo.
unsigned int ArquivoBinario::numeroRegistros() {
	return tamanhoArquivo() / tamanhoRegistro();
}

// Fecha o arquivo.
void ArquivoBinario::fechar() {
	if (arquivoBinario.is_open()) arquivoBinario.close();
}

// Obtém a referência do arquivoBinario.
fstream& ArquivoBinario::getArquivoBinario() {
	return arquivoBinario;
}

// Obtém o nome do arquivo.
string ArquivoBinario::getNomeArquivo() {
	return nomeArquivo;
}


void ArquivoBinario::reposicionarArquivo() {
	
	arquivoBinario.clear();
	// Obtém a posição inicial do arquivo.
	arquivoBinario.seekp(0, ios::beg);
}

// Obtém o tamanho do arquivo em bytes.
unsigned long ArquivoBinario::tamanhoArquivo() {

	reposicionarArquivo();

	unsigned long inicio = static_cast<unsigned long>(arquivoBinario.tellp());

	// Obtém a posição final do arquivo.
	arquivoBinario.seekp(0, ios::end);
	unsigned long fim = static_cast<unsigned long>(arquivoBinario.tellp());

	// Calcula o tamanho do arquivo.
	return fim - inicio;
}
