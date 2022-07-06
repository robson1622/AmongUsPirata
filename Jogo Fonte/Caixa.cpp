#include "Caixa.hpp"
#include "Vetor.hpp"
#include "Jogador.hpp"
#include "Personagem.hpp"
#define PATH_CAIXA "Art/Caixa/1.png"

Caixa::Caixa():Obstaculos()
{
	tipoObjeto = Ente::TipoObjeto::CAIXA;
	areaOcupada = new VetorF(0, 0);
	Recta->setSize(sf::Vector2f(28, 28));
	areaOcupada->x = 28;
	areaOcupada->y = 28;
	setForca(0);
	setimagem_local(PATH_CAIXA);
}

Caixa::~Caixa()
{

}