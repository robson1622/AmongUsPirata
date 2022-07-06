#include "Fase.hpp"
#include "Vetor.hpp"
#include "Lista.hpp"
#include "Randomizador.hpp"
#include "Projetil.hpp"
#include "Inimigo.hpp"
#include "FireMan.hpp"
#include "IceMan.hpp"
#include "Blocos.hpp"
#include "Pedra.hpp"
#include "Caixa.hpp"
#include "Espinhos.hpp"
#include "GerenciadorColisoes.hpp"
#include <iostream>
#include "HistoricoJogo.hpp"
#include "Jogo.hpp"
#include "Porco.hpp"
#include "PorcoBomba.hpp"
#include "Chefao.hpp"
#include "Bomba.hpp"
#include "BolaDeGelo.hpp"
#include "BolaDeFogo.hpp"
#include "Caixa.hpp"
#include "Espinhos.hpp"
#include "Pedra.hpp"
// A medida que a construtora for precisando, criamos funcoes para gerar os objetos
Fase::Fase():Ente() {

	gColisoes = new GerenciadorColisoes();
	listaInimigos = new Lista<Inimigo>;
	listaProjetil = new Lista<Projetil>();
	listaJogadores = new Lista<Jogador>();
	randor = new Randomizador();
	mapaDeBlocos= new map<pair<int, int>, Obstaculos*>();
	listaObstaculos = new Lista<Obstaculos>();

}

