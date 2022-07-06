#include "Menu.hpp"
#include "Vetor.hpp"
#include "Ente.hpp"

#define PATH_BOTAO "art/Botao.png"
class Botao: public Ente
{
private:

public:
	Botao(VetorF* posicao, const char* texto);
	~Botao();
	void setPosicao(VetorF* pos);
	void setTexturaForma(sf::Texture* textura);
	void setLocalIamgem(const char* local);
	void setMensagem(const char* texto);
	void animacao();
	void setOrigem();
	void desenhar();
};
