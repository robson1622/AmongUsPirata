#pragma once
#include "Entidade.hpp"

class VetorF;
class MovimentoImagem;
class Projetil :public Entidade {
protected:
	int forca;
	MovimentoImagem* voando;
	MovimentoImagem* colidindo;
	bool fim;
public:
	Projetil();
	~Projetil();
	//retorna true caso o objeto ja tenha terminado suas funcoe
	//como depois de uma bomba explodir
	bool podeApagar();
	int getForca(void)const;
	//Virtual pura, objeto que derivar tem que declarar a funcao =)
	void movimentar();
	//Virtual pura, objeto que derivar tem que declarar a funcao =)
	void desenhar();
	virtual void colidiu(Jogador* player);
	virtual void colidiu(Obstaculos* obs);
	virtual void colidiu(Inimigo* inim);
	virtual void colidiu(Projetil* proj);
};