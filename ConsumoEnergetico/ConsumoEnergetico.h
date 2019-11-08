#ifndef CONSUMO_ENERGETICO_H
#define CONSUMO_ENERGETICO_H
#include <string>
#include <vector>
#include "Cliente.h"
#include "Fatura.h"
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

	int interpretarUmParametro(char * paramtero);

private:

	int menu();
	bool lerContaDigital();

	

	bool interpretarSaidaConversor(int codigoSaida);

	

	//Fatura fatura;
	Fatura conta;
};


#endif // !CONSUMO__ENERGETICO_H

int main(int argc, char * argv[]);
