#include "ExtratorDeDados.h"
#include "ConsumoEnergetico.h"
#include "EntradaESaida.h"
#include "ArquivoTexto\ArquivoTexto.h"
#include "ArquivoCliente.h"
#include "ArquivoFatura.h"
#include "Cliente.h"
#include "Constantes.h"

#include "ArquivoHistorico.h"

#include <string>
#include <vector>


using namespace std;

ConsumoEnergetico::ConsumoEnergetico() { }

int ConsumoEnergetico::iniciar() {

	ES::mudarLocalizacao();
	return menu();

}


int ConsumoEnergetico::interpretarComando(char * argumentos[]) {
	return 0;
}

void ConsumoEnergetico::exibirInformacao() {
	cout << "CEE vers�o 0.1: Relat�rio de Consumo de Energia El�trica" << endl;
	cout << "2019 Ramon Giovane https://github.com/RamonGiovane" << endl;


	cout << "uso:\n1. Importando uma fatura ou v�rias faturas da CEMIG\n\tcee <fatura> | <diret�rio> " << endl << endl;
	cout << "2. Pesquisa de consumo\n\tcee <numeroCliente> [m�s e ano referente]\n\tExemplos:\n\t\tcee 8005243542\n\t\tcee 8005243542 set/2019" << endl << endl;
	cout << "3. Exibir hist�rico de consumo\n\tcee <numeroCliente> <mesAnoIncial> <mesAnoFinal>" << endl << endl;
	cout << "4. C�lculo de consumo de energia\n\tcee <numeroCliente> <mesAno> <arquivo>" << endl << endl;

	cout << "Mais informa��es em: https://github.com/RamonGiovane/ConsumoEnergetico" << endl;

}
int ConsumoEnergetico::iniciar(int numeroArgumentos, char * argumentos[]) {
	cout << endl;
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
/*L� v�rias faturas PDF de um caminho especificado. � necess�rio a lista de arquivos do diret�rio e seu caminho absoluto,
para que eles sejam encontrados.
Exibe ao usu�rio os status da opera��es. Retorna true em caso de sucesso, false em falha.*/
int ConsumoEnergetico::importarFaturas(vector<string> listaArquivos, const string & caminhoDiretorio) {
	int arquivosIgnorados = 0, arquivosLidos = 0;
	string caminhoCompleto;

	for (string arquivo : listaArquivos) {
		caminhoCompleto = formatarCaminhoCompleto(caminhoDiretorio, arquivo);
		if (importarFatura(caminhoCompleto))
			arquivosLidos++;
		else arquivosIgnorados++;
	}

	relatorioImportacaoArquivos(arquivosLidos, arquivosIgnorados);

	return arquivosIgnorados;

}

void ConsumoEnergetico::relatorioImportacaoArquivos(int arquivosLidos, int arquivosIgnorados) {
	string arquivoLidoStr = " arquivo lido com sucesso.", arquivosLidosStr = " arquivos lidos com sucesso.";
	string arquivoIgnoradoStr = " arquivo com falha ignorado.", arquivosIgnoradosStr = " arquivos com falha ignorados.";

	cout << "\n\nA leitura terminou.\n" << arquivosLidos << (arquivosLidos == 1 ? arquivoLidoStr : arquivosLidosStr) <<
		endl << arquivosIgnorados << (arquivosIgnorados == 1 ? arquivoIgnoradoStr : arquivosIgnoradosStr) << endl << endl;
}

/*L� uma fatura em PDF do caminho especificado. Exibe ao usu�rio os status da opera��es. Retorna true em caso de sucesso, false em falha.*/
bool ConsumoEnergetico::importarFatura(const string & caminhoArquivo, bool printMensagemFinal) {
	cout << "\nLendo " + caminhoArquivo;
	if (!lerContaDigital(caminhoArquivo)) {
		cout << "\nIgnorando arquivo...\n\n";
		if (printMensagemFinal) relatorioImportacaoArquivos(0, 1);
		return false;
	}

	cout << "\nArquivo lido e importado com sucesso...\n\n";

	if (printMensagemFinal) relatorioImportacaoArquivos(1, 0);

	return true;

}

int ConsumoEnergetico::interpretarUmParametro(char * paramtero) {
	string caminhoDiretorio = paramtero;

	cout << paramtero << endl;
	//string caminhoDiretorio = "AAA.";

	vector<string> arquivos;
	if (ES::obterArquivosDiretorio(caminhoDiretorio, arquivos)) {
		if (arquivos.empty())
			return importarFatura(caminhoDiretorio, true);
		return importarFaturas(arquivos, caminhoDiretorio);

	}
	if (!ES::isNumber(paramtero)) {
		cout << "\nCliente n�o localizado.\n";
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

	//salvarDados(f);

	ArquivoCliente arquivoCliente;
	arquivoCliente.abrir("Cliente.dat");
	//arquivoCliente.escreverObjeto(f.getCliente());

	
	//Cliente* c = arquivoCliente.lerObjeto(arquivoCliente.pesquisarCliente("7008637570"));

	//if (c == NULL) cout << endl << "Null";

	//cout << c << endl;
	//cout << c->getNome() << endl;
	//cout << c->toString();
	//system("pause");

	return salvarDados(f);

}
bool ConsumoEnergetico::salvarDados(Fatura fatura) {
	
	ArquivoFatura arquivoFatura;
	arquivoFatura.abrir(ARQUIVO_FATAURA);
	
	int registro = arquivoFatura.pesquisarFatura(fatura.getCliente().getNumero(),
		fatura.getMesReferente(), fatura.getAnoReferente());
	
	if (registro == -1) {
		arquivoFatura.escreverObjeto(fatura);
		return true;
	}
	cout << endl << "Esta fatura j� foi importada anteriormente.";

	arquivoFatura.fechar();

	ArquivoHistorico arquivoHistorico;
	arquivoHistorico.abrir(ARQUIVO_HISTORICO_CONSUMO);
	int reg = arquivoHistorico.pesquisarHistorico(fatura.getCliente().getNumero());

	return false;
}

int mesAnoEmNumeroUnico(const string & mesAno) {
	int mes, ano;
	ES::strMesAnoToInt(mesAno, mes, ano);
	return ano * 100 + mes;
}

void ConsumoEnergetico::definirCaminhoPrograma(char * argv[]) {

	caminhoPrograma = argv[0];
	int i = caminhoPrograma.size() - 1;

	while (true) {
		if (caminhoPrograma[i--] == '\\') break;
		caminhoPrograma.pop_back();
	}


}



int main(int argc, char * argv[]) {

	ConsumoEnergetico().iniciar(argc, argv);

	//return 1;
	ConsumoEnergetico().iniciar();
	return system("pause");
}
