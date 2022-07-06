#pragma once
#include "SFML/Graphics.hpp"
#include "Lista.hpp"
#include "Ente.hpp"
/*
Sprite é onde ficará a imagem a ser desenhada, Texture salva o local onde essa imagem está
Lista parametrizada com IntRect é uma lista das posições de cada frame a ser desenhado na
imagem salva em imagem
*/

class VetorF;
//Essa classe serve somente para trocar as imagens a serem exibidas de forma que pareça que o
//objeto esta se movendo como por exemplo um personagem correndo
class MovimentoImagem:public Ente {
private:
	//aponta para a posicao em outro objeto
	VetorF *posicao;

	bool localCarregadoCorretamente;
	//Essa variavel guarda uma lista de objetos que dão a posicao e o tamanho onde a imagem citada a cima deve ser
	//cortada, para se desenhar na tela apenas o freme pretendido.
	Lista<sf::IntRect> posicaoNaImagem;

	// numero total de frames em uma imagem
	unsigned int nImagens;
	//Contador para desenhar uma apos a outra.
	unsigned int imagemAtual;

	//funcao que atualiza posicao da imagem na tela, chamada automaticamente com desenhar.
	void atualizar(const int posicaoNova);
public:
	MovimentoImagem();
	~MovimentoImagem();
	bool imagemInvertida();
	void virarADireita(void);
	void virarAEsquerda(void);
	void setImagemAtual(const  int  i);
	void voltarPrimeiraImagem();
	void setPosicao(VetorF* vet);
	const sf::RectangleShape* pegarImagemAtual();
	VetorF* getPosicao() const;
	void setLarguraAltura(const int largura,const int altura);
	bool setLocalDaImagem(const char* local);
	void setOutraPosicaoNaImagem(VetorF& posicao, VetorF& tamanho);
	void setOutraPosicaoNaImagem(const int posX, const int posY, const int tamX, const int tamY);
	//Setar size pois se colocar um padao barra de vida buga
	//O parametro com defalt serve para escolher a imagem que deve ser desenhada
	//para o caso da barra de vida isso é escencial
	void desenhar(const int imagemEspecifica = -1);
	bool chegouAUltimaImagem(void);
};

