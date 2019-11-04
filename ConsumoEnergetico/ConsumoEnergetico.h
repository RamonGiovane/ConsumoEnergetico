#ifndef CONSUMO_ENERGETICO_H
#define CONSUMO_ENERGETICO_H
#include <string>
#include <vector>
#include "Fatura.h"
#include "Cliente.h"
#include "ContaDigital.h"
using namespace std;

class ConsumoEnergetico
{

public:
	
	ConsumoEnergetico();
	int iniciar();

private:
	const  static string ARQUIVO_SAIDA;
	const static string CAMINHO_SAIDA;
	int menu();
	bool lerContaDigital();
	bool lerArquivoTexto(string & conteudoArquivo);
	bool obterInformacoes(vector<string>& linhasArquivo, const string & conteudoArquivo);
	
	bool obterInformacoes(vector<string>& linhasArquivo);

	bool obterDemaisInformacoes(vector<string>& linhasArquivo, Cliente & cliente, int & posicaoAtual);

	bool obterCliente(vector<string>& linhasArquivo, Cliente & cliente, int & posicaoAtual);

	bool obterValoresFaturados(vector<string>& linhasArquivo, FaturaEnergia & fatura, int & posicaoAtual);
	
	bool obterHistoricoConsumo(vector<string>& linhasArquivo, int & posicaoAtual);

	bool obterHistoricoConsumo(const string & linha);

	

	int procurarNumeroLinha(const vector<string>& linhasArquivo, const string & termoPesquisado, int posicaoInicial);


	string procurarItem(const vector<string>& linhasArquivo, const string & termoPesquisado,
						int & posicaoAtual, const string & termoFinal = "");
	vector<string>& procurarLinha(const vector<string> & linhasArquivo, const string & termoPesquisado,
						int & posicaoAtual, const string & termoFinal = "");
	
	double extrairValoresFaturados(vector<string>& linhasArquivo, int & posicaoAtual);
	//bool extrairValoresFaturados(vector<string>& linhasArquivo, int posicaoAtual);
	bool interpretarSaidaConversor(int codigoSaida);

	

	//Fatura fatura;
	ContaDigital conta;
};


#endif // !CONSUMO__ENERGETICO_H

const string ConsumoEnergetico::ARQUIVO_SAIDA = string("saida.txt");
const string ConsumoEnergetico::CAMINHO_SAIDA = string("xpdf\\saida.txt");


