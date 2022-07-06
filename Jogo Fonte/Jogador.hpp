#pragma once
#include "Personagem.hpp"


class Jogador : public Personagem{
protected:
	unsigned int contaMortos;
public:
	Jogador();
	~Jogador();
	

	//Incrementa o nummero de mortes do jogador
	void operator+=(const bool matou);
	unsigned int getPontuacao()const;
	void setPontuacao(const unsigned int valor);
	void movimentar();
	virtual void controlar(const VetorF& direcao);
	virtual void desenhar();
	//cada jogador tem seu projetil, por isso aqui é virtual
	virtual Projetil* atacar()=0;
	//os jogadores terao o mesmo modo operante de colisao
	//ntap eles seram declarados em jogador
	void colidiu(Jogador* player);
	void colidiu(Obstaculos* obs);
	void colidiu(Inimigo* inim);
	void colidiu(Projetil* proj);
};