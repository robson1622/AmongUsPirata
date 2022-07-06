#pragma once
#include "Projetil.hpp"

class Bomba :public Projetil {
private:
	VetorF *impacto;
public:
	Bomba();
	~Bomba();
	void colidiu(Jogador* player);
	void colidiu(Inimigo* inim);
};