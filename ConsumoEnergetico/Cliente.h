#ifndef CLIENTE_H
#define CLIENTE_H

#include <string>
using namespace std;

class Cliente
{
public:
	Cliente();
	Cliente(string numero, string nome, string CPF, string rua, string bairro, string CEP, string cidade);

	Cliente& setNome(string nome);
	Cliente& setRua(string rua);
	Cliente& setBairro(string bairro);
	Cliente& setCidade(string cidade);
	Cliente& setCEP(string CEP);
	Cliente& setNumero(string numero);
	Cliente& setCPF(string cpf);

	string getNome();
	string getRua();
	string getBairro();
	string getCidade();
	string getCEP();
	string getCPF();
	string getNumero();

	string toString();

private:
	string nome;
	string rua;
	string bairro;
	string CEP;
	string cidade;
	string numero;
	string cpf;
};

#endif // !CLIENTE_H