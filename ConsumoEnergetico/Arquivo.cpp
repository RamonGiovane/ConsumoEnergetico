#include <iostream>
#include "Arquivo.h"

/* Abre o arquivo com o nome especificado em nomeArquivo para escrita e leitura de dados.
* Se o arquivo não existir ele será criado.
* Retorna true se o arquivo foi aberto ou se já estava aberto com sucesso e false caso contrário.
*/
template<class T>
bool Arquivo<T>::abrir(string nomeArquivo) {

	if (this->nomeArquivo == nomeArquivo && arquivoBinario.is_open())
		return arquivoBinario ? true : false;

	this->nomeArquivo = nomeArquivo;

	// Abre o arquivo binário para escrita (acrescenta toda saída no fim do arquivo) e leitura de dados.
	arquivoBinario.open(nomeArquivo, ios::app | ios::in | ios::binary);

	//if (arquivoBinario) return true;
	//return false;

	return arquivoBinario ? true : false;
}

// Fecha o arquivo.
template<class T>
void Arquivo<T>::fechar() {
	if (arquivoBinario.is_open()) arquivoBinario.close();
}

template<class T>
void Arquivo<T>::reposicionarArquivo() {

	arquivoBinario.clear();
	// Obtém a posição inicial do arquivo.
	arquivoBinario.seekp(0, ios::beg);
}

// Obtém a referência do arquivoBinario.
template<class T>
fstream& Arquivo<T>::getArquivo() {
	return arquivoBinario;
}

// Obtém o nome do arquivo.
template<class T>
string Arquivo<T>::getNomeArquivo() {
	return nomeArquivo;
}

// Obtém o tamanho do arquivo em bytes.
template<class T>
unsigned long Arquivo<T>::tamanhoArquivo() {
	
	reposicionarArquivo();

	unsigned long inicio = static_cast<unsigned long>(arquivoBinario.tellp());

	// Obtém a posição final do arquivo.
	arquivoBinario.seekp(0, ios::end);
	unsigned long fim = static_cast<unsigned long>(arquivoBinario.tellp());

	// Calcula o tamanho do arquivo.
	return fim - inicio;
}
