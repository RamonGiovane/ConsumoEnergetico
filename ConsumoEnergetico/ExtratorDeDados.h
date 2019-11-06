#ifndef EXTRATOR_DE_DADOS_H
#define EXTRATOR_DE_DADOS_H
#include <string>
#include <vector>
#include "Cliente.h"
#include "ValoresFaturados.h"
#include "Fatura.h"
const string ARQUIVO_SAIDA = string("saida.txt");
const string CAMINHO_SAIDA = string("xpdf\\saida.txt");

class ExtratorDeDados
{



public:

	ExtratorDeDados();

	Fatura lerFaturaPDF(const string & caminho);

private:
	bool interpretarSaidaConversor(int codigoSaida);

	bool lerArquivoTexto(string & conteudoArquivo);

	bool obterInformacoes(vector<string>& linhasArquivo);

	bool obterDemaisInformacoes(vector<string>& linhasArquivo, Cliente & cliente, int & posicaoAtual);

	bool obterCliente(vector<string>& linhasArquivo, Cliente & cliente, int & posicaoAtual);

	bool obterValoresFaturados(vector<string>& linhasArquivo, ValoresFaturados & fatura, int & posicaoAtual);

	bool obterHistoricoConsumo(vector<string>& linhasArquivo, int & posicaoAtual);

	bool obterHistoricoConsumo(const string & linha);



	int procurarNumeroLinha(const vector<string>& linhasArquivo, const string & termoPesquisado, int posicaoInicial);

	int procurarNumeroLinha(const vector<string>& linhasArquivo, int posicaoAtual,  string padraoRegex);


	string procurarItem(const vector<string>& linhasArquivo, const string & termoPesquisado,
		int & posicaoAtual, const string & termoFinal = "");

	vector<string>& procurarLinha(const vector<string> & linhasArquivo, const string & termoPesquisado,
		int & posicaoAtual, const string & termoFinal = "");

	double extrairValoresFaturados(vector<string>& linhasArquivo, int & posicaoAtual);


	Fatura fatura;

	string mensagemErro;

};




#endif // !EXTRATOR_DE_DADOS_H

