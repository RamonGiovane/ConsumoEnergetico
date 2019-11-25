#include <string>
#include "EntradaESaida.h"
#include "Consumo.h"

using namespace std;

Consumo::Consumo(){
	mes = ano = dias = 0;
	consumoKWh = mediaConsumoDiario = 0;
}


Consumo::Consumo(int mes, int ano, double consumoKWh, double mediaConsumoDiario, int dias, string numeroInstalcao){
	setMes(mes).setAno(ano).setConsumoKWh(consumoKWh).setMediaConsumoDiario(mediaConsumoDiario).setDias(dias).setNumeroInstalacao(numeroInstalcao);
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

Consumo & Consumo::setConsumoKWh(double consumo)
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

Consumo & Consumo::setNumeroInstalacao(string numeroInstalacao)
{
	this->numeroInstalcao = numeroInstalacao;
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
	sprintf_s(str, 1000, "%1.2d/%d  %1.3d kWh  %1.2f kWh/dia em %d dias", mes, ano, (int)consumoKWh, mediaConsumoDiario, dias);
	return str;
}

bool Consumo::comparador(Consumo & consumo1, Consumo & consumo2)
{
	int comparacao = consumo1.getNumeroInstalacao().compare(consumo2.getNumeroInstalacao());
	if (comparacao < 0) return false;
	if (comparacao > 0) return true;

	if (consumo1.getAno() < consumo2.getAno()) return false;
	if (consumo1.getAno() > consumo2.getAno()) return true;

	if (consumo1.getMes() < consumo2.getMes()) return false;
	if (consumo1.getMes() > consumo2.getMes()) return true;

	return false;
}

int Consumo::getMes()
{
	return mes;
}

int Consumo::getAno()
{
	return ano;
}

double Consumo::getConsumoKWh()
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

string Consumo::getNumeroInstalacao()
{
	return numeroInstalcao;
}
