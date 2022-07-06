#pragma once
#include "Blocos.hpp"
#include "Lista.hpp"

#include "SFML/Graphics.hpp"
#include "Obstaculos.hpp"
#include "Pedra.hpp"

class Fase1;

class Fase
{
protected:
	Lista<Obstaculos>* listaObstaculos;
	Lista<Bloco>* listaBlocos;
	sf::Sprite fundo_fase;
	sf::Texture fundo_fase_local;

	
	void setFundo_Fase_Local(const char* local);
	void setFundo_Fase(sf::Texture* text);

public:
	Fase();
	~Fase();
	void desenhar(sf::RenderWindow* janela);
	Lista<Obstaculos>* getObstaculos();
	Lista<Bloco>* getBlocos();
};

