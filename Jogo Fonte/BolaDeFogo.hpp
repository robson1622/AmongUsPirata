#pragma once
#include "Projetil.hpp"

class BolaDeFogo : public Projetil {
private:
	bool queimacao;
public:
	BolaDeFogo();
	~BolaDeFogo();
	void colidiu(Jogador* player);
	void colidiu(Inimigo* inim);
	void colidiu(Projetil* proj);
};