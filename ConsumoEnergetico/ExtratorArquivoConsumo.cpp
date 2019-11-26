#include "ExtratorArquivoConsumo.h"
#include "ArquivoHistorico.h"
#include "Consumo.h"
#include "EntradaESaida.h"
#include "Constantes.h"
#include <vector>
#include <string>

using namespace std;
bool ExtratorArquivoConsumo::lerArquivoDeConsumo(Consumo & consumo, const string & numeroCliente, const string & caminhoArquivoEntrada) {
	string textoArquivo;

	Consumo consumoDoMes;
	ES::lerArquivoTexto(textoArquivo, caminhoArquivoEntrada);

	if (textoArquivo == SNULL) return erro(MSGE_ARQUIVO_ENTRADA);

	vector<string> linhas;
	int mesArquivo, anoArquivo;
	ES::quebrarTexto(linhas, textoArquivo, BARRA_N);
	if (linhas.empty()) { return erro(MSGE_ARQUIVO_ENTRADA); }

	if (!lerValidarCabecalhoArquivoDeConsumo(linhas[0], mesArquivo, anoArquivo)) return false;

	double consumoCalculado = calcularConsumo(linhas, mesArquivo, anoArquivo);
	if (consumoCalculado == -1) return false;


	consumo.setConsumoKWh(consumoCalculado);

	return 1;
	//return gerarDadosConusmo(consumo, dias, mes, ano);

}


bool ExtratorArquivoConsumo::lerValidarCabecalhoArquivoDeConsumo(const string & linhaCabecalho, int & mes, int & ano) {
	const string LINHA_1 = " 1.";
	vector<string> cabecalho;
	ES::quebrarTexto(cabecalho, linhaCabecalho, ESPACO);

	string dataInvalida;

	if (cabecalho[0] == HASH_TAG && cabecalho.size() == 4) {
		if (!ES::strMesAnoToInt(cabecalho[3], mes, ano))
			dataInvalida = BARRA_N + MSG_DATA_INVALIDA;
		else
			return true;
	}
	setMensagemErro(MSGE_SINTAXE_INVALIDA + LINHA_1 + ITEM_LINHA + cabecalho[0] + BARRA_N + dataInvalida);
	return false;
}

bool gerarDadosConsumo(Consumo * consumo, const string & numeroInstalacao, int dias, int mes, int ano) {
	ArquivoHistorico arquivo;
	arquivo.abrir(FILE_HISTORICO_DAT);

	int registro = arquivo.pesquisarConsumoNoHistorico(numeroInstalacao, mes, ano);
	if (registro == -1) return false;
	consumo = arquivo.lerObjeto(registro);

	return true;

}

double ExtratorArquivoConsumo::calcularConsumo(const vector<string> & linhasArquivo, int mes, int ano) {
	double valorConsumo, totalConsumo = 0;

	for (size_t i = 1; i < linhasArquivo.size(); i++) {
		valorConsumo = obterConsumoKWh(linhasArquivo[i]);
		if (valorConsumo == -1) {
			setMensagemErro(MSGE_SINTAXE_INVALIDA + ES::intToStr((int)i + 1) + ITEM_LINHA + linhasArquivo[i]);
			return -1;
		}
		totalConsumo += valorConsumo;
	}

	return totalConsumo;
}



double ExtratorArquivoConsumo::obterConsumoKWh(const string & linhaDoConsumo) {
	vector<string> itemsLinha;
	double horas, watts;
	ES::quebrarTexto(itemsLinha, linhaDoConsumo, ESPACO);

	//A linha de consumo será lida de trás para frente, por isso armazena-se a última posição
	size_t posicao = itemsLinha.size() - 1;

	/*Valida se a linha tem os elementos minimos necessarios e no mesmo if se o
	* primeiro valor númerico (orrespondente a kWh ou h) é mesmo um número*/
	if (posicao < 2 || !ES::isNumber(itemsLinha[posicao - 1])) return -1;

	if (_strnicmp(itemsLinha[posicao].c_str(), KWH, itemsLinha[posicao].size()) == 0)
		return ES::strToDouble(itemsLinha[posicao - 1]);


	if (_strnicmp(itemsLinha[posicao].c_str(), H, itemsLinha[posicao].size()) == 0) {
		horas = ES::strToDouble(itemsLinha[--posicao]);
		
		if (_strnicmp(itemsLinha[--posicao].c_str(), W, itemsLinha[posicao].size()) == 0
			&& ES::isNumber(itemsLinha[posicao - 1])) {
		
			watts = ES::strToDouble(itemsLinha[posicao - 1]);

			return watts / 1000 * horas;
		}
	}

	return -1;
}
