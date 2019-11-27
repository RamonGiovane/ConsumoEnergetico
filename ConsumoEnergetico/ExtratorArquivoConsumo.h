#ifndef EXTRATOR_ARQUIVO_CONSUMO
#define EXTRATOR_ARQUIVO_CONSUMO
#include "RelatorDeErros.h"
#include "Consumo.h"
#include "ArquivoHistorico.h"
#include "ArquivoFatura.h"
#include <string>
#include <vector>

using namespace std;
class ExtratorArquivoConsumo : public RelatorDeErros
{

public:

	bool lerArquivoDeConsumo(const string & numeroCliente, const string & caminhoArquivoEntrada, char * mesAno);

	inline string getConteudoResposta() {
		return conteudoResposta;
	}

	inline ~ExtratorArquivoConsumo() {
		arquivoHistorico.fechar();
		arquivoFatura.fechar();
	}

private:
	bool lerArquivoDeConsumo(const string & numeroCliente, const string & caminhoArquivoEntrada, int mesFatura, int anoFatura);

	bool interpretarArquivoDeConsumo(vector<string>& linhas, const string & numeroCliente, int mesFatura, int anoFatura);

	double procurarPrecoEnergia(Consumo & consumo);

	bool gerarResultados(vector<Consumo> consumosMesAnoArquivo, vector<Consumo> consumoMesAnoSintaxe, double consumoCalculado);

	bool procurarConsumosDoCliente(vector<Consumo>& consumos, const string & numeroCliente, int mes, int ano);

	bool lerValidarCabecalhoArquivoDeConsumo(const string & linhaCabecalho, int & mes, int & ano);

	double calcularConsumo(const vector<string>& linhasArquivo, int mes, int ano);

	double obterConsumoKWh(const string & linhaDoConsumo);


	string conteudoResposta;

	ArquivoHistorico arquivoHistorico;

	ArquivoFatura arquivoFatura;
	
};


#endif // !EXTRATOR_ARQUIVO_CONSUMO



