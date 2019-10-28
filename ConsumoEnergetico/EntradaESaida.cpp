#include "EntradaESaida.h"


string EntradaESaida::lerString(string mensagem) {
	string linha;
	do {
		cout << mensagem;
		getline(cin, linha);
	} while (linha == "");
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
	string command = "xpdf\\pdftotext.exe -raw " + caminhoArquivo + arquivoDestino;
	return system(command.c_str);
}

