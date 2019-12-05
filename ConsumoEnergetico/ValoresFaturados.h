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


	/*Obt�m o valor de adicional de acordo com a cor da bandeira*/
	double obterValorAdicional(Bandeira::Cor bandeira);
	
	/*Define o valor de consumo mensal faturado*/
	ValoresFaturados& setConsumo(int consumo);
	
	/*Define o pre�o da energia el�trica*/
	ValoresFaturados& setPreco(double preco);

	/*Define o valor da energia el�trica, sem encargos. Ou seja, n�o corresponde ao valor a pagar*/
	ValoresFaturados& setValorDaFatura(double valor);
	
	/*Define o valor de encargo da ilumina��o p�blica*/
	ValoresFaturados& setValorIluminacaoPublica(double valor);

	/*Define o valor de adicional das bandeiras. Por padr�o, s�o considerados como 0.0*/
	ValoresFaturados& definirAdicionais(double bandeiraAmarela, double bandeiraVermleha);

	/*Obt�m o valor de consumo mensal faturado*/
	int getConsumo();

	/*Obt�m o pre�o da energia el�trica*/
	double getPreco();
	
	/*Obt�m o valor da fatura de energia el�trica, sem encargos. Ou seja, n�o corresponde ao valor a pagar*/
	double getValorDaFatura();
	
	/*Obt�m o valor de encargo da ilumina��o p�blica*/
	double getValorIluminacaoPublica();

	/*Obt�m uma representa��o string deste objeto*/
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