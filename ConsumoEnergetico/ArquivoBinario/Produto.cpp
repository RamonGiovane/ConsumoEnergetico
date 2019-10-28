#include <iostream>  
#include <iomanip>
#include "Produto.h"

Produto::Produto() {
	preco = 0;
	quantidade = 0;
}

Produto::Produto(string nome, int quantidade, float preco) {
	setNome(nome);
	setQuantidade(quantidade);
	setPreco(preco);
}

/* Configura o nome do produto com no máximo TAMANHO_STRING caracteres. Se o tamanho 
   do nome for superior a TAMANHO_STRING os caracteres excedentes serão descartados.
*/
void Produto::setNome(string nome) {
	// Verifica se nome possui no máximo TAMANHO_STRING caracteres.
	if (nome.length() <= TAMANHO_STRING)
		this->nome = nome;
	else 
		// Extrai TAMANHO_STRING caracteres da string nome a partir da posição zero.
		this->nome = nome.substr(0, TAMANHO_STRING);
}

string Produto::getNome() {
	return nome;
}

void Produto::setQuantidade(int quantidade) {
	this->quantidade = (quantidade >= 0 ? quantidade : 0);
}

int Produto::getQuantidade() {
	return quantidade;
}

void Produto::setPreco(float preco) {
	this->preco = (preco >= 0 ? preco : 0);
}

float Produto::getPreco() {
	return preco;
}

// Exibe os dados do produto no console.
void Produto::imprimir() {
	cout << " " << left << setw(20) << nome << setw(5) << quantidade
		 << right << fixed << showpoint << setw(5) << setprecision(2) << preco << endl;
}