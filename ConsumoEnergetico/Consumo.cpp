#include <string>
#include "EntradaESaida.h"
#include "Consumo.h"

using namespace std;
Consumo::Consumo()
{
	mes = ano = dias = consumoKWh = 0;
	mediaConsumoDiario = 0;
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

	int mes = identificarMes(v[0]);

	if (mes == 0) return false;

	this->mes = mes;
	
	ano = ES::strToInt(v[1]);
	if (ano < 2000)
		ano += 2000;

	return true;

}

int  Consumo::identificarMes(string strMes) {
	if (strMes == "JAN" || strMes == "jan")
		return 1;
	if (strMes == "FEV" || strMes == "fev")
		return 2;
	if (strMes == "MAR" || strMes == "mar")
		return 3;
	if (strMes == "ABR" || strMes == "abr")
		return 4;
	if (strMes == "MAI" || strMes == "mai")
		return 5;
	if (strMes == "JUN" || strMes == "jun")
		return 6;
	if (strMes == "JUL" || strMes == "jul")
		return 7;
	if (strMes == "AGO" || strMes == "ago")
		return 8;
	if (strMes == "SET" || strMes == "set")
		return 9;
	if (strMes == "OUT" || strMes == "out")
		return 10;
	if (strMes == "NOV" || strMes == "nov")
		return 11;
	if (strMes == "DEZ" || strMes == "dez")
		return 12;
	return 0;
}

string Consumo::toString() {
	char str[500];
	sprintf_s(str, 500, "Ano: %d Mês: %d Consumo: %d kWh Média: %1.2f kWh/dia em %d dias", ano, mes, consumoKWh, mediaConsumoDiario, dias);
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
