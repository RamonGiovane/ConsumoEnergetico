#ifndef FATURA_H
#define FATURA_H
#include "Bandeira.h"
#include "ValorFaturado.h"
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
	ValorFaturado* valoresFaturados;
	Bandeira* bandeiras;

};

#endif // FATURA_H