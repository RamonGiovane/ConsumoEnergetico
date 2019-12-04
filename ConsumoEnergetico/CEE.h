#ifndef CONSUMO_ENERGETICO_H
#define CONSUMO_ENERGETICO_H
#include <string>
#include <vector>
#include "Cliente.h"
#include "Fatura.h"
#include "Constantes.h"
using namespace std;

class CEE
{

public:
	CEE();

	int interpretarComando(int numeroArgumentos, char * argumentos[]);
	
	void exibirInformacao();
	int iniciar(int argc, char * argv[]);

	void adicionarFaturaComFalha(const string & caminhoArquivo);

	int importarFaturas(vector<string> listaArquivos, string caminhoDiretorio);

	void relatorioImportacaoArquivos(int arquivosLidos, int arquivosIgnorados);

	bool importarFatura(const string & caminhoArquivo, bool printMensagemFinal = false, int tipoArquivo = TIPO_PDF);

	//bool importarFatura(const string & caminhoArquivo, bool printMensagemFinal = false);

	int promptImportarFaturas();

	int interpretarUmParametro(char * paramtero);
	
	int interpretarTresParametros(char * paramtero1, char * paramtero2, char * paramtero3);

	int interpretarDoisParametros(char * parametro1, char * parametro2);

	bool calcularConsumoDeEnergia(char * numeroCliente, char * mesAno, char * arquivoEntrada);

	bool pesquisaHistoricoConsumo(char * numeroCliente, char * mesAnoInicial, char * mesAnoFinal);

	bool exibirHistorico(const vector<Consumo>& historico, char * mesAnoInicial, char * mesAnoFinal);
	
	bool verificarXPDF();

	bool pesquisaConsumo(char * numeroCliente, char * mesAno = NULL);

	void exibirPesquisaConsumo(Fatura * fatura);

	void exibirCliente(Cliente * cliente);

	bool pesquisarExibirCliente(const string & numeroCliente);



private:


	bool lerContaDigital(const string & caminhoArquivo, int tipoArquivo = TIPO_PDF);

	bool salvarDados(Fatura fatura);
	
	void definirCaminhoPrograma(char * argumentosMain[]);


	Fatura conta;

	ExtratorDeFaturas extrator;

	string relatorioArquivosIgnorados;

	string caminhoPrograma;
};


#endif // !CONSUMO__ENERGETICO_H

int main(int argc, char * argv[]);
