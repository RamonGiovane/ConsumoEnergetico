#include "EntradaESaida.h"
#include <string>
using namespace std;
string EntradaESaida::lerString(string mensagem) {
	string linha;
	cout << mensagem;
	while (linha == ""){
		getline(cin, linha);
	}
	return linha;
}
int EntradaESaida::lerInteiro(string mensagem) {
	int opcao;
	cout << mensagem;
	cin >> opcao;
	return opcao;
}

void EntradaESaida::mudarLocalizacao() {
	setlocale(LC_ALL, "pt-BR");
}

int EntradaESaida::PDFToText(string caminhoArquivo, string arquivoDestino) {
	string command = "xpdf\\pdftotext.exe -raw " + caminhoArquivo + " " + arquivoDestino;
	return system(command.c_str());
}

int EntradaESaida::removerArquivo(string caminhoArquivo) {
	
	char command[150];
	sprintf_s(command, 150,  "del %s" , caminhoArquivo.c_str());
	strcat_s(command, " > nul");
	return system(command);
}

