#pragma once
#include <iostream>
#include <fstream>
#include <map>
using std::map;
using std::pair;
using std::string;
using std::make_pair;


class ObjetoPadrao {
public:
	string nome;
	int fase;
	int vida;
	int idTipo;
	int id;
	int idAssociacao;
	int pontuacao;
	float px;
	float py;
};

template <class TIPO>
class Lista;

class VetorF;
class HistoricoJogo
{
public:
	

	HistoricoJogo();
	~HistoricoJogo();

	//Salvar
	Lista<ObjetoPadrao>* carregar();
	void salvar(ObjetoPadrao obg);
	void adicionarJogadaRanking(ObjetoPadrao obg);
	void apagarSave();
	const static bool exiteJogoSalvo();
	const static int faseSalva();
	//Informacoes importantes
	//bool existeJogadaSalva();
	//const int getFase()const;
};


