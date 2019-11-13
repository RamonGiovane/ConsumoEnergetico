#ifndef CONSUMO_ENERGETICO_H
#define CONSUMO_ENERGETICO_H
#include <string>
#include <vector>
#include "Cliente.h"
#include "Fatura.h"
using namespace std;

class ConsumoEnergetico
{

public:
	ConsumoEnergetico();

	int iniciar();
	int interpretarComando(int numeroArgumentos, char * argumentos[]);
	int interpretarComando(char * argumentos[]);
	void exibirInformacao();
	int iniciar(int argc, char * argv[]);

	//int importarFaturas(vector<string> listaArquivos);

	int importarFaturas(vector<string> listaArquivos, const string & caminhoDiretorio);

	void relatorioImportacaoArquivos(int arquivosLidos, int arquivosIgnorados);

	bool importarFatura(const string & caminhoArquivo, bool printMensagemFinal = false);

	int interpretarUmParametro(char * paramtero);

private:

	int menu();
	bool lerContaDigital(const string & caminhoArquivo);

	bool salvarDados(Fatura fatura);
	
	void definirCaminhoPrograma(char * argumentosMain[]);
	
	

	bool interpretarSaidaConversor(int codigoSaida);


	Fatura conta;

	ExtratorDeDados extrator;

	string caminhoPrograma;
};


#endif // !CONSUMO__ENERGETICO_H

int main(int argc, char * argv[]);
