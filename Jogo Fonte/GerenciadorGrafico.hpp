#include "SFML/Graphics.hpp"

template <class TIPO>
class Lista;
class GerenciadorGrafico
{
private:
	sf::RenderWindow* janela;
	sf::Font fonte;
	std::string nome;

public:
	GerenciadorGrafico(const char* nome_jogo);
	~GerenciadorGrafico();
	void Limpar();
	void Display();
	void Fechar();
	bool Open() const;
	bool Evento(sf::Event *event);
	void desenhar(sf::RectangleShape* imagem);
	void desenhar(sf::Text* text);
	void reniciarNome();

    sf::RenderWindow* getJanela() const;
	GerenciadorGrafico* getGerenciador();
	void nomeTextEntered(sf::Event tipo);
	std::string getNome() const;
};

