#include "ArquivoFatura.h"


#include <iostream>
#include <io.h>
#include "ArquivoBinario.h"
#include "ArquivoFatura.h"
#include "ArquivoCliente.h"
#include "ArquivoHistorico.h"
#include "Constantes.h"



/* Obtém o tamanho do registro em bytes.
* 20 bytes da descrição do fatura com 20 caracteres (1 byte por caractere);
*  4 bytes da quantidade;
*  4 bytes do preço.
*/
unsigned int ArquivoFatura::tamanhoRegistro() {
	return (TAMANHO_CODIGOS * sizeof(char) * 6) + (sizeof(int) * 2) + (sizeof(double) * 5);
}

void ArquivoFatura::objetoParaRegistro(Fatura & fatura, RegistroFatura & registro) {
	
	// Copiando os atributos do objeto Fatura para a estrutura RegistroFatura.
	strncpy_s(registro.numeroCliente, TAMANHO_CODIGOS, fatura.getCliente().getNumero().c_str(), fatura.getCliente().getNumero().length());
	strncpy_s(registro.numeroInstalacao, TAMANHO_CODIGOS, fatura.getNumeroInstalacao().c_str(), fatura.getNumeroInstalacao().length());
	strncpy_s(registro.dataVencimento, TAMANHO_CODIGOS, fatura.getDataVencimento().c_str(), fatura.getDataVencimento().length());
	strncpy_s(registro.dataDeLeitura, TAMANHO_CODIGOS, fatura.getDataDeLeitura().c_str(), fatura.getDataDeLeitura().length());
	strncpy_s(registro.dataDeLeituraAnterior, TAMANHO_CODIGOS, fatura.getDataDeLeituraAnterior().c_str(), fatura.getDataDeLeituraAnterior().length());
	strncpy_s(registro.proximaDataDeLeitura, TAMANHO_CODIGOS, fatura.getProximaDataDeLeitura().c_str(), fatura.getProximaDataDeLeitura().length());

	registro.mesReferente = fatura.getMesReferente();
	registro.anoReferente = fatura.getAnoReferente();
	registro.valorAPagar = fatura.getValorAPagar();

	registro.precoIluminacaoPublica = fatura.getValoresFaturados().getValorIluminacaoPublica();
	registro.precoEnergia = fatura.getValoresFaturados().getPreco();
	registro.valorDaFatura = fatura.getValoresFaturados().getValorDaFatura();

	registro.bandeiraAmarela = fatura.getValoresFaturados().obterValorAdicional(Bandeira::Cor::AMARELA);
	registro.bandeiraVermelha = fatura.getValoresFaturados().obterValorAdicional(Bandeira::Cor::VERMELHA);

	registro.consumoKWh = fatura.getValoresFaturados().getConsumo();
}

// Escreve o objeto Fatura como um registro do arquivo.
bool ArquivoFatura::escreverObjeto(Fatura fatura) {
	RegistroFatura registro;

	objetoParaRegistro(fatura, registro);

	if(!salvarCliente(fatura.getCliente())) return false;

	if(!salvarHistoricoConsumo(fatura)) return false;

	// Posiciona no fim do arquivo.
	getArquivoBinario().seekp(0, ios::end);

	// Escreve os dados do fatura no arquivo usando a estrutura RegistroFatura.
	getArquivoBinario().write(reinterpret_cast<const char *>(&registro), tamanhoRegistro());

	return true;
}


bool ArquivoFatura::posicionarNoInicio() {
	getArquivoBinario().seekp(0, ios::beg);
	return true;
}

bool ArquivoFatura::posicionarNoFinal() {
	getArquivoBinario().seekp(0, ios::end);
	return true;
}

bool ArquivoFatura::salvarCliente(const Cliente & cliente) {
	ArquivoCliente arquivo;
	arquivo.abrir(FILE_CLIENTE_DAT);
	arquivo.escreverObjeto(cliente);
	arquivo.fechar();
	return true;
}

bool ArquivoFatura::salvarHistoricoConsumo(Fatura & fatura) {
	ArquivoHistorico arquivo;
	const int TAMANHO_HISTORICO = 12;
	arquivo.abrir(FILE_HISTORICO_DAT);
	
	for (int i = 0; i <= TAMANHO_HISTORICO; i++) {
		Consumo consumo;
		if (!fatura.obterConsumoDoHistorico(consumo, i)) { arquivo.fechar(); return false; }

		//Verifia se o consumo passado ja está gravado no arquivo
		if (arquivo.pesquisarConsumoNoHistorico(fatura.getNumeroInstalacao(), 
			consumo.getMes(), consumo.getAno()) != -1) continue;


		consumo.setNumeroInstalacao(fatura.getNumeroInstalacao());
		
		arquivo.escreverObjeto(consumo, fatura.getCliente().getNumero());
	}

	arquivo.fechar();
	return true;
}
/* Lê os dados de um registro do arquivo e armazena-os no objeto Fatura.
* Retorna o objeto Fatura. Em caso de erro retorna NULL.
*/
Fatura* ArquivoFatura::lerObjeto(unsigned int numeroRegistro, bool consultaDetalhada) {
	RegistroFatura registro;

	// Posiciona no registro a ser lido.
	getArquivoBinario().seekg(numeroRegistro * tamanhoRegistro());

	// Lê o registro e armazena os dados no objeto fatura.
	getArquivoBinario().read(reinterpret_cast<char *>(&registro), tamanhoRegistro());

	/* Se a leitura não falhar o objeto Fatura será retornado com os dados lidos do arquivo.
	Cria um objeto Fatura com os dados recuperados do arquivo e armazenados na estrutura registro.
	*/
	if (getArquivoBinario()) {
		Fatura* fatura = new Fatura();
		registroParaFatura(*fatura, registro);
		return fatura;
	}
	else return NULL;
}

