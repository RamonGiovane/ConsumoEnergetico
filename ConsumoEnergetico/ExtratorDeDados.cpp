#include "ExtratorDeDados.h"
#include "Fatura.h"
#include "ArquivoTexto\ArquivoTexto.h"
#include "EntradaESaida.h"
#include "ArquivoHistorico.h"
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
	ES::quebrarTexto(linhasArquivo, conteudoConta, BARRA_N, ";");
	if (!importarFatura(linhasArquivo)) return false;
	
	return true;
}
void extrairString(string & resultado, const vector<string> & palavras, const string & termoFinal) {
	for (string s : palavras) {
		if (s.find(termoFinal) != std::string::npos) break;
		resultado.append(s).append(" ");
	}
}
bool ExtratorDeDados::importarFatura(const vector<string> & linhas) {
	int posicao = 0;
	vector<string> palavras;
	posicao = ES::procurarLinha(palavras, linhas, "Nº DO CLIENTE", posicao);
	string nome;
	extrairString(nome, palavras, "Nº DO CLIENTE");
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