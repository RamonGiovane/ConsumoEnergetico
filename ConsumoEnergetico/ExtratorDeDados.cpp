#include "ExtratorDeDados.h"
#include "Fatura.h"
#include "ArquivoTexto\ArquivoTexto.h"
#include "EntradaESaida.h"
#include <regex>


ExtratorDeDados::ExtratorDeDados(){ }
const string LINHA_BANDEIRA_AMARELA = "Band. Amarela - ";
const string LINHA_HISTORICO_CONSUMO = "Histórico de Consumo";
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
		mensagemErro = "\nFALHA: O arquivo não pôde ser lido. Provavelmente não é um arquivo PDF ou não existe.";
		//ES::exibirAbortarOperacao();
		fatura = faturaVazia;
		return false;
	}

	cout << "\nLendo a conta digital... ";
	if (!lerArquivoTexto(conteudoConta)) {
		mensagemErro = "\nFALHA: O conteúdo da conta não pôde ser lido. Possivelmente o arquivo está corrompido.";
		fatura = faturaVazia;
		return false;
	}

	cout << "\nObtendo informações da conta... ";
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
static const string ERRO_ABRIR_ARQUIVO_PDF = "FALHA: O arquivo PDF informado não existe ou está corrompido.";
static const string ERRO_ABRIR_ARQUIVO_SAIDA = "FALHA: Não foi possível gerar os dados de saída";
static const string ERRO_DE_PERMISSAO = "FALHA: O programa não tem permissão para ler o arquivo PDF informado ou gerar os dados de saída.";
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



	ValoresFaturados valores;
	Cliente cliente;
	
	if (linhasArquivo[0] == "Valores Faturados")
		return lerTextoModo1(linhasArquivo, fatura, cliente, valores);
	
	if (linhasArquivo[0] == "Acesse o Cemig Atende")
		return lerTextoModo2(linhasArquivo, fatura, cliente, valores);
	//cout << "\nNot implemented!\n";

	mensagemErro = "Este arquivo pdf não corresponde a uma conta de luz CEMIG";
	return false;

}

bool ExtratorDeDados::lerTextoModo1(vector<string> & linhasArquivo, Fatura & fatura, Cliente & cliente, ValoresFaturados & valores) {
	int posicaoAtual = 0;

	//Extraindo todas as informações do arquivo de texto
	if (!obterValoresFaturados(linhasArquivo, valores, posicaoAtual)) return false;
	if (!obterHistoricoConsumo(linhasArquivo, posicaoAtual, "MÊS/ANO CONSUMO kWh MÉDIA kWh/Dia Dias")) return false;
	if (!obterCliente(linhasArquivo, cliente, posicaoAtual, "Comprovante de Pagamento")) return false;
	if (!obterNumeroClienteEInstalacao(linhasArquivo, cliente, posicaoAtual)) return false;
	if (!obterMesVencimentoEValor(linhasArquivo, posicaoAtual)) return false;
	if (!obterDatasDeLeitura(linhasArquivo, posicaoAtual)) return false;

	fatura.setCliente(cliente);
	fatura.setValoresFaturados(valores);

	cout << endl << endl << fatura.toString() << endl;

	return true;
}

bool ExtratorDeDados::lerTextoModo2(vector<string> & linhasArquivo, Fatura & fatura, Cliente & cliente, ValoresFaturados & valores) {
	int posicaoAtual = 21;

	//Extraindo todas as informações do arquivo de texto
	if (!obterCliente(linhasArquivo, cliente, posicaoAtual, "Modalidade Tarifária")) return false;
	if (!obterNumeroClienteEInstalacao(linhasArquivo, cliente, posicaoAtual)) return false;
	cout << endl << cliente.toString();
	if (!obterDatasDeLeitura(linhasArquivo, posicaoAtual)) return false;
	if (!obterHistoricoConsumo(linhasArquivo, posicaoAtual, LINHA_BANDEIRA_AMARELA)) return false;
	if (!obterValoresFaturados(linhasArquivo, valores, posicaoAtual)) return false;
	if (!obterMesVencimentoEValor(linhasArquivo, posicaoAtual)) return false;


	fatura.setCliente(cliente);
	fatura.setValoresFaturados(valores);

	cout << endl << endl << fatura.toString() << endl;

	return true;

}

