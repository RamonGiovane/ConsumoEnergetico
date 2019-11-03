#include "ContaDigital.h"



ContaDigital::ContaDigital()
{
}


string ContaDigital::getNumeroInstalacao() { 
	return numeroInstalacao; 
}
void ContaDigital::setNumeroInstalacao(string numeroInstalacao) { 
	this->numeroInstalacao = this->numeroInstalacao;
}

string ContaDigital::getDataVencimento() { 
	return dataVencimento;
}

void ContaDigital::setDataVencimento(string dataVencimento)
{
	this->dataVencimento = dataVencimento;
}

double ContaDigital::getValorAPagar() { 
	return valorAPagar; 
}

void ContaDigital::setValorAPagar(double valor) { 
	this->valorAPagar = valorAPagar; 
}

string ContaDigital::getMesReferente() { 
	return mesReferente; 
}
void ContaDigital::setMesReferente(string mesReferente) { 
	this->mesReferente = mesReferente; 
}

Cliente ContaDigital::getCliente() {
	return cliente; 
}
void ContaDigital::setCliente(Cliente cliente) { 
	this->cliente = cliente;
}

FaturaEnergia ContaDigital::getDadosFatura() {
	return dadosFatura; 
}
void ContaDigital::setDadosFatura(FaturaEnergia dadosFatura) { 
	this->dadosFatura = dadosFatura; 
}