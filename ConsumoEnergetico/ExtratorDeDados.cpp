#include "ExtratorDeDados.h"
#include "Fatura.h"
#include "ArquivoTexto\ArquivoTexto.h"
#include "EntradaESaida.h"
#include <regex>


ExtratorDeDados::ExtratorDeDados(){ }

//(Fatura & fatura, const string & caminhoPrograma, const string & caminhoArquivo)
bool ExtratorDeDados::lerFaturaPDF(Fatura & fatura, const string & caminhoPrograma, const string& caminhoArquivo) {
	
	this->caminhoPrograma = caminhoPrograma;

	string conteudoConta;
	vector<string> linhasArquivo;
	const char  DELIMITADOR = '\n';
	static Fatura faturaVazia = Fatura();

	ES::removerArquivo(ARQUIVO_SAIDA);

	cout << "\nConvertendo PDF... ";
	if (!ES::PDFToText(caminhoArquivo, caminhoPrograma, ARQUIVO_SAIDA)) {
		mensagemErro = "\nFALHA: O arquivo n�o p�de ser lido. Provavelmente n�o � um arquivo PDF ou n�o existe.";
		//ES::exibirAbortarOperacao();
		fatura = faturaVazia;
		return false;
	}

	cout << "\nLendo a conta digital... ";
	if (!lerArquivoTexto(conteudoConta)) {
		mensagemErro = "\nFALHA: O conte�do da conta n�o p�de ser lido. Possivelmente o arquivo est� corrompido.";
		fatura = faturaVazia;
		return false;
	}

	cout << "\nObtendo informa��es da conta... ";
	ES::quebrarTexto(linhasArquivo, conteudoConta, DELIMITADOR);
	if (!obterInformacoes(linhasArquivo)) {
		mensagemErro = "\nFALHA: " + mensagemErro;
		fatura = faturaVazia;
		return false;
	}

	fatura = this->fatura;

	return true;
}

static const string SEM_ERROS = "Sucesso.";
static const string ERRO_ABRIR_ARQUIVO_PDF = "FALHA: O arquivo PDF informado n�o existe ou est� corrompido.";
static const string ERRO_ABRIR_ARQUIVO_SAIDA = "FALHA: N�o foi poss�vel gerar os dados de sa�da";
static const string ERRO_DE_PERMISSAO = "FALHA: O programa n�o tem permiss�o para ler o arquivo PDF informado ou gerar os dados de sa�da.";
static const string ERRO_DESCONHECIDO = "FALHA: Um erro desconhecido ocorreu ao converter o arquivo PDF.";

string ExtratorDeDados::getMensagemErro() {
	return mensagemErro;
}

