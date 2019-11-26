#include <string>
#include <iostream>
#include  <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;
class ES {

public:

	static int identificarMesAbreviado(const string & strMes);
	

	static string mesToStr(int mes);
	static void mudarLocalizacao();
	static bool obterArquivosDiretorio(const string & caminhoDiretorio, vector<string>& listaArquivos);

	static bool PDFToTextTable(const string & caminhoArquivo, const string & caminhoPrograma, const string & arquivoDestino);

	static bool removerArquivo(string caminhoArquivo);
	static bool arquivoExiste(const string & nomeArquivo);

	static bool quebrarTexto(vector<string>&fragmentos, const string & texto, char delimitador);

	static bool quebrarTexto(vector<string>& fragmentos, const string & texto, char delimitador, const string & separador);

	static bool strMesAnoToInt(const string & mesAno, int & mes, int & ano);

	static long strToLong(const string & str);

	static int strToInt(const string& str);
	static double strToDouble(const string& str);
	static string doubleToStr(const double & numero, int precision = 2);
	static string intToStr(const int & numero);

	static bool lerArquivoTexto(string & conteudoArquivo, const string & caminhoArquivo);
	
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
	
	
	static int procurarLinha(vector<string>& resultado, const vector<string>& linhasArquivo, 
		const string & termoPesquisado, int posicaoDeInicio = 0, const char * termoFinal = NULL);

	static string quebrarString(const string & str);
	
	static int procurarNumeroLinha(const vector<string>& linhasArquivo, const string & termoPesquisado, int posicaoInicial);





};