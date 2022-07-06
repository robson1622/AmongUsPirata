#include "Espinhos.hpp"
#include "Vetor.hpp"
#include "Jogador.hpp"
#define PATH_FLECHA "Art/Espinhos/1.png"

Espinhos::Espinhos() :Obstaculos()
{
	tipoObjeto = Ente::TipoObjeto::ESPINHO;
	areaOcupada = new VetorF(0, 0);
	Recta->setSize(sf::Vector2f(40, 20));
	areaOcupada->x = 40;
	areaOcupada->y = 20;
	setForca(5);
	setimagem_local(PATH_FLECHA);
}

Espinhos::~Espinhos()
{
}

void Espinhos::colidiu(Jogador* player)
{
	player->operator--(20);
}
