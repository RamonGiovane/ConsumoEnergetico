#include "ExtratorDeDados.h"
#include "ConsumoEnergetico.h"
#include "EntradaESaida.h"
#include "ArquivoTexto\ArquivoTexto.h"
#include "Cliente.h"
#include <sstream>
#include <vector>



using namespace std;

ConsumoEnergetico::ConsumoEnergetico(){ }

int ConsumoEnergetico::iniciar() {
	
	ES::mudarLocalizacao();
	return menu();

}


int ConsumoEnergetico::interpretarComando(char * argumentos[]) {
	return 0;
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
	definirCaminhoPrograma(argumentos);
	ES::mudarLocalizacao();
	return interpretarComando(numeroArgumentos, argumentos);
}

string formatarCaminhoCompleto(const string & caminhoDiretorio, const string & nomeArquivo) {
	
	if (caminhoDiretorio == nomeArquivo) return caminhoDiretorio;
	
	string caminhoCompleto(caminhoDiretorio);

	if (caminhoCompleto[caminhoCompleto.size() - 1] != '\\')
		caminhoCompleto.append("\\");

	caminhoCompleto.append(nomeArquivo);
	return caminhoCompleto;
}
int ConsumoEnergetico::importarFaturas(vector<string> listaArquivos, const string & caminhoDiretorio) {
	int arquivosIgnorados = 0, arquivosLidos = 0;
	string caminhoCompleto;



	for (string arquivo : listaArquivos) {
		
		caminhoCompleto = formatarCaminhoCompleto(caminhoDiretorio, arquivo);

		cout << "\nLendo " + caminhoCompleto;
		if (!lerContaDigital(caminhoCompleto)) {
			cout << "\nIgnorando arquivo...\n\n";
			arquivosIgnorados++;
		}
		else {
			cout << "\nArquivo lido e importado com sucesso...\n\n";
			arquivosLidos++;
		}
	}
	cout << "\n\nA leitura terminou.\n" << arquivosLidos << " arquivo(s) lido(s) com sucesso.\n" << 
		arquivosIgnorados << " arquivo(s) com falha ignorado(s)." << endl << endl;

	return 1;

}

int ConsumoEnergetico::interpretarUmParametro(char * paramtero) {
	string caminhoDiretorio  = "C:\\Users\\ramon\\Desktop\\test_ground";
	vector<string> arquivos;
	if (ES::obterArquivosDiretorio(caminhoDiretorio, arquivos))
		return importarFaturas(arquivos, caminhoDiretorio);
		//return 1;
	if (!ES::isNumber(paramtero)) {
		cout << "\nCliente não localizado.\n";
		return 0;
	}

	//return pesquisarConsumo(paramtero);
	return 1;
}


int ConsumoEnergetico::interpretarComando(int numeroArgumentos, char * argumentos[]) {

	switch (numeroArgumentos) {
	case 2: 
		return interpretarUmParametro(argumentos[1]);
		break;
	case 3:
		//return pesquisaConsumo(argumentos[0], argumentos[1]);
		break;
	case 4:
		//return interpretarTresParametros(argumentos);
		break;
	
	default:
		exibirInformacao();
		break;
	}
	return 1;
}

int ConsumoEnergetico::menu()
{
	//exibirInformacao();
	string menu("\n1-Ler Conta Digital\n2-Exibir Programa\n3-Executar Programa\n4-Sair\n");
	int opcao;
	while (true) {
		cout << menu.c_str();
		opcao = ES::lerInteiro("\nEscolha: ");
		switch (opcao) {
		case 1:
			lerContaDigital("C:/Users/ramon/Desktop/corr.pdf");
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

bool ConsumoEnergetico::lerContaDigital(const string & caminhoArquivo) {

	Fatura f;
	if (!extrator.lerFaturaPDF(f, caminhoPrograma, caminhoArquivo)) { cout << extrator.getMensagemErro(); return false; }

	return true;

}


void ConsumoEnergetico::definirCaminhoPrograma(char * argv[]) {
	
	caminhoPrograma = argv[0];
	int i = caminhoPrograma.size()-1;
	cout << endl << caminhoPrograma;
	while (true) {
		if (caminhoPrograma[i--] == '\\') break;
		caminhoPrograma.pop_back();
	}
	
	
}



int main(int argc, char * argv[]) {
	

	cout << endl << "a" << endl;
	ConsumoEnergetico().iniciar(argc, argv);
	
	//return 1;
	ConsumoEnergetico().iniciar();
	return system("pause");
}
