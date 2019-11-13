#include <string>
#include "EntradaESaida.h"
#include "Consumo.h"

using namespace std;
Consumo::Consumo(){
	mes = ano = dias = consumoKWh = 0;
	mediaConsumoDiario = 0;
}

Consumo::Consumo(int mes, int ano, int consumoKWh, double mediaConsumoDiario, int dias) {
	setMes(mes).setAno(ano).setConsumoKWh(consumoKWh).setMediaConsumoDiario(mediaConsumoDiario).setDias(dias);
}
Consumo & Consumo::setMes(int mes)
{
	this->mes = mes;
	return *this;
}

Consumo & Consumo::setAno(int ano)
{
	this->ano = ano;
	return *this;
}

Consumo & Consumo::setConsumoKWh(int consumo)
{
	consumoKWh = consumo;
	return *this;
}

Consumo & Consumo::setMediaConsumoDiario(double media)
{
	mediaConsumoDiario = media;
	return *this;
}

Consumo & Consumo::setDias(int dias)
{
	this->dias = dias;
	return *this;
}

bool Consumo::definirMesAno(string mesAnoStr)
{
	vector<string> v;
	ES::quebrarTexto(v, mesAnoStr, '/');

	if (v.size() != 2) return false;

	int mes = ES::identificarMesAbreviado(v[0]);

	if (mes == 0) return false;

	this->mes = mes;
	
	ano = ES::strToInt(v[1]);
	if (ano < 2000)
		ano += 2000;

	return true;

}



string Consumo::toString() {
	char str[1000];
	sprintf_s(str, 1000, "Ano: %d Mês: %d Consumo: %d kWh Média: %1.2f kWh/dia em %d dias", ano, mes, consumoKWh, mediaConsumoDiario, dias);
	return str;
}

int Consumo::getMes()
{
	return mes;
}

int Consumo::getAno()
{
	return ano;
}

int Consumo::getConsumoKWh()
{
	return consumoKWh;
}

double Consumo::getMediaConsumoDiario()
{
	return mediaConsumoDiario;
}

int Consumo::getDias()
{
	return dias;
}
