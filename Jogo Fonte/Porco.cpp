#include "Porco.hpp"
#include "MovimentoImagem.hpp"
#include "Vetor.hpp"
#include "Jogador.hpp"
#include "Bomba.hpp"
//Valor do alcance da bomba em pixels
#define ALCANCEATAQUE 25
#define BARRAVIDA 0
#define PARADO 1
#define CORRENDO 2
#define ATACANDO 3
#define SENDOATACADO 4

Porco::Porco():Inimigo(),atacou(false) {
	tipoObjeto = Ente::TipoObjeto::PORCO;
	for (int i = 0; i < 5; i++) {
		MovimentoImagem* novo = new MovimentoImagem();
		movimentos->adicionar(novo);
	}
	areaOcupada->x = 24;
	areaOcupada->y = 24;
	posicao->x = 240;
	posicao->y = 600;
	forca = 1;
	maxVelocidade->x = 3;
	maxVelocidade->y = 1;
	delayAtaque = 10;
	movimentos->pegar(PARADO)->setPosicao(posicao);
	movimentos->pegar(PARADO)->setLarguraAltura(34, 28);
	movimentos->pegar(CORRENDO)->setPosicao(posicao);
	movimentos->pegar(CORRENDO)->setLarguraAltura(34, 28);
	movimentos->pegar(ATACANDO)->setPosicao(posicao);
	movimentos->pegar(ATACANDO)->setLarguraAltura(34, 28);
	movimentos->pegar(SENDOATACADO)->setPosicao(posicao);
	movimentos->pegar(SENDOATACADO)->setLarguraAltura(34, 28);

	movimentos->pegar(PARADO)->setLocalDaImagem("Art/PORCO/parado.png");
	movimentos->pegar(CORRENDO)->setLocalDaImagem("Art/PORCO/correndo.png");
	movimentos->pegar(ATACANDO)->setLocalDaImagem("Art/PORCO/atacando.png");
	movimentos->pegar(SENDOATACADO)->setLocalDaImagem("Art/PORCO/sendoAtacado.png");
	for (int i = 0; i < 12; i++) {
		if (i < 11) {
			movimentos->pegar(PARADO)->setOutraPosicaoNaImagem(i * 34, 0, 34, 28);
		}
		if (i < 5) {
			movimentos->pegar(ATACANDO)->setOutraPosicaoNaImagem(i * 34, 0, 34, 28);
		}
		if (i < 6) {
			movimentos->pegar(CORRENDO)->setOutraPosicaoNaImagem(i * 34, 0, 34, 28);
		}
		if (i < 2) {
			movimentos->pegar(SENDOATACADO)->setOutraPosicaoNaImagem(i * 34, 0, 34, 28);
		}
	}


}
Porco::~Porco() {

}
void Porco::movimentar() {
	if (jogadorVisto) {
		velocidade->x = -posicao->vetorUnitario(jogadorVisto->getPosicao()).x * maxVelocidade->x;
		if (posicao->distancia(jogadorVisto->getPosicao()) > ALCANCEATAQUE) {
			jogadorNaAreaDeAtaque = false;
			atacou = false;
		}
		else {
			jogadorNaAreaDeAtaque = true;
			atacou = true;
			if (delayAtaque <= ultimoAtaque) {
				ultimoAtaque = 0;
				atacou = false;
				jogadorVisto->operator--(forca);
				if (jogadorVisto->morreu()) {
					jogadorVisto = NULL;
				}
				movimentos->pegar(ATACANDO)->setImagemAtual(0);
			}
			velocidade->x = 0;
		}
	}
	else {
		velocidade->x = 0;
	}
	posicao->x += (velocidade->x * maxVelocidade->x);
	posicao->y += (velocidade->y * maxVelocidade->y);
	posicaoBarraVida->x = posicao->x + (areaOcupada->y / 4);
	posicaoBarraVida->y = posicao->y;

}
void Porco::desenhar() {
	ultimoAtaque++;
	if (vida > -1) {
		movimentos->pegar(BARRAVIDA)->desenhar(vida);
	}
	if (velocidade->x > 0) {
		for (int i = 1; i < 6; i++) {
			movimentos->pegar(i)->virarADireita();
		}
	}
	else if (velocidade->x < 0) {
		for (int i = 1; i < 6; i++) {
			movimentos->pegar(i)->virarAEsquerda();
		}
	}


	if (atacou || !movimentos->pegar(ATACANDO)->chegouAUltimaImagem()) {
		movimentos->pegar(ATACANDO)->desenhar();
	}
	else if (logVida != vida || !movimentos->pegar(SENDOATACADO)->chegouAUltimaImagem()) {
		logVida = vida;
		movimentos->pegar(SENDOATACADO)->desenhar();
	}
	else if (velocidade->x != 0) {
		movimentos->pegar(CORRENDO)->desenhar();
	}
	else {
		movimentos->pegar(PARADO)->desenhar();
	}
	
}
