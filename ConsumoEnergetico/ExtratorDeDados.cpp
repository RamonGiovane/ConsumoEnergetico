#include "ExtratorDeDados.h"
#include "Fatura.h"
#include "ArquivoTexto\ArquivoTexto.h"
#include "EntradaESaida.h"
#include "ArquivoHistorico.h"
#include "ArquivoFatura.h"
#include "Constantes.h"
#include <regex>


ExtratorDeDados::ExtratorDeDados(){ }
ExtratorDeDados::ExtratorDeDados(const string & caminhoPrograma) {
	setCaminhoDoPrograma(caminhoPrograma);
}

void ExtratorDeDados::setCaminhoDoPrograma(const string & caminhoPrograma) {
	this->caminhoPrograma = caminhoPrograma;
}

string ExtratorDeDados::getCaminhoDoPrograma() {
	return caminhoPrograma;
}



/*Se o caminho do programa estiver indefinido retorna false, sem definir uma mensagem de erro.*/
bool ExtratorDeDados::importarFaturaPDF(const string& caminhoArquivo) {
	Fatura fatura;
	
	if (caminhoPrograma.empty()) return false;

	cout << MSG_CONVERTENDO_PDF;
	if (!ES::PDFToTextTable(caminhoArquivo, caminhoPrograma, FILE_SAIDA_TMP)) {
		mensagemErro = MSG_ERRO_ARQUIVO_NAO_LIDO;
		return false;
	}

	string conteudoConta;
	vector<string> linhasArquivo;

	cout << MSG_LENDO_FATURA;
	if (!lerArquivoTexto(conteudoConta)) {
		mensagemErro = MSG_ERRO_ARQUIVO_CORROMPIDO;
		return false;
	}

	cout << MSG_OBTENDO_INFO;
	ES::quebrarTexto(linhasArquivo, conteudoConta, BARRA_N);
	if (!importarFatura(linhasArquivo)) return false;
	
	return true;
}


string extrairString(const vector<string> & palavras, const string & termoFinal, int posicaoInicial = 0) {
	string resultado;
	string item;
	for (; posicaoInicial < palavras.size(); posicaoInicial++) {
		item = palavras[posicaoInicial];
		if (item == termoFinal) break;
		resultado.append(item).append(" ");
	}
	return resultado;

}
const string SVAZIO = "";
string extrairString(const vector<string> & palavras, int posicaoInicial = 0) {
	
	return extrairString(palavras, SVAZIO, posicaoInicial);
}
string extrairString(const string & texto, const string & termoFinal, int posicaoInicial = 0) {
	vector<string> palavras;
	ES::quebrarTexto(palavras, texto, ESPACO);
	return extrairString(palavras, posicaoInicial);
	
}




string extrairPalavra(const string linha, int numeroItem = 0) {

	vector<string> palavras;
	ES::quebrarTexto(palavras, linha, ESPACO);
	
	if (palavras.size() < numeroItem + 1) return string();
	
	return palavras[numeroItem];
}



const char MSG_ARQUIVO_CORROMPIDO[] = "Provavelmente o arquivo PDF está corrompido.";
const char MSG_FATURA_INVALIDA[] = "\nFALHA: O arquivo fornecido não corresponde a uma fatura CEMIG.";
const char STR_N_DO_CLIENTE[] = "Nº DO CLIENTE";
const string MSGE_DADOS_INCOMPLETOS_CLIENTE = "\nFALHA: Dados do cliente inconsistentes." + string(MSG_ARQUIVO_CORROMPIDO);

/*A partir da linha contendo o a cep e a cidade do cliente, extrai e armazena em um objeto esses itens.
Retorna false em caso de falha e armazena uma mensagem de erro contendo a causa*/
bool ExtratorDeDados::extrairCEPCidade(Cliente & cliente, const string & linha) {
	vector<string> palavras;
	
	ES::quebrarTexto(palavras, linha, ' ');
	
	if (palavras.empty()) return false;
	
	cliente.setCEP(palavras[0]);
	cliente.setCidade(palavras[1] + palavras[2]);
	
	return true;
}

/*A partir de um vector com as linhas do arquivo e uma posicao de leitura, extrai e armazena em um objeto
os campos que correspondem ao endereço do cliente.
Retorna false em caso de falha e armazena uma mensagem erro contendo a causa*/
bool ExtratorDeDados::extrairEndereco(Cliente & cliente, const vector<string> & linhas, int & posicao) {
	vector<string> itens;
	int numeroItens = 4;
	posicao = 0;
	string resultadoRegex;

	for (; itens.size() < numeroItens && posicao < linhas.size(); posicao++) {
		if (!ES::procurarPadrao(resultadoRegex, linhas[posicao], "(^[A-Z]+)|(^\\d{5}[-]\\d{3})")) continue;
		ES::quebrarTexto(itens, linhas[posicao], BARRA_N);

	}

	if (itens.size() == numeroItens) {
		cliente.setRua(itens[1]);
		cliente.setBairro(itens[2]);
		if (extrairCEPCidade(cliente, itens[3]))
			return true; //só retorna true se todas as validacoes derem certo
	}

	mensagemErro = MSGE_DADOS_INCOMPLETOS_CLIENTE;
	return false;
}

