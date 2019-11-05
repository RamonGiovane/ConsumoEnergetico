#ifndef CONSUMO_ENERGETICO_H
#define CONSUMO_ENERGETICO_H
#include <string>
#include <vector>
#include "Cliente.h"
#include "ContaDigital.h"
using namespace std;

class ConsumoEnergetico
{

public:
	
	ConsumoEnergetico();
	int iniciar();

private:

	int menu();
	bool lerContaDigital();

	

	bool interpretarSaidaConversor(int codigoSaida);

	

	//Fatura fatura;
	ContaDigital conta;
};


#endif // !CONSUMO__ENERGETICO_H



