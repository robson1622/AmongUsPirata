#include "Chefao.hpp"
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

Chefao::Chefao() :Inimigo() {
	tipoObjeto = Ente::TipoObjeto::CHEFAO;

	for (int i = 0; i < 5; i++) {
		MovimentoImagem* novo = new MovimentoImagem();
		novo->setLarguraAltura(78, 52);
		movimentos->adicionar(novo);
	}

	tocandoChao = false;
	forca = 3;
	campoDeVisao = 400;
	delayAtaque = 18;
	maxVelocidade->x = 1;
	maxVelocidade->y = 1;
	areaOcupada->x = 30;
	areaOcupada->y = 38;
	posicao->x = 300;
	posicao->y = 80;
	posicaoBarraVida->x = 300 - 20;
	posicaoBarraVida->x = 80 - 15;

	movimentos->pegar(PARADO)->setPosicao(posicao);
	movimentos->pegar(PARADO)->setLarguraAltura(82, 60);
	movimentos->pegar(CORRENDO)->setPosicao(posicao);
	movimentos->pegar(CORRENDO)->setLarguraAltura(82, 60);
	movimentos->pegar(ATACANDO)->setPosicao(posicao);
	movimentos->pegar(ATACANDO)->setLarguraAltura(82, 60);
	movimentos->pegar(SENDOATACADO)->setPosicao(posicao);
	movimentos->pegar(SENDOATACADO)->setLarguraAltura(82, 60);

	movimentos->pegar(PARADO)->setLocalDaImagem("Art/CHEFAO/parado.png");
	movimentos->pegar(CORRENDO)->setLocalDaImagem("Art/CHEFAO/correndo.png");
	movimentos->pegar(ATACANDO)->setLocalDaImagem("Art/CHEFAO/atacando.png");
	movimentos->pegar(SENDOATACADO)->setLocalDaImagem("Art/CHEFAO/sendoAtacado.png");
	for (int i = 0; i < 12; i++) {
		if (i < 11) {
			movimentos->pegar(PARADO)->setOutraPosicaoNaImagem(i * 78, 0, 78, 58);
		}
		if (i < 5) {
			movimentos->pegar(ATACANDO)->setOutraPosicaoNaImagem(i * 78, 0, 78, 58);
		}
		if (i < 6) {
			movimentos->pegar(CORRENDO)->setOutraPosicaoNaImagem(i * 78, 0, 78, 58);
		}
		if (i < 2) {
			movimentos->pegar(SENDOATACADO)->setOutraPosicaoNaImagem(i * 78, 0, 78, 58);
		}
	}


}
Chefao::~Chefao() {

}
void Chefao::movimentar() {

	if(jogadorVisto){
		velocidade->x = -posicao->vetorUnitario(jogadorVisto->getPosicao()).x * maxVelocidade->x;
		if (posicao->distancia(jogadorVisto->getPosicao()) > ALCANCEATAQUE){
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
void Chefao::desenhar() {
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