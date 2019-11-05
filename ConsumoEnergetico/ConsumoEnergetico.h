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
	int interpretarComando(int numeroArgumentos, char * argumentos[]);
	int interpretarComando(char * argumentos[]);
	void exibirInformacao();
	int iniciar(int argc, char * argv[]);

private:

	int menu();
	bool lerContaDigital();

	

	bool interpretarSaidaConversor(int codigoSaida);

	

	//Fatura fatura;
	ContaDigital conta;
};


#endif // !CONSUMO__ENERGETICO_H

int main(int argc, char * argv[]);
