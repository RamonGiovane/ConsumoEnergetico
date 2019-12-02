#include "ExtratorDeFaturas.h"
#include "Fatura.h"
#include "ArquivoTexto\ArquivoTexto.h"
#include "EntradaESaida.h"
#include "ArquivoHistorico.h"
#include "ArquivoFatura.h"
#include "Constantes.h"
#include <regex>


ExtratorDeFaturas::ExtratorDeFaturas() { }
ExtratorDeFaturas::ExtratorDeFaturas(const string & caminhoPrograma) {
	setCaminhoDoPrograma(caminhoPrograma);
}

void ExtratorDeFaturas::setCaminhoDoPrograma(const string & caminhoPrograma) {
	this->caminhoPrograma = caminhoPrograma;
}

string ExtratorDeFaturas::getCaminhoDoPrograma() {
	return caminhoPrograma;
}

const char ARRAB = '\\';
const char DIR_FATURAS[] = "faturas\\";
bool ExtratorDeFaturas::salvarCopiaArquivoTexto(const string & caminhoArquivo, const string & caminhoPrograma) {

	char comando[1000];
	string filePath;
	vector<string> files;
	ES::quebrarTexto(files, caminhoArquivo, ARRAB);

	if (!ES::copiarArquivo(FILE_SAIDA_TMP, caminhoPrograma + DIR_FATURAS))
		return erro("\nAVISO: N�o foi poss�vel guardar um c�pia do arquivo texto desta fatura. Pois a convers�o do PDF falhou");

	cout << "A fatura foi salva como  texto em ";
	return true;
	
}

/*Se o caminho do programa estiver indefinido retorna false, sem definir uma mensagem de erro.*/
bool ExtratorDeFaturas::importarFaturaPDF(const string& caminhoArquivo) {
	Fatura fatura;

	if (caminhoPrograma.empty()) return false;

	cout << MSG_CONVERTENDO_PDF;
	if (!ES::PDFToTextTable(caminhoArquivo, caminhoPrograma, FILE_SAIDA_TMP)) {
		setMensagemErro(MSGE_ARQUIVO_NAO_LIDO);
		return false;
	}


	string conteudoConta;
	vector<string> linhasArquivo;

	cout << MSG_LENDO_FATURA;
	if (!ES::lerArquivoTexto(conteudoConta, FILE_SAIDA_TMP)) {
		setMensagemErro(MSGE_ARQUIVO_CORROMPIDO);
		return false;
	}

	cout << MSG_OBTENDO_INFO;
	ES::quebrarTexto(linhasArquivo, conteudoConta, BARRA_N);
	if (!importarFatura(linhasArquivo)) return false;

	return true;
}

string extrairPalavra(const string linha, size_t numeroItem = 0) {

	vector<string> palavras;
	ES::quebrarTexto(palavras, linha, ESPACO);

	if (palavras.size() < numeroItem + 1) return string();

	return palavras[numeroItem];
}


/*A partir da linha contendo o a cep e a cidade do cliente, extrai e armazena em um objeto esses itens.
Retorna false em caso de falha e armazena uma mensagem de erro contendo a causa*/
bool ExtratorDeFaturas::extrairCEPCidade(Cliente & cliente, const string & linha) {
	vector<string> palavras;

	ES::quebrarTexto(palavras, linha, ESPACO);

	if (palavras.empty()) return false;

	cliente.setCEP(palavras[0]);
	cliente.setCidade(palavras[1] + palavras[2]);

	return true;
}


