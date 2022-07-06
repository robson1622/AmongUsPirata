#pragma once
#include <iostream>
#include <map>
using std::map;
using std::pair;
class GerenciadorGrafico;
template <class TIPO>
class Lista;

class Projetil;
class Jogador;
class Inimigo;
class Obstaculos;
class GerenciadorColisoes {
private:
	Lista<Jogador>* listaJogadores;
	Lista<Obstaculos>* listaObstaculos;
	Lista<Inimigo>* listaInimigos;
	Lista<Projetil>* listaProjetil;
	map<pair<int, int>, Obstaculos*> *mapaObstaculos;

public:
	GerenciadorColisoes();
	~GerenciadorColisoes();
	void checarColisoes();
	
	
	void setLista(Lista<Obstaculos>* lista);
	void setLista(Lista<Jogador>* lista);
	void setLista(Lista<Projetil>* lista);
	void setLista(Lista<Inimigo>* lista);
	void setMapaDeObstaculos(map<pair<int, int>, Obstaculos*> *mapaDeObstaculos);
};