Fase::~Fase() {

	for (std::map<pair<int, int>, Obstaculos*>::iterator itr = mapaDeBlocos->begin(); itr != mapaDeBlocos->end(); itr++) {
		Obstaculos* aux = itr->second;
		delete aux;

	}

	for (int i = 0; i < listaJogadores->tamanhoLista(); i++) {
		listaJogadores->remover(i);
	}
	for (int i = 0; i < listaObstaculos->tamanhoLista(); i++) {
		listaObstaculos->remover(i);
	}

	for (int i = 0; i < listaInimigos->tamanhoLista(); i++) {
		listaInimigos->remover(i);
	}
	for (int i = 0; i < listaProjetil->tamanhoLista(); i++) {
		listaProjetil->remover(i);
	}

	delete (gColisoes);
}
void Fase::recarregarFase(Jogo *p) {
	HistoricoJogo hist;
	ObjetoPadrao *aux;
	Lista<ObjetoPadrao>* lista = hist.carregar();
	VetorF posicao(0, 0);
	int vida = 0;
	int fase = 0;
	int idTipo = -1;
	int id = -1;
	int idAssociacao = -1;
	unsigned int pontuacao = 0;
	float px = 0;
	float py = 0;

	for (int i = 0; i < lista->tamanhoLista(); i++) {
		aux = lista->pegar(i);
		posicao.x = aux->px;
		posicao.y = aux->py;
		vida = aux->vida;
		idTipo = aux->idTipo;
		id = aux->id;
		idAssociacao = aux->idAssociacao;
		pontuacao = aux->pontuacao;

		if (idTipo == Ente::TipoObjeto::ICEMAN) {
			IceMan* novo = new IceMan();
			novo->setPosicao(&posicao);
			novo->setVida(vida);
			novo->setPontuacao(pontuacao);
			novo->setID(id);
			novo->setTipoObjeto(idTipo);
			p->setIce(novo);
			listaJogadores->adicionar(static_cast<Jogador*>(novo));
		}
		else if (idTipo == Ente::TipoObjeto::FIREMAN) {
			FireMan* novo = new FireMan();
			novo->setPosicao(&posicao);
			novo->setVida(vida);
			novo->setPontuacao(pontuacao);
			novo->setID(id);
			novo->setTipoObjeto(idTipo);
			p->setFire(novo);
			listaJogadores->adicionar(static_cast<Jogador*>(novo));
		}
		else if (idTipo == Ente::TipoObjeto::PORCO) {
			Porco* novo = new Porco();
			novo->setPosicao(&posicao);
			novo->setVida(vida);
			novo->setID(id);
			novo->setTipoObjeto(idTipo);
			listaInimigos->adicionar(static_cast<Inimigo*>(novo));
		}
		else if (idTipo == Ente::TipoObjeto::PORCOBOMBA) {
			PorcoBomba* novo = new PorcoBomba();
			novo->setPosicao(&posicao);
			novo->setVida(vida);
			novo->setID(id);
			novo->setTipoObjeto(idTipo);
			listaInimigos->adicionar(static_cast<Inimigo*>(novo));
		}
		else if (idTipo == Ente::TipoObjeto::CHEFAO) {
			Chefao* novo = new Chefao();
			novo->setPosicao(&posicao);
			novo->setVida(vida);
			novo->setID(id);
			novo->setTipoObjeto(idTipo);
			listaInimigos->adicionar(static_cast<Inimigo*>(novo));
		}
		else if (idTipo == Ente::TipoObjeto::CAIXA) {
			Caixa* novo = new Caixa();
			novo->setPosicao(&posicao);
			novo->setID(id);
			novo->setTipoObjeto(idTipo);
			listaObstaculos->adicionar(static_cast<Obstaculos*>(novo));
		}
		else if (idTipo == Ente::TipoObjeto::ESPINHO) {
			Espinhos* novo = new Espinhos();
			novo->setPosicao(&posicao);
			novo->setID(id);
			novo->setTipoObjeto(idTipo);
			listaObstaculos->adicionar(static_cast<Obstaculos*>(novo));
		}
		else if (idTipo == Ente::TipoObjeto::BOLAFOGO) {
			BolaDeFogo* novo = new BolaDeFogo();
			novo->setPosicao(&posicao);
			novo->setID(id);
			novo->setTipoObjeto(idTipo);
			listaProjetil->adicionar(static_cast<Projetil*>(novo));
		}
		else if (idTipo == Ente::TipoObjeto::BOLAGELO) {
			BolaDeGelo* novo = new BolaDeGelo();
			novo->setPosicao(&posicao);
			novo->setID(id);
			novo->setTipoObjeto(idTipo);
			listaProjetil->adicionar(static_cast<Projetil*>(novo));
		}
		else if (idTipo == Ente::TipoObjeto::BOMBA) {
			Bomba* novo = new Bomba();
			novo->setPosicao(&posicao);
			novo->setID(id);
			novo->setTipoObjeto(idTipo);
			listaProjetil->adicionar(static_cast<Projetil*>(novo));
		}
		else if (idTipo == Ente::TipoObjeto::PEDRA) {
			Pedra* novo = new Pedra();
			novo->setPosicao(&posicao);
			novo->setID(id);
			novo->setTipoObjeto(idTipo);
			listaObstaculos->adicionar(static_cast<Obstaculos*>(novo));
		}
	}
	inicizalizarColivideis();
	recarregarCenario();
}
void Fase::desenhar() {

	Ente::desenhar();

	
	for (std::map<pair<int, int>, Obstaculos*>::iterator itr = mapaDeBlocos->begin(); itr != mapaDeBlocos->end(); itr++) {
		Obstaculos* aux = itr->second;
		if (aux) {
			aux->desenhar();
		}
	
	}
	for (int i = 0; i < listaObstaculos->tamanhoLista(); i++) {
		listaObstaculos->operator[](i)->desenhar();
	}

	for (int i = 0; i < listaJogadores->tamanhoLista(); i++) {
		listaJogadores->operator[](i)->desenhar();
	}
	
	for (int i = 0; i < listaInimigos->tamanhoLista(); i++) {
		listaInimigos->operator[](i)->desenhar();
	}
	for (int i = 0; i < listaProjetil->tamanhoLista(); i++) {
		listaProjetil->operator[](i)->desenhar();
	}
}


void Fase::checarColisao()
{
	gColisoes->checarColisoes();
}

void Fase::inicizalizarColivideis()
{
	gColisoes->setLista(listaInimigos);
	gColisoes->setLista(listaProjetil);
	gColisoes->setMapaDeObstaculos(mapaDeBlocos);
	gColisoes->setLista(listaObstaculos);
	gColisoes->setLista(listaJogadores);
}

