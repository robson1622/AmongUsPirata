#pragma once
#include "Lista.hpp"
#include "SFML/Graphics.hpp"
#include "Ente.hpp"
#include "Jogo.hpp"

class Botao;

class Menu : public Ente
{
protected:
	Lista<Botao>* ListaBotao;
	//CaixaTexto caixaT
	Jogo* pJogo;
	int maximo, minimo,selecionado;
	estado_jogo estado_menu;
public:
	
	Menu(Jogo* jogo, int max, int min, estado_jogo est);
	~Menu();
	virtual void exibirMenu()=0;
	virtual void executar() = 0;
	void setFundoMenu(sf::Texture* textura);
	void setFundo_Menu_Local(const char* local);
	void selecaoCima();
	void selecaoBaixo();
	int  getSelecionado() const;
	estado_jogo getEstadoMenu() const;
};