RegistroFatura* ArquivoFatura::lerRegistro(unsigned int numeroRegistro) {
	RegistroFatura registro;

	// Posiciona no registro a ser lido.
	getArquivoBinario().seekg(numeroRegistro * tamanhoRegistro());

	// Lê o registro e armazena os dados no objeto fatura.
	getArquivoBinario().read(reinterpret_cast<char *>(&registro), tamanhoRegistro());

	/* Se a leitura não falhar o objeto Fatura será retornado com os dados lidos do arquivo.
	Cria um objeto Fatura com os dados recuperados do arquivo e armazenados na estrutura registro.
	*/
	if (getArquivoBinario()) {
		return new RegistroFatura(registro);
	}
	else return NULL;
}

Fatura ArquivoFatura::registroParaFatura(Fatura & fatura, const RegistroFatura & registro, bool consultaDetalhada) {
	
	fatura.setMesReferente(registro.mesReferente);
	fatura.setAnoReferente(registro.anoReferente);
	fatura.setDataDeLeitura(registro.dataDeLeitura);
	fatura.setDataDeLeituraAnterior(registro.dataDeLeituraAnterior);
	fatura.setProximaDataDeLeitura(registro.proximaDataDeLeitura);
	fatura.setNumeroInstalacao(registro.numeroInstalacao);
	fatura.setDataVencimento(registro.dataVencimento);
	fatura.setValorAPagar(registro.valorAPagar);


	if (consultaDetalhada) {

		ArquivoCliente arquivoCliente;
		arquivoCliente.abrir(FILE_CLIENTE_DAT);
		Cliente * cliente = arquivoCliente.lerObjeto(arquivoCliente.pesquisarCliente(registro.numeroCliente));
		arquivoCliente.fechar();

		ValoresFaturados valores;
		valores.setConsumo(registro.consumoKWh);
		valores.setPreco(registro.precoEnergia);
		valores.setValorDaFatura(registro.valorDaFatura);
		valores.setValorIluminacaoPublica(registro.precoIluminacaoPublica);

		fatura.setCliente(*cliente);
		fatura.setValoresFaturados(valores);

		delete cliente;
	}

	else {
		Cliente cliente;
		cliente.setNumero(registro.numeroCliente);
		fatura.setCliente(cliente);
	}

	return fatura;
}


Fatura* ArquivoFatura::obterFatura(int mesReferente, int anoReferente, const string & numeroInstalacao) {
	return lerObjeto(pesquisarFatura(mesReferente, anoReferente, VAZIO, numeroInstalacao));

}

Fatura* ArquivoFatura::obterFatura(const string & numeroCliente, int mesReferente, int anoReferente) {
	return lerObjeto(pesquisarFatura(mesReferente, anoReferente, numeroCliente, VAZIO));
}


/* Pesquisa o número de um cliente no arquivo. Em caso de sucesso retorna o número do registro
* onde o fatura está armazenado, caso contrário, retorna -1.
*/
int ArquivoFatura::pesquisarFatura(string numeroCliente, int mesReferente, int anoReferente, int posicao) {
	RegistroFatura *fatura;

	// Obtém o número de registros do arquivo.
	unsigned registros = numeroRegistros();

	// Percorre o arquivo a procura do nome do fatura.
	for (unsigned reg = posicao; reg < registros; reg++) {
		// Recupera o fatura do aquivo.
		fatura = lerRegistro(reg);

		// Verifica se é o número procurado.
		if (!_stricmp(numeroCliente.c_str(), fatura->numeroCliente)) {

			if ((anoReferente == 0 && mesReferente == 0) ||
				mesReferente == fatura->mesReferente &&
				anoReferente == fatura->anoReferente) {

				return reg;
			}
		}
	}
	return -1;
}

/* Pesquisa o número de um cliente no arquivo. Em caso de sucesso retorna o número do registro
* onde o fatura está armazenado, caso contrário, retorna -1.
*/
int ArquivoFatura::pesquisarFatura(int mesReferente, int anoReferente, string numeroCliente, string numeroInstalacao) {
	RegistroFatura *fatura;

	if (numeroCliente.empty() && numeroInstalacao.empty()) return -1;

	bool a = posicionarNoInicio();

	// Obtém o número de registros do arquivo.
	unsigned registros = numeroRegistros();

	// Percorre o arquivo a procura do nome do fatura.
	for (unsigned reg = 0; reg < registros; reg++) {
		// Recupera o fatura do aquivo.
		fatura = lerRegistro(reg);

		// Verifica se é o número procurado.
		if (!_stricmp(numeroCliente.c_str(), fatura->numeroCliente) == 0
			|| !_stricmp(numeroInstalacao.c_str(), fatura->numeroInstalacao) == 0) {

			if ((mesReferente == 0 && anoReferente == 0) ||
				mesReferente == fatura->mesReferente &&
				anoReferente == fatura->anoReferente) {

				return reg;
			}
		}
	}
	return -1;
}