bool ExtratorDeDados::obterDatasDeLeitura(vector<string>& linhasArquivo, int & posicaoAtual)
{
	string padraoRegex = "\\s*\\d{2}[/]\\d{2}\\s\\d{2}[/]\\d{2}\\s\\d{2}[/]\\d{2}";
	
	string datas = ES::procurarPadrao(linhasArquivo, posicaoAtual, padraoRegex);
	if (datas == "") { mensagemErro = "Não foi possível computar as datas de leitura"; return false; }

	vector<string> linha;
	ES::quebrarTexto(linha, datas, ' ');
	
	if (linha[0] == "")
		linha.erase(linha.begin());


	if (fatura.getAnoReferente() == 0) {
		int ano = procurarAnoReferente(linhasArquivo, posicaoAtual);
		if (ano == 0) return false;
		fatura.setAnoReferente(ano);
	}

	formatarEAdicionarDatasDeLeitura(linha[0], linha[1], linha[2]);


	return true;
}

int ExtratorDeDados::procurarAnoReferente(const vector<string> & linhasArquivo, int posicaoAtual) {
	vector<string> data;
	ES::quebrarTexto(data, linhasArquivo[posicaoAtual + 1], '/');
	return ES::strToInt(data[2]);
}
/*Insere às datas de leitura, anterior, atual e proxima, seus respectivos anos. Em seguida, as armazena no objeto fatura.*/
bool ExtratorDeDados::formatarEAdicionarDatasDeLeitura(const string & dataLeituraAnterior, const string & dataLeituraAtual, const string & proximaDataLeitura, int ano){
	
	if(ano == 0) ano = fatura.getAnoReferente();
	
	string anoAtualStr = "/" + ES::intToStr(ano);
	
	//Se a data da leitura anterior for em dezembro, então decrementa-se o ano  atual para ela.
	if (obterMesData(dataLeituraAnterior) == 12)
		 fatura.setDataDeLeituraAnterior(dataLeituraAnterior + "/" + ES::intToStr(ano - 1));
	else
		fatura.setDataDeLeituraAnterior(dataLeituraAnterior + anoAtualStr);

	//Se a data da proxima leitura for em janeiro, então incrementa-se o ano atual para ela.
	if (obterMesData(proximaDataLeitura) == 1)
		fatura.setProximaDataDeLeitura(proximaDataLeitura + "/" + ES::intToStr(ano + 1));
	else
		fatura.setProximaDataDeLeitura(proximaDataLeitura + anoAtualStr);

	fatura.setDataDeLeitura(dataLeituraAtual + anoAtualStr);

	return true;

}

/*Retorna o número de um mês a partir de uma data no formato "MM/yyyy"*/
int ExtratorDeDados::obterMesData(const string & data) {
	vector<string> v;
	ES::quebrarTexto(v, data, '/');
	return ES::strToInt(v[0]);

}

bool ExtratorDeDados::obterNumeroClienteEInstalacao(vector<string>& linhasArquivo, Cliente & cliente, int & posicaoAtual)
{
	vector<string> linha;

	//Separando Numero do cliente e numero da instalacao
	ES::quebrarTexto(linha, linhasArquivo[posicaoAtual], ' ');

	cliente.setNumero(linha[0]);
	fatura.setNumeroInstalacao(linha[1]);

	return true;
}

bool ExtratorDeDados::obterMesVencimentoEValor(vector<string>& linhasArquivo, int & posicaoAtual)
{
	// \\s*\\d{2}[/]\\d{2}\\s\\d{2}[/]\\d{2}\\s\\d{2}[/]\\d{2}";
	string padrao = "\\.*\\d{2}[/]\\d{2}[/]\\d{4}\\s{1}";//[R$]*\\d{1,9}[,]\\d{2}"; /*000088011333 3000755750 22 / 10 / 2019 R$193, 23*/
	cout << endl << "match " << ES::procurarPadrao(linhasArquivo, posicaoAtual, padrao);

	vector<string> linha;
	//posicaoAtual += 2;



	//PROCURAR O TERMO POR PADRAO REGEX
	
	//Separando mes, vencimento e valor a pagar
	ES::quebrarTexto(linha, linhasArquivo[posicaoAtual], ' ');
	if (linha[0].size() == 8) {
		fatura.setMesAnoReferente(linha[0]);
		fatura.setDataVencimento(linha[1]);
	}
	else {
		fatura.setMesAnoReferente(linhasArquivo[posicaoAtual + 1]);
		fatura.setDataVencimento(linha[0]);
	}
	fatura.setValorAPagar(ES::strToDouble(linha[2]));

	return true;

}

