#include "Jogador.hpp"
#include "Obstaculos.hpp"
#include "Inimigo.hpp"
#include "Blocos.hpp"
#include "Projetil.hpp"
#include "Vetor.hpp"
#include "MovimentoImagem.hpp"


#define BARRAVIDA 0
#define PARADO 1
#define CORRENDO 2
#define PULANDO 3
#define ATACANDO 4
#define SENDOATACADO 5


Jogador::Jogador():Personagem(),contaMortos(0) {
	tocandoChao = false;
}
Jogador::~Jogador(){
}
unsigned int Jogador::getPontuacao()const {
	return contaMortos;
}
void Jogador::setPontuacao(const unsigned int valor) {
	contaMortos = valor;
}
void Jogador::controlar(const VetorF& direcao) {
	if (direcao.y == 1 && tocandoChao) {
		velocidade->y = -maxVelocidade->y;
		tocandoChao = false;
	}
	else if (direcao.y == -1 && ultimoAtaque >= delayAtaque) {
		atacou = true;
		ultimoAtaque = 0;
	}
	if (tocandoChao) {
		velocidade->x = direcao.x * maxVelocidade->x;
	}
	
}
void Jogador::desenhar() {
	//
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
	else if (abs(velocidade->y) > 1 && !tocandoChao) {
		movimentos->pegar(PULANDO)->desenhar();
	}
	else if (velocidade->x != 0) {
		movimentos->pegar(CORRENDO)->desenhar();
	}
	else if (logVida != vida) {
		logVida = vida;
		movimentos->pegar(SENDOATACADO)->desenhar();
	}
	else {
		movimentos->pegar(PARADO)->desenhar();
	}

	
}
void Jogador::operator+=(const bool matou) {
	if (matou) {
		contaMortos++;
	}
}

void Jogador::movimentar() {
	*posicao += velocidade;
	*posicaoBarraVida = posicao;
	*posicaoBarraVida -= 16;
	
}


void Jogador::colidiu(Jogador* player) {
	VetorF diferenca(0, 0);
	VetorF aux(0, 0);
	diferenca.x = player->getPosicao()->x - posicao->x;
	diferenca.y = player->getPosicao()->y - posicao->y;
	if (abs(diferenca.x + velocidade->x) > abs(diferenca.x)) {
		velocidade->x = (velocidade->x + player->velocidade->x)/ 2;
		aux.x = velocidade->x;
		aux.y = player->velocidade->y;
		player->setVelocidade(aux);
	}
	if(diferenca.y + velocidade->y < diferenca.y){
		velocidade->y = 0;
	}
}
void Jogador::colidiu(Obstaculos* obs) {

	if(!obs->getObstaculoFixo()){
		VetorF diferenca(0, 0);
		VetorF aux(0, 0);
		diferenca.x = obs->getPosicao()->x - posicao->x;
		diferenca.y = posicao->y - obs->getPosicao()->y;
		if (abs(diferenca.x + velocidade->x) > abs(diferenca.x)) {
			velocidade->x = (velocidade->x + obs->getVelocidade()->x) / 2;
			aux.x = velocidade->x;
			aux.y = obs->getVelocidade()->y;
			obs->setVelocidade(aux);
		}
	}
}
void Jogador::colidiu(Inimigo* inim) {
	VetorF diferenca(0, 0);
	VetorF aux(0, 0);
	diferenca.x = inim->getPosicao()->x - posicao->x;
	diferenca.y = inim->getPosicao()->y - posicao->y;
	if (abs(diferenca.x + velocidade->x) > abs(diferenca.x)) {
		velocidade->x = (velocidade->x + inim->getVelocidade()->x) / 2;
		aux.x = velocidade->x;
		aux.y = inim->getVelocidade()->y;
		inim->setVelocidade(aux);
	}
	if (diferenca.y + velocidade->y < diferenca.y) {
		velocidade->y = 0;
	}
}
void Jogador::colidiu(Projetil* proj) {
	operator--(proj->getForca());
}