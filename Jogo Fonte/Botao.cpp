#include "Botao.hpp"

Botao::Botao(VetorF* posicao, const char* texto):Ente()
{
	setLocalIamgem(PATH_BOTAO);
	setPosicao(posicao);
	setMensagem(texto);
	setOrigem();
}

Botao::~Botao()
{
}

void Botao::setPosicao(VetorF* pos)
{
	Recta->setPosition(pos->sfml());
}


void Botao::setTexturaForma(sf::Texture* textura)
{
	Recta->setSize(sf::Vector2f(220, 50));
	Recta->setTexture(textura);
}

void Botao::setLocalIamgem(const char* local)
{
	localImagem->loadFromFile(local);
	setTexturaForma(localImagem);
}


void Botao::setMensagem(const char* texto)
{
	text.setString(texto);
	font.loadFromFile("Art/Montserrat-ExtraBold.ttf");
	text.setFont(font);

	text.setCharacterSize(24);
	text.setOrigin(text.getLocalBounds().left + text.getLocalBounds().width / 
		2.0f, text.getLocalBounds().top + text.getLocalBounds().height / 2.0f);

	text.setPosition(Recta->getPosition());
	text.setFillColor(sf::Color::White);
}

void Botao::animacao()
{
	if (text.getOutlineThickness() == 4) {
		text.setOutlineThickness(0);
		Recta->setSize(sf::Vector2f(220, 50));
	}
	else
	{
		Recta->setSize(sf::Vector2f(240, 55));
		text.setOutlineThickness(4);
	}

	setOrigem();
}

void Botao::setOrigem()
{
	Recta->setOrigin(Recta->getLocalBounds().left + Recta->getLocalBounds().width
		/ 2.0f, Recta->getLocalBounds().top + Recta->getLocalBounds().height / 2.0f);
}

void Botao::desenhar()
{
	Ente::desenhar();
	Ente::desenhartext();
}

