#include "ExtratorDeDados.h"
#include "CEE.h"
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

CEE::CEE() { }



int CEE::interpretarComando(char * argumentos[]) {
	return 0;
}

void CEE::exibirInformacao() {
	cout << "CEE versão 0.1: Relatório de Consumo de Energia Elétrica" << endl;
	cout << "2019 Ramon Giovane https://github.com/RamonGiovane" << endl;


	cout << "uso:\n1. Importando uma fatura ou várias faturas da CEMIG\n\tcee <fatura> | <diretório> " << endl << endl;
	cout << "2. Pesquisa de consumo\n\tcee <numeroCliente> [mês e ano referente]\n\tExemplos:\n\t\tcee 8005243542\n\t\tcee 8005243542 set/2019" << endl << endl;
	cout << "3. Exibir histórico de consumo\n\tcee <numeroCliente> <mesAnoIncial> <mesAnoFinal>" << endl << endl;
	cout << "4. Cálculo de consumo de energia\n\tcee <numeroCliente> <mesAno> <arquivo>" << endl << endl;

	cout << "Mais informações em: https://github.com/RamonGiovane/ConsumoEnergetico" << endl;

}
int CEE::iniciar(int numeroArgumentos, char * argumentos[]) {
	
	definirCaminhoPrograma(argumentos);
	
	//Define a localização para o Brasil
	ES::mudarLocalizacao();
	
	//Cria o diretório em que os arquivos binários ficarão
	ES::criarDiretorio("data");

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
/*Lê várias faturas PDF de um caminho especificado. É necessário a lista de arquivos do diretório e seu caminho absoluto,
para que eles sejam encontrados.
Exibe ao usuário os status da operações. Retorna true em caso de sucesso, false em falha.*/
int CEE::importarFaturas(vector<string> listaArquivos, const string & caminhoDiretorio) {
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

void CEE::relatorioImportacaoArquivos(int arquivosLidos, int arquivosIgnorados) {
	string arquivoLidoStr = " arquivo lido com sucesso.", arquivosLidosStr = " arquivos lidos com sucesso.";
	string arquivoIgnoradoStr = " arquivo com falha ignorado.", arquivosIgnoradosStr = " arquivos com falha ignorados.";

	cout << "\n\nA leitura terminou.\n" << arquivosLidos << (arquivosLidos == 1 ? arquivoLidoStr : arquivosLidosStr) <<
		endl << arquivosIgnorados << (arquivosIgnorados == 1 ? arquivoIgnoradoStr : arquivosIgnoradosStr) << endl << endl;
}

/*Lê uma fatura em PDF do caminho especificado. Exibe ao usuário os status da operações. Retorna true em caso de sucesso, false em falha.*/
bool CEE::importarFatura(const string & caminhoArquivo, bool printMensagemFinal) {
	cout << "\nLendo " + caminhoArquivo;
	if (!lerContaDigital(caminhoArquivo)) {
		cout << "\nIgnorando arquivo...\n\n";
		if (printMensagemFinal) relatorioImportacaoArquivos(0, 1);
		return false;
	}

	cout << "\nArquivo lido e importado com sucesso...\n\n";

	if (printMensagemFinal) relatorioImportacaoArquivos(1, 0);

	return true;
////
}

int CEE::interpretarUmParametro(char * paramtero) {
	string caminhoDiretorio = paramtero;

	cout << paramtero << endl;

	vector<string> arquivos;
	if (ES::obterArquivosDiretorio(caminhoDiretorio, arquivos)) {
		if (arquivos.empty())
			return importarFatura(caminhoDiretorio, true);
		return importarFaturas(arquivos, caminhoDiretorio);

	}
	return pesquisaConsumo(paramtero);
			

}

bool CEE::pesquisaConsumo(char * numeroCliente, char * mesAno) {
	Cliente * cliente = pesquisarCliente(numeroCliente);
	
	if (cliente == NULL) { cout << "\nCliente não localizado.\n";  return false; }

	
	ArquivoFatura arquivo;
	Fatura * fatura;

	arquivo.abrir(FILE_FATURA_DAT);

	int posicao = 0;
	int mes = 0, ano = 0;
	bool exibido = false;
	
	if (mesAno != NULL) {
		ES::strMesAnoToInt(mesAno, mes, ano);
		if (mes == 0 || ano == 0) {
			cout << "\nParâmetro de data inválido.\n";
			return false;
		}
	}
	
	exibirCliente(cliente);
	
	while (true) {
		posicao = arquivo.pesquisarFatura(numeroCliente, mes, ano, posicao);
		
		if (posicao == -1) break;

		fatura = arquivo.lerObjeto(posicao);
		exibirPesquisaConsumo(fatura);

		delete fatura;
		
		exibido = true;

		posicao++;
	}

	if (!exibido) cout << "\nNenhum dado de fatura foi encontrado para os termos pesquisados.";
	return exibido;
}

void CEE::exibirPesquisaConsumo(Fatura * fatura) {
	cout << endl << "Consumo da Instalação Nº " << fatura->getNumeroInstalacao() << ": " << fatura->getValoresFaturados().getConsumo() << " kWh";
	cout << endl << "Valor a pagar: R$ " << fatura->getValorAPagar() << " | Data de Vencimento: " << fatura->getDataVencimento();
	cout << endl << "Referente a: " << ES::mesToStr(fatura->getMesReferente()) << " de " << fatura->getAnoReferente() << endl;
}

void CEE::exibirCliente(Cliente * cliente) {
	cout << endl << "|| Pesquisando dados do cliente:" << endl << cliente->toString() << endl;

}

Cliente* CEE::pesquisarCliente(const string & numeroCliente) {
	ArquivoCliente arquivo;
	
	arquivo.abrir(FILE_CLIENTE_DAT);
	
	int registro = arquivo.pesquisarCliente(numeroCliente);
	if (registro == -1) return NULL;
	
	return arquivo.lerObjeto(registro);

}

int CEE::interpretarComando(int numeroArgumentos, char * argumentos[]) {

	switch (numeroArgumentos) {
	case 2:
		return interpretarUmParametro(argumentos[1]);
		break;
	case 3:
		return pesquisaConsumo(argumentos[1], argumentos[2]);
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


bool CEE::lerContaDigital(const string & caminhoArquivo) {

	Fatura f;
	if (!extrator.lerFaturaPDF(f, caminhoPrograma, caminhoArquivo)) { cout << extrator.getMensagemErro(); return false; }

	//salvarDados(f);

	ArquivoCliente arquivoCliente;
	arquivoCliente.abrir(FILE_CLIENTE_DAT);

	return salvarDados(f);

}
bool CEE::salvarDados(Fatura fatura) {
	
	ArquivoFatura arquivoFatura;
	arquivoFatura.abrir(FILE_FATURA_DAT);
	
	int registro = arquivoFatura.pesquisarFatura(fatura.getCliente().getNumero(),
		fatura.getMesReferente(), fatura.getAnoReferente());
	
	if (registro == -1) {
		arquivoFatura.escreverObjeto(fatura);
		return true;
	}
	cout << endl << "Esta fatura já foi importada anteriormente.";

	arquivoFatura.fechar();

	ArquivoHistorico arquivoHistorico;
	arquivoHistorico.abrir(FILE_HISTORICO_DAT);
	int reg = arquivoHistorico.pesquisarHistorico(fatura.getCliente().getNumero());

	return false;
}

int mesAnoEmNumeroUnico(const string & mesAno) {
	int mes, ano;
	ES::strMesAnoToInt(mesAno, mes, ano);
	return ano * 100 + mes;
}

void CEE::definirCaminhoPrograma(char * argv[]) {

	caminhoPrograma = argv[0];
	int i = caminhoPrograma.size() - 1;

	while (true) {
		if (caminhoPrograma[i--] == '\\') break;
		caminhoPrograma.pop_back();
	}


}

int main(int argc, char * argv[]) {

	CEE().iniciar(argc, argv);

	return system("pause");
}
