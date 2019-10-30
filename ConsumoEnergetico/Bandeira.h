#ifndef BANDEIRA_H
#define BANDEIRA_H

class Bandeira
{
public:
	Bandeira();
	~Bandeira();
private:
	enum class Cor
	{
		AMARELA, VERMELHA
	};

	Cor cor;
	double valor;
};

#endif // !BANDEIRA_H