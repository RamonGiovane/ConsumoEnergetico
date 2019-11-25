#include <string>
#include <iostream>
#include  <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;
class ES {
#define SUCESSO_STR = "Sucesso."
public:
	static string lerString(string mensagem);
	static int lerInteiro(string mensagem);
	static int identificarMesAbreviado(string strMes);
	static string mesToStr(int mes);
	static void mudarLocalizacao();
	static bool obterArquivosDiretorio(const string & caminhoDiretorio, vector<string>& listaArquivos);

	static bool PDFToText(const string & caminhoArquivo, const string & caminhoPrograma, const string & arquivoDestino);

	static bool PDFToTextTable(const string & caminhoArquivo, const string & arquivoDestino);

	static bool PDFToTextTable(const string & caminhoArquivo, const string & caminhoPrograma, const string & arquivoDestino);

	static bool removerArquivo(string caminhoArquivo);
	static bool arquivoExiste(const string & nomeArquivo);
	static void exibirAbortarOperacao();

	static bool quebrarTexto(vector<string>& fragmentos, const string & texto, char delimitador);

	static bool quebrarTexto(vector<string>& fragmentos, const string & texto, char delimitador, const string & separador);

	static bool strMesAnoToInt(const string & mesAno, int & mes, int & ano);

	static long strToLong(const string & str);

	static int strToInt(const string& str);
	static double strToDouble(const string& str);
	static string doubleToStr(const double & numero, int precision = 2);
	static string intToStr(const int & numero);
	
	static void criarDiretorio(const string & nomeDir, bool ocultarSaida = true);
	
	static bool isNumber(const std::string& s);
	//new procura padrao numa string
	static bool procurarPadrao(string & resultado, const string & texto, string padraoRegex);

	static string procurarPadrao(const vector<string>& linhasTexto, int & posicaoAtual, string padraoRegex);
	static vector<string>& procurarLinha(const vector<string>& linhasArquivo, const string & termoPesquisado,
		int & posicaoAtual, const string & termoFinal);

	//new
	static string procurarLinha(const vector<string>& linhasArquivo, const string & termoPesquisado, int & posicaoDeInicio);
	
	static string procurarItem(const vector<string>& linhasArquivo, const string & termoPesquisado,
		int & posicaoAtual, const string & termoFinal = "");
	
	
	static int procurarLinha(vector<string>& resultado, const vector<string>& linhasArquivo, const string & termoPesquisado, int posicaoDeInicio = 0, const char * termoFinal = NULL);
	
	static int procurarNumeroLinha(const vector<string>& linhasArquivo, const string & termoPesquisado, int posicaoInicial);


	enum CodigoDeSaida {

		SEM_ERROS = 0, ERRO_ABRIR_ARQUIVO_PDF = 1, ERRO_ABRIR_ARQUIVO_SAIDA = 2, ERRO_DE_PERMISSAO = 3
	};


};