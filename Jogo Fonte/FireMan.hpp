#pragma once
#include "Jogador.hpp"

class FireMan : public Jogador {
private:
public:
	FireMan();
	~FireMan();
	Projetil* atacar();

};