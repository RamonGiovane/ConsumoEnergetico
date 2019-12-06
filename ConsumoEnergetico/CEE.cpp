#include "ExtratorDeFaturas.h"
#include "CEE.h"
#include "EntradaESaida.h"
#include "ArquivoTexto.h"
#include "ArquivoCliente.h"
#include "ArquivoFatura.h"
#include "Cliente.h"
#include "Constantes.h"
#include "ArquivoHistorico.h"
#include "ExtratorArquivoConsumo.h"
#include <string>
#include <vector>


using namespace std;

CEE::CEE() { }


void CEE::exibirInformacao() {
	cout << PROG_INFO;
}
/*Inicia, interpreta os argumentos passados para o programa e executa a operação solicitada, se for válida.*/
int CEE::iniciar(int numeroArgumentos, char * argumentos[]) {

	
	definirCaminhoPrograma(argumentos);

	//Define a localização para o Brasil
	ES::mudarLocalizacao();

	//Cria o diretório em que os arquivos binários ficarão
	ES::criarDiretorio(DIR_DATA);
	
	return interpretarComando(numeroArgumentos, argumentos);
}

/*Registra o nome de uma fatura ou arquivo que falhou durante a importação*/
void CEE::adicionarFaturaComFalha(const string & nomeArquivo)
{

	if (relatorioArquivosIgnorados.empty())
		relatorioArquivosIgnorados = STR_ARQUIVOS_FALHARAM;
	else
		relatorioArquivosIgnorados += VIRGULA_ESPACO;

	relatorioArquivosIgnorados += nomeArquivo;

}

/*Adiciona o nome de um arquivo ao caminho de de um diretório. Se o diretório não possuir um terminador de barra no final, a mesma será inserida*/
string formatarCaminhoCompletoImportacao(const string & caminhoDiretorio, const string & nomeArquivo) {

	if (caminhoDiretorio == nomeArquivo) return caminhoDiretorio;

	string caminhoCompleto(caminhoDiretorio);

	if (caminhoCompleto.back() != ARRAB)
		caminhoCompleto.append("\\");

	caminhoCompleto.append(nomeArquivo);
	return caminhoCompleto;
}
/*Lê várias faturas PDF de um caminho especificado. É necessário a lista de arquivos do diretório e seu caminho absoluto,
para que eles sejam encontrados.
Exibe ao usuário os status da operações. Retorna true em caso de sucesso, false em falha.*/
int CEE::importarFaturas(vector<string> listaArquivos, string caminhoDiretorio) {
	int arquivosIgnorados = 0, arquivosLidos = 0;
	string caminhoCompleto;

	//Se o dietório passado é um ou vários esapços em branco 
	if (std::all_of(caminhoDiretorio.begin(),caminhoDiretorio.end(),isspace)) caminhoDiretorio = caminhoPrograma;
	for (string arquivo : listaArquivos) {
		caminhoCompleto = formatarCaminhoCompletoImportacao(caminhoDiretorio, arquivo);
		if (importarFatura(caminhoCompleto))
			arquivosLidos++;
		else { adicionarFaturaComFalha(arquivo); arquivosIgnorados++; }
	}

	relatorioImportacaoArquivos(arquivosLidos, arquivosIgnorados);
	

	return arquivosIgnorados;

}

/*Exibe um relatório de importação mostrando quantos arquivos foram lidos e quantos foram ignorados*/
void CEE::relatorioImportacaoArquivos(int arquivosLidos, int arquivosIgnorados) {
	
	cout << MSG_FIM_LEITURA << arquivosLidos << (arquivosLidos == 1 ? MSG_ARQUIVO_LIDO : MSG_ARQUIVOS_LIDOS) << endl;
	cout << arquivosIgnorados << (arquivosIgnorados == 1 ? MSG_ARQUIVO_IGNORADO : MSG_ARQUIVOS_IGNORADOS);
	cout << endl << relatorioArquivosIgnorados;
	cout << endl << endl;
}


/*Lê uma fatura em PDF do caminho especificado. Exibe ao usuário os status da operações. Retorna true em caso de sucesso, false em falha.*/
bool CEE::importarFatura(const string & caminhoArquivo, bool printMensagemFinal, int tipoArquivo) {
	cout << MSG_LENDO + caminhoArquivo;
	if (!lerFaturaDigital(caminhoArquivo, tipoArquivo)) {
		cout << MSG_IGNORANDO_ARQUIVO;
		if (printMensagemFinal) relatorioImportacaoArquivos(0, 1);
		return false;
	}

	cout << MSG_ARQUIVO_IMPORTADO;

	if (printMensagemFinal) relatorioImportacaoArquivos(1, 0);

	return true;

}



/*Executado quando o programa é iniciado sem parâmetros.
  Exibe um prompt ao usuário, confirmando se ele realmente que realizar um import no diretório atual*/
int CEE::promptImportarFaturas() {
	
	cout << NO_PARAM_INFO;

	cin.ignore();

	return interpretarUmParametro("");
}

