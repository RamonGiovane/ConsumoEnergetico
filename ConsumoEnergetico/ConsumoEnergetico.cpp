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

	caminho = "C:/Users/ramon/Desktop/corr.pdf";
	string c1 = "C:/Users/ramon/Downloads/FaturaCEMIG_22112019.pdf";
	//caminho = "C:/Users/Usuario/Desktop/fat.pdf";


	Fatura f = extrator.lerFaturaPDF(caminho);
	Fatura f2  = extrator.lerFaturaPDF(c1);

	cout << f.toString();

	cout << f2.toString();


	return true;
}




int main(int argc, char * argv[]) {
	//return ConsumoEnergetico().iniciar(argc, argv);
	return ConsumoEnergetico().iniciar();
}
