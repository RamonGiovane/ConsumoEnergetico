#include <clocale>
#include "TestarArquivoBinario.h"

//int main() {
//	return testarArquivoBinario();
//}

// Testa o funcionamento dos m�todos da classe ArquivoBinario.
int testarArquivoBinario() {
	setlocale(LC_ALL, "pt-BR");

	// Cria o objeto ArquivoProduto e abre o arquivo Produto.dat armazenado em disco.
	ArquivoProduto arquivoProduto;
	arquivoProduto.abrir("Produto.dat");

	// Grava 6 produtos no arquivo.
	gravar(arquivoProduto);		

	// Exibe todos os registros do arquivo Produto.dat.
	relatorio(arquivoProduto);	
	promptUniversal();	
	limpaTela();

	// Pesquisa por um produto no arquivo Produto.dat.
	consultar(arquivoProduto);  

	// Exibe todos os registros do arquivo Produto.dat.
	relatorio(arquivoProduto);	
	promptUniversal();	
	limpaTela();

	// Exclui um registro do arquivo Produto.dat.
	excluir(arquivoProduto);	 
	relatorio(arquivoProduto);

	// Exclui todos os registros do arquivo Produto.dat.
	excluirRegistros(arquivoProduto);

	// Fecha o arquivo Produto.dat.
	arquivoProduto.fechar();

	cout << endl << endl;
	return 0;
} // testarArquivoBinario()

// Grava o objeto Produto no arquivo Produto.dat.
void gravar(ArquivoProduto &arquivoProduto) {
	Produto produtos[] = { Produto("Arroz", 10, 13.5F), Produto("Feij�o", 20, 8.5F),
						   Produto("Sabonete", 30, 1.5F), Produto("Carne", 40, 18.5F),
						   Produto("Perfume", 2, 85.90F), Produto("Creme Dental", 5, 1.85F) };
	
	cout << " ----- Grava��o -----\n\n Gravando os objetos abaixo no arquivo Produto.dat...\n\n";

	// Gravando os objetos do vetor de objetos produtos no arquivo.
	for (int prod = 0; prod < _countof(produtos); prod++) {
		cout << " " << prod + 1 << ". ";
		produtos[prod].imprimir();
		arquivoProduto.escreverObjeto(produtos[prod]);
	}
} 

// Exibe todos os registros do arquivo Produto.dat.
void relatorio(ArquivoProduto &arquivoProduto) {
	Produto *produto;

	cout << "\n\n ----- Relat�rio -----\n\n Exibindo os objetos lidos do arquivo Produto.dat...\n\n";

	// Obt�m o n�mero de registros do arquivo.
	int registros = arquivoProduto.numeroRegistros();

	// L� todos os registros do arquivo e exibe no v�deo.
	for (int reg = 0; reg < registros; reg++) {
		produto = arquivoProduto.lerObjeto(reg);
		cout << " " << reg + 1 << ". ";
		produto->imprimir();
	}
} 

// Pesquisa por um produto no arquivo Produto.dat.
void consultar(ArquivoProduto &arquivoProduto) {
	int registro;

	cout << " ----- Consulta -----\n\n Consultando o produto Creme Dental no arquivo Produto.dat...\n\n";

	// Pesquisa por um produto no arquivo.
	Produto *produto = pesquisar(arquivoProduto, "Creme Dental", registro);

	// Se o produto foi encontrado exibe os dados no v�deo.
	if (produto)
		produto->imprimir();
	else
		cout << " -=> O produto Creme Dental n�o est� cadastrado no arquivo Produto.dat.";
}

// Exclui um registro do arquivo Produto.dat.
void excluir(ArquivoProduto &arquivoProduto) {
	int registro;
	char op;

	cout << " ----- Exclus�o -----\n\n Excluindo o produto Feij�o do arquivo Produto.dat...\n\n";

	// Pesquisa por um produto no arquivo.
	Produto *produto = pesquisar(arquivoProduto, "Feij�o", registro);

	// Se o produto foi encontrado exibe os dados no v�deo e solicita a confirma��o da exclus�o.
	if (produto) {
		produto->imprimir();

		do { cout << "\n Confirma exclus�o, Sim ou N�o? "; op = toupper(_getche());
		} while (op != 'S' && op != 'N');

		// Exclui o registro se a opera��o foi exclu�da.
		if (op == 'S') {
			arquivoProduto.excluirRegistro(registro);
			cout << "\n\n -=> Registro exclu�do com sucesso.\n";
		}
		else cout << "\n\n -=> Opera��o cancelada.\n";
	}
	else
		cout << " -=> O produto Feij�o n�o est� cadastrado no arquivo Produto.dat.";
} // excluir()

/* Pesquisa por um produto no arquivo Produto.dat.
 * Em caso de sucesso armazena o n�mero do registro no 3� par�metro e retorna o objeto Produto,
 * caso contr�rio, retorna NULL e numeroRegistro recebe -1.
*/
Produto* pesquisar(ArquivoProduto &arquivoProduto, string nome, int& numeroRegistro) {
	// Pesquisa por um produto no arquivo.
	numeroRegistro = arquivoProduto.pesquisarProduto(nome);

	// Se o produto foi encontrado obt�m os dados do arquivo.
	if (numeroRegistro != -1)
		return arquivoProduto.lerObjeto(numeroRegistro);
	else 
		return NULL;
} 

// Exclui todos os registros do arquivo Produto.dat.
void excluirRegistros(ArquivoProduto &arquivoProduto) {
	cout << "\n\n Excluindo todos os registros do arquivo Produto.dat...\n\n";

	for (int registro = arquivoProduto.numeroRegistros() - 1; registro >= 0; registro--) {
		cout << "Excluindo o registro " << registro + 1 << "...\n";
		arquivoProduto.excluirRegistro(registro);
	}
}