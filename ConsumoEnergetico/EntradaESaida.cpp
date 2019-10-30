#include "EntradaESaida.h"
#include <string>
#include <fstream>
#include <cstdio>

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

/**/
int EntradaESaida::PDFToText(string caminhoArquivo, string arquivoDestino) {
	string command = "xpdf\\pdftotext.exe -raw " + caminhoArquivo + " " + arquivoDestino;
	return system(command.c_str());
}

/*Remove um arquivo do disco r�gido. Se a opera��o for bem sucedida, retorna true. Se o arquivo n�o existir ou um erro ocorrer, 
retorna false.*/
bool EntradaESaida::removerArquivo(string caminhoArquivo) {

	return remove(caminhoArquivo.c_str()) != 0 ? false : true;
	
}

