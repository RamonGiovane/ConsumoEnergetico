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

	int iniciar(int argc, char * argv[]);

private:

	int interpretarComando(int numeroArgumentos, char * argumentos[]);

	void exibirInformacao();

	void adicionarFaturaComFalha(const string & caminhoArquivo);

	int importarFaturas(vector<string> listaArquivos, string caminhoDiretorio);

	void relatorioImportacaoArquivos(int arquivosLidos, int arquivosIgnorados);

	bool importarFatura(const string & caminhoArquivo, bool printMensagemFinal = false, int tipoArquivo = TIPO_PDF);

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

	bool lerFaturaDigital(const string & caminhoArquivo, int tipoArquivo = TIPO_PDF);
	
	void definirCaminhoPrograma(char * argumentosMain[]);


	string relatorioArquivosIgnorados;

	string caminhoPrograma;

};


#endif // !CONSUMO__ENERGETICO_H

int main(int argc, char * argv[]);
