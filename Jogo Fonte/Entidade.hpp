#pragma once
#include "SFML/Graphics.hpp"
#include "Ente.hpp"

class VetorF;
class Jogador;
class Inimigo;
class Projetil;
class Blocos;
class Obstaculos;
class Entidade : public Ente{

protected:
	//guarda apenas o tipo de objeto que é
	//os atributos staticos tem o nome referente a eles
	int ID;
	VetorF* velocidade;
	VetorF *areaOcupada;

	bool podeDeletar;
public:

	Entidade();
	//Utilize Ente::PERSONAGEM para setar um personagem por exemplo
	Entidade(const int TIPOOBJETO);
	~Entidade();
	bool podeDeletarEntidade(void);
	//retorna true se houve uma colisao com a Entidade passada.
	virtual bool operator==(const Entidade *colidivel2);
	const int getID();
	//Essa funcao retorna um vetor de x = largura e y = altura do objeto
	const VetorF* getAreaOcupada() ;
	void setAreaOcupada(const VetorF* lugar);
	const VetorF* getVelocidade(void) ;
	void setVelocidade(const VetorF &valor);
	//Virtual pura, objeto que derivar tem que declarar a funcao =)
	void virtual movimentar() = 0;

};