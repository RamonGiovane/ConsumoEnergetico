#include "ValoresFaturados.h"

ValoresFaturados::ValoresFaturados()
{
	inicializarBandeiras();
}
void ValoresFaturados::inicializarBandeiras()
{
	bandeiraAmarela = Bandeira(Bandeira::Cor::AMARELA);
	bandeiraVermelha = Bandeira(Bandeira::Cor::VERMELHA);
}

ValoresFaturados::ValoresFaturados(int consumo, double valorFaturado, double preco)
{
	inicializarBandeiras();
	setConsumo(consumo).setValorFaturado(valorFaturado).setPreco(preco);
}

ValoresFaturados & ValoresFaturados::setConsumo(int consumo)
{
	this->consumo = consumo;
	return *this;
}

ValoresFaturados & ValoresFaturados::setPreco(double preco)
{
	this->preco = preco;
	return *this;
}

ValoresFaturados & ValoresFaturados::setValorFaturado(double valor)
{
	this->valorFaturado = valor;
	return *this;
}

ValoresFaturados & ValoresFaturados::setValorIluminacaoPublica(double valor)
{
	iluminacaoPublica = valor;
	return *this;
}

ValoresFaturados & ValoresFaturados::definirAdicionais(double bandeiraAmarela, double bandeiraVermelha)
{
	this->bandeiraAmarela.setValor(bandeiraAmarela);
	this->bandeiraVermelha.setValor(bandeiraVermelha);
	return *this;
}

string ValoresFaturados::toString()
{
	char str[500];
	sprintf_s(str, 500,
		"Preço da energia elétrica: R$%1.8f\nConsumo faturado este mês: %d kWh\nValor da fatura: R$% 1.2f\n"  
		"Valor de contribuição de iluminação pública: R$ %1.2f\nAdicionais já inclusos no preço:\nBandeira Amarela: R$ %1.2f\nBandeira Vermelha: R$ %1.2f",
		preco, consumo, valorFaturado, iluminacaoPublica, bandeiraAmarela.getValor(), bandeiraVermelha.getValor());
	return str;
}



int ValoresFaturados::getConsumo()
{
	return consumo;
}

double ValoresFaturados::getPreco()
{
	return preco;
}

double ValoresFaturados::getValorFaturado()
{
	return valorFaturado;
}

double ValoresFaturados::getValorIluminacaoPublica()
{
	return iluminacaoPublica;
}