bool ExtratorDeDados::interpretarSaidaConversor(int codigoSaida) {
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

bool ExtratorDeDados::lerArquivoTexto(string& conteudoArquivo) {
	ArquivoTexto arquivo;
	arquivo.abrir(ARQUIVO_SAIDA, TipoDeAcesso::LEITURA);
	conteudoArquivo = arquivo.ler();
	arquivo.fechar();
	return conteudoArquivo == "NULL" ? false : true;
}

bool ExtratorDeDados::obterInformacoes(vector<string>& linhasArquivo) {

	if (linhasArquivo[0] != "Valores Faturados") {
		mensagemErro = "Este arquivo pdf n�o corresponde a uma conta de luz CEMIG";
		return false;
	}

	ValoresFaturados valores;
	Cliente cliente;
	int posicaoAtual = 0;


	//Extraindo todas as informa��es do arquivo de texto
	if (!obterValoresFaturados(linhasArquivo, valores, posicaoAtual)) return false;
	if (!obterHistoricoConsumo(linhasArquivo, posicaoAtual)) return false;
	if (!obterCliente(linhasArquivo, cliente, posicaoAtual)) return false;
	if (!obterNumeroClienteEInstalacao(linhasArquivo, cliente, posicaoAtual)) return false;
	if (!obterMesVencimentoEValor(linhasArquivo, posicaoAtual)) return false;
	if (!obterDatasDeLeitura(linhasArquivo, posicaoAtual)) return false;
	



	fatura.setCliente(cliente);
	fatura.setValoresFaturados(valores);
	
	return true;
}

bool ExtratorDeDados::obterDatasDeLeitura(vector<string>& linhasArquivo, int & posicaoAtual)
{
	string padraoRegex = "\\s\\d{2}[/]\\d{2}\\s\\d{2}[/]\\d{2}\\s\\d{2}[/]\\d{2}";
	
	string datas = ES::procurarPadrao(linhasArquivo, posicaoAtual, padraoRegex);
	if (datas == "") { mensagemErro = "N�o foi poss�vel computar as datas de leitura"; return false; }

	vector<string> linha;
	ES::quebrarTexto(linha, datas, ' ');
	

	//Nao pega a posi��o 0 porque corresponde � um espa�o em branco
	formatarEAdicionarDatasDeLeitura(linha[1], linha[2], linha[3]);


	return true;
}

/*Insere �s datas de leitura, anterior, atual e proxima, seus respectivos anos. Em seguida, as armazena no objeto fatura.*/
bool ExtratorDeDados::formatarEAdicionarDatasDeLeitura(const string & dataLeituraAnterior, const string & dataLeituraAtual, const string & proximaDataLeitura){
	int ano = fatura.getAnoReferente();
	
	string anoAtualStr = "/" + ES::intToStr(ano);
	
	//Se a data da leitura anterior for em dezembro, ent�o decrementa-se o ano  atual para ela.
	if (obterMesData(dataLeituraAnterior) == 12)
		 fatura.setDataDeLeituraAnterior(dataLeituraAnterior + "/" + ES::intToStr(ano - 1));
	else
		fatura.setDataDeLeituraAnterior(dataLeituraAnterior + anoAtualStr);

	//Se a data da proxima leitura for em janeiro, ent�o incrementa-se o ano atual para ela.
	if (obterMesData(proximaDataLeitura) == 1)
		fatura.setProximaDataDeLeitura(proximaDataLeitura + "/" + ES::intToStr(ano + 1));
	else
		fatura.setProximaDataDeLeitura(proximaDataLeitura + anoAtualStr);

	fatura.setDataDeLeitura(dataLeituraAtual + anoAtualStr);

	return true;

}

/*Retorna o n�mero de um m�s a partir de uma data no formato "MM/yyyy"*/
int ExtratorDeDados::obterMesData(const string & data) {
	vector<string> v;
	ES::quebrarTexto(v, data, '/');
	return ES::strToInt(v[0]);

}

bool ExtratorDeDados::obterNumeroClienteEInstalacao(vector<string>& linhasArquivo, Cliente & cliente, int & posicaoAtual)
{
	vector<string> linha;

	//Separando Numero do cliente e numero da instalacao
	ES::quebrarTexto(linha, linhasArquivo[++posicaoAtual], ' ');

	cliente.setNumero(linha[0]);
	fatura.setNumeroInstalacao(linha[1]);

	return true;
}

bool ExtratorDeDados::obterMesVencimentoEValor(vector<string>& linhasArquivo, int & posicaoAtual)
{

	vector<string> linha;
	posicaoAtual += 2;

	
	//Separando mes, vencimento e valor a pagar
	ES::quebrarTexto(linha, linhasArquivo[posicaoAtual], ' ');
	fatura.setMesAnoReferente(linha[0]);
	fatura.setDataVencimento(linha[1]);
	fatura.setValorAPagar(ES::strToDouble(linha[2]));

	return true;

}

bool ExtratorDeDados::obterCliente(vector<string>& linhasArquivo, Cliente & cliente, int & posicaoAtual) {


	int pos = posicaoAtual;
	posicaoAtual = ES::procurarNumeroLinha(linhasArquivo, "Comprovante de Pagamento", posicaoAtual);
	if (posicaoAtual == -1 )
		posicaoAtual = ES::procurarNumeroLinha(linhasArquivo, "NnW", pos);
	if (posicaoAtual == -1) {
		return false;
	}

	cliente.setNome(linhasArquivo[++posicaoAtual]);
	cliente.setRua(linhasArquivo[++posicaoAtual]);
	cliente.setBairro(linhasArquivo[++posicaoAtual]);

	vector<string> linha;

	//Separando CEP de Cidade
	ES::quebrarTexto(linha, linhasArquivo[++posicaoAtual], ' ');
	cliente.setCEP(linha[0]).setCidade(linha[1] + " " + linha[2]);

	posicaoAtual += 2;

	return true;
}

bool ExtratorDeDados::obterValoresFaturados(vector<string>& linhasArquivo, ValoresFaturados & fatura, int & posicaoAtual) {

	double  bandeiraAmarela, bandeiraVermelha;

	vector<string> linhaEnergiaEletrica =
		ES::procurarLinha(linhasArquivo, "Energia El�trica kWh", posicaoAtual, "Encargos/Cobran�as");

	if (linhaEnergiaEletrica.empty()) {
		mensagemErro = "Imposs�vel computar linha sobre Energia El�trica kWh";
		return false;
	}

	size_t tamanhoLinhaEnergia = linhaEnergiaEletrica.size();

	fatura.setValorFaturado(ES::strToDouble(linhaEnergiaEletrica[--tamanhoLinhaEnergia]));
	fatura.setPreco(ES::strToDouble(linhaEnergiaEletrica[--tamanhoLinhaEnergia]));
	fatura.setConsumo(ES::strToInt((linhaEnergiaEletrica[--tamanhoLinhaEnergia])));
	fatura.setValorIluminacaoPublica(ES::strToDouble(ES::procurarItem(linhasArquivo, "Contrib Ilum Publica Municipal", posicaoAtual, "Tarifas Aplicadas (sem impostos)")));

	bandeiraAmarela = ES::strToDouble(ES::procurarItem(linhasArquivo, "Bandeira Amarela", posicaoAtual));
	bandeiraVermelha = ES::strToDouble(ES::procurarItem(linhasArquivo, "Bandeira Vermelha", posicaoAtual));

	fatura.definirAdicionais(bandeiraAmarela, bandeiraVermelha);

	return true;
}

bool ExtratorDeDados::obterHistoricoConsumo(vector<string>& linhasArquivo, int & posicaoAtual) {
	string termo = "M�S/ANO CONSUMO kWh M�DIA kWh/Dia Dias";
	posicaoAtual = ES::procurarNumeroLinha(linhasArquivo, termo, posicaoAtual);
	if (posicaoAtual == -1) {
		mensagemErro = "Dados de hist�rico de consumo n�o econtrados. ";
		return false;
	}
	for (int i = 0; i < 13; i++) {
		if (!obterHistoricoConsumo(linhasArquivo[++posicaoAtual])) {
			mensagemErro = "Dados de hist�rico de consumo inconsistentes. ";
			return false;
		}
	}
	return true;
}

bool ExtratorDeDados::obterHistoricoConsumo(const string & linha) {
	vector<string> dados;
	ES::quebrarTexto(dados, linha, ' ');

	if (dados.size() != 4) return false;

	Consumo consumo;
	if (!consumo.definirMesAno(dados[0])) return false;

	consumo.setConsumoKWh(ES::strToInt(dados[1]));
	consumo.setMediaConsumoDiario(ES::strToDouble(dados[2]));
	consumo.setDias(ES::strToInt(dados[3]));

	fatura.adicionarHistoricoConsumo(consumo);

	return true;
}




double ExtratorDeDados::extrairValoresFaturados(vector<string>& linhasArquivo, int& posicaoAtual) {
	posicaoAtual = 2;
	vector<string> linhasValores;
	string descricao;
	int quantidade = 0;
	double tarifa = 0, valor = 0;

	while (linhasArquivo[posicaoAtual] != "Encargos/Cobran�as") {
		ES::quebrarTexto(linhasValores, linhasArquivo[posicaoAtual], ' ');

		//Verifica se a linha atual se trata de Energia El�trica KwH
		int i = 0;
		for (; i < (int)linhasValores.size(); i++) {
			if (!ES::isNumber(linhasValores[i]))
				descricao.append(linhasValores[i] + " ");
			else break;
		}

		if (descricao != "Energia El�trica KwH")
			continue;

		valor = ES::strToDouble(linhasValores[linhasValores.size() - 1]);
	}
	return valor;
}
