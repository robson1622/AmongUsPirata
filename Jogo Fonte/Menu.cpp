#include "Menu.hpp"
#include "GerenciadorEventos.hpp"
#include "Botao.hpp"
#include "Vetor.hpp"


Menu::Menu(Jogo* jogo,int max,int min, estado_jogo est):Ente(),
maximo(max), minimo(min),selecionado(0),pJogo(jogo),estado_menu(est)
{
	
	ListaBotao = new Lista<Botao>();
	setgGrafico(pJogo->getGrafico());
}

Menu::~Menu()
{
}


void Menu::setFundoMenu(sf::Texture* textura)
{
	Recta->setTexture(textura);
	Recta->setSize(sf::Vector2f(1280, 720));
}

void Menu::setFundo_Menu_Local(const char* local)
{
	if (localImagem->loadFromFile(local))
		setFundoMenu(localImagem);

}

void Menu::selecaoCima()
{
	if (selecionado > minimo ) {
	 
		selecionado--;
		ListaBotao->operator[](selecionado)->animacao();
		ListaBotao->operator[](selecionado + 1)->animacao();
	}
}

void Menu::selecaoBaixo()
{
	if (selecionado < maximo) {
	selecionado++;
	ListaBotao->operator[](selecionado)->animacao();
	ListaBotao->operator[](selecionado - 1)->animacao();
	}
}


int Menu::getSelecionado() const
{
	return selecionado;
}

estado_jogo Menu::getEstadoMenu() const
{
	return estado_menu;
}


