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


class ArquivoFatura
{


public:
	// Cria um objeto para manipular o arquivo bin�rio com acesso aleat�rio.
	ArquivoFatura();

	/* Cria um objeto para manipular o arquivo bin�rio com acesso aleat�rio cujo nome de arquivo est�
	* especificado em nomeArquivo. Em seguida, abre o arquivo para leitura e escrita.
	*/
	ArquivoFatura(string nomeArquivo);

	// Exclui o objeto arquivo bin�rio.
	~ArquivoFatura();

	/* Abre o arquivo com o nome especificado em nomeArquivo para escrita e leitura de dados.
	* Retorna true se o arquivo foi aberto com sucesso e false caso contr�rio.
	*/
	bool abrir(string nomeArquivo);

	// Fecha o arquivo.
	void fechar();

	// Obt�m o nome do arquivo.
	string getNomeArquivo();

	// Obt�m o tamanho do arquivo em bytes.
	unsigned long tamanhoArquivo();

	// Obt�m o n�mero de registros do arquivo.
	unsigned int numeroRegistros();

	// Obt�m o tamanho do registro em bytes.
	unsigned int tamanhoRegistro();

	void objetoParaRegistro(Fatura & fatura, RegistroFatura & registro);

	// Escreve o objeto Fatura como um registro do arquivo.
	bool escreverObjeto(Fatura fatura);
	

	/* L� os dados de um registro do arquivo e armazena-os no objeto Produto.
	* Retorna o objeto Produto. Em caso de erro retorna NULL.
	*/

	Fatura * lerObjeto(unsigned int numeroRegistro, bool consultaDetalhada = true);
	
	Fatura * obterFatura(int mesReferente, int anoReferente, const string & numeroInstalacao);
	
	Fatura * obterFatura(const string & numeroCliente, int mesReferente, int anoReferente);

	/* Pesquisa uma fatura no arquivo. Em caso de sucesso retorna o n�mero do registro
	* onde o fatura est� armazenado, caso contr�rio, retorna -1.
	*/
	int pesquisarFatura(string numeroCliente, int mesReferente = 0, int anoReferente = 0, int posicao = 0);
	int pesquisarFatura(int mesReferente, int anoReferente, string numeroCliente = "", string numeroInstalacao = "");


private:
	ArquivoBinario *arqBin;

	bool posicionarNoInicio();

	bool posicionarNoFinal();

	bool salvarCliente(const Cliente & cliente);
	
	bool salvarHistoricoConsumo(Fatura & fatura);

	Fatura registroParaFatura(Fatura & fatura, const RegistroFatura & registro, bool consultaDetalhada = true);

	RegistroFatura * lerRegistro(unsigned int numeroRegistro);
};

#endif // !ARQUIVO_FATURA_H


