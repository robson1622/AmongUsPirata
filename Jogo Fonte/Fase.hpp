#pragma once
#include "Blocos.hpp"
#include "Lista.hpp"
#include "SFML/Graphics.hpp"
#include "Ente.hpp"

#include <iostream>
#include <map>
using std::map;
using std::pair;
using std::make_pair;

template <class TIPO>
class Lista;
class Jogador;
class Obstaculos;
class Inimigo;
class Projetil;
class Blocos;
class Obstaculos;
class Randomizador;
class Jogo;
class GerenciadorColisoes;

class Fase : public Ente
{
protected:
	//Como estes sao atributos agregados, mas atributos utilizados por todas as fases
	//os fiz static
	Lista<Jogador>* listaJogadores;

	GerenciadorColisoes* gColisoes;

	Randomizador* randor;
	Lista<Inimigo>* listaInimigos;
	Lista<Projetil>* listaProjetil;
	map<pair<int,int>, Obstaculos*> *mapaDeBlocos;
	Lista<Obstaculos>* listaObstaculos;

	

public:
	Fase();
	~Fase();
	//chama movimentar de todas as entidade
	void movimentarEntes();
	//chama desenhar de todas as entidades
	void desenhar();
	void recarregarFase(Jogo* p);
	Lista<Jogador>* getJogadores() const;
	Lista<Inimigo>* getInimigo() const;
	Lista<Projetil>* getProjetil() const;
	Lista<Obstaculos>* getObstaculos() const;
	void adicionarJogador(Jogador* player);
	void geraObstaculos();
	void setFundo_Fase_Local(const char* local);
	void setFundo_Fase(sf::Texture* text);
	void checarColisao();
	void inicizalizarColivideis();
	void recarregarFase(Lista<Inimigo>* inimigos,Lista<Obstaculos>* obs, Lista<Projetil>* projeteis);

	virtual void recarregarCenario()=0;
};

