#include "ExtratorArquivoConsumo.h"
#include "ArquivoHistorico.h"
#include "Consumo.h"
#include "EntradaESaida.h"
#include "Constantes.h"
#include "ArquivoFatura.h"
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

bool ExtratorArquivoConsumo::calcularConsumosArquivo(vector<Consumo> & consumos, double consumoArquivoCalculado, const string & numeroCliente, int mes, int ano) {
	
	if (!procurarConsumosDoCliente(consumos, numeroCliente, mes, ano))
		return erro( SEM_DADOS_INPUT_FILE + ES::mesToStr(mes)  + BARRA + ES::intToStr(ano));

	for (Consumo & c : consumos) {
		c.setConsumoKWh(consumoArquivoCalculado);
		c.setMediaConsumoDiario(calcularMediaDiaria(consumoArquivoCalculado, c.getDias()));
	}
	return true;

	
}

bool ExtratorArquivoConsumo::interpretarArquivoDeConsumo(vector<string> & linhas, const string & numeroCliente, int mesFatura, int anoFatura) {
	int mesArquivo, anoArquivo;
	
	//Consumos de todas as instalações do cliente para os mes/ano passados no arquivo e na sintaxe dos programa 
	vector<Consumo> consumosMesAnoArquivo, consumosMesAnoFaturas;

	if (!lerValidarCabecalhoArquivoDeConsumo(linhas[0], mesArquivo, anoArquivo)) return false;

	double consumoCalculado = calcularConsumo(linhas, mesArquivo, anoArquivo);
	if (consumoCalculado == -1) return false;

	
	//Procurando consumos do mês e ano fornecidos no arquivo de entrada
	if (!calcularConsumosArquivo(consumosMesAnoArquivo, consumoCalculado, numeroCliente, mesArquivo, anoArquivo))
		return false;
	
	
	//Procurando consumos do mês e ano fornecidos na sintaxe do programa
	if (!procurarConsumosDoCliente(consumosMesAnoFaturas, numeroCliente, mesFatura, anoFatura))
		return erro(SEM_DADOS_INPUT_SINTAX + ES::mesToStr(mesFatura) + BARRA + ES::intToStr(anoFatura));

	ES::organizarConsumos(consumosMesAnoFaturas);
	ES::organizarConsumos(consumosMesAnoArquivo);

	return gerarResultados(consumosMesAnoArquivo, consumosMesAnoFaturas, consumoCalculado);

}

double ExtratorArquivoConsumo::calcularMediaDiaria(double consumo, int diasFaturados) {
	return diasFaturados == 0 ? 0 : consumo / diasFaturados;
}

double ExtratorArquivoConsumo::obterValorConsumoEletrico(Consumo consumo, bool calcularConsumo) {
	
	Fatura *f = procurarFatura(consumo);
	double valor;
	if (f == NULL) return -1;

	if (!calcularConsumo) valor =  f->getValoresFaturados().getValorDaFatura();

	else 
		valor =  f->getValoresFaturados().getPreco()  * consumo.getConsumoKWh();
	

	delete f;
	return valor;
}

Fatura * ExtratorArquivoConsumo::procurarFatura(Consumo & consumo) {

	arquivoFatura.abrir(FILE_FATURA_DAT);
	Fatura * f =
		arquivoFatura.obterFatura(consumo.getMes(), consumo.getAno(), consumo.getNumeroInstalacao());
	
	return f;
	
}

