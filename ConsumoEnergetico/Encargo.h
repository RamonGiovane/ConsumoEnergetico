#ifndef ENCARGO_H
#define ENCARGO_H
#include <string>
using namespace std;
class Encargo
{
public:
	Encargo();
	~Encargo();

private:
	string descricao;
	double valor;
	
};

#endif // !ENCARGO_H