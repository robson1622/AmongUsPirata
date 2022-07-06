#include "MenuNovaFase.hpp"
#include "Vetor.hpp"
#include "Botao.hpp"
#include "GerenciadorEventos.hpp"
#include "Fase1.hpp"
#include "Fase.hpp"
#include "Fase2.hpp"


MenuNovaFase::MenuNovaFase(Jogo* jogo, estado_jogo est):Menu(jogo,3,0,est)
{

	float pos = 0.0;
	for (int i = 0; i <= 3; i++) {
		VetorF* posicao = new VetorF(1280 / 2.0f, (420 + pos) / 2.0f);
		Botao* bot = new Botao(posicao, texto_botao[i]);
		//DEIXAR PRIMEIRO BOTÃO SETADO
		if (i == 0)
			bot->animacao();

		ListaBotao->adicionar(bot);
		pos += 140;
	}

	setFundo_Menu_Local(PATH_BACK_MENU);
}

MenuNovaFase::~MenuNovaFase()
{
}

void MenuNovaFase::executar()
{
		
			if (selecionado == 0) {
				pJogo->setEstado(estado_jogo::jogando);
				carregarFase(1);
			}

			if (selecionado == 1) {
				pJogo->setEstado(estado_jogo::jogando);
				carregarFase(2);
			}

			if (selecionado == 2) {
				pJogo->setEstado(estado_jogo::jogando);
				carregarFase(3);
			}

			if (selecionado == 3) {
				pJogo->setEstado(estado_jogo::menuPrincipal);
			}
			
		
}


void MenuNovaFase::carregarFase(const int i)
{
	if (pJogo->getTipoFase() == 1){
		pJogo->verificarFase();
		Fase1* faseEscolhida = new Fase1();
		faseEscolhida->Cenario(i,pJogo->getJogador1(), pJogo->getJogador2());
		pJogo->setfaseP(faseEscolhida);
		pJogo->setTipoFase(1);
		pJogo->setqtd_player(i);
	}
	else
	{
		Fase2* faseEscolhida = new Fase2();
		pJogo->verificarFase();
		faseEscolhida->Cenario(i, pJogo->getJogador1(), pJogo->getJogador2());
		pJogo->setfaseS(faseEscolhida);
		pJogo->setTipoFase(2);
		pJogo->setqtd_player(i);
	}
}

void MenuNovaFase::exibirMenu()
{
	Ente::desenhar();
	for (int i = 0; i < ListaBotao->tamanhoLista(); i++) {
		ListaBotao->operator[](i)->desenhar();
	}
}




