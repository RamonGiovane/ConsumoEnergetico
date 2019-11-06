#include "ExtratorDeDados.h"
#include "Fatura.h"
#include "ArquivoTexto\ArquivoTexto.h"
#include "EntradaESaida.h"



ExtratorDeDados::ExtratorDeDados(){ }

Fatura ExtratorDeDados::lerContaPDF(string& caminho) {
	string conteudoConta;
	vector<string> linhasArquivo;
	const char  DELIMITADOR = '\n';
	static Fatura faturaVazia = Fatura();


	ES::removerArquivo(ARQUIVO_SAIDA);

	cout << "\nConvertendo PDF... ";
	if (!interpretarSaidaConversor(ES::PDFToText(caminho, ARQUIVO_SAIDA))) {

		//ES::exibirAbortarOperacao();
		return faturaVazia;
	}

	cout << "\nLendo a conta digital... ";
	if (!lerArquivoTexto(conteudoConta)) {
		cout << "\nFALHA: O conteúdo da conta não pôde ser lido. Possivelmente o arquivo está corrompido.";
		//ES::exibirAbortarOperacao();
		return faturaVazia;
	}
	cout << "\nObtendo informações da conta... ";
	ES::quebrarTexto(linhasArquivo, conteudoConta, DELIMITADOR);
	if (!obterInformacoes(linhasArquivo)) {
		cout << "\nFALHA: " << mensagemErro;
		//ES::exibirAbortarOperacao();
		return faturaVazia;
	}

	return fatura;
}

static const string SEM_ERROS = "Sucesso.";
static const string ERRO_ABRIR_ARQUIVO_PDF = "FALHA: O arquivo PDF informado não existe ou está corrompido.";
static const string ERRO_ABRIR_ARQUIVO_SAIDA = "FALHA: Não foi possível gerar os dados de saída";
static const string ERRO_DE_PERMISSAO = "FALHA: O programa não tem permissão para ler o arquivo PDF informado ou gerar os dados de saída.";
static const string ERRO_DESCONHECIDO = "FALHA: Um erro desconhecido ocorreu ao converter o arquivo PDF.";


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
		mensagemErro = "Este arquivo pdf não corresponde a uma conta de luz CEMIG";
		return false;
	}

	ValoresFaturados valores;
	Cliente cliente;
	int posicaoAtual = 0;

	obterValoresFaturados(linhasArquivo, valores, posicaoAtual);
	obterHistoricoConsumo(linhasArquivo, posicaoAtual);
	obterCliente(linhasArquivo, cliente, posicaoAtual);
	obterDemaisInformacoes(linhasArquivo, cliente, posicaoAtual);

	fatura.setCliente(cliente);
	fatura.setValoresFaturados(valores);

	cout << fatura.toString();

	return true;
}
bool ExtratorDeDados::obterDemaisInformacoes(vector<string>& linhasArquivo, Cliente & cliente, int & posicaoAtual)
{
	vector<string> linha;

	//Separando Numero do cliente e numero da instalacao
	ES::quebrarTexto(linha, linhasArquivo[++posicaoAtual], ' ');

	cliente.setNumero(linha[0]);
	fatura.setNumeroInstalacao(linha[1]);

	//Separando Numero do cliente e numero da instalacao
	ES::quebrarTexto(linha, linhasArquivo[++posicaoAtual], ' ');

	linha = vector<string>();
	cout << linhasArquivo[posicaoAtual];
	//Separando mes, vencimento e valor a pagar
	ES::quebrarTexto(linha, linhasArquivo[++posicaoAtual], ' ');
	fatura.setMesReferente(linha[0]);
	fatura.setDataVencimento(linha[1]);
	fatura.setValorAPagar(ES::strToDouble(linha[2]));


	return true;

}
bool ExtratorDeDados::obterCliente(vector<string>& linhasArquivo, Cliente & cliente, int & posicaoAtual) {

	//while (linhasArquivo[posicaoAtual] != "Comprovante de Pagamento")
	//	posicaoAtual++;
	int pos = posicaoAtual;
	posicaoAtual = procurarNumeroLinha(linhasArquivo, "Comprovante de Pagamento", posicaoAtual);
	if (posicaoAtual == -1 )
		posicaoAtual = procurarNumeroLinha(linhasArquivo, "NnW", pos);
	if (posicaoAtual == -1) {
		return false;
	}
	cout << linhasArquivo[posicaoAtual+1];

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
		procurarLinha(linhasArquivo, "Energia Elétrica kWh", posicaoAtual, "Encargos/Cobranças");

	if (linhaEnergiaEletrica.empty()) {
		mensagemErro = "Impossível computar linha sobre Energia Elétrica kWh";
		return false;
	}

	size_t tamanhoLinhaEnergia = linhaEnergiaEletrica.size();

	fatura.setValorFaturado(ES::strToDouble(linhaEnergiaEletrica[--tamanhoLinhaEnergia]));
	fatura.setPreco(ES::strToDouble(linhaEnergiaEletrica[--tamanhoLinhaEnergia]));
	fatura.setConsumo(ES::strToInt((linhaEnergiaEletrica[--tamanhoLinhaEnergia])));
	fatura.setValorIluminacaoPublica(ES::strToDouble(procurarItem(linhasArquivo, "Contrib Ilum Publica Municipal", posicaoAtual, "Tarifas Aplicadas (sem impostos)")));

	bandeiraAmarela = ES::strToDouble(procurarItem(linhasArquivo, "Bandeira Amarela", posicaoAtual));
	bandeiraVermelha = ES::strToDouble(procurarItem(linhasArquivo, "Bandeira Vermelha", posicaoAtual));

	fatura.definirAdicionais(bandeiraAmarela, bandeiraVermelha);

	return true;
}

