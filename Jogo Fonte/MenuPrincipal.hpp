#include "Menu.hpp"

#define PATH_BACK_MENU "art/BackgroundMenu.jpg"

class MenuPrincipal : public Menu
{
private:
	char texto_botao[5][30] = { "CARREGAR", "FASE 1", "FASE 2", "CLASSIFICAÇÃO","SAIR"};
	
public:
	MenuPrincipal(Jogo* jogo, estado_jogo est);
	~MenuPrincipal();
	void executar();
	void exibirMenu();
	

};
