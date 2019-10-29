#ifndef CONSUMO_H
#define CONSUMO_H
#include <string>

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
};


#endif // !CONSUMO_H

const string ConsumoEnergetico::ARQUIVO_SAIDA = string("saida.txt");
const string ConsumoEnergetico::CAMINHO_SAIDA = string("xpdf\\saida.txt");


