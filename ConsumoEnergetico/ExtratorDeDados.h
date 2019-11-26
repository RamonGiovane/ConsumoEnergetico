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

	string getMensagemErro();

private:

	inline bool ExtratorDeDados::erro(const string & mensagemErro) {
		this->mensagemErro = mensagemErro;
		return false;
	}

	//new
	bool extrairCEPCidade(Cliente & cliente, const string & linha);

	//new
	bool extrairNomeEEndereco(Cliente & cliente, const vector<string>& linhas, int & posicao);

	//new
	bool extrairDadosCliente(const vector<string>& linhas);


	//new 
	bool obterPrecoEConsumo(ValoresFaturados & valores, const vector<string>& linhas, int & posicao);

	//new
	bool obterValoresFaturados(const vector<string>& linhas, int & posicao);

	//new 
	bool salvarFatura();

	void popularConsumo(const vector<string>& itensLinha, const string & numeroInstalacao, int mes, int ano);

	bool extrairHistoricoConsumo(const vector<string>& linhas, int & posicao, const string & numeroInstalacao);

	//new
	bool importarFatura(vector<string>& linhas);

	bool lerArquivoDeConsumo(Consumo & consumo, const string & numeroCliente, const string & caminhoArquivoEntrada);

	bool lerArquivoTexto(string & conteudoArquivo);

	//new
	bool obterMesAnoReferente(const vector<string>& linhasArquivo, int & posicaoAtual);

	bool obterDatasDeLeitura(const vector<string>& linhasArquivo, int & posicaoAtual);

	int procurarAnoReferente(const vector<string>& linhasArquivo, int posicaoAtual);

	bool formatarEAdicionarDatasDeLeitura(const string & dataLeituraAnterior, const string & dataLeituraAtual, const string & proximaDataLeitura, int anoFatura = 0);

	int obterMesData(const string & data);

	bool obterNumeroClienteEInstalacao(const vector<string>& linhasArquivo, Cliente & cliente, int & posicaoAtual);

	bool obterMesVencimentoEValor(vector<string>& linhasArquivo, int & posicaoAtual);

	bool obterHistoricoConsumo(const string & linha);

	bool lerValidarCabecalhoArquivoDeConsumo(const string & linhaCabecalho, int & mes, int & ano);


	Fatura fatura;

	string mensagemErro;

	string caminhoPrograma;

};


#endif // !EXTRATOR_DE_DADOS_H