/*A partir de um vector com as linhas do arquivo e uma posicao de leitura, extrai e armazena em um objeto
os campos que correspondem ao nome e endere�o do cliente.
Retorna false em caso de falha e armazena uma mensagem erro contendo a causa*/
bool ExtratorDeFaturas::extrairNomeEEndereco(Cliente & cliente, const vector<string> & linhas, int & posicao) {
	vector<string> itens;
	int numeroItens = 4;
	posicao = 0;
	string resultadoRegex;

	for (; (int) itens.size() < numeroItens && posicao < (int)linhas.size(); posicao++) {
		if (!ES::procurarPadrao(resultadoRegex, linhas[posicao], REGEX_CEP_E_NOMES)) continue;
		ES::quebrarTexto(itens, linhas[posicao], BARRA_N);

	}

	if (itens.size() == numeroItens) {
		cliente.setNome(ES::quebrarString(itens[0]));
		cliente.setRua(ES::quebrarString(itens[1]));
		cliente.setBairro(ES::quebrarString(itens[2]));
		if (extrairCEPCidade(cliente, itens[3]))
			return true; //s� retorna true se todas as validacoes derem certo
	}

	return erro(MSGE_DADOS_INCOMPLETOS_CLIENTE);
}

bool ExtratorDeFaturas::extrairDadosCliente(const vector<string> & linhas) {
	vector<string> palavras;
	Cliente cliente;

	int posicao = 0;
	posicao = ES::procurarLinha(palavras, linhas, STR_N_DO_CLIENTE, posicao);

	if (palavras.empty())
		return erro(MSGE_FATURA_INVALIDA);

	if (!obterNumeroClienteEInstalacao(linhas, cliente, posicao)) return false;

	//Obtendo endere�o do cliente
	if (!extrairNomeEEndereco(cliente, linhas, ++posicao)) return false;

	//Obtendo CPF
	cliente.setCPF(extrairPalavra(linhas[posicao], 1));
	if (cliente.getCPF().empty()) return false;

	fatura.setCliente(cliente);

	return true;
}


bool ExtratorDeFaturas::obterPrecoEConsumo(ValoresFaturados & valores, const vector<string> & linhas, int & posicao) {

	//Exemplo da linha sendo lida nesta fun��o:
	//O pagamento desta conta n�o quita d�bitos anteriores.		Energia El�trica   kWh	125	0,97485177	121,84	

	int numeroLinha = ES::procurarNumeroLinha(linhas, LINHA_ENERGIA, posicao);
	vector<string> palavras;
	size_t ultimaPosicao;
	if (numeroLinha != -1) {
		ES::quebrarTexto(palavras, linhas[numeroLinha], ESPACO);

		ultimaPosicao = palavras.size() - 1;
		if (ultimaPosicao <= 1) return false;

		valores.setValorDaFatura(ES::strToDouble(palavras[ultimaPosicao]));
		valores.setPreco(ES::strToDouble(palavras[--ultimaPosicao]));
		valores.setConsumo(ES::strToInt(palavras[--ultimaPosicao]));

		return true;
	}
	return false;
}
bool ExtratorDeFaturas::extrairValoresFaturados(const vector<string> & linhas, int & posicao) {
	ValoresFaturados valores;
	if (!obterPrecoEConsumo(valores, linhas, posicao)) return erro(MSGE_VALORES_FATURADOS);

	int posicaoCopia = posicao;

	//Procurando contrib. iluminac�o. (Se falhar, volta a posicao para a copia)
	string iluminacao = ES::procurarItem(linhas, LINHA_ILUMINACAO, posicao);
	if (iluminacao.empty()) posicao = posicaoCopia;

	valores.setValorIluminacaoPublica(ES::strToDouble(iluminacao));

	//Procurando e definindo bandeiras
	valores.definirAdicionais(ES::strToDouble(ES::procurarItem(linhas, LINHA_BANDEIRA_AMARELA, posicao)),
		ES::strToDouble(ES::procurarItem(linhas, LINHA_BANDEIRA_VERMELHA, posicaoCopia)));


	fatura.setValoresFaturados(valores);
	return true;
}
bool ExtratorDeFaturas::salvarFatura() {

	ArquivoFatura arquivoFatura;
	arquivoFatura.abrir(FILE_FATURA_DAT);

	int registro = arquivoFatura.pesquisarFatura(fatura.getCliente().getNumero(),
		fatura.getMesReferente(), fatura.getAnoReferente());

	if (registro != -1) {
		cout << endl << MSG_FATURA_JA_EXISTE;

		return true;
	}
	arquivoFatura.escreverObjeto(fatura);

	arquivoFatura.fechar();

	return true;
}


