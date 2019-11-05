#include "ExtratorDeDados.h"
#include "ContaDigital.h"
#include "ArquivoTexto\ArquivoTexto.h"
#include "EntradaESaida.h"


ExtratorDeDados::ExtratorDeDados(ContaDigital conta)
{
	this->conta = conta;
}

bool ExtratorDeDados::lerArquivoTexto(string& conteudoArquivo) {
	ArquivoTexto arquivo;
	arquivo.abrir(ARQUIVO_SAIDA, TipoDeAcesso::LEITURA);
	conteudoArquivo = arquivo.ler();
	return conteudoArquivo == "NULL" ? false : true;
}


bool ExtratorDeDados::obterInformacoes(vector<string>& linhasArquivo) {

	if (linhasArquivo[0] != "Valores Faturados") return false;

	ValoresFaturados fatura;
	Cliente cliente;
	int posicaoAtual = 0;

	obterValoresFaturados(linhasArquivo, fatura, posicaoAtual);
	obterHistoricoConsumo(linhasArquivo, posicaoAtual);
	obterCliente(linhasArquivo, cliente, posicaoAtual);
	obterDemaisInformacoes(linhasArquivo, cliente, posicaoAtual);

	conta.setCliente(cliente);
	conta.setValoresFaturados(fatura);

	cout << conta.toString();

	return true;
}
bool ExtratorDeDados::obterDemaisInformacoes(vector<string>& linhasArquivo, Cliente & cliente, int & posicaoAtual)
{
	vector<string> linha;

	//Separando Numero do cliente e numero da instalacao
	ES::quebrarTexto(linha, linhasArquivo[++posicaoAtual], ' ');

	cliente.setNumero(linha[0]);
	conta.setNumeroInstalacao(linha[1]);

	//Separando Numero do cliente e numero da instalacao
	ES::quebrarTexto(linha, linhasArquivo[++posicaoAtual], ' ');

	linha = vector<string>();

	//Separando mes, vencimento e valor a pagar
	ES::quebrarTexto(linha, linhasArquivo[++posicaoAtual], ' ');
	conta.setMesReferente(linha[0]);
	conta.setDataVencimento(linha[1]);
	conta.setValorAPagar(ES::strToDouble(linha[2]));


	return true;

}
bool ExtratorDeDados::obterCliente(vector<string>& linhasArquivo, Cliente & cliente, int & posicaoAtual) {

	while (linhasArquivo[posicaoAtual] != "Comprovante de Pagamento")
		posicaoAtual++;

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
	string detalheErro;

	double valor, preco, iluminacao, bandeiraAmarela, bandeiraVermelha;
	int consumo;

	vector<string> linhaEnergiaEletrica =
		procurarLinha(linhasArquivo, "Energia El�trica kWh", posicaoAtual, "Encargos/Cobran�as");

	if (linhaEnergiaEletrica.empty()) {
		detalheErro = "Imposs�vel computar linha sobre Energia El�trica kWh";
		return false;
	}

	int tamanhoLinhaEnergia = linhaEnergiaEletrica.size();

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
	string termo = "M�S/ANO CONSUMO kWh M�DIA kWh/Dia Dias";
	posicaoAtual = procurarNumeroLinha(linhasArquivo, termo, posicaoAtual);
	if (posicaoAtual == -1) return false;
	for (int i = 0; i < 13; i++) {
		if (!obterHistoricoConsumo(linhasArquivo[++posicaoAtual]))
			return false;
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

	conta.adicionarHistoricoConsumo(consumo);

	return true;
}

int ExtratorDeDados::procurarNumeroLinha(const vector<string>& linhasArquivo, const string & termoPesquisado, int posicaoAtual) {
	cout << linhasArquivo[posicaoAtual];
	for (; posicaoAtual < linhasArquivo.size() - 1; posicaoAtual++) {
		if (linhasArquivo[posicaoAtual].find(termoPesquisado) != std::string::npos)
			return posicaoAtual;
	}
	return -1;

}



/*
Procura nas linhas do arquivo (const vector<string> & linhasArquivo) o valor correpondente � um termo pesquisado, a partir do numero de uma linha
at� uma linha em que seu conte�do seja especificado por um termo de parada (const string & termoFinal).
Por exemplo, pesquisando o termo "Bandeira Vermelha", sendo as linhas subseguintes � posi��o especificada:

"Energia El�trica kWh 0,66833000
Adicional Bandeiras - J� inclu�do no Valor a Pagar
Bandeira Vermelha 9,81
Hist�rico de Consumo
M�S/ANO CONSUMO kWh M�DIA kWh/Dia Dias
SET/19 162 5,22 31"

Seria retornado o valor "9,81" como string. A pesquisa seria feita at� o termo final "Hist�rico de Consumo" ou at� o final do vector.
O valor a ser retornado � sempre o �ltimo item da linha separado por espa�os em branco. Importante notar que a refer�ncia contendo o n�mero
da linha atual na chamada da fun��o ser� alterada, passando a ter o n�mero da linha em que a pesquisa finalizou.
Se o termo final for uma string vazia, a pesquisa � finalizada na pr�xima posi��o ap�s �quela que corresponder ao termo correto ou
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

	//Iterar pelas linhas at� encontrar o fim
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


