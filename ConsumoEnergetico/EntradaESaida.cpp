#include "EntradaESaida.h"
#include <string>
#include <fstream>
#include <cstdio>
#include <iostream>

using namespace std;
string ES::lerString(string mensagem) {
	string linha;
	cout << mensagem;
	while (linha == ""){
		getline(cin, linha);
	}
	return linha;
}
int ES::lerInteiro(string mensagem) {
	int opcao;
	cout << mensagem;
	cin >> opcao;
	return opcao;
}

/*Identifica e retorna o número de um mês a partir de sua abreviação. Por exemplo: JAN = 1; AGO = 8; NOV = 11*/
int  ES::identificarMesAbreviado(string strMes) {
	if (strMes == "JAN" || strMes == "jan")
		return 1;
	if (strMes == "FEV" || strMes == "fev")
		return 2;
	if (strMes == "MAR" || strMes == "mar")
		return 3;
	if (strMes == "ABR" || strMes == "abr")
		return 4;
	if (strMes == "MAI" || strMes == "mai")
		return 5;
	if (strMes == "JUN" || strMes == "jun")
		return 6;
	if (strMes == "JUL" || strMes == "jul")
		return 7;
	if (strMes == "AGO" || strMes == "ago")
		return 8;
	if (strMes == "SET" || strMes == "set")
		return 9;
	if (strMes == "OUT" || strMes == "out")
		return 10;
	if (strMes == "NOV" || strMes == "nov")
		return 11;
	if (strMes == "DEZ" || strMes == "dez")
		return 12;
	return 0;
}

/*Retorna a representação textual de um mês a partir de seu número. Caso o número fornecido não corresponda a um mês, uma string vazia será retornada*/
string  ES::mesToStr(int mes) {
	switch (mes)
	{
	case 1:
		return "Janeiro";
	case 2:
		return "Fevereiro";
	case 3:
		return "Março";
	case 4:
		return "Abril";
	case 5:
		return "Maio";
	case 6:
		return "Junho";
	case 7:
		return "Julho";
	case 8:
		return "Agosto";
	case 9:
		return "Setembro";
	case 10:
		return "Outubro";
	case 11:
		return "Novembro";
	case 12:
		return "Dezembro";
	}

	return "";
}
void ES::mudarLocalizacao() {
	setlocale(LC_ALL, "pt-BR");
}

/**/
int ES::PDFToText(string caminhoArquivo, string arquivoDestino) {
	string command = "xpdf\\pdftotext.exe -raw " + caminhoArquivo + " " + arquivoDestino;
	return system(command.c_str());
}

/*Remove um arquivo do disco rígido. Se a operação for bem sucedida, retorna true. Se o arquivo não existir ou um erro ocorrer, 
retorna false.*/
bool ES::removerArquivo(string caminhoArquivo) {

	return remove(caminhoArquivo.c_str()) != 0 ? false : true;
	
}

void ES::exibirAbortarOperacao() {
	cout << "\nA operação foi abortada." << endl << endl;
}

bool ES::quebrarTexto(vector<string> &fragmentos, const string& texto, char delimitador) {
	
	if (texto.empty()) return false;

	stringstream ss(texto);
	string linha;
	while (getline(ss, linha, delimitador)) {
		fragmentos.push_back(linha);

	}
	return true;
}

int ES::strToInt(const string & str)
{
	return str.empty() || !isNumber(str) ? 0 : stoi(str);
}

double ES::strToDouble(const string & str)
{
	return str.empty() || !isNumber(str) ? 0 : stod(str);
}

string ES::doubleToStr(const double & numero, int precision)
{
	stringstream stream;
	stream << fixed << setprecision(precision) << numero;
	return stream.str();
}

string ES::intToStr(const int & numero)
{
	stringstream stream;
	stream << numero;
	return stream.str();
}


bool ES::isNumber(const string& s)
{
	return !s.empty() && find_if(s.begin(),
		s.end(), [](char c) { return (!isdigit(c) && c != ',' && c != '.'); }) == s.end();
}


