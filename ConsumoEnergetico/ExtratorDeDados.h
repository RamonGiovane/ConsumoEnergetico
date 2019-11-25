#ifndef EXTRATOR_DE_DADOS_H
#define EXTRATOR_DE_DADOS_H
#include <string>
#include <vector>
#include "Cliente.h"
#include "ValoresFaturados.h"
#include "Fatura.h"

const string CAMINHO_SAIDA = string("xpdf\\saida.tmp");

class ExtratorDeDados
{



public:

	ExtratorDeDados();

	ExtratorDeDados(const string & caminhoPrograma);

	void setCaminhoDoPrograma(const string & caminhoPrograma);

	string getCaminhoDoPrograma();

	bool importarFaturaPDF(const string & caminhoArquivo);

	//new
	bool extrairCEPCidade(Cliente & cliente, const string & linha);

	//new
	bool extrairEndereco(Cliente & cliente, const vector<string>& linhas, int & posicao);

	//new
	bool extrairDadosCliente(string & numeroDaInstalacao, const vector<string>& linhas);
	
	//new
	bool erro(const string & mensagemErro);

	//new 
	bool obterPrecoEConsumo(ValoresFaturados & valores, const vector<string>& linhas, int & posicao);

	//new
	bool obterValoresFaturados(const vector<string>& linhas, int & posicao);

	//new 
	bool salvarFatura();

	void popularConsumo(const vector<string>& itensLinha, const string & numeroInstalacao, const string & mesAno);

	bool extrairHistoricoConsumo(const vector<string>& linhas, int & posicao, const string & numeroInstalacao);

	//new
	bool importarFatura(vector<string>& linhas);

	bool lerFaturaPDF(Fatura & fatura, const string & caminhoPrograma, const string & caminhoArquivo);

	bool lerArquivoDeConsumo(Consumo & consumo, const string & numeroCliente, const string & caminhoArquivoEntrada);

	double calcularConsumo(const vector<string>& linhasArquivo, int mes, int ano);

	string getMensagemErro();

private:
	
	string caminhoPrograma;

	bool interpretarSaidaConversor(int codigoSaida);

	bool lerArquivoTexto(string & conteudoArquivo);

	bool obterInformacoes(vector<string>& linhasArquivo);

	bool lerTextoModo1(vector<string>& linhasArquivo, Fatura & fatura, Cliente & cliente, ValoresFaturados & valores);

	bool lerTextoModo2(vector<string>& linhasArquivo, Fatura & fatura, Cliente & cliente, ValoresFaturados & valores);

	//new
	bool obterMesAnoReferente(const vector<string>& linhasArquivo, int & posicaoAtual);

	bool obterDatasDeLeitura(const vector<string>& linhasArquivo, int & posicaoAtual);

	int procurarAnoReferente(const vector<string>& linhasArquivo, int posicaoAtual);

	bool formatarEAdicionarDatasDeLeitura(const string & dataLeituraAnterior, const string & dataLeituraAtual, const string & proximaDataLeitura, int anoFatura = 0);

	int obterMesData(const string & data);

	bool obterNumeroClienteEInstalacao(vector<string>& linhasArquivo, Cliente & cliente, int & posicaoAtual);

	bool obterMesVencimentoEValor(vector<string>& linhasArquivo, int & posicaoAtual);

	bool obterCliente(vector<string>& linhasArquivo, Cliente & cliente, int & posicaoAtual, const string & termoReferencia);

	bool obterValoresFaturados(vector<string>& linhasArquivo, ValoresFaturados & fatura, int & posicaoAtual);

	bool obterHistoricoConsumo(vector<string>& linhasArquivo, int & posicaoAtual, const string & termoReferencia);

	bool obterHistoricoConsumo(const string & linha);

	double extrairValoresFaturados(vector<string>& linhasArquivo, int & posicaoAtual);

	int calcularConsumo(const vector<string>& linhasArquivo, Consumo & consumo, int mes, int ano);

	double obterConsumoKWh(const string & linhaDoConsumo);

	bool lerValidarCabecalhoArquivoDeConsumo(const string & linhaCabecalho, int & mes, int & ano);


	Fatura fatura;

	string mensagemErro;

};




#endif // !EXTRATOR_DE_DADOS_H

