#include "PorcoBomba.hpp"
#include "MovimentoImagem.hpp"
#include "Vetor.hpp"
#include "Jogador.hpp"
#include "Bomba.hpp"
//Valor do alcance da bomba em pixels
#define ALCANCEBOMBA 150
#define BARRAVIDA 0
#define PARADO 1
#define CORRENDO 2
#define JOGANDOBOMBA 3
#define SENDOATACADO 4

PorcoBomba::PorcoBomba():Inimigo(),pegouBomba(false) {
	tipoObjeto = Ente::TipoObjeto::PORCOBOMBA;
	for (int i = 0; i < 5; i++) {
		MovimentoImagem* novo = new MovimentoImagem();
		movimentos->adicionar(novo);
	}
	areaOcupada->x = 24;
	areaOcupada->y = 24;
	posicao->x = 240;
	posicao->y = 600;
	forca = 2;
	maxVelocidade->x = 2;
	maxVelocidade->y = 1;

	campoDeVisao = 300;

	delayAtaque = 22;
	arremecaProjetil = true;

	movimentos->pegar(PARADO)->setPosicao(posicao);
	movimentos->pegar(PARADO)->setLarguraAltura(34, 28);
	movimentos->pegar(CORRENDO)->setPosicao(posicao);
	movimentos->pegar(CORRENDO)->setLarguraAltura(34, 28);
	movimentos->pegar(JOGANDOBOMBA)->setPosicao(posicao);
	movimentos->pegar(JOGANDOBOMBA)->setLarguraAltura(34,28);
	movimentos->pegar(SENDOATACADO)->setPosicao(posicao);
	movimentos->pegar(SENDOATACADO)->setLarguraAltura(34,28);

	movimentos->pegar(PARADO)->setLocalDaImagem("Art/PORCO_BOMBA/Idle (26x26).png");
	movimentos->pegar(CORRENDO)->setLocalDaImagem("Art/PORCO_BOMBA/Run (26x26).png");
	movimentos->pegar(JOGANDOBOMBA)->setLocalDaImagem("Art/PORCO_BOMBA/Throwing Boom (26x26).png");
	movimentos->pegar(SENDOATACADO)->setLocalDaImagem("Art/PORCO_BOMBA/Hit (34x28).png");
	for (int i = 0; i < 12; i++) {
		if (i < 10) {
			movimentos->pegar(PARADO)->setOutraPosicaoNaImagem(i * 26, 0, 26, 26);
		}
		if (i < 5) {
			movimentos->pegar(JOGANDOBOMBA)->setOutraPosicaoNaImagem(i * 26, 0, 26, 26);
		}
		if (i < 6) {
			movimentos->pegar(CORRENDO)->setOutraPosicaoNaImagem(i * 26, 0, 26, 26);
		}
		if (i < 2) {
			movimentos->pegar(SENDOATACADO)->setOutraPosicaoNaImagem(i * 34, 0, 34, 28);
		}
	}


}
PorcoBomba::~PorcoBomba() {

}
void PorcoBomba::movimentar() {
	if (jogadorVisto) {
		velocidade->x = -posicao->vetorUnitario(jogadorVisto->getPosicao()).x * maxVelocidade->x;
		if (posicao->distancia(jogadorVisto->getPosicao()) > ALCANCEBOMBA) {
			jogadorNaAreaDeAtaque = false;
			atacou = false;
		}
		else {
			jogadorNaAreaDeAtaque = true;
			if (delayAtaque <= ultimoAtaque) {
				ultimoAtaque = 0;
				atacou = true;
				if (jogadorVisto->morreu()) {
					jogadorVisto = NULL;
				}
				movimentos->pegar(JOGANDOBOMBA)->setImagemAtual(0);
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
void PorcoBomba::desenhar() {
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


	if (atacou || !movimentos->pegar(JOGANDOBOMBA)->chegouAUltimaImagem()) {
		movimentos->pegar(JOGANDOBOMBA)->desenhar();
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
Projetil* PorcoBomba::atacar() {
	if (atacou) {
		Bomba* rojao = new Bomba();
		VetorF posicaoProjetil(0, posicao->y - (areaOcupada->y / 2));
		float angulo = float(asin(abs(posicao->x - jogadorVisto->getPosicao()->x) * 0.5 / 900)/2);
		VetorF velocidadeInicial(30*cos(angulo),30*sin(angulo) );
		if (movimentos->pegar(1)->imagemInvertida()) {
			rojao->setVelocidade(VetorF(-velocidadeInicial.x, -velocidadeInicial.y));
			posicaoProjetil.x = -1 + posicao->x - (areaOcupada->x + rojao->getAreaOcupada()->x) / 2;
		}
		else {
			posicaoProjetil.x = 1 + posicao->x + (areaOcupada->x + rojao->getAreaOcupada()->x) / 2;
			rojao->setVelocidade(VetorF(velocidadeInicial.x, -velocidadeInicial.y));
		}

		rojao->setPosicao(&posicaoProjetil);
		atacou = false;
		return static_cast<Projetil*>(rojao);
	}
	else {
		return NULL;
	}
}