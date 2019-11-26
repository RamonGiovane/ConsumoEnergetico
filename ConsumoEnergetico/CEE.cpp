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
	cout << PROG_INFO;
}
int CEE::iniciar(int numeroArgumentos, char * argumentos[]) {

	definirCaminhoPrograma(argumentos);

	//Define a localização para o Brasil
	ES::mudarLocalizacao();

	//Cria o diretório em que os arquivos binários ficarão
	ES::criarDiretorio(DIR_DATA);

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
	

	cout << MSG_FIM_LEITURA << arquivosLidos << (arquivosLidos == 1 ? MSG_ARQUIVO_LIDO : MSG_ARQUIVOS_LIDOS) << endl;
	cout << arquivosIgnorados << (arquivosIgnorados == 1 ? MSG_ARQUIVO_IGNORADO : MSG_ARQUIVOS_IGNORADOS);
	cout << endl << endl;
}

/*Lê uma fatura em PDF do caminho especificado. Exibe ao usuário os status da operações. Retorna true em caso de sucesso, false em falha.*/
bool CEE::importarFatura(const string & caminhoArquivo, bool printMensagemFinal) {
	cout << MSG_LENDO + caminhoArquivo;
	if (!lerContaDigital(caminhoArquivo)) {
		cout << MSG_IGNORANDO_ARQUIVO;
		if (printMensagemFinal) relatorioImportacaoArquivos(0, 1);
		return false;
	}

	cout << MSG_ARQUIVO_IMPORTADO;

	if (printMensagemFinal) relatorioImportacaoArquivos(1, 0);

	return true;

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
	
	cout << TITLE_HISTORICO << mesAnoInicial << STR_A << mesAnoFinal << STR_D_PERIOD;
	
	if (historico.empty()) cout << SBARRA_N << MSG_DADOS_NAO_ENCONTRADOS;
	
	string instalacao;
	for (Consumo consumo : historico) {
		if (instalacao != consumo.getNumeroInstalacao()) {
			instalacao = consumo.getNumeroInstalacao();
			cout << SUBTITLE_INSTALACAO << consumo.getNumeroInstalacao() << endl;
			cout << SUBTITLE_HISTORICO;
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
	if (!ES::arquivoExiste(caminhoPrograma + PATH_XPDF)) {
		cout << MSGE_MISSING_XPDF;
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
	cout << endl <<
	STR_CONSUMO_INSTALACAO << fatura->getNumeroInstalacao() << STR_D_PERIOD
		<< fatura->getValoresFaturados().getConsumo() << STR_KWH;
	
	cout << endl << 
	STR_VALOR_A_PAGAR << fatura->getValorAPagar() << SEPARTOR <<  STR_DATA_VENC << fatura->getDataVencimento();
	
	cout << endl << 
	STR_REFERENTE << ES::mesToStr(fatura->getMesReferente()) << STR_DE << fatura->getAnoReferente() << endl;
}

void CEE::exibirCliente(Cliente * cliente) {
	cout << endl << TITLE_PESQUISANDO_CLIENTE << endl << cliente->toString() << endl;

}

bool CEE::pesquisarExibirCliente(const string & numeroCliente) {
	ArquivoCliente arquivo;

	arquivo.abrir(FILE_CLIENTE_DAT);

	int registro = arquivo.pesquisarCliente(numeroCliente);

	if (registro == -1) {
		cout << MSG_CLIENTE_NAO_LOCALIZADO; return false;
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

	ExtratorDeDados extrator(caminhoPrograma);
	
	if (!extrator.importarFaturaPDF(caminhoArquivo)) { 
		cout << extrator.getMensagemErro(); 
		return false; 
	}
	return true;

}
bool CEE::salvarDados(Fatura fatura) {

	ArquivoFatura arquivoFatura;
	arquivoFatura.abrir(FILE_FATURA_DAT);

	int registro = arquivoFatura.pesquisarFatura(fatura.getCliente().getNumero(),
		fatura.getMesReferente(), fatura.getAnoReferente());
	//verificar isso
	if (registro != -1) {
		cout << endl << MSG_FATURA_JA_EXISTE;

		return true;
	}
	arquivoFatura.escreverObjeto(fatura);

	arquivoFatura.fechar();

	return true;

}


void CEE::definirCaminhoPrograma(char * argv[]) {

	caminhoPrograma = argv[0];
	size_t i = caminhoPrograma.size() - 1;

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
