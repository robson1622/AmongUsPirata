#include "Obstaculos.hpp"
#include "Inimigo.hpp"
#include "Jogador.hpp"
#include "Projetil.hpp"
#include "Vetor.hpp"

#include <iostream>
using std::cout;
using std::endl;

Obstaculos::Obstaculos():Entidade(),forca(0),fixo(false)
{
	velocidade->x = 0;
	velocidade->y = 1;
}

Obstaculos::~Obstaculos()
{
}
void Obstaculos::colidiuPersonagem(Personagem* p) {
	if (forca > 0) {
		p->operator--(forca);
	}
	else if (fixo) {
		VetorF aux(0, 0);
		//guarda o vetor que aponta do bloco para o personagem
		VetorF direcaoPersonagem(posicao->x - p->getPosicao()->x, posicao->y - p->getPosicao()->y);
		//essa variavel aguada a distancia maxima para que a colisao tenha ocorrido
		VetorF distanciaColisao((areaOcupada->x + p->getAreaOcupada()->x)/2, (areaOcupada->y/2) + (p->getAreaOcupada()->y/2));

		if (abs(direcaoPersonagem.y) < distanciaColisao.y ) {
			if (direcaoPersonagem.y > 0) {
				aux.x = p->getPosicao()->x;
				aux.y = posicao->y - distanciaColisao.y;
				p->setPosicao(&aux);
				if (p->getVelocidade()->y >= 0) {
					aux.y = 0;
				}
				else {
					aux.y = p->getVelocidade()->y;
				}
				aux.x = p->getVelocidade()->x;
				p->setVelocidade(&aux);
				p->setTocandoChao(true);
			}
			else if (direcaoPersonagem.y < 0) {
				if (p->getVelocidade()->y <= 0) {
					aux.y = -p->getVelocidade()->y;
				}
				else {
					aux.y = p->getVelocidade()->y;
				}
				aux.x = p->getVelocidade()->x;
				p->setVelocidade(&aux);
			}
		}
		if (abs(direcaoPersonagem.x) < distanciaColisao.x && operator==(p)){
			if (direcaoPersonagem.x < 0) {
				aux.y = p->getPosicao()->y;
				aux.x = posicao->x + distanciaColisao.x + 1;
				p->setPosicao(&aux);
				

			}
			else if (direcaoPersonagem.x > 0) {
				aux.y = p->getPosicao()->y;
				aux.x = posicao->x - distanciaColisao.x - 1;
				p->setPosicao(&aux);
			}
		}
	}
}
bool Obstaculos::getObstaculoFixo() {
	return fixo;
}
bool Obstaculos::getCausaDano() {
	return (forca > 0);
}
void Obstaculos::setForca(int f)
{
	forca = f;
}

int Obstaculos::getForca()
{
	return forca;
}

void Obstaculos::setimagem_local(const char* local)
{
	localImagem->loadFromFile(local);
	setImagem(localImagem);
}

void Obstaculos::setImagem(sf::Texture* text)
{
	Recta->setTexture(text);
}

void Obstaculos::movimentar(){
	if (!fixo) {
		*posicao += velocidade;
		Recta->setPosition(posicao->sfml());
	}
}
void Obstaculos::colidiu(Jogador* player){
	colidiuPersonagem(static_cast<Personagem*>(player));
}
void Obstaculos::colidiu(Obstaculos* obs){
	if (!fixo) {
		velocidade->y = 0;
		fixo = true;
	}

}
void Obstaculos::colidiu(Inimigo* inim){
	colidiuPersonagem(static_cast<Personagem*>(inim));
}