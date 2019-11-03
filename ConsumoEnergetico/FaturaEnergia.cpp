#include "FaturaEnergia.h"

FaturaEnergia::FaturaEnergia()
{
	inicializarBandeiras();
}
void FaturaEnergia::inicializarBandeiras()
{
	bandeiraAmarela = Bandeira(Bandeira::Cor::AMARELA);
	bandeiraVermelha = Bandeira(Bandeira::Cor::VERMELHA);
}

FaturaEnergia::FaturaEnergia(int consumo, double valorFaturado, double preco)
{
	inicializarBandeiras();
	setConsumo(consumo).setValorFaturado(valorFaturado).setPreco(preco);
}

FaturaEnergia & FaturaEnergia::setConsumo(int consumo)
{
	this->consumo = consumo;
	return *this;
}

FaturaEnergia & FaturaEnergia::setPreco(double preco)
{
	this->preco = preco;
	return *this;
}

FaturaEnergia & FaturaEnergia::setValorFaturado(double valor)
{
	this->valorFaturado = valor;
	return *this;
}

FaturaEnergia & FaturaEnergia::setValorIluminacaoPublica(double valor)
{
	iluminacaoPublica = valor;
	return *this;
}

FaturaEnergia & FaturaEnergia::definirAdicionais(double bandeiraAmarela, double bandeiraVermelha)
{
	this->bandeiraAmarela.setValor(bandeiraAmarela);
	this->bandeiraVermelha.setValor(bandeiraVermelha);
	return *this;
}



int FaturaEnergia::getConsumo()
{
	return consumo;
}

double FaturaEnergia::getPreco()
{
	return preco;
}

double FaturaEnergia::getValorFaturado()
{
	return valorFaturado;
}

double FaturaEnergia::getValorIluminacaoPublica()
{
	return iluminacaoPublica;
}



