#ifndef VALOR_FATURADO
#define VALOR_FATURADO
#include <string>
#include "Bandeira.h"
using namespace std;
class ValoresFaturados
{
public:
	ValoresFaturados();
	
	ValoresFaturados(int consumo, double valorFaturado, double preco);
	//ValorFaurado(string descricao, consumo, valor, bandeiraAmarela, bandeiraVermelha);
	
	ValoresFaturados& setConsumo(int consumo);
	ValoresFaturados& setPreco(double preco);
	ValoresFaturados& setValorFaturado(double valor);
	ValoresFaturados& setValorIluminacaoPublica(double valor);

	int getConsumo();
	double getPreco();
	double getValorFaturado();
	double getValorIluminacaoPublica();

	ValoresFaturados& definirAdicionais(double bandeiraAmarela, double bandeiraVermleha);
	
	string toString();

private:
	int consumo;
	double valorFaturado;
	double preco;
	double iluminacaoPublica;
	void inicializarBandeiras();
	Bandeira bandeiraAmarela, bandeiraVermelha;




};

#endif // !VALOR_FATURADO