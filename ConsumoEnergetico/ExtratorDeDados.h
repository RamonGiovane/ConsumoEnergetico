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

	bool lerFaturaPDF(Fatura & fatura, const string & caminhoPrograma, const string & caminhoArquivo);

	string getMensagemErro();

private:
	
	string caminhoPrograma;

	bool interpretarSaidaConversor(int codigoSaida);

	bool lerArquivoTexto(string & conteudoArquivo);

	bool obterInformacoes(vector<string>& linhasArquivo);

	bool obterDatasDeLeitura(vector<string>& linhasArquivo, int & posicaoAtual);

	bool formatarEAdicionarDatasDeLeitura(const string & dataLeituraAnterior, const string & dataLeituraAtual, const string & proximaDataLeitura);

	int obterMesData(const string & data);

	bool obterNumeroClienteEInstalacao(vector<string>& linhasArquivo, Cliente & cliente, int & posicaoAtual);

	bool obterMesVencimentoEValor(vector<string>& linhasArquivo, int & posicaoAtual);

	bool obterCliente(vector<string>& linhasArquivo, Cliente & cliente, int & posicaoAtual);

	bool obterValoresFaturados(vector<string>& linhasArquivo, ValoresFaturados & fatura, int & posicaoAtual);

	bool obterHistoricoConsumo(vector<string>& linhasArquivo, int & posicaoAtual);

	bool obterHistoricoConsumo(const string & linha);

	double extrairValoresFaturados(vector<string>& linhasArquivo, int & posicaoAtual);


	Fatura fatura;

	string mensagemErro;

};




#endif // !EXTRATOR_DE_DADOS_H

