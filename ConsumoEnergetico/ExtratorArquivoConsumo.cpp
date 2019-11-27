#include "ExtratorArquivoConsumo.h"
#include "ArquivoHistorico.h"
#include "Consumo.h"
#include "EntradaESaida.h"
#include "Constantes.h"
#include <vector>
#include <string>

using namespace std;

bool ExtratorArquivoConsumo::lerArquivoDeConsumo(const string & numeroCliente, const string & caminhoArquivoEntrada, char * mesAno) {
	int mes, ano;
	ES::strMesAnoToInt(mesAno, mes, ano);
	return lerArquivoDeConsumo(numeroCliente, caminhoArquivoEntrada, mes, ano);
}
bool ExtratorArquivoConsumo::lerArquivoDeConsumo(const string & numeroCliente, const string & caminhoArquivoEntrada, int mesFatura, int anoFatura) {
	string textoArquivo;

	Consumo consumoDoMes;
	ES::lerArquivoTexto(textoArquivo, caminhoArquivoEntrada);

	if (textoArquivo == SNULL) return erro(MSGE_ARQUIVO_ENTRADA);

	vector<string> linhas;
	ES::quebrarTexto(linhas, textoArquivo, BARRA_N);
	if (linhas.empty()) { return erro(MSGE_ARQUIVO_ENTRADA); }

	return interpretarArquivoDeConsumo(linhas, numeroCliente, mesFatura, anoFatura);
}

bool ExtratorArquivoConsumo::interpretarArquivoDeConsumo(vector<string> & linhas, const string & numeroCliente, int mesFatura, int anoFatura) {
	int mesArquivo, anoArquivo;

	Consumo consumoArquivo;
	vector<Consumo> consumosMesAnoArquivo, consumosMesAnoSintaxe;

	if (!lerValidarCabecalhoArquivoDeConsumo(linhas[0], mesArquivo, anoArquivo)) return false;

	double consumoCalculado = calcularConsumo(linhas, mesArquivo, anoArquivo);
	if (consumoCalculado == -1) return false;


	consumoArquivo.setConsumoKWh(consumoCalculado);
	
	//Procurando consumos do mês e ano fornecidos no arquivo de entrada
	if (!procurarConsumosDoCliente(consumosMesAnoArquivo, numeroCliente, mesArquivo, anoArquivo))
		return erro("\nFALHA: Não há dados de consumo deste cliente para o mês/ano fornecidos no arquivo de entrada: " + mesArquivo + BARRA + anoArquivo);

	//Procurando consumos do mês e ano fornecidos na sintaxe do programa
	if (!procurarConsumosDoCliente(consumosMesAnoSintaxe, numeroCliente, mesArquivo, anoArquivo))
		return erro("\nFALHA: Não há dados de consumo deste cliente para o mês/ano fornecidos nos parâmetros de entrada do programa: " + mesArquivo + BARRA + anoArquivo);

	ES::organizarConsumos(consumosMesAnoSintaxe);
	ES::organizarConsumos(consumosMesAnoArquivo);

	return gerarResultados(consumosMesAnoArquivo, consumosMesAnoSintaxe, consumoCalculado);

}

//bool ExtratorArquivoConsumo::calcularDadosConsumo(Consumo & consumoResposta, Consumo consumo, double consumoKWhCalculado) {
//	consumoResposta.setDias(consumo.getDias());
//	consumoResposta.setConsumoKWh(consumoKWhCalculado);
//	consumoResposta.setMediaConsumoDiario(consumoKWhCalculado / consumo.getDias());
//	consumo.
//}

double calcularMediaDiaria(double consumo, int diasFaturados) {
	return diasFaturados == 0 ? 0 : consumo / diasFaturados;
}

double obterValorConsumoEletrico(Consumo consumo) {
	static int valorConsumo = 0;
	return 0;
}
const char STR_CONSUMO_MENSAL[] = "\n  Consumo mensal: ";
const char STR_CONSUMO_DIARIO[] = "\n  Consumo médio diário: ";
const char STR_VALOR_CONSUMO[] = "\n  Valor do consumo elétrico: ";
const char STR_NUMERO_DIAS[] = "\n  Número de dias: ";
const char STR_DADOS_FATURA_EM[] = " >> Dados da fatura Cemig em ";
const char STR_DADOS_CALCULADOS[] = ">> Dados calculados para ";
const char RS[] = "R$ ";

string gerarResultado(Consumo consumo, bool valorConsumoEnergia = false) {
	double consumoKwH = consumo.getConsumoKWh();
	int dias = consumo.getDias();
	static double valorConsumo = 0;
	valorConsumo = valorConsumoEnergia ? obterValorConsumoEletrico(consumo) : valorConsumo;

	return STR_CONSUMO_MENSAL + ES::doubleToStr(consumoKwH) + KWH +
		//calcular media fora desse metodo
		STR_CONSUMO_DIARIO + ES::doubleToStr(calcularMediaDiaria(consumoKwH, dias)) + KWH +
		STR_VALOR_CONSUMO  + ES::doubleToStr(valorConsumo) + KWH +
		STR_NUMERO_DIAS + RS + ES::doubleToStr(valorConsumo);
}
bool compararConsumos(Consumo c1, Consumo c2) {
	return c1.getNumeroInstalacao() == c1.getNumeroInstalacao() && c1.getAno() == c2.getAno() && c1.getMes() == c2.getMes();
}
bool gerarResultado(Consumo consumoArquivo, Consumo consumoFatura) {

	string r = STR_DADOS_FATURA_EM + ES::mesToStr(consumoFatura.getMes()) + BARRA + ES::intToStr(consumoFatura.getAno());
	r += gerarResultado(consumoFatura);
	
	string r = STR_DADOS_CALCULADOS + ES::mesToStr(consumoArquivo.getMes()) + BARRA + ES::intToStr(consumoArquivo.getAno());
	r += gerarResultado(consumoArquivo, compararConsumos(consumoArquivo, consumoFatura));

	

}

bool ExtratorArquivoConsumo::gerarResultados(vector<Consumo> consumosMesAnoArquivo, vector<Consumo> consumoMesAnoSintaxe, double consumoCalculado) {
	int posicaoConsumosArquivo = 0, posicaoConsumosFaturas = 0;
	string numeroInstalacao;
	while (true) {
		
		
		if (posicaoConsumosArquivo < consumoMesAnoSintaxe.size()) {
			numeroInstalacao = consumoMesAnoSintaxe[posicaoConsumosFaturas].getNumeroInstalacao();
			adicionarConteudoResposta(SUBTITLE_INSTALACAO);

		}

		
			
	}
}

bool ExtratorArquivoConsumo::procurarConsumosDoCliente(vector<Consumo> & consumos, const string & numeroCliente, int mes, int ano) {

	if (!arquivo.abrir(FILE_HISTORICO_DAT) ||
		!arquivo.obterHistoricoConsumo(consumos, numeroCliente, mes, ano)) return false;
	
	return true;

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
