#pragma once
#include "Menu.hpp"
#define PATH_BACK_MENU "art/BackgroundMenu.jpg"

class MenuNovaFase : public	Menu
{
private:
	char texto_botao[4][20] = { "IceMan", "FireMan","Os Dois","Retonar" };
public:
	MenuNovaFase(Jogo* jogo, estado_jogo est);
	~MenuNovaFase();
	void executar();
	void carregarFase(const int i);
	void exibirMenu();

};

