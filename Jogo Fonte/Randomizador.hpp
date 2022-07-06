#pragma once
#include <time.h>
#include "Lista.hpp"
#include "Entidade.hpp"

#include <iostream>
#include <map>
using std::map;
using std::pair;
using std::make_pair;


class VetorF;
class Randomizador {
private:
	Lista<Entidade> listaColidiveis;
public:
	Randomizador();
	~Randomizador();
	VetorF posicaoAleatoria(const VetorF* posMaxima, int passo);
	static int valorAteatorio(const int min, const int max);
	VetorF posicaoAleatoriaSemColisao(const VetorF *areaLivreNecessaria, int passo, const VetorF* posMaxima=NULL);
	void adicionarEntidade(Entidade *novo);
	static const bool boleanoAleatorio();
};