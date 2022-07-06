#pragma once
#include "Obstaculos.hpp"

class Espinhos : public Obstaculos
{
private:

public:
	Espinhos();
	~Espinhos();
	void colidiu(Jogador* player);
	const char* getLocal_imagem() { return ""; };
};

