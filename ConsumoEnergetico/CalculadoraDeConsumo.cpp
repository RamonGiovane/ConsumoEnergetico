#include "CalculadoraDeConsumo.h"
#include "Consumo.h"
#include "ArquivoHistorico.h"
#include "Constantes.h"
#include "EntradaESaida.h"
#include <string>
#include <vector>

using namespace std;

CalculadoraDeConsumo::CalculadoraDeConsumo()
{
}


CalculadoraDeConsumo::~CalculadoraDeConsumo()
{
}



bool gerarDadosConsumo(Consumo * consumo, const string & numeroInstalacao, int dias, int mes, int ano) {
	ArquivoHistorico arquivo;
	arquivo.abrir(FILE_HISTORICO_DAT);

	int registro = arquivo.pesquisarConsumoNoHistorico(numeroInstalacao, mes, ano);
	if (registro == -1) return false;
	consumo = arquivo.lerObjeto(registro);

	return true;

}

double CalculadoraDeConsumo::calcularConsumo(const vector<string> & linhasArquivo, int mes, int ano) {
	double valorConsumo, totalConsumo = 0;

	for (size_t i = 1; i < linhasArquivo.size(); i++) {
		valorConsumo = obterConsumoKWh(linhasArquivo[i]);
		if (valorConsumo == -1) {
			mensagemErro = MSGE_SINTAXE_INVALIDA + ES::intToStr((int)i + 1) + "\n\t>> " + linhasArquivo[i];
			return -1;
		}
		totalConsumo += valorConsumo;
	}

	return totalConsumo;
}

double CalculadoraDeConsumo::obterConsumoKWh(const string & linhaDoConsumo) {
	vector<string> itemsLinha;
	double horas, watts;
	ES::quebrarTexto(itemsLinha, linhaDoConsumo, ' ');

	//A linha de consumo será lida de trás para frente, por isso armazena-se a última posição
	size_t posicao = itemsLinha.size() - 1;

	/*Valida se a linha tem os elementos minimos necessarios e no mesmo if se o
	* primeiro valor númerico (kWh ou h) é mesmo um número*/
	if (posicao < 2 || !ES::isNumber(itemsLinha[posicao - 1])) return -1;

	if (itemsLinha[posicao] == "kWh")
		return ES::strToDouble(itemsLinha[posicao - 1]);


	if (itemsLinha[posicao] == "h") {
		horas = ES::strToDouble(itemsLinha[--posicao]);
		if (itemsLinha[--posicao] == "w" && ES::isNumber(itemsLinha[posicao - 1])) {
			watts = ES::strToDouble(itemsLinha[posicao - 1]);

			return watts / 1000 * horas;
		}
	}

	return -1;
}