void ExtratorDeFaturas::popularConsumo(const vector<string> & itensLinha, const string & numeroInstalacao, int mes, int ano) {
	
	//verifica se a posicao 0 da linha corresponde ao mes/ano. se sim, pula para a posicao 1
	int posicao = ES::isNumber(itensLinha[0]) ? 0 : 1; 
	Consumo consumo;
	
	consumo.setMes(mes);
	consumo.setAno(ano);
	consumo.setConsumoKWh(ES::strToInt(itensLinha[posicao++]));
	consumo.setMediaConsumoDiario(ES::strToDouble(itensLinha[posicao++]));
	consumo.setDias(ES::strToInt(itensLinha[posicao++]));
	consumo.setNumeroInstalacao(numeroInstalacao);

	fatura.adicionarHistoricoConsumo(consumo);
}


bool ExtratorDeFaturas::extrairHistoricoConsumo(const vector<string> & linhas, int & posicao, const string & numeroInstalacao) {
	int numeroLinha = ES::procurarNumeroLinha(linhas, LINHA_HISTORICO, posicao);

	if (numeroLinha == -1) return erro(MSGE_HISTORICO_NAO_ENCONTRADO); else posicao = numeroLinha;

	int valoresComputados = 0;
	string padraoEncontrado;
	vector<string> itensLinha;
	
	int mes = fatura.getMesReferente();
	int ano = fatura.getAnoReferente();

	for (++posicao; (size_t)posicao < linhas.size(); posicao++) {

		if (valoresComputados == TAMANHO_HISTORICO) break;

		itensLinha.clear();

		ES::quebrarTexto(itensLinha, linhas[posicao], ESPACO);

		if (!ES::procurarPadrao(padraoEncontrado, linhas[posicao], REGEX_LINHA_HISTORICO)) continue;

		popularConsumo(itensLinha, numeroInstalacao, mes, ano);

		valoresComputados++;
		
		mes--;
		if (mes == 0) { ano--; mes = 12; };
	}

	if (valoresComputados != TAMANHO_HISTORICO) return erro(MSGE_HISTORICO_INCONSISTENTE);

	return true;
}

bool ExtratorDeFaturas::importarFatura(vector<string> & linhas) {
	int posicao = 0;
	vector<string> palavras;

	string numeroInstalacao;

	if (extrairDadosCliente(linhas))

		if (extrairMesAnoReferente(linhas, posicao))

			if (extrairDatasDeLeitura(linhas, posicao))

				if (extrairValoresFaturados(linhas, posicao))

					if (extrairHistoricoConsumo(linhas, posicao, numeroInstalacao))

						if (extrairMesVencimentoEValor(linhas, posicao)) {

							salvarFatura();

							return true;
						}

	return false;
}

bool ExtratorDeFaturas::extrairMesAnoReferente(const vector<string>& linhasArquivo, int & posicaoAtual) {
	string data = ES::procurarPadrao(linhasArquivo, posicaoAtual, REGEX_MES_REFERENTE);
	if (data.empty() || !fatura.setMesAnoReferente(data)) { return erro("N�o foi poss�vel computar datas da fatura"); return false; }

	return true;
}

const char MSGE_DATAS_LEITURA[] = "FALHA:\n N�o foi poss�vel computar as datas de leitura";
bool ExtratorDeFaturas::extrairDatasDeLeitura(const vector<string>& linhasArquivo, int & posicaoAtual)
{

	string datas = ES::procurarPadrao(linhasArquivo, posicaoAtual, REGEX_DATAS_LEITURA);
	if (datas == VAZIO) 
		return erro(MSGE_DATAS_LEITURA);

	vector<string> linha;
	ES::quebrarTexto(linha, datas, ESPACO);

	if (linha[0].empty())
		linha.erase(linha.begin());


	if (fatura.getAnoReferente() == 0) {
		int ano = procurarAnoReferente(linhasArquivo, posicaoAtual);
		if (ano == 0) return false;
		fatura.setAnoReferente(ano);
	}

	formatarEAdicionarDatasDeLeitura(linha[0], linha[1], linha[2]);


	return true;
}

