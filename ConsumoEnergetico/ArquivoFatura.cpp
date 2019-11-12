#include "ArquivoFatura.h"


#include <iostream>
#include <io.h>
#include "ArquivoBinario\ArquivoBinario.h"
#include "ArquivoFatura.h"

// Cria um objeto para manipular o arquivo bin�rio com acesso aleat�rio.
ArquivoFatura::ArquivoFatura() {
	arqBin = new ArquivoBinario();
}

/* Cria um objeto para manipular o arquivo bin�rio com acesso aleat�rio cujo nome de arquivo est�
* especificado em nomeArquivo. Em seguida, abre o arquivo para leitura e escrita.
*/
ArquivoFatura::ArquivoFatura(string nomeArquivo) {
	arqBin = new ArquivoBinario();
	arqBin->abrir(nomeArquivo);
}

// Exclui o objeto arquivo bin�rio.
ArquivoFatura::~ArquivoFatura() {
	delete arqBin;
}

/* Abre o arquivo com o nome especificado em nomeArquivo para escrita e leitura de dados.
* Retorna true se o arquivo foi aberto com sucesso e false caso contr�rio.
*/
bool ArquivoFatura::abrir(string nomeArquivo) {
	if (!arqBin->getArquivoBinario().is_open())
		return arqBin->abrir(nomeArquivo);
	return true;
}

// Fecha o arquivo.
void ArquivoFatura::fechar() {
	arqBin->fechar();
}

// Obt�m o nome do arquivo.
string ArquivoFatura::getNomeArquivo() {
	return arqBin->getNomeArquivo();
}

// Obt�m o tamanho do arquivo em bytes.
unsigned long ArquivoFatura::tamanhoArquivo() {
	return arqBin->tamanhoArquivo();
}

// Obt�m o n�mero de registros do arquivo.
unsigned int ArquivoFatura::numeroRegistros() {
	return tamanhoArquivo() / tamanhoRegistro();
}

/* Obt�m o tamanho do registro em bytes.
* 20 bytes da descri��o do fatura com 20 caracteres (1 byte por caractere);
*  4 bytes da quantidade;
*  4 bytes do pre�o.
*/
unsigned int ArquivoFatura::tamanhoRegistro() {
	return (TAMANHO_STRING * sizeof(char) * 6) + (sizeof(int) * 2) + (sizeof(double) * 5);
}

// Escreve o objeto Fatura como um registro do arquivo.
void ArquivoFatura::escreverObjeto(Fatura fatura) {
	RegistroFatura registro;

	// Copiando os atributos do objeto Fatura para a estrutura RegistroFatura.
	strncpy_s(registro.numeroCliente, TAMANHO_STRING, fatura.getCliente().getNumero().c_str(), fatura.getCliente().getNumero().length());
	strncpy_s(registro.numeroInstalacao, TAMANHO_STRING, fatura.getNumeroInstalacao().c_str(), fatura.getNumeroInstalacao().length());
	strncpy_s(registro.dataVencimento, TAMANHO_STRING, fatura.getDataVencimento().c_str(), fatura.getDataVencimento().length());
	strncpy_s(registro.dataDeLeitura, TAMANHO_STRING, fatura.getDataDeLeitura().c_str(), fatura.getDataDeLeitura().length());
	strncpy_s(registro.dataDeLeituraAnterior, TAMANHO_STRING, fatura.getDataDeLeituraAnterior().c_str(), fatura.getDataDeLeituraAnterior().length());
	strncpy_s(registro.proximaDataDeLeitura, TAMANHO_STRING, fatura.getProximaDataDeLeitura().c_str(), fatura.getProximaDataDeLeitura().length());
	
	registro.mesReferente = fatura.getMesReferente();
	registro.anoReferente = fatura.getAnoReferente();
	registro.valorAPagar = fatura.getValorAPagar();

	registro.precoIluminacaoPublica = fatura.getValoresFaturados().getValorIluminacaoPublica();
	registro.precoEnergia = fatura.getValoresFaturados().getPreco();
	
	registro.bandeiraAmarela = 0;
	registro.bandeiraVermelha = 0;
	
	registro.consumoKWh = fatura.getValoresFaturados().getConsumo();

	// Posiciona no fim do arquivo.
	arqBin->getArquivoBinario().seekp(0, ios::end);

	// Escreve os dados do fatura no arquivo usando a estrutura RegistroFatura.
	arqBin->getArquivoBinario().write(reinterpret_cast<const char *>(&registro), tamanhoRegistro());
}

/* L� os dados de um registro do arquivo e armazena-os no objeto Fatura.
* Retorna o objeto Fatura. Em caso de erro retorna NULL.
*/
Fatura* ArquivoFatura::lerObjeto(unsigned int numeroRegistro) {
	RegistroFatura registro;

	// Posiciona no registro a ser lido.
	arqBin->getArquivoBinario().seekg(numeroRegistro * tamanhoRegistro());

	// L� o registro e armazena os dados no objeto fatura.
	arqBin->getArquivoBinario().read(reinterpret_cast<char *>(&registro), tamanhoRegistro());

	/* Se a leitura n�o falhar o objeto Fatura ser� retornado com os dados lidos do arquivo.
	Cria um objeto Fatura com os dados recuperados do arquivo e armazenados na estrutura registro.
	*/
	if (arqBin->getArquivoBinario())
		return new Fatura();
	else return NULL;
}

/* Exclui um registro do arquivo. O primeiro registro � o n�mero zero (0).
* Retorna true se o registro foi exclu�do com sucesso e false caso contr�rio.
*/
bool ArquivoFatura::excluirRegistro(unsigned int numeroRegistro) {
	// Obt�m o n�mero de registros do arquivo.
	unsigned registros = numeroRegistros();

	// Verifica se o n�mero do registro � v�lido.
	if (numeroRegistro >= 0 && numeroRegistro < registros) {
		// Cria um novo arquivo que receber� o conte�do do arquivo atual sem o registro a ser exclu�do.
		ArquivoFatura arquivo("Fatura.tmp");

		// Copia todos os registros do arquivo Fatura.dat para Fatura.tmp.
		for (unsigned reg = 0; reg < registros; reg++)
			if (reg != numeroRegistro)
				arquivo.escreverObjeto(*lerObjeto(reg));

		// Fecha os arquivos para que possam ser removido e renomeado.
		arquivo.fechar();
		fechar();

		// Remove o arquivo com o registro a ser exclu�do e renomeia o novo arquivo.
		_unlink("Fatura.dat");
		rename("Fatura.tmp", "Fatura.dat");

		// Reabre o arquivo "Fatura.dat".
		abrir("Fatura.dat");
		return true;
	}
	return false;
}

/* Pesquisa o n�mero de um cliente no arquivo. Em caso de sucesso retorna o n�mero do registro
* onde o fatura est� armazenado, caso contr�rio, retorna -1.
*/
int ArquivoFatura::pesquisarFatura(string numeroCliente) {
	Fatura *fatura;

	// Obt�m o n�mero de registros do arquivo.
	unsigned registros = numeroRegistros();

	// Percorre o arquivo a procura do nome do fatura.
	for (unsigned reg = 0; reg < registros; reg++) {
		// Recupera o fatura do aquivo.
		fatura = lerObjeto(reg);

		// Verifica se � o n�mero procurado.
		if (!_stricmp(numeroCliente.c_str(), fatura->getCliente().getNumero().c_str()))
			return reg;
	}
	return -1;
}
