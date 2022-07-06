#pragma once
#include "SFML/Graphics.hpp"

/*
ID é da forma 1001, onde o primeiro dígito é o tipo de objeto e os tres ultimos são a ordem de criacao do objeto.
*/
class VetorF;
class GerenciadorGrafico;

class Ente {
private:
	int ID;
	static int contID;

protected:
	int tipoObjeto;

	VetorF* posicao;
	sf::RectangleShape* Recta;
	sf::Texture* localImagem;

	sf::Text text;
	sf::Font font;

	static  GerenciadorGrafico* gGrafico;
public:
	const struct TipoObjeto {
	public:
		const static int ICEMAN;
		const static int FIREMAN;
		const static int PORCO;
		const static int PORCOBOMBA;
		const static int CHEFAO;
		const static int BLOCOS;
		const static int CAIXA;
		const static int ESPINHO;
		const static int BOLAFOGO;
		const static int BOLAGELO;
		const static int BOMBA;
		const static int PEDRA;
	};
	


	Ente();
	~Ente();
	//Lembrese de alocar a posicao da imagem e o sprite
	virtual void desenhar();
	void desenhartext();
	//Setar a posicao do que é desenhavel,se preferir, objeto Ente
	void setPosicao(VetorF* vet);
	//void inicializarTextura(const char* local);
	const VetorF* getPosicao(void) const;
	static void setgGrafico(GerenciadorGrafico* gG);
	const int getTipoObjeto()const;
	const int getID()const;
	void setID(const int identificacao);
	//Utilizar a struct constante para saber os valores referentes a cada tipo
	void setTipoObjeto(const int TIPODEOBJETO);
};