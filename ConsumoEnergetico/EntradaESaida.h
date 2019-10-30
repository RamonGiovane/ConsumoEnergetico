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
	static bool removerArquivo(string caminhoArquivo);

	enum CodigoDeSaida {

		SEM_ERROS = 0, ERRO_ABRIR_ARQUIVO_PDF = 1, ERRO_ABRIR_ARQUIVO_SAIDA = 2, ERRO_DE_PERMISSAO = 3
	};

};