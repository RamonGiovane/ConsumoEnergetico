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
	setConsumo(consumo).setValorDaFatura(valorFaturado).setPreco(preco);
}

double ValoresFaturados::obterValorAdicional(Bandeira::Cor bandeira) {
	switch (bandeira)
	{
	case Bandeira::Cor::AMARELA:
		return bandeiraAmarela.getValor();
	case Bandeira::Cor::VERMELHA:
		return bandeiraVermelha.getValor();
	default:
		return -1;

	}
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

ValoresFaturados & ValoresFaturados::setValorDaFatura(double valor)
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
	//N�o est� sendo usado. Serve apenas para fins de teste
	char str[500];
	sprintf_s(str, 500,
		"Pre�o da energia el�trica: R$%1.8f\nConsumo faturado este m�s: %d kWh\nValor da fatura: R$% 1.2f\n"
		"Valor de contribui��o de ilumina��o p�blica: R$ %1.2f\nAdicionais j� inclusos no pre�o:\nBandeira Amarela: R$ %1.2f\nBandeira Vermelha: R$ %1.2f",
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

double ValoresFaturados::getValorDaFatura()
{
	return valorFaturado;
}

double ValoresFaturados::getValorIluminacaoPublica()
{
	return iluminacaoPublica;
}



