#pragma once
#include "Inimigo.hpp"

class Porco : public Inimigo {
private:
	bool atacou;
public:
	Porco();
	~Porco();
	void movimentar();
	void desenhar();
};

