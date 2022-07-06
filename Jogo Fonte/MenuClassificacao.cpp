#include "MenuClassificacao.hpp"
#include "Vetor.hpp"
#include "Botao.hpp"
#include "GerenciadorGrafico.hpp"
#include <iostream>
using std::cout;
using std::endl;

MenuClassificacao::MenuClassificacao(Jogo* jogo, estado_jogo est):Menu(jogo, 0, 0, est)
{
	VetorF* posicao = new VetorF(1280 / 2.0f, 470);
	Botao* bot = new Botao(posicao, "RETORNAR");
	bot->animacao();
	ListaBotao->adicionar(bot);

	font.loadFromFile("Art/Montserrat-ExtraBold.ttf");
	setFundo_Menu_Local(PATH_BACK_MENUCLAS);

}

MenuClassificacao::~MenuClassificacao()
{
}

void MenuClassificacao::exibirMenu()
{

	carregar();
	Ente::desenhar();
	for (int i = 0; i < ListaBotao->tamanhoLista(); i++) {
		ListaBotao->operator[](i)->desenhar();
	}

	desenhartext();
}

void MenuClassificacao::carregar()
{
	std::ifstream arq;
	arq.open("include/Ranking.dat", std::ios::in);

	if (!arq) {
		cout << "ERRO AO CARREGAR CLASSICAÇÃO" << endl;
		exit(0);
	}

	std::string text_des;
	std::string text_des_aux;
	int pontos;

	float pos = 0.0;
	for (int i = 0; i < 2; i++)
	{
		arq >> text_des_aux >> pontos;

		if (!text_des_aux.empty()) {

			int i = 0;
			while(i<30) {
				text_des_aux += "-";
				i++;
			}

			text_des_aux += std::to_string(pontos);
		}

		text_des_aux += "\n";
		text_des += text_des_aux;
		text_des_aux = "";
	}

	text.setString(text_des);
	text.setFont(font);
	text.setCharacterSize(20);
	text.setFillColor(sf::Color::White);
	text.setPosition(sf::Vector2f(1280 / 2, 220));
	text.setOrigin(text.getLocalBounds().left + text.getLocalBounds().width /
		2.0f, text.getLocalBounds().top + text.getLocalBounds().height / 2.0f);
	text.setOutlineThickness(2);
}

void MenuClassificacao::executar()
{
	pJogo->setEstado(estado_jogo::menuPrincipal);
}
