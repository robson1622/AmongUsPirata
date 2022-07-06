#pragma once
#include "Obstaculos.hpp"


class Pedra:public Obstaculos
{
private:
public:
	Pedra();
	~Pedra();
	void colidiu(Jogador* player) ;
	const char* getLocal_imagem() { return ""; };

};

