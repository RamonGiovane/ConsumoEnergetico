#ifndef EXTRATOR_DE_FATURAS_H
#define EXTRATOR_DE_FATURAS_H
#include <string>
#include <vector>
#include "Cliente.h"
#include "ValoresFaturados.h"
#include "Fatura.h"
#include "RelatorDeErros.h"


class ExtratorDeFaturas : public RelatorDeErros
{

public:

	ExtratorDeFaturas();

	ExtratorDeFaturas(const string & caminhoPrograma);

	void setCaminhoDoPrograma(const string & caminhoPrograma);

	string getCaminhoDoPrograma();

	bool salvarCopiaArquivoTexto(const string & caminhoArquivo, const string & caminhoPrograma);

	bool importarFaturaPDF(const string & caminhoArquivo);

	bool importarFaturaTXT(const string & caminhoArquivo);

private:

	//new
	bool extrairCEPCidade(Cliente & cliente, const string & linha);

	//new
	bool extrairNomeEEndereco(Cliente & cliente, const vector<string>& linhas, int & posicao);

	//new
	bool extrairDadosCliente(const vector<string>& linhas);


	//new 
	bool obterPrecoEConsumo(ValoresFaturados & valores, const vector<string>& linhas, int & posicao);

	//new
	bool extrairValoresFaturados(const vector<string>& linhas, int & posicao);

	//new 
	bool salvarFatura();

	void popularConsumo(const vector<string>& itensLinha, const string & numeroInstalacao, int mes, int ano);

	bool extrairHistoricoConsumo(const vector<string>& linhas, int & posicao, const string & numeroInstalacao);

	//new
	bool importarFatura(vector<string>& linhas);

	//new
	bool extrairMesAnoReferente(const vector<string>& linhasArquivo, int & posicaoAtual);

	bool extrairDatasDeLeitura(const vector<string>& linhasArquivo, int & posicaoAtual);

	int procurarAnoReferente(const vector<string>& linhasArquivo, int posicaoAtual);

	bool formatarEAdicionarDatasDeLeitura(const string & dataLeituraAnterior, const string & dataLeituraAtual, const string & proximaDataLeitura, int anoFatura = 0);

	int obterMesData(const string & data);

	bool obterNumeroClienteEInstalacao(const vector<string>& linhasArquivo, Cliente & cliente, int & posicaoAtual);

	bool extrairMesVencimentoEValor(vector<string>& linhasArquivo, int & posicaoAtual);

	bool obterHistoricoConsumo(const string & linha);



	Fatura fatura;

	string caminhoPrograma;

};


#endif // !EXTRATOR_DE_FATURAS_H