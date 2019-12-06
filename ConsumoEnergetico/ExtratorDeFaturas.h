#ifndef EXTRATOR_DE_FATURAS_H
#define EXTRATOR_DE_FATURAS_H
#include <string>
#include <vector>
#include "Cliente.h"
#include "ValoresFaturados.h"
#include "ArquivoFatura.h"
#include "Fatura.h"
#include "RelatorDeErros.h"


class ExtratorDeFaturas : public RelatorDeErros
{

public:

	ExtratorDeFaturas();

	ExtratorDeFaturas(const string & caminhoPrograma);

	~ExtratorDeFaturas();

	void setCaminhoDoPrograma(const string & caminhoPrograma);

	string getCaminhoDoPrograma();

	bool importarFaturaPDF(const string & caminhoArquivo);

	bool salvarCopiaArquivoTexto(const string & caminhoArquivo);

	bool importarFaturaTXT(const string & caminhoArquivo);

private:

	bool extrairCEPCidade(Cliente & cliente, const string & linha);

	bool extrairNomeEEndereco(Cliente & cliente, const vector<string>& linhas, int & posicao);

	
	bool extrairDadosCliente(const vector<string>& linhas);
	 
	bool obterPrecoEConsumo(ValoresFaturados & valores, const vector<string>& linhas, int & posicao);

	
	bool extrairValoresFaturados(const vector<string>& linhas, int & posicao);

	 
	bool salvarFatura();

	void popularConsumo(const vector<string>& itensLinha, const string & numeroInstalacao, int mes, int ano);

	bool extrairHistoricoConsumo(const vector<string>& linhas, int & posicao, const string & numeroInstalacao);

	
	bool importarFatura(vector<string>& linhas);

	
	bool extrairMesAnoReferente(const vector<string>& linhasArquivo, int & posicaoAtual);

	bool extrairDatasDeLeitura(const vector<string>& linhasArquivo, int & posicaoAtual);

	int procurarAnoReferente(const vector<string>& linhasArquivo, int posicaoAtual);

	bool formatarEAdicionarDatasDeLeitura(const string & dataLeituraAnterior, const string & dataLeituraAtual, const string & proximaDataLeitura, int anoFatura = 0);

	int obterMesData(const string & data);

	bool obterNumeroClienteEInstalacao(const vector<string>& linhasArquivo, Cliente & cliente, int & posicaoAtual);

	bool extrairMesVencimentoEValor(vector<string>& linhasArquivo, int & posicaoAtual);
	
	Fatura fatura;

	ArquivoFatura arquivoFatura;

	string caminhoPrograma;


};


#endif // !EXTRATOR_DE_FATURAS_H