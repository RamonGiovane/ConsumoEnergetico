#include "ContaDigital.h"
#include "Consumo.h"
#include "ValoresFaturados.h"

ContaDigital::ContaDigital()
{
}


string ContaDigital::getNumeroInstalacao() { 
	return numeroInstalacao; 
}
void ContaDigital::setNumeroInstalacao(string numeroInstalacao) { 
	this->numeroInstalacao = numeroInstalacao;
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
	this->valorAPagar = valor; 
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

ValoresFaturados ContaDigital::getValoresFaturados() {
	return valoresFaturados; 
}
void ContaDigital::setValoresFaturados(ValoresFaturados dadosFatura) { 
	this->valoresFaturados = dadosFatura; 
}

bool ContaDigital::adicionarHistoricoConsumo(Consumo consumo)
{
	static int pos = 0;
	if (pos == CAPACIDADE_HISTORICO_CONSUMO)
		return false;
	historicoConsumo[pos++] = consumo;
	return true;
}
string  ContaDigital::obterHistoricoConsumo() {
	string historico;
	for (int i = 0; i < CAPACIDADE_HISTORICO_CONSUMO; i++)
		historico.append(historicoConsumo[i].toString() + "\n");
	return historico;
}


string ContaDigital::toString()
{
	char str[2000];
	sprintf_s(str, 2000, "\n\nNúmero da Instalação:%s\nDados do Cliente:\n%s\nValor a Pagar:R$ %1.2f\nReferente a: %s\tData de Vencimento: %s\n\nDetalhes da Fatura:\n%s\n\nHistórico de Consumo:\n%s",
		numeroInstalacao.c_str(), cliente.toString().c_str(), valorAPagar, mesReferente.c_str(), dataVencimento.c_str(), valoresFaturados.toString().c_str(), obterHistoricoConsumo().c_str());
	return str;
}
