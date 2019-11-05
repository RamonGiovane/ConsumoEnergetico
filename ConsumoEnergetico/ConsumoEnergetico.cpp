#include "ExtratorDeDados.h"
#include "ConsumoEnergetico.h"
#include "EntradaESaida.h"
#include "ArquivoTexto\ArquivoTexto.h"
#include "Cliente.h"
#include <sstream>
#include <vector>

ConsumoEnergetico::ConsumoEnergetico()
{

}

int ConsumoEnergetico::iniciar() {
	ES::mudarLocalizacao();
	return menu();

}


int ConsumoEnergetico::interpretarComando(char * argumentos[]) {
	return 1;
}

void ConsumoEnergetico::exibirInformacao() {
	cout << "CEE versão 0.1: Relatório de Consumo de Energia Elétrica" << endl;
	cout << "2019 Ramon Giovane https://github.com/RamonGiovane" << endl;


	cout << "uso:\n1. Importando uma fatura ou várias faturas da CEMIG\n\tcee <fatura> | <diretório> " << endl << endl;
	cout << "2. Pesquisa de consumo\n\tcee <numeroCliente> [mês e ano referente]\n\tExemplos:\n\t\tcee 8005243542\n\t\tcee 8005243542 set/2019" << endl << endl;
	cout << "3. Exibir histórico de consumo\n\tcee <numeroCliente> <mesAnoIncial> <mesAnoFinal>" << endl << endl;
	cout << "4. Cálculo de consumo de energia\n\tcee <numeroCliente> <mesAno> <arquivo>" << endl << endl;
	
	cout << "Mais informações em: https://github.com/RamonGiovane/ConsumoEnergetico" << endl;

}
int ConsumoEnergetico::iniciar(int numeroArgumentos, char * argumentos[]) {
	return interpretarComando(numeroArgumentos, argumentos);
}
int ConsumoEnergetico::interpretarComando(int numeroArgumentos, char * argumentos[]) {
	switch (numeroArgumentos) {
	case 1: 
		//return importarFaturas(argumentos[0]);
		break;
	case 2:
		//return pesquisaConsumo(argumentos[0], argumentos[1]);
		break;
	case 3:
		//return interpretarComando(argumentos);
		break;
	
	default:
		exibirInformacao();
		break;
	}
	return 1;
}

int ConsumoEnergetico::menu()
{
	exibirInformacao();
	string menu("\n1-Ler Conta Digital\n2-Exibir Programa\n3-Executar Programa\n4-Sair\n");
	int opcao;
	while (true) {
		cout << menu.c_str();
		opcao = ES::lerInteiro("\nEscolha: ");
		switch (opcao) {
		case 1:
			lerContaDigital();
			break;
		case 2:
			//exibirPrograma(maquinaExecucao);
			break;
		case 3:
			//executarPrograma(maquinaExecucao);
			break;
		case 4:
			return 1;
		default:
			break;
		}
	}
	return 0;
}

bool ConsumoEnergetico::lerContaDigital() {
	string caminho = ES::lerString("Insira o caminho do arquivo PDF:\n>>");
	
	ExtratorDeDados extrator;

	//caminho = "C:/Users/ramon/Desktop/fat.pdf";
	caminho = "C:/Users/Usuario/Desktop/fat.pdf";
	//A partir daqui, passar essas operações para o ExtratorDeDados

	//extrator.lerContaDigital(caminho);

	string conteudoConta;
	vector<string> linhasArquivo;
	const char  DELIMITADOR = '\n';

	ES::removerArquivo(ARQUIVO_SAIDA);

	cout << "\nConvertendo PDF... ";
	if (!interpretarSaidaConversor(ES::PDFToText(caminho, ARQUIVO_SAIDA))) {

		ES::exibirAbortarOperacao();
		return false;
	}

	cout << "\nLendo a conta digital... ";
	if (!extrator.lerArquivoTexto(conteudoConta)) {
		cout << "\nFALHA: O conteúdo da conta não pôde ser lido. Possivelmente o arquivo está corrompido.";
		ES::exibirAbortarOperacao();
		return false;
	}
	cout << "\nObtendo informações da conta... ";
	ES::quebrarTexto(linhasArquivo, conteudoConta, DELIMITADOR);
	if (extrator.obterInformacoes(linhasArquivo)) {

	}

	return true;
}


static const string SEM_ERROS = "Sucesso.";
static const string ERRO_ABRIR_ARQUIVO_PDF = "FALHA: O arquivo PDF informado não existe ou está corrompido.";
static const string ERRO_ABRIR_ARQUIVO_SAIDA = "FALHA: Não foi possível gerar os dados de saída";
static const string ERRO_DE_PERMISSAO = "FALHA: O programa não tem permissão para ler o arquivo PDF informado ou gerar os dados de saída.";
static const string ERRO_DESCONHECIDO = "FALHA: Um erro desconhecido ocorreu ao converter o arquivo PDF.";


bool ConsumoEnergetico::interpretarSaidaConversor(int codigoSaida) {
	switch (codigoSaida) {
	case ES::CodigoDeSaida::SEM_ERROS:
		cout << SEM_ERROS;
		return true;

	case ES::ERRO_ABRIR_ARQUIVO_PDF:
		cout << ERRO_ABRIR_ARQUIVO_PDF;
		return false;

	case ES::ERRO_ABRIR_ARQUIVO_SAIDA:
		cout << ERRO_ABRIR_ARQUIVO_SAIDA;
		return false;

	case ES::ERRO_DE_PERMISSAO:
		cout << ERRO_DE_PERMISSAO;
		return false;

	default:
		cout << ERRO_DESCONHECIDO;
		return false;
	}
	return false;

}

int main(int argc, char * argv[]) {
	//return ConsumoEnergetico().iniciar(argc, argv);
	return ConsumoEnergetico().iniciar();
}
