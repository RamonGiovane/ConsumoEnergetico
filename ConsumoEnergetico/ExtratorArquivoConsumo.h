#ifndef EXTRATOR_ARQUIVO_CONSUMO
#define EXTRATOR_ARQUIVO_CONSUMO
#include "RelatorDeErros.h"
#include "Consumo.h"
#include <string>
#include <vector>

using namespace std;
class ExtratorArquivoConsumo : public RelatorDeErros
{

public:
	bool lerArquivoDeConsumo(Consumo & consumo, const string & numeroCliente, const string & caminhoArquivoEntrada);

	inline string getConteudoResposta() {
		return conteudoResposta;
	}

private:
	
	bool lerValidarCabecalhoArquivoDeConsumo(const string & linhaCabecalho, int & mes, int & ano);

	double calcularConsumo(const vector<string>& linhasArquivo, int mes, int ano);

	double obterConsumoKWh(const string & linhaDoConsumo);


	string conteudoResposta;
	
};


#endif // !EXTRATOR_ARQUIVO_CONSUMO



