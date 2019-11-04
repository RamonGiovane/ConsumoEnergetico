#ifndef CONSUMO_H
#define CONSUMO_H
#include <string>
using namespace std;
class Consumo
{
public:
	Consumo();
	Consumo& setMes(int mes);
	Consumo& setAno(int ano);
	Consumo& setConsumoKWh(int consumo);
	Consumo& setMediaConsumoDiario(double media);
	Consumo& setDias(int dias);

	bool definirMesAno(string mesAnoStr);

	int getMes();
	int getAno();
	int getConsumoKWh();
	double getMediaConsumoDiario();
	int getDias();

	string toString();

private:
	int mes;
	int ano;
	int consumoKWh;
	double mediaConsumoDiario;
	int dias;

	int identificarMes(string strMes);
	
};


#endif // !CONSUMO_H


