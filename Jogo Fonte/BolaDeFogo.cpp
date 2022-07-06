#include "BolaDeFogo.hpp"
#include "MovimentoImagem.hpp"
#include "Vetor.hpp"
#include "Jogador.hpp"
#include "Inimigo.hpp"
#include "Randomizador.hpp"

BolaDeFogo::BolaDeFogo():queimacao(false) {
	tipoObjeto = Ente::TipoObjeto::BOLAFOGO;
	voando->setPosicao(posicao);
	colidindo->setPosicao(posicao);

	areaOcupada->x = 25;
	areaOcupada->y = 25;

	voando->setLocalDaImagem("Art/BolaFogo/Fireball.png");
	voando->setLarguraAltura(25, 25);
	colidindo->setLocalDaImagem("Art/BolaFogo/Colidiu.png");
	colidindo->setLarguraAltura(25, 25);

	for (int i = 0; i < 6; i++) {
		if (i < 2) {
			colidindo->setOutraPosicaoNaImagem(i * 41, 0, 41, 24);
		}
		if (i < 3) {
			voando->setOutraPosicaoNaImagem(i * 40, 0, 40, 24);
		}
	}
}
BolaDeFogo::~BolaDeFogo() {

}
void BolaDeFogo::colidiu(Jogador* player) {
	queimacao = Randomizador::boleanoAleatorio();
	delete voando;
	voando = NULL;
	velocidade->x = velocidade->y = 0;
	fim = !queimacao;
	player->operator--(forca);
}
void BolaDeFogo::colidiu(Inimigo* inim) {
	queimacao = Randomizador::boleanoAleatorio();
	delete voando;
	voando = NULL;
	velocidade->x = velocidade->y = 0;
	fim = !queimacao;
	inim->operator--(forca);
}
void BolaDeFogo::colidiu(Projetil* proj) {
	fim = true;
}