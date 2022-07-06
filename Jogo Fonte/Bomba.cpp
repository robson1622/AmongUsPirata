#include "Bomba.hpp"
#include "MovimentoImagem.hpp"
#include "Randomizador.hpp"
#include "Vetor.hpp"
#include "Jogador.hpp"
#include "Inimigo.hpp"
#include "Vetor.hpp"

Bomba::Bomba(): Projetil() {
	tipoObjeto = Ente::TipoObjeto::BOMBA;
	voando->setPosicao(posicao);
	colidindo->setPosicao(posicao);
	impacto = new VetorF();
	impacto->x = float(Randomizador::valorAteatorio(1, 2));
	impacto->y = -float(Randomizador::valorAteatorio(1, 4));

	areaOcupada->x = 25;
	areaOcupada->y = 25;

	voando->setLocalDaImagem("Art/BOMBA/Bomb On (52x56).png");
	voando->setLarguraAltura(52, 56);

	colidindo->setLocalDaImagem("Art/BOMBA/Boooooom (52x56).png");
	colidindo->setLarguraAltura(52, 56);

	for (int i = 0; i < 6; i++) {
		if (i < 6) {
			colidindo->setOutraPosicaoNaImagem(i * 52, 0, 52, 56);
		}
		if (i < 4) {
			voando->setOutraPosicaoNaImagem(i * 52, 0, 52, 56);
		}
	}
}
Bomba::~Bomba() {
	delete impacto;
}
void Bomba::colidiu(Jogador* player) {
	delete voando;
	voando = NULL;
	velocidade->x = velocidade->y = 0;
	//forca = 0;
	player->operator--(forca);
	VetorF aux(0, 0);
	aux.x = (impacto->x * velocidade->x / abs(velocidade->x)) + player->getVelocidade()->x;
	aux.y = (impacto->y * velocidade->y / abs(velocidade->y)) + player->getVelocidade()->y;
	player->setVelocidade(&aux);
}
void Bomba::colidiu(Inimigo* inim) {
	delete voando;
	voando = NULL;
	velocidade->x = velocidade->y = 0;
	//forca = 0;
	inim->operator--(forca);
	VetorF aux(0, 0);
	aux.x = impacto->x + inim->getVelocidade()->x;
	aux.y = impacto->y + inim->getVelocidade()->y;
	inim->setVelocidade(&aux);
}