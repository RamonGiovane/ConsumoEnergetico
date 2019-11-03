#ifndef BANDEIRA_H
#define BANDEIRA_H

class Bandeira
{


public:
	enum class Cor { AMARELA, VERMELHA};
	Bandeira();
	Bandeira(Cor cor);
	Bandeira(Cor cor, double valor);

	Bandeira& setCor(Cor cor);
	Bandeira& setValor(double valor);

	Cor getCor();
	double getValor();
	
private:


	Cor cor;
	double valor;
};

#endif // !BANDEIRA_H