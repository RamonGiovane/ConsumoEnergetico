#include "Fatura.h"
#include "Consumo.h"
#include "ValoresFaturados.h"
#include "EntradaESaida.h"
#include <iostream>

Fatura::Fatura() {

	valorAPagar = 0;
	mesReferente = anoReferente = 0;

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

int Fatura::getMesReferente() { 
	return mesReferente; 
}
void Fatura::setMesReferente(int mesReferente) {
	this->mesReferente = mesReferente;
}

int Fatura::getAnoReferente() {
	return anoReferente;
}
void Fatura::setAnoReferente(int anoReferente) {
	this->anoReferente = anoReferente;
}

Cliente Fatura::getCliente() {
	return cliente; 
}
void Fatura::setCliente(Cliente cliente) { 
	this->cliente = cliente;
}

string Fatura::getDataDeLeitura()
{
	return dataDeLeitura;
}

void Fatura::setDataDeLeitura(string dataDeLeitura)
{
	this->dataDeLeitura = dataDeLeitura;
}

string Fatura::getDataDeLeituraAnterior()
{
	return dataDeLeituraAnterior;
}

void Fatura::setDataDeLeituraAnterior(string dataDeLeituraAnterior)
{
	this->dataDeLeituraAnterior = dataDeLeituraAnterior;
}

string Fatura::getProximaDataDeLeitura()
{
	return proximaDataDeLeitura;
}

void Fatura::setProximaDataDeLeitura(string proximaDataDeLeitura)
{
	this->proximaDataDeLeitura = proximaDataDeLeitura;
}

ValoresFaturados Fatura::getValoresFaturados() {
	return valoresFaturados; 
}
void Fatura::setValoresFaturados(ValoresFaturados dadosFatura) { 
	this->valoresFaturados = dadosFatura; 
}

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
string  Fatura::obterHistoricoConsumoStr() {
	string historico;
	for (int i = 0; i < CAPACIDADE_HISTORICO_CONSUMO; i++)
		historico.append(historicoConsumo[i].toString() + "\n");
	return historico;
}


bool Fatura::obterConsumoDoHistorico(Consumo & consumo, int posicaoDoHistorico)  {
	if (posicaoDoHistorico < 0 || posicaoDoHistorico > 12)
		return false;
	consumo = Consumo(historicoConsumo[posicaoDoHistorico]);
	return true;
}

bool Fatura::setMesAnoReferente(const string & mesAno) {
	vector<string> v;
	int mes, ano;
	ES::quebrarTexto(v, mesAno, '/');

	if (v.size() != 2) return false;

	ES::strMesAnoToInt(mesAno, mes, ano);

	setMesReferente(mes);
	setAnoReferente(ano);

	return true;
}

string Fatura::toString()
{
	char str[3000];
	sprintf_s(str, 3000, "\n\nNúmero da Instalação:%s\nDados do Cliente:\n%s"
		"\n\nDatas de Leitura:\n Anterior: %s Atual: %s Próxima: %s"
		"\n\n============\n  Valor a Pagar : R$ %1.2f\n"
		"\n  Referente a: %s/%d\n  Data de Vencimento: %s\n==============="
		"\n\nDetalhes da Fatura:\n%s\n\nHistórico de Consumo:\n%s",
		numeroInstalacao.c_str(), cliente.toString().c_str(), 
		dataDeLeituraAnterior.c_str(), dataDeLeitura.c_str(), proximaDataDeLeitura.c_str(),
		valorAPagar, ES::mesToStr(mesReferente).c_str(), 
		anoReferente, dataVencimento.c_str(), valoresFaturados.toString().c_str(), obterHistoricoConsumoStr().c_str());
	return str;
}