bool ExtratorDeDados::obterCliente(vector<string>& linhasArquivo, Cliente & cliente, int & posicaoAtual, const string & termoReferencia) {


	int pos = posicaoAtual;
	posicaoAtual = ES::procurarNumeroLinha(linhasArquivo, termoReferencia, posicaoAtual);
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
	if (linhasArquivo[posicaoAtual] == "Nº DO CLIENTE Nº DA INSTALAÇÃO")
		posicaoAtual++;

	return true;
}

bool ExtratorDeDados::obterValoresFaturados(vector<string>& linhasArquivo, ValoresFaturados & valoresFaturados, int & posicaoAtual) {

	double  bandeiraAmarela, bandeiraVermelha;

	vector<string> linhaEnergiaEletrica =
		ES::procurarLinha(linhasArquivo, "Energia Elétrica kWh", posicaoAtual, "Encargos/Cobranças");

	if (linhaEnergiaEletrica.empty()) {
		mensagemErro = "Impossível computar linha sobre Energia Elétrica kWh";
		return false;
	}

	size_t tamanhoLinhaEnergia = linhaEnergiaEletrica.size();

	valoresFaturados.setValorDaFatura(ES::strToDouble(linhaEnergiaEletrica[--tamanhoLinhaEnergia]));
	valoresFaturados.setPreco(ES::strToDouble(linhaEnergiaEletrica[--tamanhoLinhaEnergia]));
	valoresFaturados.setConsumo(ES::strToInt((linhaEnergiaEletrica[--tamanhoLinhaEnergia])));
	valoresFaturados.setValorIluminacaoPublica(ES::strToDouble(ES::procurarItem(linhasArquivo, "Contrib Ilum Publica Municipal", posicaoAtual, "Tarifas Aplicadas (sem impostos)")));

	bandeiraAmarela = ES::strToDouble(ES::procurarItem(linhasArquivo, "Bandeira Amarela", posicaoAtual));
	bandeiraVermelha = ES::strToDouble(ES::procurarItem(linhasArquivo, "Bandeira Vermelha", posicaoAtual));

	cout << valoresFaturados.toString();

	valoresFaturados.definirAdicionais(bandeiraAmarela, bandeiraVermelha);

	return true;
}


bool ExtratorDeDados::obterHistoricoConsumo(vector<string>& linhasArquivo, int & posicaoAtual, const string & termoReferencia) {

	posicaoAtual = ES::procurarNumeroLinha(linhasArquivo, termoReferencia, posicaoAtual);
	if (posicaoAtual == -1) {
		mensagemErro = "Dados de histórico de consumo não econtrados. ";
		return false;
	}

 
	string tst = linhasArquivo[posicaoAtual];
	
	for (int i = 0; i < 13; i++) {
		if (!obterHistoricoConsumo(linhasArquivo[++posicaoAtual])) {
			mensagemErro = "Dados de histórico de consumo inconsistentes. ";
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

	while (linhasArquivo[posicaoAtual] != "Encargos/Cobranças") {
		ES::quebrarTexto(linhasValores, linhasArquivo[posicaoAtual], ' ');

		//Verifica se a linha atual se trata de Energia Elétrica KwH
		int i = 0;
		for (; i < (int)linhasValores.size(); i++) {
			if (!ES::isNumber(linhasValores[i]))
				descricao.append(linhasValores[i] + " ");
			else break;
		}

		if (descricao != "Energia Elétrica KwH")
			continue;

		valor = ES::strToDouble(linhasValores[linhasValores.size() - 1]);
	}
	return valor;
}
