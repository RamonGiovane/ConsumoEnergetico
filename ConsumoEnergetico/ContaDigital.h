#ifndef CONTA_DIGITAL_H
#define CONTA_DIGITAL_H
#include <string>
#include "Cliente.h"
#include "FaturaEnergia.h"

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
	FaturaEnergia getDadosFatura();
	void setDadosFatura(FaturaEnergia dadosFatura);


private:
	string numeroInstalacao;
	string dataVencimento;
	double valorAPagar;
	string mesReferente;
	Cliente cliente;
	FaturaEnergia dadosFatura;

};


#endif // !CONTA_DIGITAL_H


