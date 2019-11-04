#include "ContaDigital.h"
#include "Consumo.h"
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

FaturaEnergia ContaDigital::getDadosFatura() {
	return dadosFatura; 
}
void ContaDigital::setDadosFatura(FaturaEnergia dadosFatura) { 
	this->dadosFatura = dadosFatura; 
}

bool ContaDigital::adicionarHistoricoConsumo(Consumo consumo)
{
	static int pos = 0;
	if (pos == CAPACIDADE_HISTORICO_CONSUMO - 1)
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
	sprintf_s(str, 2000, "Número da Instalação:%s\nDados do Cliente:\n%s\nValor a Pagar:%1.2f\nReferente a: %s\tData de Vencimento: %s\nDetalhes da Fatura:%s\nHistórico de Consumo:%s",
		numeroInstalacao.c_str(), cliente.toString().c_str(), valorAPagar, mesReferente.c_str(), dataVencimento.c_str(), dadosFatura.toString().c_str(), obterHistoricoConsumo().c_str());
	return str;
}
