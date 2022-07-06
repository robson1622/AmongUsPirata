#pragma once
#include "Menu.hpp"

class MenuPause : public Menu
{
private:
	char texto_botao[2][20] = { "RETORNAR", "SALVAR E SAIR" };
public:
	MenuPause( Jogo* jogo, estado_jogo est);
	~MenuPause();
	void executar();
	void exibirMenu();
	
};

