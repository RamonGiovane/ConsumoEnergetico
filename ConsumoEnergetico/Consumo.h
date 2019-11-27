#ifndef CONSUMO_H
#define CONSUMO_H
#include <string>
using namespace std;
class Consumo 
{
public:
	Consumo();
	Consumo(int mes, int ano, double consumoKWh, double mediaConsumoDiario, int dias, string numeroInstalcao);

	Consumo& setMes(int mes);
	Consumo& setAno(int ano);
	Consumo& setConsumoKWh(double consumo);
	Consumo& setMediaConsumoDiario(double media);
	Consumo& setDias(int dias);
	Consumo& setNumeroInstalacao(string numeroInstalacao);
	bool definirMesAno(string mesAnoStr);

	int getMes();
	int getAno();
	double getConsumoKWh();
	double getMediaConsumoDiario();
	int getDias();
	string getNumeroInstalacao();

	string toString();

	static bool comparador(Consumo & consumo1, Consumo & consumo2);

private:
	int mes;
	int ano;
	double consumoKWh;
	double mediaConsumoDiario;
	int dias;
	string numeroInstalcao;
	
};


#endif // !CONSUMO_H


