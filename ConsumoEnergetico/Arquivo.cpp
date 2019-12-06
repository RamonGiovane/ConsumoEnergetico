#include <iostream>
#include "Arquivo.h"

/* Abre o arquivo com o nome especificado em nomeArquivo para escrita e leitura de dados.
* Se o arquivo n�o existir ele ser� criado.
* Retorna true se o arquivo foi aberto ou se j� estava aberto com sucesso e false caso contr�rio.
*/
template<class T>
bool Arquivo<T>::abrir(string nomeArquivo) {

	if (this->nomeArquivo == nomeArquivo && arquivoBinario.is_open())
		return arquivoBinario ? true : false;

	this->nomeArquivo = nomeArquivo;

	// Abre o arquivo bin�rio para escrita (acrescenta toda sa�da no fim do arquivo) e leitura de dados.
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
	// Obt�m a posi��o inicial do arquivo.
	arquivoBinario.seekp(0, ios::beg);
}

// Obt�m a refer�ncia do arquivoBinario.
template<class T>
fstream& Arquivo<T>::getArquivo() {
	return arquivoBinario;
}

// Obt�m o nome do arquivo.
template<class T>
string Arquivo<T>::getNomeArquivo() {
	return nomeArquivo;
}

// Obt�m o tamanho do arquivo em bytes.
template<class T>
unsigned long Arquivo<T>::tamanhoArquivo() {
	
	reposicionarArquivo();

	unsigned long inicio = static_cast<unsigned long>(arquivoBinario.tellp());

	// Obt�m a posi��o final do arquivo.
	arquivoBinario.seekp(0, ios::end);
	unsigned long fim = static_cast<unsigned long>(arquivoBinario.tellp());

	// Calcula o tamanho do arquivo.
	return fim - inicio;
}
