#pragma once
#include "SFML/Graphics.hpp"
#include <list>
#include "Menu.hpp"
#include "Jogo.hpp"
//#include "Menu.hpp"

class GerenciadorGrafico;

class GerenciadorEventos {
private:
	GerenciadorGrafico* gGraficos;
	
	std::list<Menu*> listaMenu;
	std::list<Menu*>::iterator it_listaMenu;

	Jogo* pjogo;


public:
	
	GerenciadorEventos(Jogo* jogo);
	~GerenciadorEventos();
	void loopEventos();
	void ControlarJogador();
	void setListaMenu(Menu* mE);
	void executarKey(sf::Event tipo);
};