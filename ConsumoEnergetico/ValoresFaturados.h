#ifndef VALOR_FATURADO
#define VALOR_FATURADO
#include <string>
#include "Bandeira.h"
using namespace std;
class ValoresFaturados
{
public:
	ValoresFaturados();
	
	ValoresFaturados(int consumo, double valorDaFatura, double preco);


	/*Obtém o valor de adicional de acordo com a cor da bandeira*/
	double obterValorAdicional(Bandeira::Cor bandeira);
	
	/*Define o valor de consumo mensal faturado*/
	ValoresFaturados& setConsumo(int consumo);
	
	/*Define o preço da energia elétrica*/
	ValoresFaturados& setPreco(double preco);

	/*Define o valor da energia elétrica, sem encargos. Ou seja, não corresponde ao valor a pagar*/
	ValoresFaturados& setValorDaFatura(double valor);
	
	/*Define o valor de encargo da iluminação pública*/
	ValoresFaturados& setValorIluminacaoPublica(double valor);

	/*Define o valor de adicional das bandeiras. Por padrão, são considerados como 0.0*/
	ValoresFaturados& definirAdicionais(double bandeiraAmarela, double bandeiraVermleha);

	/*Obtém o valor de consumo mensal faturado*/
	int getConsumo();

	/*Obtém o preço da energia elétrica*/
	double getPreco();
	
	/*Obtém o valor da fatura de energia elétrica, sem encargos. Ou seja, não corresponde ao valor a pagar*/
	double getValorDaFatura();
	
	/*Obtém o valor de encargo da iluminação pública*/
	double getValorIluminacaoPublica();

	/*Obtém uma representação string deste objeto*/
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