bool ExtratorDeDados::extrairDadosCliente(string & numeroDaInstalacao, const vector<string> & linhas) {
	vector<string> palavras;
	Cliente cliente;
	int posicao = 0;
	posicao = ES::procurarLinha(palavras, linhas, STR_N_DO_CLIENTE, posicao);

	if (palavras.empty()) {
		mensagemErro = MSG_FATURA_INVALIDA;
		return false;
	}

	cliente.setNome(extrairString(palavras));

	//Obtendo numero cliente e da instalacao e jogando no vector
	ES::quebrarTexto(palavras, linhas[++posicao], ' ');
	
	//Obtendo do vector
	cliente.setNumero(palavras[palavras.size() - 1]);
	palavras.pop_back();
	numeroDaInstalacao = palavras[palavras.size() - 1];
	palavras.pop_back();

	//Obtendo endereço do cliente
	if (!extrairEndereco(cliente, linhas, ++posicao)) return false;

	//Obtendo CPF
	cliente.setCPF(extrairPalavra(linhas[posicao], 1));
	if (cliente.getCPF().empty()) return false;

	fatura.setCliente(cliente);

	return true;
}
const char LINHA_ENERGIA[] = "Energia Elétrica";
const char LINHA_ILUMINACAO[] = "Contrib Ilum Publica Municipal";
const char MSGE_VALORES_FATURADOS[] = "\nFALHA: Não foi possível computar os valores faturados.";

bool ExtratorDeDados::erro(const string & mensagemErro) {
	this->mensagemErro = mensagemErro;
	return false;
}

