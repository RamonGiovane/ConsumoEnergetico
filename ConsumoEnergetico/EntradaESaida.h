#include <string>
#include <iostream>
#include  <sstream>
using namespace std;
class EntradaESaida {
public:
	static string lerString(string mensagem);
	static int lerInteiro(string mensagem);
	static void mudarLocalizacao();
	static int PDFToText(string caminhoArquivo, string arquivoDestino);
	

};

