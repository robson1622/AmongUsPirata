#pragma once



#include "Personagem.hpp"

class VetorF;
class Jogador;
class Inimigo : public Personagem {
protected:
	Jogador* jogadorVisto;
	int campoDeVisao;
	bool jogadorNaAreaDeAtaque;
public:
	Inimigo();
	~Inimigo();
	//Se o jogador esta no campo de visao, ele é guardado no ponteiro jogadorVisto e se retorna true
	//mas se nao esta, e eh igual a o que estava anteriormente, entao ele eh removido
	bool checarSeJogadorFoiVisto(Jogador* player);
	virtual void movimentar()=0;
	virtual void desenhar()=0;
	virtual Projetil* atacar();
	virtual void golpiarJogador();
	//Cada objeto que for herdeiro dessa classe deve decidir o que acontece quando colidir com outro objeto
	Jogador* getJogadorVisto();
	void setJogadorVisto(Jogador* play);
	void colidiu(Jogador* player);
	void colidiu(Obstaculos* obs);
	void colidiu(Projetil* proj);
};
