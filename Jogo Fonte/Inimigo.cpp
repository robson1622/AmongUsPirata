
#include "Inimigo.hpp"
#include "Projetil.hpp"
#include "Obstaculos.hpp"
#include "Jogador.hpp"
#include "Vetor.hpp"
#include "Randomizador.hpp"

Inimigo::Inimigo() :Personagem(),jogadorVisto(NULL),jogadorNaAreaDeAtaque(false) {
	Randomizador temp;
	campoDeVisao = temp.valorAteatorio(50, 250);
}
Inimigo::~Inimigo() {

}
//O jogador mais proximo, dentro do campo de visao é recebido pela a funcao.
bool Inimigo::checarSeJogadorFoiVisto(Jogador *player) {
	if(player){
		if (campoDeVisao >= posicao->distancia(player->getPosicao())) {
			jogadorVisto = player;
			return true;
		}
		else if (player == jogadorVisto) {
			jogadorVisto = NULL;
			return false;
		}
	}
	return false;
}
Projetil* Inimigo::atacar() {
	return NULL;
}
void Inimigo::golpiarJogador() {
	if (jogadorVisto && jogadorNaAreaDeAtaque) {
		colidiu(jogadorVisto);
	}
}
Jogador* Inimigo::getJogadorVisto() {
	return jogadorVisto;
}
void Inimigo::setJogadorVisto(Jogador* play) {
	if(play)
		jogadorVisto = play;
}

void Inimigo::colidiu(Jogador* player) {
	VetorF diferenca(0, 0);
	VetorF aux(0, 0);
	diferenca.x = player->getPosicao()->x - posicao->x;
	diferenca.y = player->getPosicao()->y - posicao->y;
	if (abs(diferenca.x + velocidade->x) > abs(diferenca.x)) {
		velocidade->x = (velocidade->x + player->getVelocidade()->x) / 2;
		aux.x = velocidade->x;
		aux.y = player->getVelocidade()->y;
		player->setVelocidade(aux);
	}
	if (diferenca.y + velocidade->y < diferenca.y) {
		velocidade->y = 0;
	}
}
void Inimigo::colidiu(Obstaculos* obs) {
	if (!obs->getObstaculoFixo()) {
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
void Inimigo::colidiu(Projetil* proj) {
	operator--(proj->getForca());
}