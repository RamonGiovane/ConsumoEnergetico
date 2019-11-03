#ifndef FATURA_H
#define FATURA_H
#include "Bandeira.h"
#include "FaturaEnergia.h"
#include "Encargo.h"
class Fatura
{
public:
	Fatura();
	~Fatura();

	bool adicionarValorFaturado(string descricao,
		int consumo,
		double tarifa,
		double valor,
		double tarifaAplicada);



private:
	
	bool adicionarValorFaturado(FaturaEnergia valorFaturado);

};

#endif // FATURA_H