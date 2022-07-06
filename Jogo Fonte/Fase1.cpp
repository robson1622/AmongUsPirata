#include "Fase1.hpp"
#include "Vetor.hpp"
#include "FireMan.hpp"
#include "IceMan.hpp"
#include "Randomizador.hpp"
#include "Porco.hpp"
#include "PorcoBomba.hpp"
#include <iostream>
using std::cout;
using std::endl;
//#include "Pedra.hpp"

#include "HistoricoJogo.hpp"

Fase1::Fase1():Fase(), passou_fase(false) {
	
	setFundo_Fase_Local(PATH_FASE1);
}

Fase1::~Fase1(){
	//listaObstaculos->limpar();
}



void Fase1::Cenario(const int qtdplayer,IceMan* jogador1, FireMan* jogador2){
	VetorF* pos = new VetorF(0, 0);

	
	VetorF posicao1(80, 80);

	arq.open("include/Fase1.txt");
	for (int i = 0; i < LINHAS; i++) {
		for (int j = 0; j < COLUNAS; j++) {
			arq >> plataforma[i][j];
		}
	}
	arq.close();

	if (qtdplayer == 1) {
		listaJogadores->adicionar(static_cast<Jogador*>(jogador1));
		jogador1->setPosicao(&posicao1);
		randor->adicionarEntidade(static_cast<Entidade*>(jogador1));
		
	}

	if (qtdplayer == 2) {
		listaJogadores->adicionar(static_cast<Jogador*>(jogador2));
		jogador2->setPosicao(&posicao1);
		randor->adicionarEntidade(static_cast<Entidade*>(jogador2));
	}

	if (qtdplayer == 3) {
		listaJogadores->adicionar(static_cast<Jogador*>(jogador1));
		listaJogadores->adicionar(static_cast<Jogador*>(jogador2));
		jogador1->setPosicao(&posicao1);
		jogador2->setPosicao(&posicao1);
		randor->adicionarEntidade(static_cast<Entidade*>(jogador1));
		randor->adicionarEntidade(static_cast<Entidade*>(jogador2));

	}

	for (int i = 0; i < LINHAS; i++) {
		for (int j = 0; j < COLUNAS; j++) {
			if (plataforma[i][j] != 0) {
				pos->x = (float) j * 40;
				pos->y = (float) i * 40;
				Blocos* novo_bloco = new Blocos();
				std::string loc = "Art/Fase1/" + std::to_string(plataforma[i][j]) + ".png";
				novo_bloco->setPosicao(pos);
				*pos = 40.f;
				novo_bloco->setAreaOcupada(pos);
				novo_bloco->setLocalImagem(loc.c_str());
				mapaDeBlocos->operator[](make_pair(j, i)) = static_cast<Obstaculos*>(novo_bloco);

				//Blocos do tipo 2 são blocos que a posicao pode ter alguma entidade
				if(plataforma[i][j] = 2)
				randor->adicionarEntidade(static_cast<Entidade*>(novo_bloco));
			}
		}
	}
	
	//geraObstaculos();
	geraInimigos();
	inicizalizarColivideis();
}

bool Fase1::getPassouFase()
{
	for (int i = 0; i < listaJogadores->tamanhoLista(); i++) {
		if ((listaJogadores->operator[](i)->getPosicao()->x > 1200) && ((listaJogadores->operator[](i)->getPosicao()->y > 600)))
			passou_fase = true;
		else
		{
			passou_fase = false;
		}
	}
	return passou_fase;
}

void Fase1::geraInimigos()
{


	int qtd = 0;
	qtd = randor->valorAteatorio(3, 8);

	for (int i = 0; i < qtd; i++) {
		VetorF posicao(0, 0);
		Porco* po = new Porco();
		posicao = randor->posicaoAleatoriaSemColisao(po->getAreaOcupada(), 40);
		po->setPosicao(&posicao);
		randor->adicionarEntidade(po);
		listaInimigos->adicionar(static_cast<Inimigo*>(po));
		
		
	}

	qtd = randor->valorAteatorio(1, 3);

	for (int i = 0; i < qtd; i++) {
		VetorF posicao2(0, 0);
		PorcoBomba* pb = new PorcoBomba();
		posicao2 = randor->posicaoAleatoriaSemColisao(pb->getAreaOcupada(), 40);
		pb->setPosicao(&posicao2);
		listaInimigos->adicionar(static_cast<Inimigo*>(pb));
		randor->adicionarEntidade(pb);
	}
}

void Fase1::recarregarCenario()
{
	VetorF* pos = new VetorF(0, 0);

	arq.open("include/Fase1.txt");
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
				std::string loc = "Art/Fase1/" + std::to_string(plataforma[i][j]) + ".png";
				novo_bloco->setPosicao(pos);
				*pos = 40.f;
				novo_bloco->setAreaOcupada(pos);
				novo_bloco->setLocalImagem(loc.c_str());
				mapaDeBlocos->operator[](make_pair(j, i)) = static_cast<Obstaculos*>(novo_bloco);
			}
		}
	}
}




