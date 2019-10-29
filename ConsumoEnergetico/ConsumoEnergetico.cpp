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
			//lerPrograma(maquinaExecucao);
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
	string caminho = EntradaESaida::lerString("--Insira o caminho do arquivo---\n>>");
	EntradaESaida::removerArquivo(ConsumoEnergetico::ARQUIVO_SAIDA);
	cout << "\nO arquivo de saída será criado...";
	EntradaESaida::PDFToText(caminho, ConsumoEnergetico::ARQUIVO_SAIDA);
	return true;
}

int main() {
	return ConsumoEnergetico().iniciar();
}
