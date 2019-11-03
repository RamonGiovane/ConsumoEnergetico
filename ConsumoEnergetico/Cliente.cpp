#include "Cliente.h"



Cliente::Cliente()
{
}

Cliente::Cliente(string nome, string rua, string bairro, string CEP, string cidade)
{
	setNome(nome).setBairro(bairro).setRua(rua).setCidade(cidade).setCEP(CEP);
}


Cliente & Cliente::setNome(string nome)
{
	this->nome = nome;
	return *this;
}

Cliente & Cliente::setRua(string rua)
{
	this->rua = rua;
	return *this;
}

Cliente & Cliente::setBairro(string bairro)
{
	this->bairro = bairro;
	return *this;
}

Cliente & Cliente::setCidade(string cidade)
{
	this->cidade = cidade;
	return *this;
}

Cliente & Cliente::setCEP(string CEP)
{
	this->CEP = CEP;
	return *this;
}

Cliente & Cliente::setNumero(string numero)
{
	this->numero = numero;
	return *this;
}

string Cliente::getNome()
{
	return nome;
}

string Cliente::getRua()
{
	return rua;
}

string Cliente::getBairro()
{
	return bairro;
}

string Cliente::getCidade()
{
	return cidade;
}

string Cliente::getCEP()
{
	return CEP;
}

string Cliente::getNumero()
{
	return numero;
}

string Cliente::toString()
{
	char str[200];
	sprintf_s(str, 200, "Número: %s\nNome: %s\nRua: %s\nBairro: %s\nCidade: %s\nCEP: %s", 
		numero.c_str(), nome.c_str(), rua.c_str(), bairro.c_str(), cidade.c_str(), CEP.c_str());
	return str;
}
