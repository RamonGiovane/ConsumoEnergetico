#ifndef ARQUIVO_FATURA_H
#define ARQUIVO_FATURA_H
#include <string>
#include "Fatura.h"
#include "ArquivoBinario\ArquivoBinario.h"

#define TAMANHO_STRING 25
using namespace std;
struct RegistroFatura {
	char numeroCliente[TAMANHO_STRING];
	char numeroInstalacao[TAMANHO_STRING];
	char dataVencimento[TAMANHO_STRING];
	char dataDeLeitura[TAMANHO_STRING], dataDeLeituraAnterior[TAMANHO_STRING], proximaDataDeLeitura[TAMANHO_STRING];
	
	int mesReferente, anoReferente;
	double valorAPagar;
	
	int consumoKWh;
	double valorDaFatura;
	double precoEnergia;
	double precoIluminacaoPublica;
	double bandeiraAmarela, bandeiraVermelha;
};
//string numeroInstalacao;
//string dataVencimento;
//double valorAPagar;
//int mesReferente, anoReferente;
//Cliente cliente;
//string dataDeLeitura, dataDeLeituraAnterior, proximaDataDeLeitura;
//ValoresFaturados valoresFaturados;

class ArquivoFatura
{


public:
	// Cria um objeto para manipular o arquivo binário com acesso aleatório.
	ArquivoFatura();

	/* Cria um objeto para manipular o arquivo binário com acesso aleatório cujo nome de arquivo está
	* especificado em nomeArquivo. Em seguida, abre o arquivo para leitura e escrita.
	*/
	ArquivoFatura(string nomeArquivo);

	// Exclui o objeto arquivo binário.
	~ArquivoFatura();

	/* Abre o arquivo com o nome especificado em nomeArquivo para escrita e leitura de dados.
	* Retorna true se o arquivo foi aberto com sucesso e false caso contrário.
	*/
	bool abrir(string nomeArquivo);

	// Fecha o arquivo.
	void fechar();

	// Obtém o nome do arquivo.
	string getNomeArquivo();

	// Obtém o tamanho do arquivo em bytes.
	unsigned long tamanhoArquivo();

	// Obtém o número de registros do arquivo.
	unsigned int numeroRegistros();

	// Obtém o tamanho do registro em bytes.
	unsigned int tamanhoRegistro();

	void objetoParaRegistro(Fatura & fatura, RegistroFatura & registro);

	// Escreve o objeto Produto como um registro do arquivo.
	bool escreverObjeto(Fatura fatura);
	

	/* Lê os dados de um registro do arquivo e armazena-os no objeto Produto.
	* Retorna o objeto Produto. Em caso de erro retorna NULL.
	*/

	Fatura * lerObjeto(unsigned int numeroRegistro, bool consultaDetalhada = true);

	Fatura registroParaFatura(Fatura & fatura, const RegistroFatura & registro, bool consultaDetalhada = true);


	/* Exclui um registro do arquivo. O primeiro registro é o número zero (0).
	* Retorna true se o registro foi excluído com sucesso e false caso contrário.
	*/
	bool excluirRegistro(unsigned int numeroRegistro);


	/* Pesquisa uma fatura no arquivo. Em caso de sucesso retorna o número do registro
	* onde o fatura está armazenado, caso contrário, retorna -1.
	*/
	int pesquisarFatura(string numeroCliente, int mesReferente, int anoReferente);


private:
	ArquivoBinario *arqBin;

	bool salvarCliente(const Cliente & cliente);
	bool salvarHistoricoConsumo(Fatura & fatura);
};

#endif // !ARQUIVO_FATURA_H