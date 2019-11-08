#include "Bandeira.h"

Bandeira::Bandeira()
{
	valor = 0;
}


Bandeira::Bandeira(Cor cor) {
	setCor(cor);
	valor = 0;
}

Bandeira::Bandeira(Cor cor, double valor)
{
	setCor(cor).setValor(valor);
}

Bandeira & Bandeira::setCor(Cor cor)
{
	this->cor = cor;
	return *this;
}

Bandeira & Bandeira::setValor(double valor) {
	this->valor = valor;
	return *this;
}

Bandeira::Cor Bandeira::getCor()
{
	return cor;
}

double Bandeira::getValor()
{
	return valor;
}
