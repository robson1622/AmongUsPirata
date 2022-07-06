#include "Projetil.hpp"
#include "MovimentoImagem.hpp"
#include "Vetor.hpp"
#include "Jogador.hpp"
#include "Inimigo.hpp"
#include "Obstaculos.hpp"

#include <iostream>
using std::cout;
using std::endl;

Projetil::Projetil() :Entidade(),forca(1),fim(false) {
	voando = new MovimentoImagem();
	colidindo = new MovimentoImagem();
}

Projetil::~Projetil() {
	delete colidindo;
}

//Se colidiu, entao eu posso apagar a animacao de voando
bool Projetil::podeApagar() {
	return fim;
}
int Projetil::getForca(void)const {
	return forca;
}
void Projetil::movimentar() {
	*posicao += velocidade;
}
void Projetil::desenhar() {
	if (voando) {
		if (velocidade->x > 0) {
			voando->virarADireita();
			colidindo->virarADireita();
		}
		else {
			voando->virarAEsquerda();
			colidindo->virarADireita();
		}
		voando->desenhar();
	}
	else {
		colidindo->desenhar();
		if (colidindo->chegouAUltimaImagem()) {
			fim = true;
		}
	}
}
void Projetil::colidiu(Jogador* player) {
	delete voando;
	voando = NULL;
	velocidade->x = velocidade->y = 0;
	forca = 0;
	player->operator--(forca);
}
void Projetil::colidiu(Obstaculos* obs) {
	delete voando;
	velocidade->x = velocidade->y = 0;
	voando = NULL;
}
void Projetil::colidiu(Inimigo* inim) {
	delete voando;
	voando = NULL;
	velocidade->x = velocidade->y = 0;
	forca = 0;
	inim->operator--(forca);
}
void Projetil::colidiu(Projetil* proj) {
	delete voando;
	velocidade->x = velocidade->y = 0;
	voando = NULL;
}