//old
int ExtratorDeFaturas::procurarAnoReferente(const vector<string> & linhasArquivo, int posicaoAtual) {
	vector<string> data;
	ES::quebrarTexto(data, linhasArquivo[posicaoAtual + 1], BARRA);
	return ES::strToInt(data[2]);
}

/*Insere �s datas de leitura, anterior, atual e proxima, seus respectivos anos. Em seguida, as armazena no objeto fatura.*/
bool ExtratorDeFaturas::formatarEAdicionarDatasDeLeitura(const string & dataLeituraAnterior, const string & dataLeituraAtual, const string & proximaDataLeitura, int ano) {

	if (ano == 0) ano = fatura.getAnoReferente();

	string anoAtualStr = BARRA + ES::intToStr(ano);

	//Se a data da leitura anterior for em dezembro, ent�o decrementa-se o ano  atual para ela.
	if (obterMesData(dataLeituraAnterior) == 12)
		fatura.setDataDeLeituraAnterior(dataLeituraAnterior + BARRA + ES::intToStr(ano - 1));
	else
		fatura.setDataDeLeituraAnterior(dataLeituraAnterior + anoAtualStr);

	//Se a data da proxima leitura for em janeiro, ent�o incrementa-se o ano atual para ela.
	if (obterMesData(proximaDataLeitura) == 1)
		fatura.setProximaDataDeLeitura(proximaDataLeitura + BARRA + ES::intToStr(ano + 1));
	else
		fatura.setProximaDataDeLeitura(proximaDataLeitura + anoAtualStr);

	fatura.setDataDeLeitura(dataLeituraAtual + anoAtualStr);

	return true;

}

/*Retorna o n�mero de um m�s a partir de uma data no formato "MM/yyyy"*/
int ExtratorDeFaturas::obterMesData(const string & data) {
	vector<string> v;
	ES::quebrarTexto(v, data, BARRA);
	return ES::strToInt(v[0]);

}


bool ExtratorDeFaturas::obterNumeroClienteEInstalacao(const vector<string>& linhasArquivo, Cliente & cliente, int & posicaoAtual)
{
	//Exemplo de linha que esta fun��o est� tentando encontrar e processar:
	// 7008637570                                  3000755750

	string numeros = ES::procurarPadrao(linhasArquivo, posicaoAtual, REGEX_CLIENTE_INSTALACAO);
	vector<string> itens;

	ES::quebrarTexto(itens, numeros, ESPACO);

	if (itens.size() != 2) return erro(MSGE_NUMEROS_NAO_ENCONTRADOS);

	cliente.setNumero(itens[0]);
	fatura.setNumeroInstalacao(itens[1]);

	return true;
}

bool ExtratorDeFaturas::extrairMesVencimentoEValor(vector<string>& linhasArquivo, int & posicaoAtual)
{
	string dataVencimentoEValor = ES::procurarPadrao(linhasArquivo, posicaoAtual, REGEX_DATA_E_VALOR);

	if (dataVencimentoEValor.empty()) return erro(MSGE_DATA_E_VALOR_NAO_ENCONTRADO);

	vector<string> itens;
	ES::quebrarTexto(itens, dataVencimentoEValor, ESPACO);

	//A string com o valor pode estar como: dd/MM/yyyy R$ xx,xx ou dd/MM/yyyy R$xx,xx
	if (itens.size() == 3)
		//apagando a palavra 'R$' na posi�ao 1
		itens.erase(itens.begin() + 1);
	else { 
		//apagando a string 'R$' na frente do valor
		itens[1].erase(itens[1].begin());
		itens[1].erase(itens[1].begin());
	}

	fatura.setDataVencimento(itens[0]);
	fatura.setValorAPagar(ES::strToDouble(itens[1]));

	return true;

}

bool ExtratorDeFaturas::obterHistoricoConsumo(const string & linha) {
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

