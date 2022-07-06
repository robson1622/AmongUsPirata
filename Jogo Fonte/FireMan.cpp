
#include "MovimentoImagem.hpp"
#include "FireMan.hpp"
#include "Vetor.hpp"
#include "BolaDeFogo.hpp"

#define PARADO 1
#define CORRENDO 2
#define PULANDO 3
#define ATACANDO 4
#define SENDOATACADO 5



FireMan::FireMan() :Jogador() {
	tipoObjeto = Ente::TipoObjeto::FIREMAN;

	for (int i = 0; i < 5; i++) {
		MovimentoImagem* novo = new MovimentoImagem();
		novo->setLarguraAltura(32,32);
		movimentos->adicionar(novo);
	}
	areaOcupada->x = 14;
	areaOcupada->y = 18;
	forca = 3;
	maxVelocidade->y = 6;
	maxVelocidade->x = 4;

	movimentos->pegar(PARADO)->setPosicao(posicao);;
	movimentos->pegar(CORRENDO)->setPosicao(posicao);
	movimentos->pegar(PULANDO)->setPosicao(posicao);
	movimentos->pegar(ATACANDO)->setPosicao(posicao);
	movimentos->pegar(SENDOATACADO)->setPosicao(posicao);



	movimentos->pegar(PARADO)->setLocalDaImagem("Art/P2/parado.png");
	movimentos->pegar(CORRENDO)->setLocalDaImagem("Art/P2/correndo.png");
	movimentos->pegar(PULANDO)->setLocalDaImagem("Art/P2/pulando.png");
	movimentos->pegar(ATACANDO)->setLocalDaImagem("Art/P2/atacando.png");
	movimentos->pegar(SENDOATACADO)->setLocalDaImagem("Art/P2/sendoAtacado.png");
	for (int i = 0; i < 12; i++) {
		if (i < 11) {
			movimentos->pegar(PARADO)->setOutraPosicaoNaImagem(i * 32, 0, 32, 32);
		}
		if (i < 5) {
			movimentos->pegar(ATACANDO)->setOutraPosicaoNaImagem(i * 32, 0, 32, 32);
		}
		if (i < 12) {
			movimentos->pegar(CORRENDO)->setOutraPosicaoNaImagem(i * 32, 0, 32, 32);
		}
		if (i < 6) {
			movimentos->pegar(PULANDO)->setOutraPosicaoNaImagem(i * 32, 0, 32, 32);
		}
		if (i < 7) {
			movimentos->pegar(SENDOATACADO)->setOutraPosicaoNaImagem(i * 32, 0, 32, 32);
		}
	}


}
FireMan::~FireMan() {

}


//Faltando configurar o intervalo de tempo que se pode lancar projetil
Projetil* FireMan::atacar() {
	if (atacou) {
		BolaDeFogo* bola = new BolaDeFogo();
		VetorF posicaoProjetil(0, posicao->y - (areaOcupada->y / 2));
		if (movimentos->pegar(1)->imagemInvertida()) {
			bola->setVelocidade(VetorF(-35, -4));
			posicaoProjetil.x = -1 + posicao->x - (areaOcupada->x + bola->getAreaOcupada()->x) / 2;
		}
		else {
			posicaoProjetil.x = 1 + posicao->x + (areaOcupada->x + bola->getAreaOcupada()->x) / 2;
			bola->setVelocidade(VetorF(35, -4));
		}

		bola->setPosicao(&posicaoProjetil);
		atacou= false;
		return static_cast<Projetil*>(bola);
	}
	else {
		return NULL;
	}
}