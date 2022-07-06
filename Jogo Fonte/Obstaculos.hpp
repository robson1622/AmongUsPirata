#pragma once
#include "SFML/Graphics.hpp"
#include "Entidade.hpp"

class Personagem;
class Obstaculos : public Entidade
{

protected:
	int forca;
	bool fixo;

	void colidiuPersonagem(Personagem* p);
public:
	Obstaculos();
	~Obstaculos();
	void setForca(int f);
	int getForca();
	bool getObstaculoFixo();
	bool getCausaDano();
	void setimagem_local(const char* local);
	void setImagem(sf::Texture* text);
	virtual void movimentar();
	virtual void colidiu(Jogador* player);
	virtual void colidiu(Obstaculos* obs);
	virtual void colidiu(Inimigo* inim);

};
