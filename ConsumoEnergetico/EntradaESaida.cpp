#include "EntradaESaida.h"
#include <string>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <regex>
#include "ArquivoTexto.h"
#include "Constantes.h"
#include "Consumo.h"


using namespace std;

/*Identifica e retorna o n�mero de um m�s a partir de sua abrevia��o. Por exemplo: JAN = 1; AGO = 8; NOV = 11*/
int  ES::identificarMesAbreviado(const string & strMes) {
	for (int i = 1; i <= 12; i++) 
		if (_strnicmp(MESES_ABREVIADOS[i].c_str(), strMes.c_str(), 3) == 0)
			return i;
	return 0;
	
}

/*Organiza um vector de consumos de acorda com a fun��o de compara��o definida na classe Consumo*/
bool ES::organizarConsumos(vector<Consumo> & historico) {
	sort(historico.begin(), historico.end(), Consumo::comparador);
	return true;
}

/*Retorna a representa��o textual de um m�s a partir de seu n�mero. Caso o n�mero fornecido n�o corresponda a um m�s, uma string vazia ser� retornada*/
string  ES::mesToStr(int mes) {
	
	if (mes < 1 || mes > 12) return string();
	
	else return MESES_STR[mes];
	
}

void ES::mudarLocalizacao() {
	setlocale(LC_ALL, "pt-BR");
}


bool ES::obterArquivosDiretorio( const string  & caminhoDiretorio, vector<string> & listaArquivos) {

	string arquivosStr;
	listaArquivos = vector<string>();
	
	//Verifica se o caminho solicitado n�o � um arquivo ao inv�s de um diret�rio
	if (ES::arquivoExiste(caminhoDiretorio)) return true;

	//Caso seja um diret�rio, limpa o arquivo que conter� a lista de diret�rios.
	removerArquivo(FILE_DIR_LIST);

	//Realiza uma chamada de sistema que lista os arquivos informados dentro do arquivo DIR_LIST
	system((COM_DIR + caminhoDiretorio + REDIRECTOR + FILE_DIR_LIST).c_str());

	//Tentando ler o arquivo gerado...
	if(!lerArquivoTexto(arquivosStr, FILE_DIR_LIST)) return false;

	//Direcionando para o vector de resposta
	quebrarTexto(listaArquivos, arquivosStr, BARRA_N);

	//Apaga o arquivo temp gerado
	ES::removerArquivo(FILE_DIR_LIST);
	
	//Se o vector estiver vazio, n�o h� arquivos para ler
	if (listaArquivos.empty()) return false;

	return true;
}

bool ES::copiarArquivo(const string & origem, const string & destino) {
	char comando[SIZE_STR];
	sprintf_s(comando, 1000, COM_CP, origem.c_str(), destino.c_str(), NUL_REDIRECTOR);
	system(comando);
	return arquivoExiste(destino);


}

/*Converte um arquivo PDF especificado em caminhoArquivo e um arquivo texto que ser� criado no caminho fornecido em arquivoDestino*/
bool ES::PDFToTextTable(const string & caminhoArquivo, const string & caminhoPrograma, const string  & arquivoDestino) {
	removerArquivo(arquivoDestino);

	char comando[SIZE_STR];
	
	sprintf_s(comando, 1000, COM_PDF_TO_TXT, caminhoPrograma.c_str(), PATH_XPDF, caminhoArquivo.c_str(), 
	arquivoDestino.c_str(), NUL_REDIRECTOR);

	system(comando);

	return  arquivoExiste(arquivoDestino);

}

/*Remove um arquivo do disco r�gido. Se a opera��o for bem sucedida, retorna true. Se o arquivo n�o existir ou um erro ocorrer, 
retorna false.*/
bool ES::removerArquivo(string caminhoArquivo) {

	return remove(caminhoArquivo.c_str()) != 0 ? false : true;
	
}

/*Verifica se um arquivo existe no caminho especificado. Retorna true se ele existir e false se for um diret�rio ou n�o existir*/
bool ES::arquivoExiste(const string& nomeArquivo) {
	ifstream f(nomeArquivo.c_str());
	return f.good();
}

bool ES::quebrarTexto(vector<string> &fragmentos, const string& texto, char delimitador) {
	
	if (texto.empty()) return false;

	stringstream ss(texto);
	string token;

	while (getline(ss, token, delimitador)) {
		if (token == VAZIO) continue;
		fragmentos.push_back(token);
	}

	return fragmentos.empty() ? false : true;
}

/*Divide uma string (par�metro texto) a partir de um delimitador, retornando em um vector, o~s fragmentos obtidos na quebra.*/
bool ES::quebrarTexto(vector<string> &fragmentos, const string& texto, char delimitador, const string& separador) {

	if (texto.empty()) return false;

	stringstream ss(texto);
	string token, lastToken = VAZIO;
	bool repetido = false;
	while (getline(ss, token, delimitador)) {

		if (!fragmentos.empty() && token == lastToken) {
			repetido = true;
			continue;
		}
		else if (repetido) {
			fragmentos.pop_back();
			fragmentos.push_back(separador);
			repetido = false;

		}
		fragmentos.push_back(token);
		lastToken = token;
	}

	return fragmentos.empty() ? false : true;
}


