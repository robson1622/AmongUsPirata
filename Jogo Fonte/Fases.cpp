#include "Fases.hpp"
#include "Vetor.hpp"


Fase::Fase() {

	listaBlocos = new Lista<Bloco>;
	listaObstaculos = new Lista<Obstaculos>;
}



Fase::~Fase() {
}


void Fase::setFundo_Fase_Local(const char* local) {
	if (this->fundo_fase_local.loadFromFile(local))
		setFundo_Fase(&fundo_fase_local);
}

void Fase::setFundo_Fase(sf::Texture* text) {
	this->fundo_fase.setTexture(*text);;

}

void Fase::GerarObstaculos()
{
	Bloco* aux = listaBlocos->operator[](listaBlocos->tamanhoLista()-1);
	Randomizador* rad=NULL;
	Pedra* ob = new Pedra();
	VetorF posicao = new VetorF(0, 0);
	posicao = (rad->posicaoAleatoria(aux->getPosicao(), 40));
	ob->setPosicao(&posicao);
	listaObstaculos->adicionar(static_cast<Obstaculos*>(ob));
}

void Fase::desenhar(sf::RenderWindow* janela) {

	if (janela)
	{

		janela->draw(this->fundo_fase);

		for (int i = 0; i < listaBlocos->tamanhoLista(); i++) {
			Bloco* aux = listaBlocos->operator[](i);
			aux->desenhar(janela);
		}

		for (int i = 0; i < listaObstaculos->tamanhoLista(); i++) {
			Obstaculos* ob = listaObstaculos->operator[](i);
			ob->desenhar(janela);
		}
	}
}

Lista<Obstaculos>* Fase::getObstaculos()
{
	return listaObstaculos;
}

Lista<Bloco>* Fase::getBlocos()
{
	return listaBlocos;
}
