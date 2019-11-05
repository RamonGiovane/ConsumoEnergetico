#ifndef CONTA_DIGITAL_H
#define CONTA_DIGITAL_H
#include <string>

#include "Cliente.h"
#include "Consumo.h"
#include "ValoresFaturados.h"

#define CAPACIDADE_HISTORICO_CONSUMO 13

using namespace std;
class ContaDigital
{
public:
	
	ContaDigital();

	string getNumeroInstalacao();
	void setNumeroInstalacao(string numeroInstalacao);
	string getDataVencimento();
	double getValorAPagar();
	void setValorAPagar(double valor);
	void setDataVencimento(string data);
	string getMesReferente();
	void setMesReferente(string mesReferente);
	Cliente getCliente();
	void setCliente(Cliente cliente);
	ValoresFaturados getValoresFaturados();
	void setValoresFaturados(ValoresFaturados valoresFaturados);
	
	bool adicionarHistoricoConsumo(Consumo consumo);

	string obterHistoricoConsumo();

	Consumo obterConsumoDoMes();

	string toString();

private:
	Consumo historicoConsumo[CAPACIDADE_HISTORICO_CONSUMO];
	string numeroInstalacao;
	string dataVencimento;
	double valorAPagar;
	string mesReferente;
	Cliente cliente;
	ValoresFaturados valoresFaturados;
	

};


#endif // !CONTA_DIGITAL_H


