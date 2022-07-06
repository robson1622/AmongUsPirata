#include "Vetor.hpp"
#include "Ente.hpp"
#include "GerenciadorGrafico.hpp"


GerenciadorGrafico* Ente::gGrafico = NULL;

int Ente::contID = 0;
const int Ente::TipoObjeto::ICEMAN = 0;
const int Ente::TipoObjeto::FIREMAN = 1;
const int Ente::TipoObjeto::PORCO = 2;
const int Ente::TipoObjeto::PORCOBOMBA = 3;
const int Ente::TipoObjeto::CHEFAO = 4;
const int Ente::TipoObjeto::BLOCOS = 5;
const int Ente::TipoObjeto::CAIXA = 6;
const int Ente::TipoObjeto::ESPINHO = 7;
const int Ente::TipoObjeto::BOLAFOGO = 8;
const int Ente::TipoObjeto::BOLAGELO = 9;
const int Ente::TipoObjeto::BOMBA = 10;
const int Ente::TipoObjeto::PEDRA = 11;

Ente::Ente():font(), text(),ID(contID++),tipoObjeto(-1) {

	Recta = new  sf::RectangleShape();
	Recta->setSize(sf::Vector2f(40.f, 40.f));
	localImagem = new sf::Texture;
	posicao = new VetorF(0, 0);
}
Ente::~Ente() {
	delete posicao;
}

void Ente::desenhar()
{
	gGrafico->desenhar(Recta);

}

void Ente::desenhartext()
{
	gGrafico->desenhar(&text);
}

void Ente::setPosicao(VetorF* vet) {
	*posicao = vet;
	if(Recta)
	Recta->setPosition(vet->sfml());
}


const VetorF* Ente::getPosicao(void) const {
	return posicao;
}


void Ente::setgGrafico(GerenciadorGrafico* gG)
{
	gGrafico = gG;
}
const int Ente::getTipoObjeto()const {
	return tipoObjeto;
}
const int Ente::getID()const {
	return ID;
}
void Ente::setID(const int identificacao) {
	ID = identificacao;
}
void Ente::setTipoObjeto(const int TIPODEOBJETO) {
	tipoObjeto = TIPODEOBJETO;
}