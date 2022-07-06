#include "MenuPrincipal.hpp"
#include "Botao.hpp"
#include "GerenciadorEventos.hpp"

MenuPrincipal::MenuPrincipal(Jogo* jogo, estado_jogo est):Menu(jogo,3,0,est)
{
	setFundo_Menu_Local(PATH_BACK_MENU);
	float pos = 0.0;

	int j = 1;
	if (pJogo->getExistecarregar()) {
		j = 0;
		maximo++;
	}

	for (int i=j; i < 5; i++) {
		VetorF* posicao = new VetorF(1280 / 2.0f, (420+pos) / 2.0f);
		Botao* bot = new Botao(posicao, texto_botao[i]);

		
		if (i == j)
		bot->animacao();

		ListaBotao->adicionar(bot);
		pos += 140;
	}
}

MenuPrincipal::~MenuPrincipal()
{
}


void MenuPrincipal::executar()
{
	if (pJogo->getExistecarregar()){
		if (selecionado == 0) {
			pJogo->setEstado(estado_jogo::jogando);
			pJogo->criarFase();
		}
	}
	else
	{
		if (selecionado == 0)
			selecionado = 1;
	}

	if (selecionado == 1) {
		pJogo->setEstado(estado_jogo::menuNovoJogo);
	}

	if (selecionado == 2) {
		pJogo->setEstado(estado_jogo::menuNovoJogo);
	}

	if (selecionado == 3) {
		pJogo->setEstado(estado_jogo::menuClassicacao);
	}
	
	if (selecionado == 4) {
		pJogo->fimJogo();
	}
	
}



void MenuPrincipal::exibirMenu()
{
	Ente::desenhar();
	
	for (int i =0; i < ListaBotao->tamanhoLista(); i++) {
		ListaBotao->operator[](i)->desenhar();
	}
}







