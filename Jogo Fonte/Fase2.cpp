#include "Fase2.hpp"
#include "Blocos.hpp"
#include "Vetor.hpp"
#include "FireMan.hpp"
#include "IceMan.hpp"
#include "Randomizador.hpp"
#include "Chefao.hpp"
#include "Porco.hpp"
#include "PorcoBomba.hpp"
#include <iostream>
using std::cout;
using std::endl;
//#include "Pedra.hpp"
Fase2::Fase2() :Fase() {

	

	setFundo_Fase_Local(PATH_FASE2);
}

Fase2::~Fase2() {
	
}



void Fase2::Cenario(const int qtdplayer, IceMan* jogador1, FireMan* jogador2) {
	VetorF* pos = new VetorF(0, 0);


	VetorF posicao1(80, 80);

	arq.open("include/Fase2.txt");
	for (int i = 0; i < LINHAS; i++) {
		for (int j = 0; j < COLUNAS; j++) {
			arq >> plataforma[i][j];
		}
	}
	arq.close();

	if (qtdplayer == 1) {
		listaJogadores->adicionar(static_cast<Jogador*>(jogador1));
		jogador1->setPosicao(&posicao1);
	}

	if (qtdplayer == 2) {
		listaJogadores->adicionar(static_cast<Jogador*>(jogador2));
		jogador2->setPosicao(&posicao1);
	}

	if (qtdplayer == 3) {

		listaJogadores->adicionar(static_cast<Jogador*>(jogador1));
		listaJogadores->adicionar(static_cast<Jogador*>(jogador2));
		jogador1->setPosicao(&posicao1);
		jogador2->setPosicao(&posicao1);
	}


	
	

	for (int i = 0; i < LINHAS; i++) {
		for (int j = 0; j < COLUNAS; j++) {
			if (plataforma[i][j] != 0) {
				pos->x = (float)j * 40;
				pos->y = (float)i * 40;
				Blocos* novo_bloco = new Blocos();
				std::string loc = "Art/Fase2/" + std::to_string(plataforma[i][j]) + ".png";
				novo_bloco->setPosicao(pos);
				*pos = 40.f;
				novo_bloco->setAreaOcupada(pos);
				novo_bloco->setLocalImagem(loc.c_str());
				mapaDeBlocos->operator[](make_pair(j, i)) = static_cast<Obstaculos*>(novo_bloco);

				//Blocos do tipo 2 são blocos que a posicao pode ter alguma entidade
				if (plataforma[i][j] = 2)
					randor->adicionarEntidade(static_cast<Entidade*>(novo_bloco));
			}
		}
	}
	geraObstaculos();
	geraInimigos();
	inicizalizarColivideis();
}

void Fase2::geraInimigos()
{
	int qtd = randor->valorAteatorio(3, 4);


	for (int i = 0; i < qtd; i++) {
		VetorF posicao1(0, 0);
		Chefao* chefin = new Chefao();
		posicao1 = randor->posicaoAleatoriaSemColisao(chefin->getAreaOcupada(), 40);
		chefin->setPosicao(&posicao1);
		listaInimigos->adicionar(static_cast<Inimigo*>(chefin));
		randor->adicionarEntidade(chefin);
	}

	qtd = randor->valorAteatorio(3, 5);

	for (int i = 0; i < qtd; i++) {
		VetorF posicao(0, 0);
		Porco* po = new Porco();
		posicao = randor->posicaoAleatoriaSemColisao(po->getAreaOcupada(), 40);
		po->setPosicao(&posicao);
		listaInimigos->adicionar(static_cast<Inimigo*>(po));
		randor->adicionarEntidade(po);

	}
	qtd = randor->valorAteatorio(3, 8);

	for (int i = 0; i < qtd; i++) {
		VetorF posicao2(0, 0);
		PorcoBomba* pb = new PorcoBomba();
		posicao2 = randor->posicaoAleatoriaSemColisao(pb->getAreaOcupada(), 40);
		pb->setPosicao(&posicao2);
		listaInimigos->adicionar(static_cast<Inimigo*>(pb));
		randor->adicionarEntidade(pb);
	}
	qtd = randor->valorAteatorio(3, 5);

}

void Fase2::recarregarCenario()
{
	VetorF* pos = new VetorF(0, 0);

	arq.open("include/Fase2.txt");
	for (int i = 0; i < LINHAS; i++) {
		for (int j = 0; j < COLUNAS; j++) {
			arq >> plataforma[i][j];
		}
	}
	arq.close();

	for (int i = 0; i < LINHAS; i++) {
		for (int j = 0; j < COLUNAS; j++) {
			if (plataforma[i][j] != 0) {
				pos->x = (float)j * 40;
				pos->y = (float)i * 40;
				Blocos* novo_bloco = new Blocos();
				std::string loc = "Art/Fase2/" + std::to_string(plataforma[i][j]) + ".png";
				novo_bloco->setPosicao(pos);
				*pos = 40.f;
				novo_bloco->setAreaOcupada(pos);
				novo_bloco->setLocalImagem(loc.c_str());
				mapaDeBlocos->operator[](make_pair(j, i)) = static_cast<Obstaculos*>(novo_bloco);
			}
		}
	}
}

