#ifndef TESTAR_ARQUIVO_BINARIO
#define TESTAR_ARQUIVO_BINARIO

#include <iostream>
#include <conio.h>
#include "ArquivoProduto.h"

// Grava o objeto Produto no arquivo Produto.dat.
void gravar(ArquivoProduto &arquivoProduto);

// Exibe todos os registros do arquivo Produto.dat.
void relatorio(ArquivoProduto &arquivoProduto);

// Exclui um registro do arquivo Produto.dat.
void excluir(ArquivoProduto &arquivoProduto);

// Pesquisa por um produto no arquivo Produto.dat.
void consultar(ArquivoProduto &arquivoProduto);

// Exclui todos os registros do arquivo Produto.dat.
void excluirRegistros(ArquivoProduto &arquivoProduto);

/* Pesquisa por um produto no arquivo Produto.dat. 
   Em caso de sucesso armazena o n�mero do registro no 3� par�metro e retorna o objeto Produto,
   caso contr�rio, retorna NULL e numeroRegistro recebe -1.
 */
Produto* pesquisar(ArquivoProduto &arquivoProduto, string nome, int& numeroRegistro);

// Testa o funcionamento dos m�todos da classe ArquivoBinario.
int testarArquivoBinario();

inline void promptUniversal() {
	std::cout << "\n\n Pressione qualquer tecla para continuar...";
	_getch();
}

inline void limpaTela() {
	system("cls");
}
#endif