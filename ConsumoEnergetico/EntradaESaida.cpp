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
	return str.empty() ? 0 : stoi(str);
}

double ES::strToDouble(const string & str)
{
	return str.empty() ? 0 : stod(str);
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
		s.end(), [](char c) { return !isdigit(c); }) == s.end();
}


