#include "Randomizador.hpp"
#include "Vetor.hpp"
#include "Bomba.hpp"
#include "Blocos.hpp"

#include <iostream>
using std::cout;
using std::endl;


Randomizador::Randomizador(){
	srand(time(NULL));
}
Randomizador::~Randomizador() {

}
VetorF Randomizador::posicaoAleatoria(const VetorF *posMaxima, int passo) {
	VetorF aleatorio;
	
	//o valor sorteado será entre 0 e passo
	aleatorio.x = float(valorAteatorio(0, int(posMaxima->x / passo)));
	aleatorio.y = float(valorAteatorio(0, int(posMaxima->y / passo)));
	//fazendo o produto por passo, teremos o valor maximo como possibilidade
	//assim, se passo é 40 e posMaxima.x == 1280, aleatorio.x = rand()%32
	//digamos que aleatorio.x == 5 , lovo 5*40 == 200
	// ou seja, só teremos posições bem especificas para gastarmos processamento com posições intermediarias
	aleatorio *= float(passo);
	return aleatorio;
}
VetorF Randomizador::posicaoAleatoriaSemColisao(const VetorF* areaLivreNecessaria, int passo, const VetorF* posMaxima) {
	Blocos bo;

	VetorF tamJanela(VetorF(1280, 720));
	bool posicaoValida = false;
	bo.setAreaOcupada(areaLivreNecessaria);
	VetorF aleatorio(0, 0);


	while (!posicaoValida) {
		if (posMaxima) {
			aleatorio = posicaoAleatoria(posMaxima, passo);
		}
		else {
			aleatorio = posicaoAleatoria(&tamJanela, passo);
		}

		bo.setPosicao(&aleatorio);
		posicaoValida = true;
		for (int i = 0; i < listaColidiveis.tamanhoLista(); i++) {
			if (bo == listaColidiveis.pegar(i)) {
				posicaoValida = false;
			}
		}
	}
	return aleatorio;
}


void Randomizador::adicionarEntidade(Entidade* novo) {
	if (novo) {
		listaColidiveis.adicionar(novo);
	}
}

int Randomizador::valorAteatorio(const int min, const int max) {
	srand(time(NULL));
	return (min + (rand() % (max - min)));
}
const bool Randomizador::boleanoAleatorio() {
	return (rand() % 2 == 1);
}