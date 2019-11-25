#ifndef CALCULADORA_CONSUMO
#include <string>
#include <vector>
using namespace std;
class CalculadoraDeConsumo
{
public:
	CalculadoraDeConsumo();
	~CalculadoraDeConsumo();

	double calcularConsumo(const vector<string>& linhasArquivo, int mes, int ano);

	double obterConsumoKWh(const string & linhaDoConsumo);

private:
	string mensagemErro;
};
#endif // !CALCULADORA_CONSUMO




