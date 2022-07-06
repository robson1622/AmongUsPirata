#pragma once
#include "Menu.hpp"
#include <fstream>
#define PATH_BACK_MENUCLAS "art/BackgroundClas.jpg"

class MenuClassificacao : public Menu
{
private:

public:
	MenuClassificacao(Jogo* jogo, estado_jogo est);
	~MenuClassificacao();
	void exibirMenu();
	void carregar();
	void executar();
};

