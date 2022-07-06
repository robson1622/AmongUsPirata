#pragma once
#include "SFML/Graphics.hpp"
#include "Entidade.hpp"
#include "Obstaculos.hpp"

class Blocos : public Obstaculos
{
private:
	const char* local_imagem;
public:
	Blocos();
	 ~Blocos();
	void setLocalImagem(const char* local);
	virtual void movimentar();
	const char* getLocal_imagem();
};

