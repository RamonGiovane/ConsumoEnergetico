#ifndef VALOR_FATURADO
#define VALOR_FATURADO
#include <string>
#include "Bandeira.h"
using namespace std;
class FaturaEnergia
{
public:
	FaturaEnergia();
	
	FaturaEnergia(int consumo, double valorFaturado, double preco);
	//ValorFaurado(string descricao, consumo, valor, bandeiraAmarela, bandeiraVermelha);
	
	FaturaEnergia& setConsumo(int consumo);
	FaturaEnergia& setPreco(double preco);
	FaturaEnergia& setValorFaturado(double valor);
	FaturaEnergia& setValorIluminacaoPublica(double valor);

	int getConsumo();
	double getPreco();
	double getValorFaturado();
	double getValorIluminacaoPublica();

	FaturaEnergia& definirAdicionais(double bandeiraAmarela, double bandeiraVermleha);
	
private:
	int consumo;
	double valorFaturado;
	double preco;
	double iluminacaoPublica;
	void inicializarBandeiras();
	Bandeira bandeiraAmarela, bandeiraVermelha;




};

#endif // !VALOR_FATURADO