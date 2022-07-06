#include "Pedra.hpp"
#include "Vetor.hpp"
#define PATH_PEDRA "Art/Pedra/1.png"

Pedra::Pedra():Obstaculos()
{
	tipoObjeto = Ente::TipoObjeto::PEDRA;
	areaOcupada = new VetorF(0,0);
	Recta->setSize(sf::Vector2f(28, 28));
	areaOcupada->x = 28;
	areaOcupada->y = 28;
	setForca(5);
	setimagem_local(PATH_PEDRA);
}

Pedra::~Pedra()
{
}

void Pedra::colidiu(Jogador* player) {

}