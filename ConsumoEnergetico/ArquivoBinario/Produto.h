#ifndef PRODUTO_H
#define PRODUTO_H

#include <string> 

using namespace std; 

#define TAMANHO_STRING 20

class Produto { 
public:
	Produto(); 
	Produto(string nome, int quantidade, float preco); 

	void setNome(string nome);
	string getNome();

	void setQuantidade(int quantidade);
	int getQuantidade();

	void setPreco(float preco);
	float getPreco();

	// Exibe os dados do produto no console.
	void imprimir();
	
private:
	string nome;
	int quantidade; 
	float preco;
}; 
#endif