bool ES::strMesAnoToInt(const string & mesAno, int & mes, int & ano) {
	vector<string> v;
	ES::quebrarTexto(v, mesAno, BARRA);

	if (v.size() != 2) return false;

	mes = ES::identificarMesAbreviado(v.front());
	ano = ES::strToInt(v[1]);

	if (mes == 0 || ano == 0) return false;

	if (ano < 2000)
		ano += 2000;

	return true;
}

/*Converte um string e retorna um string para long. Se o cont�udo  da string n�o for um n�mero v�lido, retorna 0*/
long ES::strToLong(const string & str)
{
	return str.empty() || !isNumber(str) ? 0 : stol(str);
}

/*Converte um string e retorna um string para int. Se o cont�udo  da string n�o for um n�mero v�lido, retorna 0*/
int ES::strToInt(const string & str)
{
	return str.empty() || !isNumber(str) ? 0 : stoi(str);
}

/*Converte um string e retorna um string para double. Se o cont�udo  da string n�o for um n�mero v�lido, retorna 0*/
double ES::strToDouble(const string & str)
{
	return str.empty() || !isNumber(str) ? 0 : stod(str);
}

string ES::formatarDouble(const string & numero, int precision) {
	vector<string> fragmentos;
	quebrarTexto(fragmentos, numero, PONTO);
	
	if (fragmentos.empty()) return numero;

	string decimais;
	
	int i = 0;
	for (char d : fragmentos.back()) {
		if (i == precision) break;
		decimais.push_back(d);
		i++;
	}

	return fragmentos[0] + PONTO + decimais;

}

/*Converte e retorna um double para string. Uma precis�o de n�meros depois da v�rgula pode ser definida*/
string ES::doubleToStr(const double & numero, int precision)
{
	stringstream stream;
	stream << fixed << setprecision(3) << numero;
	return formatarDouble(stream.str(), precision); //remover caracteres desse numero
}

/*Converte e retorna um int para string.*/
string ES::intToStr(const int & numero)
{
	stringstream stream;
	stream << numero;
	return stream.str();
}

bool ES::lerArquivoTexto(string& conteudoArquivo, const string & caminhoArquivo) {
	ArquivoTexto arquivo;
	if(!arquivo.abrir(caminhoArquivo, TipoDeAcesso::LEITURA)) return false;
	conteudoArquivo = arquivo.ler();
	arquivo.fechar();
	return conteudoArquivo == SNULL ? false : true;
}

/*Cria um diret�rio no caminho ou nome especificado. Se o diret�rio j� existir, exibe no console uma mensagem de erro, 
isto se for passado false para o campo opcional "ocultarSaida"*/
void ES::criarDiretorio(const string & nomeDir, bool ocultarSaida) {
	system((COM_MKDIR + nomeDir + ((ocultarSaida) ? NUL_REDIRECTOR : VAZIO)).c_str());
}

/*Verifica se o conte�do de uma string cont�m apenas d�gitos ou '.' e ','.*/
bool ES::isNumber(const string& s)
{
	return !s.empty() && find_if(s.begin(),
		s.end(), [](char c) { return (!isdigit(c) && c != VIRGULA && c != PONTO); }) == s.end();
}

/*Procura um padr�o (regex) em uma string. Se encontrado, retorna true e a string que casou com o padr�o fornecido no par�metro padraoRegex */
bool ES::procurarPadrao(string & resultado, const string & texto, string padraoRegex) {
	regex r(padraoRegex);
	string s1;
	smatch match;
	if (regex_search(texto, match, r)) {

		resultado = match.str();
		return true;
	}
	return false;
}

/*Procura um termo usando express�o regular em uma linha que contenha total ou parcialmente o termo pesquisado . Retorna o termo que case com a express�o
ou string vazia se nenhuma linha coincidir com ela*/
string ES::procurarPadrao(const vector<string>& linhasTexto, int & posicaoAtual, string padraoRegex) {
	string resultado;
	for (; posicaoAtual < (int)linhasTexto.size() - 1; posicaoAtual++) {

		if (procurarPadrao(resultado, linhasTexto[posicaoAtual], padraoRegex)) 
			return resultado;
	}
	return string();
}

