#pragma once
#include "Jogador.hpp"

class IceMan : public Jogador {
private:
	
public:
	IceMan();
	~IceMan();
	Projetil* atacar();
};