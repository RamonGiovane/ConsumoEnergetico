#ifndef CLIENTE_H
#define CLIENTE_H

#include <string>
using namespace std;

class Cliente
{
public:
	Cliente();
	~Cliente();
private:
	string nome;
	string rua;
	string bairro;
	string cep;
	string cidade;
	string estado;
	int numero;

};

#endif // !CLIENTE_H