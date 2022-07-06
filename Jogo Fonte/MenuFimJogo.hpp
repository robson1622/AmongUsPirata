#pragma once
#include "Menu.hpp"
class GerenciadorGrafico;
class HistoricoJogo;

class MenuFimJogo : public Menu
{
private:
	HistoricoJogo* his;
	GerenciadorGrafico* gG;
	int qtd_player;
public:
	MenuFimJogo(Jogo* jogo, estado_jogo est, HistoricoJogo* hJ);
	~MenuFimJogo();
	void executar();
	void atualizarText();
	void exibirMenu();
	void salvar();

};

