#ifndef ARQUIVO_HISTORICO_H
#define ARQUIVO_HISTORICO_H

#include "Consumo.h"
#include "ArquivoBinario.h"
#include <string>
#include <vector>
#include "Constantes.h"

using namespace std;
struct RegistroConsumo {
	int mes;
	int ano;
	int dias;
	double consumoKWh;
	double mediaConsumoDiario;
	char numeroCliente[TAMANHO_CODIGOS];
	char numeroInstalacao[TAMANHO_CODIGOS];
};
class ArquivoHistorico : public ArquivoBinario
{
public:
	// Cria um objeto para manipular o arquivo bin�rio com acesso aleat�rio.
	inline ArquivoHistorico() : ArquivoBinario() {};

	/* Cria um objeto para manipular o arquivo bin�rio com acesso aleat�rio cujo nome de arquivo est�
	* especificado em nomeArquivo. Em seguida, abre o arquivo para leitura e escrita.
	*/
	inline ArquivoHistorico(string nomeArquivo) : ArquivoBinario(nomeArquivo) {};


	// Obt�m o tamanho do registro em bytes.
	unsigned int tamanhoRegistro();

	void objetoParaRegistro(Consumo & consumo, RegistroConsumo & registro, const string & numeroCliente);

	void registroParaObjeto(Consumo & consumo, RegistroConsumo & registro);

	void escreverObjeto(Consumo consumo, const string & numeroCliente);

	Consumo * lerObjeto(unsigned int numeroRegistro);

	/* Exclui um registro do arquivo. O primeiro registro � o n�mero zero (0).
	* Retorna true se o registro foi exclu�do com sucesso e false caso contr�rio.
	*/
	bool excluirRegistro(unsigned int numeroRegistro);



	int pesquisarConsumoNoHistorico(const string & numeroInstalacao, int mes, int ano);


	bool obterHistoricoConsumo(vector<Consumo> & historicoConsumo, const string & numeroCliente, int mesInicial, int anoInicial, int mesFinal = 0, int anoFinal = 0);

private:

	int pesquisarConsumoNoHistorico(string numeroCliente = "", string numeroInstalacao = "", int mes = 0, int ano = 0);

	/* L� os dados de um registro do arquivo e armazena-os no objeto Historico.
	* Retorna o objeto Historico. Em caso de erro retorna NULL.
	*/
	RegistroConsumo* lerRegistro(unsigned int numeroRegistro);
};

#endif // !ARQUIVO_HISTORICO_H
