#ifndef ARQUIVO_FATURA_H
#define ARQUIVO_FATURA_H
#include <string>
#include "Fatura.h"
#include "Constantes.h"
#include "ArquivoBinario.h"


using namespace std;
struct RegistroFatura {
	char numeroCliente[TAMANHO_CODIGOS];
	char numeroInstalacao[TAMANHO_CODIGOS];
	char dataVencimento[TAMANHO_CODIGOS];
	char dataDeLeitura[TAMANHO_CODIGOS], dataDeLeituraAnterior[TAMANHO_CODIGOS], proximaDataDeLeitura[TAMANHO_CODIGOS];
	
	int mesReferente, anoReferente;
	double valorAPagar;
	
	int consumoKWh;
	double valorDaFatura;
	double precoEnergia;
	double precoIluminacaoPublica;
	double bandeiraAmarela, bandeiraVermelha;
};


class ArquivoFatura : public ArquivoBinario
{


public:
	// Cria um objeto para manipular o arquivo bin�rio com acesso aleat�rio.
	inline ArquivoFatura() : ArquivoBinario() {};

	/* Cria um objeto para manipular o arquivo bin�rio com acesso aleat�rio cujo nome de arquivo est�
	* especificado em nomeArquivo. Em seguida, abre o arquivo para leitura e escrita.
	*/
	inline ArquivoFatura(string nomeArquivo) : ArquivoBinario(nomeArquivo) {};


	// Obt�m o tamanho do registro em bytes.
	unsigned int tamanhoRegistro();

	void objetoParaRegistro(Fatura & fatura, RegistroFatura & registro);

	// Escreve o objeto Fatura como um registro do arquivo.
	bool escreverObjeto(Fatura fatura);
	

	/* L� os dados de um registro do arquivo e armazena-os no objeto Fatura.
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

	bool posicionarNoInicio();

	bool posicionarNoFinal();

	bool salvarCliente(const Cliente & cliente);
	
	bool salvarHistoricoConsumo(Fatura & fatura);

	Fatura registroParaFatura(Fatura & fatura, const RegistroFatura & registro, bool consultaDetalhada = true);

	RegistroFatura * lerRegistro(unsigned int numeroRegistro);
};

#endif // !ARQUIVO_FATURA_H


