#pragma once
#include "Fase.hpp"
#include <fstream>	

#define LINHAS 18
#define COLUNAS 32
#define PATH_FASE2 "Art/BackgroundFase2.png"

class IceMan;
class FireMan;
class Fase2 : public Fase
{
private:
	int plataforma[LINHAS][COLUNAS];
	std::ifstream arq;
public:
	Fase2();
	~Fase2();
	void Cenario(const int qtdplayer, IceMan* jogador1, FireMan* jogador2);
	void geraInimigos();
	void recarregarCenario();
};

