#include "Personagem.hpp"
#include "MovimentoImagem.hpp"
#include "Vetor.hpp"
#include "Lista.hpp"
#include "Obstaculos.hpp"
#include <iostream>
using std::cout;
using std::endl;

Personagem::Personagem():Entidade(),delayAtaque(18),ultimoAtaque(0),logVida(9),atacou(false),
	forca(1), vida(9),arremecaProjetil(false),tocandoChao(false)
	{
	maxVelocidade = new VetorF(6, 3);
	Recta->setSize(sf::Vector2f(0, 0));
	posicao = new	VetorF(80, 80);
	posicaoBarraVida = new VetorF(80 - 16, 80 - 16);

	areaOcupada = new VetorF(24, 28);

	////////////// inicializacao da barrra de vida, comun a todos os personagens
	movimentos = new Lista<MovimentoImagem>();
	MovimentoImagem* barraDeVida = new MovimentoImagem();
	barraDeVida->setLarguraAltura(64, 12);
	movimentos->adicionar(barraDeVida);
	barraDeVida->setLocalDaImagem("Art/vida.png");
	barraDeVida->setPosicao(posicaoBarraVida);

	for (int i = 0; i < 10; i++) {
		movimentos->pegar(0)->setOutraPosicaoNaImagem(i * 64, 0, 64, 12);
	}
	///////////////////////////////////////////////////////////////////////////////
	
	
}
Personagem::~Personagem() {
	delete velocidade;
	delete maxVelocidade;

	delete posicao;
	delete posicaoBarraVida;
	delete areaOcupada;
	while (movimentos->tamanhoLista()) {
		MovimentoImagem* aux = movimentos->pegar(0);
		movimentos->remover(0);
		delete aux;
	}
	delete movimentos;
}
void Personagem::setTocandoChao(const bool tocando) {
	tocandoChao = tocando;
}
const bool Personagem::getTocandoChao(void) {
	return tocandoChao;
}
bool Personagem::personagemAtacou() {
	return atacou;
}
bool Personagem::podeArremecarProjetil() {
	return arremecaProjetil;
}
//Tira vida do personagem de acordo com a forca do oponente
void Personagem::operator--(int forcaOponente) {
	if (vida > -1)
		vida -= forcaOponente;
}
void Personagem::setVelocidadeMaxima(const VetorF *valor) {
	maxVelocidade->x = valor->x;
	maxVelocidade->y = valor->y;
}
const VetorF* Personagem::getVelocidadeMaxima()const {
	return maxVelocidade;
}
void Personagem::movimentar() {
	posicao->x += (velocidade->x * maxVelocidade->x);
	posicao->y += (velocidade->y * maxVelocidade->y);
	posicaoBarraVida->x = posicao->x - (areaOcupada->x / 2);
	posicaoBarraVida->y = posicao->y - (areaOcupada->y / 2);
}
const int Personagem::getVida()const {
	return vida;
}
void Personagem::setVida(const int valor) {
	vida = valor;
}
bool Personagem::morreu(void) {
	return (-1 >= vida);
}