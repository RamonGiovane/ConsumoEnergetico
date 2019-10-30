#ifndef VALOR_FATURADO
#define VALOR_FATURADO
#include <string>
using namespace std;
class ValorFaturado
{
public:
	ValorFaturado();

private:
	string descricao;
	int consumo;
	double tarifa;
	double valor;
	double tarifaAplicada;

};

#endif // !VALOR_FATURADO