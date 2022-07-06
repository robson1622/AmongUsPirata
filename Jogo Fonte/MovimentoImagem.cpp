#include "MovimentoImagem.hpp"
#include "Vetor.hpp"
#include <iostream>
using std::cout;
using std::endl;


MovimentoImagem::MovimentoImagem():Ente(), posicao(NULL), posicaoNaImagem(), nImagens(0), imagemAtual(0), localCarregadoCorretamente(false) {
	localImagem->loadFromFile("Art/defalt.png");
}

MovimentoImagem::~MovimentoImagem() {
	for (int i = 0; i < posicaoNaImagem.tamanhoLista(); i++) {
		sf::IntRect* aux = posicaoNaImagem[0];
		posicaoNaImagem.remover(0);
		delete aux;
	}
	posicaoNaImagem.limpar();
}

bool MovimentoImagem::imagemInvertida(){
	return (Recta->getScale().x < 0);
}
void MovimentoImagem::virarADireita(void) {
	Recta->setScale(1, 1);
}
void MovimentoImagem::virarAEsquerda(void) {
	Recta->setScale(-1, 1);
}
void MovimentoImagem::setImagemAtual(const  int  i) {
	imagemAtual = i;
}
void MovimentoImagem::atualizar(const int posicaoNova) {
	//Se estiver na ultima imagem, volta a primeira
	if (imagemAtual >= nImagens) {
		imagemAtual = 0;
	}
	
	if (imagemInvertida()) {
		Recta->setPosition(posicao->x + (posicaoNaImagem[imagemAtual]->width), posicao->y);
	}
	else {
		Recta->setPosition(posicao->sfml());
	}
	Recta->setTextureRect(*posicaoNaImagem[imagemAtual]);
}

void MovimentoImagem::voltarPrimeiraImagem() {
	imagemAtual = 0;
}
void MovimentoImagem::setPosicao(VetorF* vet) {
	posicao = vet;
	Recta->setPosition(posicao->sfml());
}
const sf::RectangleShape* MovimentoImagem::pegarImagemAtual() {
	return Recta;
}
VetorF* MovimentoImagem::getPosicao()const {
	return posicao;
}
bool MovimentoImagem::setLocalDaImagem(const char* local) {
	
	if (localImagem->loadFromFile(local)) {
		Recta->setTexture(localImagem);
		localCarregadoCorretamente = true;
		return true;
	}
	else {
		cout << "Erro ao carregar imagem : " << local << " lugar errado =(." << endl;
		localImagem->loadFromFile("Art/defalt.png");
		Recta->setTexture(localImagem);
		nImagens = 1;
		localCarregadoCorretamente = false;
		return false;
	}
}
void MovimentoImagem::setOutraPosicaoNaImagem(VetorF& posicao, VetorF& tamanho) {
	if(localCarregadoCorretamente){
		sf::IntRect* novo = new sf::IntRect(int(posicao.x), int(posicao.y), int(tamanho.x),int( tamanho.y));
		nImagens++;
		posicaoNaImagem.adicionar(novo);
	}
}
void MovimentoImagem::setOutraPosicaoNaImagem(const int posX, const int posY, const int tamX, const int tamY) {
	if(localCarregadoCorretamente){
		sf::IntRect* novo = new sf::IntRect(posX,posY,tamX,tamY);
		nImagens++;
		posicaoNaImagem.adicionar(novo);
	}
}
void MovimentoImagem::desenhar(const int imagemEspecifica) {
	if(nImagens > 0 ){
		
		if(imagemEspecifica == -1){
			atualizar(++imagemAtual);
		}
		else {
			imagemAtual = imagemEspecifica;
			atualizar(imagemAtual);
		}
		Ente::desenhar();
	}
}
bool MovimentoImagem::chegouAUltimaImagem(void) {
	return (imagemAtual == (nImagens - 1));
}
void MovimentoImagem::setLarguraAltura(const int largura, const int altura) {
	Recta->setSize(sf::Vector2f(float(largura),float(altura)));
}