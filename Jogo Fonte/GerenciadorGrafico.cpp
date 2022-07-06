#include "GerenciadorGrafico.hpp"
#include "Lista.hpp"
#include <iostream>
using std::cout;
using std::endl;

#define TAM_WIDTH 1280
#define TAM_HIGH 720



GerenciadorGrafico::GerenciadorGrafico(const char* nome_jogo)
{

	janela = new sf::RenderWindow(sf::VideoMode(TAM_WIDTH, TAM_HIGH), nome_jogo);
	janela->setFramerateLimit(24);
}

GerenciadorGrafico::~GerenciadorGrafico()
{
	delete janela;

}

void GerenciadorGrafico::Limpar()
{
	janela->clear(sf::Color(0,0,0,255));
}

void GerenciadorGrafico::Display()
{
	janela->display();
}

void GerenciadorGrafico::Fechar()
{
	janela->close();
}

bool GerenciadorGrafico:: Open() const
{
	return janela->isOpen();
}

bool GerenciadorGrafico::Evento(sf::Event *event)
{
	return janela->pollEvent(*event);
}

void GerenciadorGrafico::desenhar(sf::RectangleShape* imagem)
{
	janela->draw(*imagem);
}

void GerenciadorGrafico::desenhar(sf::Text* text)
{
	janela->draw(*text);
}

void GerenciadorGrafico::reniciarNome()
{
	nome = "";
}

 sf::RenderWindow* GerenciadorGrafico::getJanela() const {
	return janela;
}

 GerenciadorGrafico* GerenciadorGrafico::getGerenciador()
 {
	 return this;
 }

void GerenciadorGrafico::nomeTextEntered(sf::Event tipo)
 {
	 if (tipo.text.unicode == '\b' && nome.size() > 0)
		 nome.erase(nome.size() - 1, 1);
	 else  //retirando interação de tecla ENTER E ESPACE
		 if (tipo.text.unicode < 128 && tipo.text.unicode != '\b' && tipo.text.unicode!=13 && tipo.text.unicode != 27)
		 nome += tipo.text.unicode;

 }


std::string GerenciadorGrafico::getNome() const
 {
	 return nome;
 }







