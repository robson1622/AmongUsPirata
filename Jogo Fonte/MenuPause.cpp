#include "MenuPause.hpp"
#include "Botao.hpp"
#define PATH_BACK_MENU "art/BackgroundMenu.jpg"

MenuPause::MenuPause(Jogo* jogo, estado_jogo est):Menu(jogo, 1, 0,est)
{
	setFundo_Menu_Local(PATH_BACK_MENU);
	float pos = 0.0;
	for (int i = 0; i < 2; i++) {
		VetorF* posicao = new VetorF(1280 / 2.0f, (420 + pos) / 2.0f);

		//DEIXAR PRIMEIRO BOTÃO SETADO
		Botao* bot = new Botao(posicao, texto_botao[i]);
		if (i == 0)
			bot->animacao();

		ListaBotao->adicionar(bot);
		pos += 140;
	}
}

MenuPause::~MenuPause()
{
}

void MenuPause::executar()
{
	if (selecionado == 0) {
		pJogo->setEstado(estado_jogo::jogando);
	}
	if (selecionado == 1) {
		pJogo->setEstado(estado_jogo::menuFim);
	}
}



void MenuPause::exibirMenu()
{
	Ente::desenhar();
	for (int i = 0; i < ListaBotao->tamanhoLista(); i++) {
		ListaBotao->operator[](i)->desenhar();
	}
}

