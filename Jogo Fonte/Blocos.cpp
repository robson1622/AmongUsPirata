#include "Blocos.hpp"
#include "Vetor.hpp"
#include "Jogador.hpp"
#include "Inimigo.hpp"
#include "Projetil.hpp"
#include "Obstaculos.hpp"

Blocos::Blocos():Obstaculos() {
	tipoObjeto = Ente::TipoObjeto::BLOCOS;
	Recta = new sf::RectangleShape();
	localImagem = new sf::Texture;
	//ID = Entidade::BLOCODAFASE;
	fixo = true;
	areaOcupada->x = 40;
	areaOcupada->y = 40;
}

Blocos::~Blocos() {
}

void Blocos::setLocalImagem(const char* local) {

	localImagem->loadFromFile(local);
	Recta->setTexture(localImagem);
	Recta->setSize(sf::Vector2f(40, 40));
	Recta->setPosition(posicao->sfml());
}

void Blocos::movimentar()
{
}