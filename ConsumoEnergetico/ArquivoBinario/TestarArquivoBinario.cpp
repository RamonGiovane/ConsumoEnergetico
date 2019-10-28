#include <clocale>
#include "TestarArquivoBinario.h"

//int main() {
//	return testarArquivoBinario();
//}

// Testa o funcionamento dos métodos da classe ArquivoBinario.
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
	Produto produtos[] = { Produto("Arroz", 10, 13.5F), Produto("Feijão", 20, 8.5F),
						   Produto("Sabonete", 30, 1.5F), Produto("Carne", 40, 18.5F),
						   Produto("Perfume", 2, 85.90F), Produto("Creme Dental", 5, 1.85F) };
	
	cout << " ----- Gravação -----\n\n Gravando os objetos abaixo no arquivo Produto.dat...\n\n";

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

	cout << "\n\n ----- Relatório -----\n\n Exibindo os objetos lidos do arquivo Produto.dat...\n\n";

	// Obtém o número de registros do arquivo.
	int registros = arquivoProduto.numeroRegistros();

	// Lê todos os registros do arquivo e exibe no vídeo.
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

	// Se o produto foi encontrado exibe os dados no vídeo.
	if (produto)
		produto->imprimir();
	else
		cout << " -=> O produto Creme Dental não está cadastrado no arquivo Produto.dat.";
}

// Exclui um registro do arquivo Produto.dat.
void excluir(ArquivoProduto &arquivoProduto) {
	int registro;
	char op;

	cout << " ----- Exclusão -----\n\n Excluindo o produto Feijão do arquivo Produto.dat...\n\n";

	// Pesquisa por um produto no arquivo.
	Produto *produto = pesquisar(arquivoProduto, "Feijão", registro);

	// Se o produto foi encontrado exibe os dados no vídeo e solicita a confirmação da exclusão.
	if (produto) {
		produto->imprimir();

		do { cout << "\n Confirma exclusão, Sim ou Não? "; op = toupper(_getche());
		} while (op != 'S' && op != 'N');

		// Exclui o registro se a operação foi excluída.
		if (op == 'S') {
			arquivoProduto.excluirRegistro(registro);
			cout << "\n\n -=> Registro excluído com sucesso.\n";
		}
		else cout << "\n\n -=> Operação cancelada.\n";
	}
	else
		cout << " -=> O produto Feijão não está cadastrado no arquivo Produto.dat.";
} // excluir()

/* Pesquisa por um produto no arquivo Produto.dat.
 * Em caso de sucesso armazena o número do registro no 3º parâmetro e retorna o objeto Produto,
 * caso contrário, retorna NULL e numeroRegistro recebe -1.
*/
Produto* pesquisar(ArquivoProduto &arquivoProduto, string nome, int& numeroRegistro) {
	// Pesquisa por um produto no arquivo.
	numeroRegistro = arquivoProduto.pesquisarProduto(nome);

	// Se o produto foi encontrado obtém os dados do arquivo.
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