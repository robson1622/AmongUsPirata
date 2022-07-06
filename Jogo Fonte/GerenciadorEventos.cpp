#include "GerenciadorEventos.hpp"
#include "GerenciadorGrafico.hpp"
#include "GerenciadorColisoes.hpp"
#include "Vetor.hpp"
#include "Lista.hpp"
#include "Jogo.hpp"
#include "Fase.hpp"
#include "Menu.hpp"
#include "MenuFimJogo.hpp"
#include <iostream>
using std::cout;
using std::endl;

GerenciadorEventos::GerenciadorEventos(Jogo* jogo) :gGraficos(NULL), pjogo(jogo) {

	gGraficos = pjogo->getGrafico();
	
}
GerenciadorEventos::~GerenciadorEventos() {
	delete gGraficos;
	delete gGraficos;
}

void GerenciadorEventos::ControlarJogador() {
	//Pega e verifica se o comando digitado pelo usuario
	//foi um dos setados para controlar os players
	VetorF direcaoIce(0, 0);
	VetorF direcaoFire(0, 0);
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		direcaoIce.x = -1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		direcaoIce.x = 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		direcaoIce.y = 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		direcaoIce.y = -1;
	}
	pjogo->movimentar(1, &direcaoIce);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		direcaoFire.x = -1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		direcaoFire.x = 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		direcaoFire.y = 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		direcaoFire.y = -1;
	}
	pjogo->movimentar(2, &direcaoFire);
	
}


void GerenciadorEventos::setListaMenu(Menu* mE)
{
	listaMenu.push_back(mE);
}

void GerenciadorEventos::executarKey(sf::Event tipo)
{
	estado_jogo estado = pjogo->getEstado();

		if (tipo.key.code == sf::Keyboard::Key::Escape) {
			if (estado == estado_jogo::jogando) {
				pjogo->setEstado(estado_jogo::menuPause);
			}
			else
			if (estado == estado_jogo::menuPause) {
				pjogo->setEstado(estado_jogo::jogando);
			}
		}
		else
		for (it_listaMenu = listaMenu.begin(); it_listaMenu != listaMenu.end(); ++it_listaMenu) {
			if (estado == (*it_listaMenu)->getEstadoMenu() ){
				if (tipo.key.code == sf::Keyboard::Key::Enter) {
					(*it_listaMenu)->executar();

					//Verficar Qual fase ele selecionou
					if (estado == estado_jogo::menuPrincipal)
						if ((*it_listaMenu)->getSelecionado() == 1 || (*it_listaMenu)->getSelecionado() == 2)
							pjogo->setTipoFase((*it_listaMenu)->getSelecionado());

				}
				else
					if (tipo.key.code == sf::Keyboard::Key::Up)
						(*it_listaMenu)->selecaoCima();
				else
					if (tipo.key.code == sf::Keyboard::Key::Down)
						(*it_listaMenu)->selecaoBaixo();
			}

				
		}
	
}


void GerenciadorEventos::loopEventos()
{
	sf::Event eventos;
	estado_jogo estado = pjogo->getEstado();

	while (gGraficos->Evento(&eventos))
	{
		if (eventos.type == sf::Event::Closed)
			gGraficos->Fechar();

		if ((eventos.type == sf::Event::KeyPressed)) {
			executarKey(eventos);
		}
		if ((eventos.type == sf::Event::TextEntered) && pjogo->getEstado()==estado_jogo::menuFim) {
			gGraficos->nomeTextEntered(eventos);
		}
	}
}
