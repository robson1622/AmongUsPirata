#include "BolaDeGelo.hpp"
#include "MovimentoImagem.hpp"
#include "Vetor.hpp"
#include "Jogador.hpp"
#include "Inimigo.hpp"

BolaDeGelo::BolaDeGelo() {
	tipoObjeto = Ente::TipoObjeto::BOLAGELO;
	voando->setPosicao(posicao);
	colidindo->setPosicao(posicao);

	areaOcupada->x = 18;
	areaOcupada->y = 18;

	voando->setLocalDaImagem("Art/BolaGelo/BolaGelo.png");
	voando->setLarguraAltura(18, 18);

	colidindo->setLocalDaImagem("Art/BolaGelo/Colidiu.png");
	colidindo->setLarguraAltura(18, 18);

	for (int i = 0; i < 6; i++) {
		if (i < 2) {
			colidindo->setOutraPosicaoNaImagem(i * 41, 0, 41, 24);
		}
		if (i < 3) {
			voando->setOutraPosicaoNaImagem(i * 40, 0, 40, 24);
		}
	}
}
BolaDeGelo::~BolaDeGelo() {

}
void BolaDeGelo::colidiu(Jogador* player) {
	VetorF aux(0, 0);
	delete voando;
	voando = NULL;
	velocidade->x = velocidade->y = 0;
	forca = 0;
	player->operator--(forca);
	aux.x = player->getVelocidadeMaxima()->x;
	aux.y = player->getVelocidadeMaxima()->y;
	aux.x *= 0.5;
	aux.y *= 0.5;
	player->setVelocidadeMaxima(&aux);
}
void BolaDeGelo::colidiu(Inimigo* inim) {
	VetorF aux(0, 0);
	delete voando;
	voando = NULL;
	velocidade->x = velocidade->y = 0;
	forca = 0;
	inim->operator--(forca);
	aux.x = inim->getVelocidadeMaxima()->x;
	aux.y = inim->getVelocidadeMaxima()->y;
	aux.x *= 0.5;
	aux.y *= 0.5;
	inim->setVelocidadeMaxima(&aux);
}