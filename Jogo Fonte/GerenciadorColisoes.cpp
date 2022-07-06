#include "GerenciadorColisoes.hpp"
#include "Fase.hpp"
#include "Lista.hpp"
#include "Vetor.hpp"

//Apenas para fins de testes 
#include "GerenciadorGrafico.hpp"
#include "Projetil.hpp"
#include "Jogador.hpp"
#include "Blocos.hpp"
#include "Inimigo.hpp"
#include "Obstaculos.hpp"

#include "SFML/Graphics.hpp"
#include <math.h>
#include <stdio.h>
#include <iostream>
using std::cout;
using std::endl;

#define GRAVIDADE 0.5

GerenciadorColisoes::GerenciadorColisoes(): 
	listaJogadores(NULL),
	listaObstaculos(NULL),
	listaInimigos(NULL),
	listaProjetil(NULL),
	mapaObstaculos(NULL)
{

}

GerenciadorColisoes::~GerenciadorColisoes() {
}
//Consideracao, os ifs ja passam para cada objeto o outro que ele colidiu
//para que assim cada um decida o que acontece de acordo as suas especificidades
void GerenciadorColisoes::checarColisoes() {
	//Requisitos:
	// Jogador - inimigo
	// Jogador - Projeteis
	// Jogador - Obstaculos
	// 
	// Inimigo - obstaculos
	// Inimigo - Projeteis
	// 
	// Projeteis - obstaculos
	// Gravidade para os nao fixos
	// 
	// 
	// 
	//Colisoes com jogadores
	for (int i = 0; i < listaJogadores->tamanhoLista(); i++) {
		Jogador* player = listaJogadores->pegar(i);
		
		if (player->personagemAtacou()) {
			Projetil* aux = player->atacar();
			if (aux) {
				listaProjetil->adicionar(aux);
			}
		}

		player->setVelocidade(VetorF(player->getVelocidade()->x, float(player->getVelocidade()->y + GRAVIDADE)));
		
		//Jogador - Inimigo
		for (int j = 0; j < listaInimigos->tamanhoLista(); j++) {
			Inimigo* enemy = listaInimigos->pegar(j);
			enemy->checarSeJogadorFoiVisto(player);
			if (enemy->podeArremecarProjetil() && enemy->personagemAtacou()) {
				Projetil* umaBomba = enemy->atacar();
				if (umaBomba) {
					listaProjetil->adicionar(umaBomba);
				}
			}
			if (*player == enemy) {
				player->colidiu(enemy);
				enemy->colidiu(player);
			}
			if (enemy->morreu()) {
				listaInimigos->remover(j);
				//existe uma lista de desenhaveis que utiliza o ponteiro
				// se deletar ele aqui ela vai dar secmentation found (pontero NULL)
				//delete enemy;
			}
		}
		//jogador - obstaculos
		for (int k = 0; k < listaObstaculos->tamanhoLista(); k++) {
			Obstaculos* obs = listaObstaculos->pegar(k);
			obs->setVelocidade(VetorF(obs->getVelocidade()->x, float(obs->getVelocidade()->y + GRAVIDADE)));
			if (*player ==obs) {
				player->colidiu(obs);
				obs->colidiu(player);
			}
		}
		//Jogador - Projetil
		for (int k = 0; k < listaProjetil->tamanhoLista(); k++) {
			Projetil* proje = listaProjetil->pegar(k);
			proje->setVelocidade(VetorF(proje->getVelocidade()->x, float(proje->getVelocidade()->y + GRAVIDADE)));
			if (*player == proje) {
				player->colidiu(proje);
				proje->colidiu(player);
			}
			if (proje->podeApagar()) {
				listaProjetil->remover(k);
				delete proje;
			}
		}

		
		//utilizo quadrantes de 40px setados na criadora de fase para minimizar a complexidade geral do codigo em tempo de execucao
		//utilizo a busca em ramos do map para verificar se nos 9  quadrantes que tem em volta do jogador
		//existe um obstaculo, se exitir, entao se verifica colisao
		//Jogador - Blocos
		for (int j = 1; j > -2; j--) {
			for (int k = 1; k > -2; k--) {
				Obstaculos* obs = mapaObstaculos->operator[](std::make_pair(int(ceil(player->getPosicao()->x / 40) + j), int(ceil(player->getPosicao()->y / 40) + k)));

				if (obs && *obs == player) {
					obs->colidiu(player);
				}
			}
		}
		if (player->morreu()) {
			listaJogadores->remover(i);
		}
	}



	//colisoes com inimigos - projetil
	for (int j = 0; j < listaInimigos->tamanhoLista(); j++) {
		Inimigo* enemy = listaInimigos->pegar(j);
		for (int k = 0; k < listaProjetil->tamanhoLista(); k++) {
			Projetil* proje = listaProjetil->pegar(k);
			if (*enemy == proje) {
				enemy->colidiu(proje);
				proje->colidiu(enemy);
			}
		}

	}


	//Colisoes obstáculo - Blocos
	for (int i = 0; i < listaObstaculos->tamanhoLista(); i++) {
		Obstaculos* aux = listaObstaculos->pegar(i);
		for (int j = 1; j > -2; j--) {
			for (int k = 1; k > -2; k--) {
				Obstaculos* obs = mapaObstaculos->operator[](std::make_pair(int(ceil(aux->getPosicao()->x / 40) + j), int(ceil(aux->getPosicao()->y / 40) + k)));
				if (obs && *obs == aux) {
					aux->colidiu(obs);
				}
			}
		}
	}


	//Colisoes Projetil - Obstaculos
	for (int i = 0; i < listaProjetil->tamanhoLista(); i++) {
		Projetil* proje = listaProjetil->pegar(i);
		Obstaculos* obs = mapaObstaculos->operator[](std::make_pair(int(ceil(proje->getPosicao()->x / 40)), int(ceil(proje->getPosicao()->y / 40))));
			if (obs && *obs == proje ) {
				proje->colidiu(obs);
			}
			//se estiver fora da janela pode apagar
			else if (proje->getPosicao()->x < 0 || proje->getPosicao()->x > 1280) {
				listaProjetil->remover(i);
				delete proje;
			}
	}

	
	//Colisoes Inimigo - Blocos
	for (int i = 0; i < listaInimigos->tamanhoLista(); i++) {
		Inimigo* enemy = listaInimigos->pegar(i);
		enemy->setVelocidade(VetorF(enemy->getVelocidade()->x, float(enemy->getVelocidade()->y + GRAVIDADE)));
		for (int j = -1; j < 2; j++) {
			for (int k = -1; k < 2; k++) {
				Obstaculos* obs = mapaObstaculos->operator[](std::make_pair(int(ceil(enemy->getPosicao()->x / 40) + j), int(ceil(enemy->getPosicao()->y / 40) + k)));
				if (obs && *obs == enemy) {
					obs->colidiu(enemy);
					enemy->colidiu(obs);
				}
			}
		}
	}
}

void GerenciadorColisoes::setLista(Lista<Obstaculos>* lista) {
	if (lista) {
		listaObstaculos= lista;
	}
}
void GerenciadorColisoes::setLista(Lista<Jogador>* lista) {
	if (lista) {
		listaJogadores = lista;
	}
}
void GerenciadorColisoes::setLista(Lista<Projetil>* lista) {
	if (lista) {
		listaProjetil = lista;
	}
}
void GerenciadorColisoes::setLista(Lista<Inimigo>* lista) {
	if (lista) {
		listaInimigos = lista;
	}
}
void GerenciadorColisoes::setMapaDeObstaculos(map<pair<int, int>, Obstaculos*> *mapaDeObstaculos) {
	if(mapaDeObstaculos){
		mapaObstaculos = mapaDeObstaculos;
	}
}