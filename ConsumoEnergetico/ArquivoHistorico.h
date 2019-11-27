#ifndef ARQUIVO_HISTORICO_H
#define ARQUIVO_HISTORICO_H

#include "Consumo.h"
#include "ArquivoBinario\ArquivoBinario.h"
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
class ArquivoHistorico
{
public:
	// Cria um objeto para manipular o arquivo binário com acesso aleatório.
	ArquivoHistorico();

	/* Cria um objeto para manipular o arquivo binário com acesso aleatório cujo nome de arquivo está
	* especificado em nomeArquivo. Em seguida, abre o arquivo para leitura e escrita.
	*/
	ArquivoHistorico(string nomeArquivo);

	// Exclui o objeto arquivo binário.
	~ArquivoHistorico();

	/* Abre o arquivo com o nome especificado em nomeArquivo para escrita e leitura de dados.
	* Retorna true se o arquivo foi aberto com sucesso e false caso contrário.
	*/
	bool abrir(string nomeArquivo);

	// Fecha o arquivo.
	void fechar();

	// Obtém o nome do arquivo.
	string getNomeArquivo();

	// Obtém o tamanho do arquivo em bytes.
	unsigned long tamanhoArquivo();

	// Obtém o número de registros do arquivo.
	unsigned int numeroRegistros();

	// Obtém o tamanho do registro em bytes.
	unsigned int tamanhoRegistro();

	void objetoParaRegistro(Consumo & consumo, RegistroConsumo & registro, const string & numeroCliente);

	void registroParaObjeto(Consumo & consumo, RegistroConsumo & registro);

	void escreverObjeto(Consumo consumo, const string & numeroCliente);

	Consumo * lerObjeto(unsigned int numeroRegistro);

	/* Exclui um registro do arquivo. O primeiro registro é o número zero (0).
	* Retorna true se o registro foi excluído com sucesso e false caso contrário.
	*/
	bool excluirRegistro(unsigned int numeroRegistro);



	int pesquisarConsumoNoHistorico(const string & numeroInstalacao, int mes, int ano);


	bool obterHistoricoConsumo(vector<Consumo> & historicoConsumo, const string & numeroCliente, int mesInicial, int anoInicial, int mesFinal = 0, int anoFinal = 0);

private:
	ArquivoBinario *arqBin;
	int pesquisarConsumoNoHistorico(string numeroCliente = "", string numeroInstalacao = "", int mes = 0, int ano = 0);

	/* Lê os dados de um registro do arquivo e armazena-os no objeto Historico.
	* Retorna o objeto Historico. Em caso de erro retorna NULL.
	*/
	RegistroConsumo* lerRegistro(unsigned int numeroRegistro);
};

#endif // !ARQUIVO_HISTORICO_H
