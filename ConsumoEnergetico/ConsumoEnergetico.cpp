#include "ConsumoEnergetico.h"
#include "EntradaESaida.h"



ConsumoEnergetico::ConsumoEnergetico()
{

}

int ConsumoEnergetico::iniciar() {
	EntradaESaida::mudarLocalizacao();
	return menu();

}

int ConsumoEnergetico::menu()
{
	string menu("\n1-Ler Conta Digital\n2-Exibir Programa\n3-Executar Programa\n4-Sair\n");
	int opcao;
	while (true) {
		cout << menu.c_str();
		opcao = EntradaESaida::lerInteiro("\nEscolha: ");
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
	string caminho = EntradaESaida::lerString("Insira o caminho do arquivo PDF:\n>>");
		
	EntradaESaida::removerArquivo(ConsumoEnergetico::ARQUIVO_SAIDA);
	
	cout << "\nConvertendo PDF... ";
	if (!interpretarSaidaConversor(EntradaESaida::PDFToText(caminho, ConsumoEnergetico::ARQUIVO_SAIDA))) {
		cout << "\nA operação foi abortada." << endl << endl;
		return false;
	}

	cout << "\nLendo a conta digital...";
	//lerContaDigital()
	
	return true;
}


static const string SEM_ERROS = "Sucesso.";
static const string ERRO_ABRIR_ARQUIVO_PDF = "FALHA: O arquivo PDF informado não existe ou está corrompido.";
static const string ERRO_ABRIR_ARQUIVO_SAIDA = "FALHA: Não foi possível gerar os dados de saída";
static const string ERRO_DE_PERMISSAO = "FALHA: O programa não tem permissão para ler o arquivo PDF informado ou gerar os dados de saída.";
static const string ERRO_DESCONHECIDO = "FALHA: Um erro desconhecido ocorreu ao converter o arquivo PDF.";

bool ConsumoEnergetico::interpretarSaidaConversor(int codigoSaida) {
	switch (codigoSaida) {
	case EntradaESaida::CodigoDeSaida::SEM_ERROS:
		cout << SEM_ERROS;
		return true;
	case EntradaESaida::ERRO_ABRIR_ARQUIVO_PDF:
		cout << ERRO_ABRIR_ARQUIVO_PDF;
		return false;

	case EntradaESaida::ERRO_ABRIR_ARQUIVO_SAIDA:
		cout << ERRO_ABRIR_ARQUIVO_SAIDA;
		return false;

	case EntradaESaida::ERRO_DE_PERMISSAO:
		cout << ERRO_DE_PERMISSAO;
		return false;

	default:
		cout << ERRO_DESCONHECIDO;
		return false;
	}
	return false;
	
}

int main() {
	return ConsumoEnergetico().iniciar();
}