bool ExtratorDeDados::obterHistoricoConsumo(vector<string>& linhasArquivo, int & posicaoAtual) {
	string termo = "MÊS/ANO CONSUMO kWh MÉDIA kWh/Dia Dias";
	posicaoAtual = procurarNumeroLinha(linhasArquivo, termo, posicaoAtual);
	if (posicaoAtual == -1) {
		mensagemErro = "Dados de histórico de consumo não econtrados. ";
		return false;
	}
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

/*Procura o número de uma linha que contém total ou parcialmente o termo pesquisado . Retorna esse número ou -1 caso a linha não seja identificada*/
int ExtratorDeDados::procurarNumeroLinha(const vector<string>& linhasArquivo, const string & termoPesquisado, int posicaoAtual) {
	for (; posicaoAtual < linhasArquivo.size() - 1; posicaoAtual++) {
		if (linhasArquivo[posicaoAtual].find(termoPesquisado) != std::string::npos)
			return posicaoAtual;
	}
	return -1;

}



/*
Procura nas linhas do arquivo (const vector<string> & linhasArquivo) o valor correpondente à um termo pesquisado, a partir do numero de uma linha
até uma linha em que seu conteúdo seja especificado por um termo de parada (const string & termoFinal).
Por exemplo, pesquisando o termo "Bandeira Vermelha", sendo as linhas subseguintes à posição especificada:

"Energia Elétrica kWh 0,66833000
Adicional Bandeiras - Já incluído no Valor a Pagar
Bandeira Vermelha 9,81
Histórico de Consumo
MÊS/ANO CONSUMO kWh MÉDIA kWh/Dia Dias
SET/19 162 5,22 31"

Seria retornado o valor "9,81" como string. A pesquisa seria feita até o termo final "Histórico de Consumo" ou até o final do vector.
O valor a ser retornado é sempre o último item da linha separado por espaços em branco. Importante notar que a referência contendo o número
da linha atual na chamada da função será alterada, passando a ter o número da linha em que a pesquisa finalizou.
Se o termo final for uma string vazia, a pesquisa é finalizada na próxima posição após àquela que corresponder ao termo correto ou
ao final do arquivo.
*/
string ExtratorDeDados::procurarItem(const vector<string> & linhasArquivo, const string & termoPesquisado,
	int & posicaoAtual, const string & termoFinal) {

	vector<string> linhasValores = procurarLinha(linhasArquivo, termoPesquisado, posicaoAtual, termoFinal);
	if (!linhasValores.empty())
		return linhasValores[linhasValores.size() - 1];

	return string("");

}

vector<string>& ExtratorDeDados::procurarLinha(const vector<string> & linhasArquivo, const string & termoPesquisado,
	int & posicaoAtual, const string & termoFinal) {

	static vector<string> linhasValores;
	linhasValores = vector<string>();
	string descricao, item;
	int posicao = posicaoAtual;

	//Iterar pelas linhas até encontrar o fim
	for (; linhasArquivo[posicaoAtual] != termoFinal && posicaoAtual < (int)linhasArquivo.size() - 1; posicaoAtual++) {

		if (linhasArquivo[posicaoAtual].find(termoPesquisado) != std::string::npos) {

			ES::quebrarTexto(linhasValores, linhasArquivo[posicaoAtual], ' ');

			return linhasValores;

		}
	}

	posicaoAtual = posicao;

	return linhasValores;
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