/*Procura o n�mero de uma linha dentro de um vector com as linhas do arquivo. Pesquisa um termo a partir de uma posi��o (int &) que ser� alterada na chamada
da fun��o, at� a que seja encontrado um termo final ou o fim do arquivo.
Retorna esse n�mero se alguma linha conter o termo pesquisado, -1 do contr�rio*/
vector<string>& ES::procurarLinha(const vector<string> & linhasArquivo, const string & termoPesquisado,
	int & posicaoAtual, const string & termoFinal) {

	static vector<string> linhasValores;
	linhasValores = vector<string>();
	string descricao, item;
	int posicao = posicaoAtual;

	//Iterar pelas linhas at� encontrar o fim
	for (; linhasArquivo[posicaoAtual] != termoFinal && posicaoAtual < (int)linhasArquivo.size() - 1; posicaoAtual++) {

		if (linhasArquivo[posicaoAtual].find(termoPesquisado) != std::string::npos) {

			quebrarTexto(linhasValores, linhasArquivo[posicaoAtual], ESPACO);

			return linhasValores;

		}
	}

	posicaoAtual = posicao;

	return linhasValores;
}

//new
string ES::procurarLinha(const vector<string>& linhasArquivo, const string & termoPesquisado, int & posicaoDeInicio) {
	for (; posicaoDeInicio < (int) linhasArquivo.size(); posicaoDeInicio++)
		if (linhasArquivo[posicaoDeInicio].find(termoPesquisado) != std::string::npos)
			return linhasArquivo[posicaoDeInicio];
	return string();
}

/*
M�TODO NOVO, PRECISA DE COMENTARIO
Procura o n�mero de uma linha dentro de um vector com as linhas do arquivo. Pesquisa um termo a partir de uma posi��o (int &) que ser� alterada na chamada
da fun��o, at� a que seja encontrado um termo final ou o fim do arquivo.
Retorna esse n�mero se alguma linha conter o termo pesquisado, -1 do contr�rio*/
int ES::procurarLinha(vector<string> & resultado, const vector<string>& linhasArquivo, const string & termoPesquisado, int posicaoDeInicio, const char * termoFinal){

	string descricao, item;
	int posicao = posicaoDeInicio;

	//Iterar pelas linhas at� encontrar o fim
	for (; posicaoDeInicio < (int)linhasArquivo.size() - 1; posicaoDeInicio++) {
		
		if (termoFinal != NULL && linhasArquivo[posicaoDeInicio] == termoFinal) break;

		if (linhasArquivo[posicaoDeInicio].find(termoPesquisado) != std::string::npos) {

			quebrarTexto(resultado, linhasArquivo[posicaoDeInicio], ESPACO, VAZIO);

			return posicaoDeInicio;

		}
	}

	return posicao;
}

/*Copia os caracteres de uma string at� que seja encontrado dois ou mais espa�os em branco. Retorna os caracteres em uma nova string*/
string ES::quebrarString(const string & str) {
	bool charVazio = false;
	string resultado;

	for (char c : str) {
		if (c == ESPACO) {
			if (charVazio) break;
			charVazio = true;
		}
		else
			charVazio = false;

		resultado.push_back(c);
	}
	return resultado;
}


/*Procura o n�mero de uma linha que cont�m total ou parcialmente o termo pesquisado . Retorna esse n�mero ou -1 caso a linha n�o seja identificada*/
int ES::procurarNumeroLinha(const vector<string>& linhasArquivo, const string & termoPesquisado, int posicaoAtual) {
	for (; posicaoAtual < (int)linhasArquivo.size() - 1; posicaoAtual++) {
		if (linhasArquivo[posicaoAtual].find(termoPesquisado) != std::string::npos)
			return posicaoAtual;
	}
	return -1;

}

/*
Procura nas linhas do arquivo (const vector<string> & linhasArquivo) o valor correpondente � um termo pesquisado, a partir do numero de uma linha
at� uma linha em que seu conte�do seja especificado por um termo de parada (const string & termoFinal).
Por exemplo, pesquisando o termo "Bandeira Vermelha", sendo as linhas subseguintes � posi��o especificada:

"Energia El�trica kWh 0,66833000
Adicional Bandeiras - J� inclu�do no Valor a Pagar
Bandeira Vermelha 9,81
Hist�rico de Consumo
M�S/ANO CONSUMO kWh M�DIA kWh/Dia Dias
SET/19 162 5,22 31"

Seria retornado o valor "9,81" como string. A pesquisa seria feita at� o termo final "Hist�rico de Consumo" ou at� o final do vector.
O valor a ser retornado � sempre o �ltimo item da linha separado por espa�os em branco. Importante notar que a refer�ncia contendo o n�mero
da linha atual na chamada da fun��o ser� alterada, passando a ter o n�mero da linha em que a pesquisa finalizou.
Se o termo final for uma string vazia, a pesquisa � finalizada na pr�xima posi��o ap�s �quela que corresponder ao termo correto ou
ao final do arquivo.
*/
string ES::procurarItem(const vector<string> & linhasArquivo, const string & termoPesquisado,
	int & posicaoAtual, const string & termoFinal) {

	vector<string> linhasValores = ES::procurarLinha(linhasArquivo, termoPesquisado, posicaoAtual, termoFinal);
	if (!linhasValores.empty())
		return linhasValores.back();

	return string();

}