/*Interpreta a entrada do programa quando apenas um parâmetro é passado para ele. 
  A operação realizada pode ser exibir uma ajuda ao usuário, importar faturas, ou pesquisar dados de consumo
  do cliente passado
*/
int CEE::interpretarUmParametro(char * parametro) {
	string strParametro = parametro;

	if (strParametro == HELP_COM1 || strParametro == HELP_COM2) {
		exibirInformacao();
		return 1;
	}
	
	vector<string> arquivos;
	if (ES::obterArquivosDiretorio(strParametro, arquivos)) {
		
		if (!verificarXPDF()) return false;
		
		if (arquivos.empty())
			return importarFatura(strParametro, true);
		return importarFaturas(arquivos, strParametro);

	}
	return pesquisaConsumo(parametro);

}
/* Interpreta a entrada do programa quando três parâmetros são passados para ele.
   As possíveis operações para estes parâmetros são:
     - calcular o consumo de energia de uma arquivo de aparelhos elétricos (se o parâmetro 3 for um arquivo);
	 - pesquisar o historico de consumo das instalações do cliente fornecido 
*/
int CEE::interpretarTresParametros(char * parametro1, char * parametro2, char * parametro3)
{
	//Se o parametro tres é um arquivo...
	if (ES::arquivoExiste(parametro3)) 
		return calcularConsumoDeEnergia(parametro1, parametro2, parametro3);
	
	//Senão, tenta outra operação...
	return pesquisaHistoricoConsumo(parametro1, parametro2, parametro3);

}
/* Interpreta a entrada do programa quando dois parâmetros são passados para ele.
	As possíveis operações para estes parâmetros são:
	- importar uma fatura em modo texto (se o parametro1 == "/i");
	- pesquisar os dados de consumo das instalações do cliente fornecido
*/
int CEE::interpretarDoisParametros(char * parametro1, char * parametro2) {
	if (parametro1 == BARRA_I) 
		return importarFatura(parametro2, true, TIPO_TEXTO);
	return pesquisaConsumo(parametro1, parametro2);
}

/*A partir do número de um cliente, de um mês/ano e o caminho de um arquivo texto com consumos passados na linha de comando,
calcula o consumo em kWh do arquivo de aparelhos e exibe relatórios. Exibe também os dados de consumo do cliente para o mês/ano passados
na linha de comando para fins de comparação.
Retorna true em caso de sucesso, retorna false e exibe mensagens de erro se algum erro ocorrer ou parâmetros incorretos forem passados.
*/
bool CEE::calcularConsumoDeEnergia(char * numeroCliente, char * mesAno, char * arquivoEntrada) {
	ExtratorArquivoConsumo extrator;
	Consumo consumo;

	if (!pesquisarExibirCliente(numeroCliente)) return false;

	if (!extrator.calcularExibirConsumosDoArquivo(numeroCliente, arquivoEntrada, mesAno)) {
		cout << endl << extrator.getMensagemErro();
		return false;
	}

	cout << endl << extrator.getConteudoResposta();
	return true;
}
/**A partir do número de um cliente, de um mês/ano inicial e final, pesquisa no arquivo binário de histórico, 
todos os consumos de todas as instalações do cliente entre o intervalo de datas especificado*/
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
	
	ES::organizarConsumos(historico);

	exibirHistorico(historico, mesAnoInicial, mesAnoFinal);

	arquivo.fechar();

	return true;
}

/*Exibe o histórico de consumo de um cliente desde que os consumos estejam num intervalo entre os parâmetros mesInicial e mesFinal*/
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
		cout << VAZIO << consumo.toString() << endl;
	}

	return true;
}


/*Verifica se a depêndencia xdpf (pdftotext.exe) se encontra em seu devido local (definido em "Constantes.h")*/
bool CEE::verificarXPDF() {
	if (!ES::arquivoExiste(caminhoPrograma + PATH_XPDF)) {
		cout << MSGE_MISSING_XPDF;
		return false;
	}
	return true;
}

/*Pesquisa e exibe os dados de fatura de um cliente de um mês/ano específico. 
Exibe um alerta ao usuário caso não sejam encontrados dados de cliente ou fatura.*/
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

/*Exibe os dados de uma fatura pesquisada.*/
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

/*Pesquisa os dados de um cliente no arquivo binário de cliente, a partir de seu número.
Ao encontrar, exibe seus dados e retorna true. Do contrário, retorna false e exibe um alerta ao usuário*/
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

/*Interpreta a quantidade de argumentos passados e redireciona a execução do programa para a função solicitada. de acordo
com o que está especificado na constante PROG_INFO em "Constantes.h"*/
int CEE::interpretarComando(int numeroArgumentos, char * argumentos[]) {

	switch (numeroArgumentos) {
	
	case 1:
		return promptImportarFaturas();

	case 2:
		return interpretarUmParametro(argumentos[1]);
		break;
	case 3:
		interpretarDoisParametros(argumentos[1], argumentos[2]);
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


/*Abre, lê e importa uma fatura digital a partir do caminho de seu arquivo e do tipo de arquivo: TIPO_TXT  ou TIPO_PDF, definido em "Constantes.h"
Retorna true em sucesso. Em caso de falha, exibe o motivo da falha e retorna false*/
bool CEE::lerFaturaDigital(const string & caminhoArquivo, int tipoArquivo) {
	
	ExtratorDeFaturas extrator(caminhoPrograma);
	
	bool status;
	switch (tipoArquivo) {

	case TIPO_PDF:
		status = extrator.importarFaturaPDF(caminhoArquivo);
		break;

	case TIPO_TEXTO:
		status = extrator.importarFaturaTXT(caminhoArquivo);
		break;

	}
	if (!status) {
		cout << extrator.getMensagemErro();
		return false;
	}
	return true;
}

/*Define o caminho que se encontra o programa para que as dependências e demais arquivos possam ser localizados. 
Isso é feito através dos argumenos passados pelo progama*/
void CEE::definirCaminhoPrograma(char * argv[]) {

	caminhoPrograma = argv[0];
	
	if (caminhoPrograma == CEE_EXE) {
		caminhoPrograma = PONTO_BARRA;
		return;
	}

	size_t i = caminhoPrograma.size() - 1;

	while (true) {
		if (caminhoPrograma[i--] == ARRAB) break;
		caminhoPrograma.pop_back();
	}

}

int main(int argc, char * argv[]) {
	CEE().iniciar(argc, argv);
	cout << endl; 
	return 0;
}