bool ExtratorDeDados::obterPrecoEConsumo(ValoresFaturados & valores, const vector<string> & linhas, int & posicao) {
	
	//Exemplo da linha sendo lida nesta função:
	//O pagamento desta conta não quita débitos anteriores.		Energia Elétrica   kWh	125	0,97485177	121,84	

	int numeroLinha = ES::procurarNumeroLinha(linhas, LINHA_ENERGIA, posicao);
	vector<string> palavras;
	int ultimaPosicao;
	if (numeroLinha != -1) {
		ES::quebrarTexto(palavras, linhas[numeroLinha], ESPACO);
		
		ultimaPosicao = palavras.size() - 1;
		if (ultimaPosicao <= 1) return false;
		
		valores.setValorDaFatura(ES::strToInt(palavras[ultimaPosicao]));
		valores.setPreco(ES::strToDouble(palavras[--ultimaPosicao]));
		valores.setConsumo(ES::strToInt(palavras[--ultimaPosicao]));
		
		return true;
	}
	return false;
}
bool ExtratorDeDados::obterValoresFaturados(const vector<string> & linhas, int & posicao) {
	ValoresFaturados valores;
	if(!obterPrecoEConsumo(valores, linhas, posicao)) return erro(MSGE_VALORES_FATURADOS);
	
	int posicaoCopia = posicao;

	//Procurando contrib. iluminacão. (Não pode falhar)
	string iluminacao = ES::procurarItem(linhas, LINHA_ILUMINACAO, posicao);
	if (iluminacao.empty()) return false;

	valores.setValorIluminacaoPublica(ES::strToDouble(iluminacao));
	
	//Procurando e definindo bandeiras
	valores.definirAdicionais(ES::strToDouble(ES::procurarItem(linhas, LINHA_BANDEIRA_AMARELA, posicao)), 
		ES::strToDouble(ES::procurarItem(linhas, LINHA_BANDEIRA_VERMELHA, posicaoCopia)));


	fatura.setValoresFaturados(valores);
	return true;
}
bool ExtratorDeDados::salvarFatura() {

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

const char LINHA_HISTORICO[] = "Histórico ";
const char MSGE_HISTORICO_NAO_ENCONTRADO[] = "\nFALHA: Dados de histórico de consumo não encontrados. ";
const char MSGE_HISTORICO_INCONSISTENTE[] = "\nFALHA: Dados de histórico de consumo inconsistentes. ";
const char REGEX_DATA_HISTORICO[] = "[A-Z]{3}[/]\\d{2}";
const int TAMANHO_HISTORICO = 13;

void ExtratorDeDados::popularConsumo(const vector<string> & itensLinha, const string & numeroInstalacao, const string & mesAno) {
	int mes, ano;
	ES::strMesAnoToInt(mesAno, mes, ano);

	Consumo consumo;

	consumo.setMes(mes);
	consumo.setAno(ano);
	consumo.setConsumoKWh(ES::strToInt(itensLinha[1]));
	consumo.setMediaConsumoDiario(ES::strToInt(itensLinha[2]));
	consumo.setDias(ES::strToInt(itensLinha[3]));
	consumo.setNumeroInstalacao(numeroInstalacao);

	fatura.adicionarHistoricoConsumo(consumo);
}


bool ExtratorDeDados::extrairHistoricoConsumo(const vector<string> & linhas, int & posicao, const string & numeroInstalacao) {
	int numeroLinha = ES::procurarNumeroLinha(linhas, LINHA_HISTORICO, posicao);
	
	if (numeroLinha == -1) return erro(MSGE_HISTORICO_NAO_ENCONTRADO); else posicao = numeroLinha;
	
	int valoresComputados = 0;
	string mesAno;
	vector<string> itensLinha;
	
	for (++posicao; (size_t)posicao < linhas.size(); posicao++) {

		if (valoresComputados == TAMANHO_HISTORICO) break;

		itensLinha.clear();

		ES::quebrarTexto(itensLinha, linhas[posicao], ESPACO);

		if (!ES::procurarPadrao(mesAno, itensLinha[0], REGEX_DATA_HISTORICO)) continue;

		popularConsumo(itensLinha, numeroInstalacao, mesAno);	

		valoresComputados++;
	}

	if (valoresComputados != TAMANHO_HISTORICO) return erro(MSGE_HISTORICO_INCONSISTENTE);

	return true;
}

bool ExtratorDeDados::importarFatura(vector<string> & linhas) {
	int posicao = 0;
	vector<string> palavras;

	string numeroInstalacao;

	if(extrairDadosCliente(numeroInstalacao, linhas))
	
	if(obterMesAnoReferente(linhas, posicao))

	if(obterDatasDeLeitura(linhas, posicao))

	if(obterValoresFaturados(linhas, posicao))

	if(extrairHistoricoConsumo(linhas, posicao, numeroInstalacao))

	if (obterMesVencimentoEValor(linhas, posicao)) {
		
		fatura.setNumeroInstalacao(numeroInstalacao); //isso nao deve ser colocado na fatura

		salvarFatura();

		return true;
	}

	return false;
}




//(Fatura & fatura, const string & caminhoPrograma, const string & caminhoArquivo)
bool ExtratorDeDados::lerFaturaPDF(Fatura & fatura, const string & caminhoPrograma, const string& caminhoArquivo) {
	
	this->caminhoPrograma = caminhoPrograma;

	string conteudoConta;
	vector<string> linhasArquivo;
	const char  DELIMITADOR = '\n';
	static Fatura faturaVazia = Fatura();

	ES::removerArquivo(FILE_SAIDA_TMP);

	cout << "\nConvertendo PDF... ";
	if (!ES::PDFToText(caminhoArquivo, caminhoPrograma, FILE_SAIDA_TMP)) {
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





bool ExtratorDeDados::lerArquivoTexto(string& conteudoArquivo) {
	ArquivoTexto arquivo;
	arquivo.abrir(FILE_SAIDA_TMP, TipoDeAcesso::LEITURA);
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
	if (!obterHistoricoConsumo(linhasArquivo, posicaoAtual, TRECHO_BANDEIRA_AMARELA)) return false;
	if (!obterValoresFaturados(linhasArquivo, valores, posicaoAtual)) return false;
	if (!obterMesVencimentoEValor(linhasArquivo, posicaoAtual)) return false;


	fatura.setCliente(cliente);
	fatura.setValoresFaturados(valores);

	cout << endl << endl << fatura.toString() << endl;

	return true;

}


bool ExtratorDeDados::obterMesAnoReferente(const vector<string>& linhasArquivo, int & posicaoAtual) {
	string data = ES::procurarPadrao(linhasArquivo, posicaoAtual, REGEX_MES_REFERENTE);
	if (data.empty() || !fatura.setMesAnoReferente(data)) { mensagemErro = "Não foi possível computar datas da fatura"; return false; }
	
	return true;
}

bool ExtratorDeDados::obterDatasDeLeitura(const vector<string>& linhasArquivo, int & posicaoAtual)
{
	
	string datas = ES::procurarPadrao(linhasArquivo, posicaoAtual, REGEX_DATAS_LEITURA);
	if (datas == "") { mensagemErro = "Não foi possível computar as datas de leitura"; return false; }

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
const char MSGE_DATA_E_VALOR_NAO_ENCONTRADO[] = "\nFALHA: Dados da fatura incompletos. Data de vencimento e valor a pagar não encontrados.\nProvavelmente o arquivo está corrompido";
const char REGEX_DATA_E_VALOR[] = "\\.*\\d{2}[/]\\d{2}[/]\\d{4}.*\\d{1,9}[,]\\d{2}";
bool ExtratorDeDados::obterMesVencimentoEValor(vector<string>& linhasArquivo, int & posicaoAtual)
{
	string dataVencimentoEValor = ES::procurarPadrao(linhasArquivo, posicaoAtual, REGEX_DATA_E_VALOR);

	if (dataVencimentoEValor.empty()) return erro(MSGE_DATA_E_VALOR_NAO_ENCONTRADO);
	
	vector<string> itens;
	ES::quebrarTexto(itens, dataVencimentoEValor, ESPACO);

	if (itens.size() == 3)
		itens.erase(itens.begin() + 1);

	fatura.setDataVencimento(itens[0]);
	fatura.setValorAPagar(ES::strToDouble(itens[1]));
	
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


bool ExtratorDeDados::lerArquivoDeConsumo(Consumo & consumo, const string & numeroCliente, const string & caminhoArquivoEntrada) {
	ArquivoTexto arquivo;
	arquivo.abrir(caminhoArquivoEntrada, LEITURA);
	int mes = 0, ano = 0;
	string arquivoTexto = arquivo.ler();
	vector<string> linhas;
	int mesArquivo, anoArquivo;
	ES::quebrarTexto(linhas, arquivoTexto, '\n');
	if (linhas.empty()) { mensagemErro = MSG_ERRO_ARQUIVO_ENTRADA; return false; }

	if (!lerValidarCabecalhoArquivoDeConsumo(linhas[100], mesArquivo, anoArquivo)) return false;

	arquivo.fechar();

	double consumoKWh = calcularConsumo(linhas, mes, ano);
	if (consumoKWh == -1) return false;


	consumo.setConsumoKWh(consumoKWh);
	return 1;
	//return gerarDadosConusmo(consumo, dias, mes, ano);

}
bool gerarDadosConsumo(Consumo * consumo, const string & numeroInstalacao, int dias, int mes, int ano) {
	ArquivoHistorico arquivo;
	arquivo.abrir(FILE_HISTORICO_DAT);

	int registro = arquivo.pesquisarConsumoNoHistorico(numeroInstalacao, mes, ano);
	if (registro == -1) return false;
	consumo =  arquivo.lerObjeto(registro);
	//consumo = new Consumo(*consumoCalculado);




}

double ExtratorDeDados::calcularConsumo(const vector<string> & linhasArquivo, int mes, int ano) {
	double valorConsumo, totalConsumo = 0;

	for (size_t i = 1; i < linhasArquivo.size(); i++) {
		valorConsumo = obterConsumoKWh(linhasArquivo[i]);
		if (valorConsumo == -1) {
			mensagemErro = MSG_SINTAXE_INVALIDA + ES::intToStr(i+1) + "\n\t>> " + linhasArquivo[i];
			return -1;
		}
		totalConsumo += valorConsumo;
	}

	return totalConsumo;
}

double ExtratorDeDados::obterConsumoKWh(const string & linhaDoConsumo) {
	vector<string> itemsLinha;
	double horas, watts;
	ES::quebrarTexto(itemsLinha, linhaDoConsumo, ' ');

	//A linha de consumo será lida de trás para frente, por isso armazena-se a última posição
	int posicao = itemsLinha.size() - 1;

	/*Valida se a linha tem os elementos minimos necessarios e no mesmo if se o
	* primeiro valor númerico (kWh ou h) é mesmo um número*/
	if (posicao < 2 || !ES::isNumber(itemsLinha[posicao - 1])) return -1;

	if (itemsLinha[posicao] == "kWh") {
		return ES::strToDouble(itemsLinha[posicao - 1]);
	}

	if (itemsLinha[posicao] == "h") {
		horas = ES::strToDouble(itemsLinha[--posicao]);
		if (itemsLinha[--posicao] == "w" && ES::isNumber(itemsLinha[posicao - 1])) {
			watts = ES::strToDouble(itemsLinha[posicao - 1]);

			return watts / 1000 * horas;
		}
	}

	return -1;

}


bool ExtratorDeDados::lerValidarCabecalhoArquivoDeConsumo(const string & linhaCabecalho, int & mes, int & ano) {
	vector<string> cabecalho;
	ES::quebrarTexto(cabecalho, linhaCabecalho, ' ');
	string dataInvalida = "";
	if (cabecalho[0] == "#" && cabecalho.size() == 4) {
		if (!ES::strMesAnoToInt(cabecalho[3], mes, ano))
			dataInvalida = string("\n") + MSG_DATA_INVALIDA;
		else
			return true;
	}
	mensagemErro = string(MSG_SINTAXE_INVALIDA) + " 1.\n\t>> " + cabecalho[0] + "\n" + dataInvalida;
	return false;
}

string ExtratorDeDados::getMensagemErro() {
	return mensagemErro;
}