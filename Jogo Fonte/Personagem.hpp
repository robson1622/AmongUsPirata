#pragma once
#include "Entidade.hpp"

template <class TIPO>
class Lista;


class MovimentoImagem;
class Jogador;
class Obstaculos;
class Inimigo;
class Blocos;
class Projetil;
class Personagem :public Entidade{
protected:
	Lista<MovimentoImagem>* movimentos;
	VetorF *maxVelocidade;
	VetorF* posicaoBarraVida;
	int forca;
	int vida;
	bool arremecaProjetil;
	bool atacou;
	bool tocandoChao;
	//contador do ultimo ataque
	int ultimoAtaque;
	//quando ultimo ataque chegar a ser >= delay, entao ele pode atacar
	int delayAtaque;
	//guarda a vida anterior para fazer a movimentacao do personagem sendo atacado
	int logVida;

public:
	Personagem();
	~Personagem();
	const bool getTocandoChao(void);
	void setTocandoChao(const bool tocando);
	//Tira vida do personagem
	void operator--(const int forcaOponente);
	void setVelocidadeMaxima(const VetorF *valor);
	const VetorF* getVelocidadeMaxima()const;
	//Adiciona 1 unidade de velocidade a posicao
	virtual void movimentar();
	virtual void desenhar()=0;
	//só tem o metodo atacar quem lanca projeteis
	virtual Projetil* atacar()=0;
	//retorna true se o personagem arremecou um projetil
	bool personagemAtacou();
	//retorna true se no metodo atacar ele retoorna um projetil
	bool podeArremecarProjetil();
	//retorna true se o personagem morreu
	//lembrando que sao 10 vidas comecando em 0 ate 9
	//logo para morrer eh -1 vidas
	const int getVida()const;
	void setVida(const int valor);
	bool morreu(void);

};
