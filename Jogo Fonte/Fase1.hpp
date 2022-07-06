#pragma once
#include "Fase.hpp"
#include <fstream>	

#define LINHAS 18
#define COLUNAS 32
#define PATH_FASE1 "Art/Background.png"

class IceMan;
class FireMan;
class Fase1 : public Fase
{
private:

	int plataforma[LINHAS][COLUNAS];
	std::ifstream arq;
	bool passou_fase;
public:
	Fase1();
	~Fase1();
	void Cenario(const int qtdplayer, IceMan* jogador1, FireMan* jogador2);
	bool getPassouFase();
	void geraInimigos();
	void recarregarCenario();
};


