
#include "GerenciadorEventos.hpp"
#include "GerenciadorGrafico.hpp"
#include "Menu.hpp"
#include "MenuPrincipal.hpp"
#include "MenuNovaFase.hpp"
#include "Fase.hpp"
#include "Vetor.hpp"
#include "Fase1.hpp"
#include "Fase2.hpp"
#include "MenuPause.hpp"
#include "MenuFimJogo.hpp"
#include "Jogador.hpp"
#include "IceMan.hpp"
#include "FireMan.hpp"
#include "MenuClassificacao.hpp"
#include "HistoricoJogo.hpp"

#include <iostream>
using std::cout;
using std::endl;

// Segunda nota parcial - Tecnicas de programacao - 2022/1
// Professor Jean Marcelo Simao
//
// Alunos:
// Robson Borges dos Santos - 2190397
// Gabriel Leite Rodrigues Barbosa Mororó - 2306298

//Bem vindo ao nosso código do jogo
//Nessa parte temos a classe principal do jogo


Jogo::Jogo()
{
	inicializar();
	loop();
}

Jogo::~Jogo()
{
}


void Jogo::inicializar()
{

		//Primeiro checar se tem um log de um jogo anteriro
		//Tendo isso, menu deve exibir continuar
		//Não tendo, deve-se exibir, iniciar, escolher fase, ranking e sair
		//Se escolher ranking, menu deve exibir o ranking e um botao voltar ao menu anteiro
	try {
		jogador1 = new IceMan();
		jogador2 = new FireMan();


		estado = estado_jogo::menuPrincipal;
		existe_carregar = HistoricoJogo::exiteJogoSalvo;
		
		
		gGraficos = new GerenciadorGrafico("AmongUs Pirata");
		gE = new GerenciadorEventos(this);

		MenuPri = new MenuPrincipal(this,estado_jogo::menuPrincipal);
		MenuFase = new MenuNovaFase(this, estado_jogo::menuNovoJogo);
		MenuP = new MenuPause(this, estado_jogo::menuPause);
		MenuF = new MenuFimJogo(this, estado_jogo::menuFim,historico);
		MenuClas = new MenuClassificacao(this, estado_jogo::menuClassicacao);

		gE->setListaMenu(static_cast<Menu*>(MenuPri));
		gE->setListaMenu(static_cast<Menu*>(MenuFase));
		gE->setListaMenu(static_cast<Menu*>(MenuP));
		gE->setListaMenu(static_cast<Menu*>(MenuF));
		gE->setListaMenu(static_cast<Menu*>(MenuClas));

	}
	catch (std::exception& ) {
		
		std::cout << "Erro ao Inicializar " << std::endl;
		exit(1);
		
	}
	
}
void Jogo::setIce(IceMan* ice) {
	jogador1 = ice;
}
void Jogo::setFire(FireMan* fire) {
	jogador2 = fire;
}

void Jogo::loop() {
	
	while (gGraficos->Open()) {
		gGraficos->Limpar();

		gE->loopEventos();

		if (estado == estado_jogo::jogando) {

			if (tipo_fase == 1) {
				
				faseP->desenhar();
				getPlayerVivo();
				gE->ControlarJogador();
				faseP->checarColisao();
				faseP->movimentarEntes();
				if (faseP->getPassouFase()) {
					trocarFase();
				}
				
			}
			else
			if (tipo_fase == 2) {
				
				faseS->desenhar();
				getPlayerVivo();
				gE->ControlarJogador();
				faseS->checarColisao();
				faseS->movimentarEntes();
			}
			
		}
		else

		if (estado == estado_jogo::menuNovoJogo) {
			MenuFase->exibirMenu();
		}

		else

		if (estado == estado_jogo::menuPrincipal) {
			MenuPri->exibirMenu();
		}

		else

		if (estado == estado_jogo::menuPause) {
			MenuP->exibirMenu();
		}

		else

		if (estado == estado_jogo::menuFim) {
			MenuF->atualizarText();
			MenuF->exibirMenu();
		}
		else
		if (estado == estado_jogo::menuClassicacao) {
				MenuClas->exibirMenu();
		}
		gGraficos->Display();
	}

}

void Jogo::criarFase()
{
	int id_fase = HistoricoJogo::faseSalva();

	if (id_fase==1) {
		faseP = new Fase1();
		faseP->recarregarFase(this);
		faseP->adicionarJogador(jogador1);
		faseP->adicionarJogador(jogador2);
		setTipoFase(id_fase);

	}
	else
	if (id_fase == 2) {
		faseS = new Fase2();
		faseS->recarregarFase(this);
		faseP->adicionarJogador(jogador1);
		faseP->adicionarJogador(jogador2);
		setTipoFase(id_fase);
	}

}

void Jogo::movimentar(const int player, const VetorF &direcao)
{
	if (player == 1) {
		jogador1->controlar(direcao);
	}
	else if(player == 2) {
		jogador2->controlar(direcao);
	}
}

void Jogo::verificarFase() {
	if (faseP != NULL) {
		delete faseP;
		faseP = NULL;
	}
	else
	if (faseS != NULL) {
		delete faseS;
		faseS = NULL;
	}
}

void Jogo::setEstado(estado_jogo es) {
	estado = es;
}

void Jogo::fimJogo()
{
	gGraficos->Fechar();
}

estado_jogo Jogo::getEstado() const
{
	return estado;
}

void Jogo::setTipoFase(int idFase)
{
	tipo_fase = idFase;
}


int Jogo::getTipoFase() const
{
	return tipo_fase;
}

int Jogo::getQtd_player() const
{
	return qtd_player;
}

void Jogo::setqtd_player(int qtd)
{
	qtd_player = qtd;
}


void Jogo::getPlayerVivo() 
{
	if (tipo_fase == 1) {
		if (faseP->getJogadores()->tamanhoLista() == 0) {
			estado = estado_jogo::menuFim;
		}
	}
	else if (tipo_fase == 2) {
		if (faseS->getJogadores()->tamanhoLista() == 0) {
			estado = estado_jogo::menuFim;
		}
	}

		
}

void Jogo::trocarFase()
{
	if (faseP != NULL) {
		int qtd_player = faseP->getJogadores()->tamanhoLista();
		delete faseP;
		faseP = NULL;
		faseS = new Fase2();
		faseS->Cenario(qtd_player, getJogador1(), getJogador2());
		tipo_fase = 2;
	}

}

GerenciadorGrafico* Jogo::getGrafico() const
{
	return gGraficos;
}

IceMan* Jogo::getJogador1() const {
	return jogador1;
}

FireMan* Jogo::getJogador2() const {
	return jogador2;
}

void Jogo::setfaseP(Fase1* p)
{
	faseP = p;
}

void Jogo::setfaseS(Fase2* p) 
{
	faseS = p;
}

Fase1* Jogo::getFase1() const
{
	return faseP;
}

Fase2* Jogo::getFase2() const
{
	return faseS;
}

bool Jogo::getExistecarregar() const
{
	return existe_carregar;
}


