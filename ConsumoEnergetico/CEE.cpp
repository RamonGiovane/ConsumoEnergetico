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

int CEE::interpretarUmParametro(char * parametro) {
	string caminhoDiretorio = parametro;

	vector<string> arquivos;
	if (ES::obterArquivosDiretorio(caminhoDiretorio, arquivos)) {
		if (!verificarXPDF()) return false;
		if (arquivos.empty())
			return importarFatura(caminhoDiretorio, true);
		return importarFaturas(arquivos, caminhoDiretorio);

	}
	return pesquisaConsumo(parametro);

}

int CEE::interpretarTresParametros(char * parametro1, char * parametro2, char * parametro3)
{
	//Se o parametro tres é um arquivo...
	if (ES::arquivoExiste(parametro3)) 
		return calcularConsumoDeEnergia(parametro1, parametro2, parametro3);
	
	//Senão, tenta outra operação...
	return pesquisaHistoricoConsumo(parametro1, parametro2, parametro3);

}


bool CEE::calcularConsumoDeEnergia(char * numeroCliente, char * mesAno, char * arquivoEntrada) {
	ExtratorDeDados extrator;
	Consumo consumo;
	if (!extrator.lerArquivoDeConsumo(consumo, numeroCliente, arquivoEntrada)) {
		cout << endl << extrator.getMensagemErro();
		return false;
	}
	return true;
}
bool CEE::pesquisaHistoricoConsumo(char * numeroCliente, char * mesAnoInicial, char * mesAnoFinal) {
	int mesInicial, anoInicial, mesFinal, anoFinal;
	
	if (!ES::strMesAnoToInt(mesAnoInicial, mesInicial, anoInicial) ||
		!ES::strMesAnoToInt(mesAnoFinal, mesFinal, anoFinal)) {
		cout << MSG_DATA_INVALIDA;
		return false;
	}

	if(!pesquisarExibirCliente(numeroCliente)) return false;

	ArquivoHistorico arquivo;
	vector<Consumo> historico;
	
	arquivo.abrir(FILE_HISTORICO_DAT);
	
	arquivo.obterHistoricoConsumo(historico, numeroCliente, mesInicial, anoInicial, mesFinal, anoFinal);
	
	organizarHistorico(historico);

	exibirHistorico(historico, mesAnoInicial, mesAnoFinal);

	arquivo.fechar();

	return true;
}

bool CEE::exibirHistorico(const vector<Consumo> & historico, char * mesAnoInicial, char * mesAnoFinal) {
	
	cout << "\n|| Histórico de consumo de " << mesAnoInicial << " a " << mesAnoFinal << ":";
	
	if (historico.empty()) cout << "\n" << MSG_DADOS_NAO_ENCONTRADOS;
	
	string instalacao;
	for (Consumo consumo : historico) {
		if (instalacao != consumo.getNumeroInstalacao()) {
			instalacao = consumo.getNumeroInstalacao();
			cout << "\n\n| Instalação Nº " << consumo.getNumeroInstalacao() << endl;
			cout << " MÊS/ANO  CONSUMO  \tMÉDIA DIÁRIA\n";
		}
		cout << " " << consumo.toString() << endl;
	}

	return true;
}

bool CEE::organizarHistorico(vector<Consumo> & historico) {
	sort(historico.begin(), historico.end(), Consumo::comparador);
	return true;
}

bool CEE::verificarXPDF() {
	if (!ES::arquivoExiste(PATH_XPDF)) {
		cout << "\nDependência não encontrada:\n\t" <<
			"> O arquivo " << PATH_XPDF << " não pôde ser localizado.\n\nO programa não pode prosseguir.\n";
		return false;
	}
	return true;
}

bool CEE::pesquisaConsumo(char * numeroCliente, char * mesAno) {

	if (!pesquisarExibirCliente(numeroCliente)) return false;

	ArquivoFatura arquivo;
	Fatura * fatura;

	arquivo.abrir(FILE_FATURA_DAT);

	int posicao = 0;
	int mes = 0, ano = 0;
	bool exibido = false;

	//Converte e verifica se a data passada e válida
	if (mesAno != NULL) 
		if(!ES::strMesAnoToInt(mesAno, mes, ano)) {
			cout << MSG_DATA_INVALIDA;
			return false;
		}

	while (true) {
		posicao = arquivo.pesquisarFatura(numeroCliente, mes, ano, posicao);

		if (posicao == -1) break;

		fatura = arquivo.lerObjeto(posicao);
		exibirPesquisaConsumo(fatura);

		delete fatura;

		exibido = true;

		posicao++;
	}

	if (!exibido) cout << MSG_DADOS_NAO_ENCONTRADOS;
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

bool CEE::pesquisarExibirCliente(const string & numeroCliente) {
	ArquivoCliente arquivo;

	arquivo.abrir(FILE_CLIENTE_DAT);

	int registro = arquivo.pesquisarCliente(numeroCliente);

	if (registro == -1) {
		cout << "\nCliente não localizado.\n"; return false;
	}
	exibirCliente(arquivo.lerObjeto(registro));
	return true;

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
		return interpretarTresParametros(argumentos[1], argumentos[2], argumentos[3]);
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
	//verificar isso
	if (registro != -1) {
		cout << endl << "AVISO: Esta fatura já foi importada anteriormente.";

		return true;
	}
	arquivoFatura.escreverObjeto(fatura);

	arquivoFatura.fechar();

	return true;
	//ArquivoHistorico arquivoHistorico;
	//arquivoHistorico.abrir(FILE_HISTORICO_DAT);
	//int reg = arquivoHistorico.pesquisarHistorico(fatura.getCliente().getNumero());

	//return false;
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
	cout << endl; 
	return system("pause");
}
