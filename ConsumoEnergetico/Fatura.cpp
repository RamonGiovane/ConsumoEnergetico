#include "Fatura.h"
#include "Consumo.h"
#include "ValoresFaturados.h"

Fatura::Fatura()
{
}


string Fatura::getNumeroInstalacao() { 
	return numeroInstalacao; 
}
void Fatura::setNumeroInstalacao(string numeroInstalacao) { 
	this->numeroInstalacao = numeroInstalacao;
}

string Fatura::getDataVencimento() { 
	return dataVencimento;
}

void Fatura::setDataVencimento(string dataVencimento)
{
	this->dataVencimento = dataVencimento;
}

double Fatura::getValorAPagar() { 
	return valorAPagar; 
}

void Fatura::setValorAPagar(double valor) { 
	this->valorAPagar = valor; 
}

string Fatura::getMesReferente() { 
	return mesReferente; 
}
void Fatura::setMesReferente(string mesReferente) { 
	this->mesReferente = mesReferente; 
}

Cliente Fatura::getCliente() {
	return cliente; 
}
void Fatura::setCliente(Cliente cliente) { 
	this->cliente = cliente;
}

ValoresFaturados Fatura::getValoresFaturados() {
	return valoresFaturados; 
}
void Fatura::setValoresFaturados(ValoresFaturados dadosFatura) { 
	this->valoresFaturados = dadosFatura; 
}
#include <iostream>
bool Fatura::adicionarHistoricoConsumo(Consumo consumo)
{
	static int pos = 0;
	
	if (pos == CAPACIDADE_HISTORICO_CONSUMO) {
		return false;
	}
	historicoConsumo[pos++] = consumo;
	if (pos == CAPACIDADE_HISTORICO_CONSUMO) pos = 0;
	return true;
}
string  Fatura::obterHistoricoConsumo() {
	string historico;
	for (int i = 0; i < CAPACIDADE_HISTORICO_CONSUMO; i++)
		historico.append(historicoConsumo[i].toString() + "\n");
	return historico;
}


string Fatura::toString()
{
	char str[2000];
	sprintf_s(str, 2000, "\n\nNúmero da Instalação:%s\nDados do Cliente:\n%s\nValor a Pagar:R$ %1.2f\nReferente a: %s\tData de Vencimento: %s\n\nDetalhes da Fatura:\n%s\n\nHistórico de Consumo:\n%s",
		numeroInstalacao.c_str(), cliente.toString().c_str(), valorAPagar, mesReferente.c_str(), dataVencimento.c_str(), valoresFaturados.toString().c_str(), obterHistoricoConsumo().c_str());
	return str;
}
