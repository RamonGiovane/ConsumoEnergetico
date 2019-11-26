#ifndef RELATOR_H
#define RELATOR_H
#include <string>

using namespace std;
class RelatorDeErros
{
public:

	inline string getMensagemErro() {
		return mensagemErro;
	}

protected:

	inline void setMensagemErro(const string & mensagemErro) {
		this->mensagemErro = mensagemErro;
	}

	//Define uma mensagem de erro e retorna false. �til para disparar um erro quando uma opera��o inv�lida acontecer.
	inline bool erro(const string & mensagemErro) {
		setMensagemErro(mensagemErro);
		return false;
	}


private:
	string mensagemErro;
};

#endif // !RELATOR_H