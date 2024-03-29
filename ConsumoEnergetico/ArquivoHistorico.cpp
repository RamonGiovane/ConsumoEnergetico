#include "ArquivoHistorico.h"
#include "ArquivoBinario.h"
#include "ArquivoHistorico.h"
#include "Constantes.h"
#include <iostream>
#include <vector>
#include <io.h>



/* Obt�m o tamanho do registro em bytes.
* 20 bytes da descri��o do consumo com 20 caracteres (1 byte por caractere);
*  4 bytes da quantidade;
*  4 bytes do pre�o.
*/
unsigned int ArquivoHistorico::tamanhoRegistro() {
	return (sizeof(int) * 4) + (sizeof(double) * 2) + (TAMANHO_CODIGOS * sizeof(char) * 2);
}

void ArquivoHistorico::objetoParaRegistro(Consumo & consumo, RegistroConsumo & registro, const string & numeroCliente) {
	registro.ano = consumo.getAno();
	registro.mes = consumo.getMes();
	registro.dias = consumo.getDias();
	registro.consumoKWh = consumo.getConsumoKWh();
	registro.mediaConsumoDiario = consumo.getMediaConsumoDiario();

	strncpy_s(registro.numeroCliente, TAMANHO_CODIGOS, numeroCliente.c_str(), numeroCliente.length());
	strncpy_s(registro.numeroInstalacao, TAMANHO_CODIGOS, consumo.getNumeroInstalacao().c_str(), consumo.getNumeroInstalacao().length());
}

void ArquivoHistorico::registroParaObjeto(Consumo & consumo, RegistroConsumo & registro){
	consumo = Consumo(registro.mes, registro.ano, registro.consumoKWh, registro.mediaConsumoDiario, registro.dias, registro.numeroInstalacao);
}

// Escreve o objeto Consumo como um registro do arquivo.
void ArquivoHistorico::escreverObjeto(Consumo consumo, const string & numeroCliente) {
	RegistroConsumo registro;

	// Copiando os atributos do objeto Consumo para a estrutura RegistroConsumo.
	objetoParaRegistro(consumo, registro, numeroCliente);

	// Posiciona no fim do arquivo.
	getArquivoBinario().seekp(0, ios::end);

	// Escreve os dados do consumo no arquivo usando a estrutura RegistroConsumo.
	getArquivoBinario().write(reinterpret_cast<const char *>(&registro), tamanhoRegistro());
}

Consumo* ArquivoHistorico::lerObjeto(unsigned int numeroRegistro) {
	Consumo* consumo = new Consumo();
	registroParaObjeto(*consumo, *lerRegistro(numeroRegistro));

	return consumo;
}

/* L� os dados de um registro do arquivo e armazena-os no objeto Consumo.
* Retorna o objeto Consumo. Em caso de erro retorna NULL.
*/
RegistroConsumo* ArquivoHistorico::lerRegistro(unsigned int numeroRegistro) {
	RegistroConsumo registro;

	// Posiciona no registro a ser lido.
	getArquivoBinario().seekg(numeroRegistro * tamanhoRegistro());

	// L� o registro e armazena os dados no objeto consumo.
	getArquivoBinario().read(reinterpret_cast<char *>(&registro), tamanhoRegistro());

	/* Se a leitura n�o falhar o objeto Consumo ser� retornado com os dados lidos do arquivo.
	Cria um objeto Consumo com os dados recuperados do arquivo e armazenados na estrutura registro.
	*/
	if (getArquivoBinario())
		return new RegistroConsumo(registro);
	else return NULL;
}