void Fase::recarregarFase(Lista<Inimigo>* inimigos, Lista<Obstaculos>* obs,
	Lista<Projetil>* projeteis)
{
	listaInimigos = inimigos;
	listaProjetil = projeteis;
	listaObstaculos = obs;
	recarregarCenario();
	inicizalizarColivideis();
}


Lista<Jogador>* Fase::getJogadores() const
{
	return listaJogadores;
}

Lista<Inimigo>* Fase::getInimigo() const
{
	return listaInimigos;
}

Lista<Projetil>* Fase::getProjetil() const
{
	return listaProjetil;
}

Lista<Obstaculos>* Fase::getObstaculos() const
{
	return listaObstaculos;
}

void Fase::adicionarJogador(Jogador* player) {
	if (listaJogadores) {
		listaJogadores->adicionar(player);
	}
	else {
		listaJogadores = new Lista<Jogador>();
		listaJogadores->adicionar(player);
	}
}

void Fase::geraObstaculos()
{
	//Valor aleatorio para quantidade do obstaculo na fase
	
	int qtd = randor->valorAteatorio(3, 6);

		for (int i = 0; i < qtd; i++) {
			VetorF posicao1(0,0);
			Espinhos* obs = new Espinhos();

			posicao1 = randor->posicaoAleatoriaSemColisao(obs->getAreaOcupada(), 40);
			obs->setPosicao(&posicao1);
			printf("%f %f \n", posicao1.x, posicao1.y);
			listaObstaculos->adicionar(static_cast<Obstaculos*>(obs));
			randor->adicionarEntidade(obs);
		}

	qtd = randor->valorAteatorio(3,6);

		for (int i = 0; i < qtd; i++) {
			VetorF posicao(0, 0);
			Pedra* pe = new Pedra();
			posicao = randor->posicaoAleatoriaSemColisao(pe->getAreaOcupada(), 40);
			pe->setPosicao(&posicao);
			printf("%f %f \n", posicao.x, posicao.y);
			listaObstaculos->adicionar(static_cast<Obstaculos*>(pe));;
			randor->adicionarEntidade(pe);
		}

	qtd = randor->valorAteatorio(3, 6);

		for (int i = 0; i < qtd; i++) {
			VetorF posicao2(0, 0);
			Caixa* ca = new Caixa();
			posicao2 = randor->posicaoAleatoriaSemColisao(ca->getAreaOcupada(), 40);
			ca->setPosicao(&posicao2);
			printf("%f %f \n", posicao2.x, posicao2.y);
			listaObstaculos->adicionar(static_cast<Obstaculos*>(ca));;

			randor->adicionarEntidade(ca);
		}

		
}


////////// movimentacoes aqui
void Fase::movimentarEntes() {
	for (int i = 0; i < listaJogadores->tamanhoLista(); i++) {
		listaJogadores->pegar(i)->movimentar();
	}
	for (map<pair<int, int>, Obstaculos*>::iterator itr = mapaDeBlocos->begin(); itr != mapaDeBlocos->end(); itr++) {
		Obstaculos* aux= itr->second;
		if (aux) {
			aux->movimentar();
		}
	}
	for (int i = 0; i < listaObstaculos->tamanhoLista(); i++) {
		listaObstaculos->pegar(i)->movimentar();
	}
	for (int i = 0; i < listaInimigos->tamanhoLista(); i++) {
		listaInimigos->pegar(i)->movimentar();
	}
	for (int i = 0; i < listaProjetil->tamanhoLista(); i++) {
		listaProjetil->pegar(i)->movimentar();
	}
}


void Fase::setFundo_Fase_Local(const char* local) {
	if (localImagem->loadFromFile(local))
		setFundo_Fase(localImagem);	
}

void Fase::setFundo_Fase(sf::Texture* textu) {
	Recta->setTexture(textu);
	Recta->setSize(sf::Vector2f(1280, 720));
}