string ExtratorArquivoConsumo::gerarResultado(Consumo consumo, bool calcularConsumo = false) {
	double consumoKwH = consumo.getConsumoKWh();
	int dias = consumo.getDias();
	double valorConsumo =  obterValorConsumoEletrico(consumo, calcularConsumo);
	string valorConsumoStr;
	if (valorConsumo == -1)
		valorConsumoStr = PRECO_ENERGIA_INDISPONIVEL;
	else valorConsumoStr = RS + ES::doubleToStr(valorConsumo);

	return STR_CONSUMO_MENSAL + ES::doubleToStr(consumoKwH) + STR_KWH +
		STR_CONSUMO_DIARIO + ES::doubleToStr(consumo.getMediaConsumoDiario()) + STR_KWH +
		STR_VALOR_CONSUMO  + valorConsumoStr +
		STR_NUMERO_DIAS + ES::intToStr(consumo.getDias());
}
bool compararConsumos(Consumo c1, Consumo c2) {
	return c1.getNumeroInstalacao() == c1.getNumeroInstalacao() && c1.getAno() == c2.getAno() && c1.getMes() == c2.getMes();
}

string ExtratorArquivoConsumo::gerarStringResultado(Consumo *consumoFatura, Consumo *consumoArquivo) {

	string r;
	
	
	if (consumoArquivo != NULL) {
		r = STR_DADOS_FATURA_EM + ES::mesToStr(consumoFatura->getMes()) + BARRA + ES::intToStr(consumoFatura->getAno());
		r += gerarResultado(*consumoFatura);
	}
	else r = STR_SEM_DADOS;
	
	r += BARRA_N;

	if (consumoFatura != NULL) {
		r += STR_DADOS_CALCULADOS + ES::mesToStr(consumoArquivo->getMes()) + BARRA + ES::intToStr(consumoArquivo->getAno());
		r += gerarResultado(*consumoArquivo, true);
	}
	else r += STR_SEM_DADOS;

	return r + BARRA_N;

}

bool ExtratorArquivoConsumo::gerarResultados(vector<Consumo> consumosMesAnoArquivo, vector<Consumo> consumoMesAnoSintaxe, double consumoCalculado) {
	unsigned posConsumosArquivo = 0, posConsumosFaturas = 0;
	size_t sizeConsumosArquivo = consumosMesAnoArquivo.size(), sizeConsumosFaturas = consumoMesAnoSintaxe.size();

	string numeroInstalacao;
	Consumo* c1 = NULL, *c2 = NULL;
	
	while (true) {
		
		bool numeroDaInstalcaoRevelado = false;

		if (posConsumosFaturas < sizeConsumosFaturas ) {
			c1 = &consumoMesAnoSintaxe[posConsumosFaturas];
			posConsumosFaturas++;
			adicionarConteudoResposta(SUBTITLE_INSTALACAO + c1->getNumeroInstalacao());
			numeroDaInstalcaoRevelado = true;
		}
		else c1 = NULL;
		
		
		if (posConsumosArquivo < sizeConsumosArquivo) {
			if (c1 == NULL || c1->getNumeroInstalacao() == consumosMesAnoArquivo[posConsumosArquivo].getNumeroInstalacao()) {
				c2 = &consumosMesAnoArquivo[posConsumosArquivo];
				posConsumosArquivo++;

				if(!numeroDaInstalcaoRevelado)
					adicionarConteudoResposta(SUBTITLE_INSTALACAO + c2->getNumeroInstalacao());
			}
		}
		else c2 = NULL;

		adicionarConteudoResposta(gerarStringResultado(c1, c2));

		if (posConsumosArquivo == sizeConsumosArquivo && sizeConsumosFaturas == sizeConsumosFaturas)
			break;
			
	}
	
	return true;
}

bool ExtratorArquivoConsumo::procurarConsumosDoCliente(vector<Consumo> & consumos, const string & numeroCliente, int mes, int ano) {

	if (!arquivoHistorico.abrir(FILE_HISTORICO_DAT) ||
		!arquivoHistorico.obterHistoricoConsumo(consumos, numeroCliente, mes, ano)) return false;
	
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

			return horas == 0 ? 0 : watts / 1000 * horas;
		}
	}

	return -1;
}

void ExtratorArquivoConsumo::adicionarConteudoResposta(const string & conteudo) {
	conteudoResposta.append(conteudo);
}
