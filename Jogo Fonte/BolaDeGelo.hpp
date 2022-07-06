#pragma once
#include "Projetil.hpp"

class BolaDeGelo : public Projetil {
private:
	int congelamento;
public:
	BolaDeGelo();
	~BolaDeGelo();
	void colidiu(Jogador* player);
	void colidiu(Inimigo* inim);
};