/* Exclui um registro do arquivo. O primeiro registro � o n�mero zero (0).
* Retorna true se o registro foi exclu�do com sucesso e false caso contr�rio.
*/
bool ArquivoHistorico::excluirRegistro(unsigned int numeroRegistro) {
	// Obt�m o n�mero de registros do arquivo.
	unsigned registros = numeroRegistros();

	// Verifica se o n�mero do registro � v�lido.
	if (numeroRegistro >= 0 && numeroRegistro < registros) {
		// Cria um novo arquivo que receber� o conte�do do arquivo atual sem o registro a ser exclu�do.
		ArquivoHistorico arquivo(FILE_HISTORICO_TMP);

		for (unsigned reg = 0; reg < registros; reg++)
			if (reg != numeroRegistro) {
				
				RegistroConsumo * registroConsumo = lerRegistro(reg);
				
				Consumo * consumo = new Consumo(registroConsumo->mes, registroConsumo->ano, registroConsumo->consumoKWh, 
					registroConsumo->mediaConsumoDiario, registroConsumo->dias, registroConsumo->numeroInstalacao);
				
				arquivo.escreverObjeto(*consumo, registroConsumo->numeroCliente);
			}

		// Fecha os arquivos para que possam ser removido e renomeado.
		arquivo.fechar();
		fechar();

		// Remove o arquivo com o registro a ser exclu�do e renomeia o novo arquivo.
		_unlink(FILE_HISTORICO_DAT);
		rename(FILE_HISTORICO_TMP, FILE_HISTORICO_TMP);

		abrir(FILE_HISTORICO_DAT);
		return true;
	}
	return false;
}

int ArquivoHistorico::pesquisarConsumoNoHistorico(const string & numeroInstalacao, int mes, int ano) {
	return pesquisarConsumoNoHistorico("", numeroInstalacao, mes, ano);
}


/* Pesquisa o n�mero de um consumo no arquivo. Em caso de sucesso retorna o n�mero do registro
* onde o consumo est� armazenado, caso contr�rio, retorna -1.
*/
int ArquivoHistorico::pesquisarConsumoNoHistorico(string numeroCliente, string numeroInstalacao, int mes, int ano) {
	
	if (numeroCliente.empty() && numeroInstalacao.empty()) return -1;
	
	RegistroConsumo *consumo;

	// Obt�m o n�mero de registros do arquivo.
	unsigned registros = numeroRegistros();

	// Percorre o arquivo a procura do nome do consumo.
	for (unsigned reg = 0; reg < registros; reg++) {
		// Recupera o consumo do aquivo.
		consumo = lerRegistro(reg);

		// Verifica se correpsponde aos termos pesquisados
		if (numeroCliente.empty() ||  !_stricmp(numeroCliente.c_str(), consumo->numeroCliente)) {
			if(numeroInstalacao.empty() || !_stricmp(numeroInstalacao.c_str(), consumo->numeroInstalacao))
				if((ano == 0 && mes == 0) || (consumo->ano == ano && consumo->mes == mes))
					return reg;
			
		}
	}
	return -1;
}


int mesAnoEmNumeroUnico(int mes, int ano) {
	
	return ano * 100 + mes;
}




/* Pesquisa e retorna em um vector todo o hist�rico de consumo de um cliente em intervalo de meses e anos qualquer.
	Se o m�s e ano finais foram omitidos (ou passados como 0), para tais, ser�o considerados o m�s e ano iniciais.
*	Retorna os dados obtidos por refer�ncia em um vector. 
	Retorna true se algum dado de consumo for encotrado, false do contr�rio.
*/
bool ArquivoHistorico::obterHistoricoConsumo(vector<Consumo> & historicoConsumo, const string & numeroCliente, int mesInicial, int anoInicial, int mesaFinal, int anoFinal) {
	RegistroConsumo *registro;
	Consumo consumo;
	
	if (mesaFinal == 0 || anoFinal == 0) {
		mesaFinal = mesInicial;
		anoFinal = anoInicial;
	}
	
	// Obt�m o n�mero de registros do arquivo.
	unsigned registros = numeroRegistros();

	int inicioPesquisa = mesAnoEmNumeroUnico(mesInicial, anoInicial);
	int fimPesquisa = mesAnoEmNumeroUnico(mesaFinal, anoFinal);
	int mesAno;

	// Percorre o arquivo a procura do nome do consumo.
	for (unsigned reg = 0; reg < registros; reg++) {
		// Recupera o consumo do aquivo.
		registro = lerRegistro(reg);

		// Verifica se � o n�mero procurado.
		if (!_stricmp(numeroCliente.c_str(), registro->numeroCliente)) {
			mesAno = mesAnoEmNumeroUnico(registro->mes, registro->ano);
			if (mesAno >= inicioPesquisa && mesAno <= fimPesquisa) {
				registroParaObjeto(consumo, *registro);
				historicoConsumo.push_back(consumo);
			}
		}
	}
	return historicoConsumo.empty() ? false : true;
}
