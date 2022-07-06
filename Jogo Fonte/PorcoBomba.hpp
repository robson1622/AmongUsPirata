#pragma once
#include "Inimigo.hpp"

class PorcoBomba: public Inimigo{
private:
	bool pegouBomba;
public:
	PorcoBomba();
	~PorcoBomba();
	void movimentar();
	void desenhar();
	Projetil* atacar();
};

