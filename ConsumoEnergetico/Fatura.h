#ifndef CONTA_DIGITAL_H
#define CONTA_DIGITAL_H
#include <string>


#include "Consumo.h"
#include "ValoresFaturados.h"
#include "Cliente.h"
#define CAPACIDADE_HISTORICO_CONSUMO 13

using namespace std;
class Fatura
{
public:
	
	Fatura();

	string getNumeroInstalacao();
	void setNumeroInstalacao(string numeroInstalacao);
	
	string getDataVencimento();
	double getValorAPagar();
	
	void setValorAPagar(double valor);
	void setDataVencimento(string data);
	
	int getMesReferente();
	void setMesReferente(int mesReferente);

	int getAnoReferente();
	void setAnoReferente(int anoReferente);
	
	Cliente getCliente();
	void setCliente(Cliente cliente);

	string getDataDeLeitura();
	void setDataDeLeitura(string dataDeLeitura);
	
	string getDataDeLeituraAnterior();
	void setDataDeLeituraAnterior(string dataDeLeitura);
	
	string getProximaDataDeLeitura();
	void setProximaDataDeLeitura(string dataDeLeitura);

	ValoresFaturados getValoresFaturados();
	void setValoresFaturados(ValoresFaturados valoresFaturados);
	
	bool adicionarHistoricoConsumo(Consumo consumo);

	string obterHistoricoConsumo();

	bool setMesAnoReferente(const string & mesAno);

	Consumo obterConsumoDoMes();

	string toString();

private:
	Consumo historicoConsumo[CAPACIDADE_HISTORICO_CONSUMO];
	string numeroInstalacao;
	string dataVencimento;
	double valorAPagar;
	int mesReferente, anoReferente;
	Cliente cliente;
	string dataDeLeitura, dataDeLeituraAnterior, proximaDataDeLeitura;
	ValoresFaturados valoresFaturados;
	

};


#endif // !CONTA_DIGITAL_H


