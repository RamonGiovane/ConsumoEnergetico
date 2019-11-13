#include "ArquivoHistorico.h"
#include "ArquivoBinario\ArquivoBinario.h"
#include "ArquivoHistorico.h"
#include "Constantes.h"
#include <iostream>
#include <io.h>

// Cria um objeto para manipular o arquivo binário com acesso aleatório.
ArquivoHistorico::ArquivoHistorico() {
	arqBin = new ArquivoBinario();
}

/* Cria um objeto para manipular o arquivo binário com acesso aleatório cujo nome de arquivo está
* especificado em nomeArquivo. Em seguida, abre o arquivo para leitura e escrita.
*/
ArquivoHistorico::ArquivoHistorico(string nomeArquivo) {
	arqBin = new ArquivoBinario();
	arqBin->abrir(nomeArquivo);
}

// Exclui o objeto arquivo binário.
ArquivoHistorico::~ArquivoHistorico() {
	delete arqBin;
}

/* Abre o arquivo com o nome especificado em nomeArquivo para escrita e leitura de dados.
* Retorna true se o arquivo foi aberto com sucesso e false caso contrário.
*/
bool ArquivoHistorico::abrir(string nomeArquivo) {
	if (!arqBin->getArquivoBinario().is_open())
		return arqBin->abrir(nomeArquivo);
	return true;
}

// Fecha o arquivo.
void ArquivoHistorico::fechar() {
	arqBin->fechar();
}

// Obtém o nome do arquivo.
string ArquivoHistorico::getNomeArquivo() {
	return arqBin->getNomeArquivo();
}

// Obtém o tamanho do arquivo em bytes.
unsigned long ArquivoHistorico::tamanhoArquivo() {
	return arqBin->tamanhoArquivo();
}

// Obtém o número de registros do arquivo.
unsigned int ArquivoHistorico::numeroRegistros() {
	return tamanhoArquivo() / tamanhoRegistro();
}

/* Obtém o tamanho do registro em bytes.
* 20 bytes da descrição do consumo com 20 caracteres (1 byte por caractere);
*  4 bytes da quantidade;
*  4 bytes do preço.
*/
unsigned int ArquivoHistorico::tamanhoRegistro() {
	return (sizeof(int) * 4) + sizeof(double) + (TAMANHO_CODIGOS * sizeof(char) * 2);
}

void ArquivoHistorico::objetoParaRegistro(Consumo & consumo, RegistroConsumo & registro, const string & numeroCliente, const string & numeroInstalacao) {
	registro.ano = consumo.getAno();
	registro.mes = consumo.getMes();
	registro.mediaConsumoDiario = consumo.getMediaConsumoDiario();
	registro.consumoKWh = consumo.getConsumoKWh();
	registro.dias = consumo.getDias();

	strncpy_s(registro.numeroCliente, TAMANHO_CODIGOS, numeroCliente.c_str(), numeroCliente.length());
	strncpy_s(registro.numeroInstalacao, TAMANHO_CODIGOS, numeroInstalacao.c_str(), numeroInstalacao.length());
}

// Escreve o objeto Consumo como um registro do arquivo.
void ArquivoHistorico::escreverObjeto(Consumo consumo, const string & numeroCliente, const string & numeroInstalacao) {
	RegistroConsumo registro;

	// Copiando os atributos do objeto Consumo para a estrutura RegistroConsumo.
	objetoParaRegistro(consumo, registro, numeroCliente, numeroInstalacao);

	// Posiciona no fim do arquivo.
	arqBin->getArquivoBinario().seekp(0, ios::end);

	// Escreve os dados do consumo no arquivo usando a estrutura RegistroConsumo.
	arqBin->getArquivoBinario().write(reinterpret_cast<const char *>(&registro), tamanhoRegistro());
}

/* Lê os dados de um registro do arquivo e armazena-os no objeto Consumo.
* Retorna o objeto Consumo. Em caso de erro retorna NULL.
*/
RegistroConsumo* ArquivoHistorico::lerObjeto(unsigned int numeroRegistro) {
	RegistroConsumo registro;

	// Posiciona no registro a ser lido.
	arqBin->getArquivoBinario().seekg(numeroRegistro * tamanhoRegistro());

	// Lê o registro e armazena os dados no objeto consumo.
	arqBin->getArquivoBinario().read(reinterpret_cast<char *>(&registro), tamanhoRegistro());

	/* Se a leitura não falhar o objeto Consumo será retornado com os dados lidos do arquivo.
	Cria um objeto Consumo com os dados recuperados do arquivo e armazenados na estrutura registro.
	*/
	if (arqBin->getArquivoBinario())
		return new RegistroConsumo(registro);
	else return NULL;
}


/* Exclui um registro do arquivo. O primeiro registro é o número zero (0).
* Retorna true se o registro foi excluído com sucesso e false caso contrário.
*/
bool ArquivoHistorico::excluirRegistro(unsigned int numeroRegistro) {
	// Obtém o número de registros do arquivo.
	unsigned registros = numeroRegistros();

	// Verifica se o número do registro é válido.
	if (numeroRegistro >= 0 && numeroRegistro < registros) {
		// Cria um novo arquivo que receberá o conteúdo do arquivo atual sem o registro a ser excluído.
		ArquivoHistorico arquivo("HistoricoConsumo.tmp");

		// Copia todos os registros do arquivo Consumo.dat para Consumo.tmp.
		for (unsigned reg = 0; reg < registros; reg++)
			if (reg != numeroRegistro) {
				
				RegistroConsumo * registroConsumo = lerObjeto(reg);
				
				Consumo * consumo = new Consumo(registroConsumo->mes, registroConsumo->ano, registroConsumo->consumoKWh, 
					registroConsumo->mediaConsumoDiario, registroConsumo->dias);
				
				arquivo.escreverObjeto(*consumo, registroConsumo->numeroCliente, registroConsumo->numeroInstalacao);
			}

		// Fecha os arquivos para que possam ser removido e renomeado.
		arquivo.fechar();
		fechar();

		// Remove o arquivo com o registro a ser excluído e renomeia o novo arquivo.
		_unlink("HistoricoConsumo.dat");
		rename("HistoricoConsumo.tmp", "HistoricoConsumo.dat");

		// Reabre o arquivo "Consumo.dat".
		abrir("HistoricoConsumo.dat");
		return true;
	}
	return false;
}

/* Pesquisa o número de um consumo no arquivo. Em caso de sucesso retorna o número do registro
* onde o consumo está armazenado, caso contrário, retorna -1.
*/
int ArquivoHistorico::pesquisarHistorico(string numeroCliente, string numeroInstalacao) {
	RegistroConsumo *consumo;

	// Obtém o número de registros do arquivo.
	unsigned registros = numeroRegistros();

	// Percorre o arquivo a procura do nome do consumo.
	for (unsigned reg = 0; reg < registros; reg++) {
		// Recupera o consumo do aquivo.
		consumo = lerObjeto(reg);

		// Verifica se é o número procurado.
		if (!_stricmp(numeroCliente.c_str(), consumo->numeroCliente)) {
			if(numeroInstalacao.empty() || !_stricmp(numeroInstalacao.c_str(), consumo->numeroInstalacao))
				return reg;
			continue;
		}
	}
	return -1;
}
