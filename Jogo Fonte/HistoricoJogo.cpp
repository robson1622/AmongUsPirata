#include "HistoricoJogo.hpp"
using std::cout;
using std::endl;


#include "Lista.hpp"
#include "Vetor.hpp"
#include <map>

#include "Porco.hpp"
#include "PorcoBomba.hpp"
#include "Chefao.hpp"

#include "Blocos.hpp"
#include "Caixa.hpp"
#include "Espinhos.hpp"

#include "Bomba.hpp"
#include "BolaDeFogo.hpp"
#include "BolaDeGelo.hpp"


HistoricoJogo::HistoricoJogo()
{
}

HistoricoJogo::~HistoricoJogo()
{
}

Lista<ObjetoPadrao>* HistoricoJogo::carregar() {
	std::ifstream arq;
	arq.open("include/save.dat", std::ios::in);

	if (!arq) {
		cout << "ERRO AO CARREGAR, include/save.dat NAO ENCONTRADO." << endl;
	}
	else {
		//Recuperando relacoes criadas dinamicamente durante o jogo
		Lista<ObjetoPadrao> *lista = new Lista<ObjetoPadrao>();
		while (!arq.eof()) {
			ObjetoPadrao* novo = new ObjetoPadrao();
			arq >> novo->fase >> novo->nome >> novo->vida >> novo->idTipo >> novo->id >> novo->idAssociacao >> novo->pontuacao >> novo->px >> novo->py;
			lista->adicionar(novo);
		}
		arq.close();
		return lista;
	}
	return NULL;
}
void HistoricoJogo::salvar(ObjetoPadrao obg) {
	Lista<ObjetoPadrao> lista;
	std::ofstream arq("include/save.dat", std::ios_base::app);
	if (!arq) {
		cout << "ERRO AO CARREGAR, include/save.dat NAO ENCONTRADO." << endl;
	}
	else {
		arq << obg.fase << ' '
			<< obg.nome << ' '
			<< obg.vida << ' '
			<< obg.idTipo << ' '
			<< obg.id << ' '
			<< obg.idAssociacao << ' '
			<< obg.pontuacao << ' '
			<< obg.px << ' '
			<< obg.py << endl;
		arq.close();

	}
	
	
}

void HistoricoJogo::adicionarJogadaRanking(ObjetoPadrao obg) {
	std::ofstream arq;
	arq.open("include/Ranking.dat", std::ios_base::app);
	arq << obg.nome << ' '
		<< obg.pontuacao <<endl;
	arq.close();
}
void HistoricoJogo::apagarSave() {
	std::ofstream arq;
	arq.open("include/save.dat");
	arq.clear();
	arq.close();
}
const int HistoricoJogo::faseSalva() {
	std::ifstream arq;
	arq.open("include/save.dat", std::ios::in);
	if (!arq.eof()) {
		int i = 0;
		arq >> i;
		arq.close();
		return i;
	}
	return -1;
}

const bool HistoricoJogo::exiteJogoSalvo() {
	std::ifstream arq;
	arq.open("include/save.dat",std::ios::in);
	if (!arq.eof()) {
		arq.close();
		return false;
	}
	arq.close();
	return true;
}
/*
void HistoricoJogo::adicionarJogadaRanking(ObjetoPadrao obg) {

}
void HistoricoJogo::carregarInimigos() {
	

	
	
}
void HistoricoJogo::carregarJogadores() {
	std::ifstream arq;
	arq.open("include/Jogadores.dat", std::ios::in);

	if (!arq) {
		cout << "ERRO AO SALVAR JOGADORES" << endl;
	}
	else if(!arq.eof()) {

		int idJogador = -1;
		int idTipo = -1;
		int player = 0;
		unsigned int pontuacao = 0;
		VetorF posicao(0,0);
		int vida = 0; 
		arq >> player >> idJogador >> idTipo >> posicao.x >> posicao.y >> pontuacao >> vida;

		if (player == 1 && icePlayer) {
			icePlayer->setVida(vida);
			icePlayer->setPosicao(&posicao);
			icePlayer->setPontuacao(pontuacao);
			icePlayer->setID(idJogador);
			icePlayer->setTipoObjeto(idTipo);
		}
		else if(firePlayer) {
			firePlayer->setVida(vida);
			firePlayer->setPosicao(&posicao);
			firePlayer->setPontuacao(pontuacao);
			firePlayer->setID(idJogador);
			firePlayer->setTipoObjeto(idTipo);
		}
		if (!arq.eof() && firePlayer) {
			arq >> player >> idJogador >> idTipo >> posicao.x >> posicao.y >> pontuacao >> vida;
			if (player == 2) {
				firePlayer->setVida(vida);
				firePlayer->setPosicao(&posicao);
				firePlayer->setPontuacao(pontuacao);
				firePlayer->setID(idJogador);
				firePlayer->setTipoObjeto(idTipo);
			}
		}

	}
	arq.close();
	
	
}


void HistoricoJogo::carregarObstaculos() {
		std::ifstream arq;
		arq.open("include/Obstaculos.dat", std::ios::in);

		if (!arq) {
			cout << "ERRO AO CARREGAR OBSTACULOS, include/Obstaculos.dat NAO FOI ENCONTRADO" << endl;
		}
		else {
			listObstaculos = new Lista<Obstaculos>();
			while(!arq.eof()) {
				VetorF posicao(0, 0);
				int idObstaculo = -1;
				int idTipo = -1;

				//arq << aux->getID() << aux->getTipoObjeto() << aux->getPosicao()->x << aux->getPosicao()->y << endl;
				arq >> idObstaculo >> idTipo >> posicao.x >> posicao.y;
				 if (idTipo == Ente::TipoObjeto::CAIXA) {
					Caixa* caixa = new Caixa();
					caixa->setID(idObstaculo);
					caixa->setTipoObjeto(idTipo);
					caixa->setPosicao(&posicao);
					listObstaculos->adicionar(caixa);
				}
				else if (idTipo == Ente::TipoObjeto::ESPINHO) {
					Espinhos* spike = new Espinhos();
					spike->setID(idObstaculo);
					spike->setTipoObjeto(idTipo);
					spike->setPosicao(&posicao);
					listObstaculos->adicionar(spike);
				}
			}
			arq.close();
		}
		
}
void HistoricoJogo::carregarProjeteis() {
	
	std::ifstream arq;
	arq.open("include/Projeteis.dat", std::ios::in);

	if (!arq) {
		cout << "ERRO AO CARREGAR INIMIGOS, include/Projeteis.dat NAO ENCONTRADO." << endl;
	}
	else {
		listProjeteis = new Lista<Projetil>();
		//Recuperando relacoes criadas dinamicamente durante o jogo
		while (!arq.eof()) {
			int idProjetil = -1;
			int idTipo = 0;
			VetorF posicao(0, 0);

			arq >> idProjetil >> idTipo >> posicao.x >> posicao.y;
			if (idTipo == Ente::TipoObjeto::BOMBA) {
				Bomba* bomba = new Bomba();
				bomba->setPosicao(&posicao);
				bomba->setID(idProjetil);
				bomba->setTipoObjeto(idTipo);
				listProjeteis->adicionar(static_cast<Projetil*>(bomba));
			}
			else if (idTipo == Ente::TipoObjeto::BOLAFOGO) {
				BolaDeFogo* fogo = new BolaDeFogo();
				fogo->setPosicao(&posicao);
				fogo->setID(idProjetil);
				fogo->setTipoObjeto(idTipo);
				listProjeteis->adicionar(static_cast<Projetil*>(fogo));
			}
			else if (idTipo == Ente::TipoObjeto::BOLAGELO) {
				BolaDeGelo* gelo = new BolaDeGelo();
				gelo->setPosicao(&posicao);
				gelo->setID(idProjetil);
				gelo->setTipoObjeto(idTipo);
				listProjeteis->adicionar(static_cast<Projetil*>(gelo));
			}
		}
		arq.close();
	}
	
}

void HistoricoJogo::carregar()
{
	std::ifstream arq;
	arq.open("include/Jogo.dat");

	if (!arq) {
		cout << "ERRO AO CARREGAR include/Jogo.dat, NAO FOI POSSIVEL SALVAR" << endl;
	}
	else {
		int p = 0;
		arq >> faseAtual >> p;
		cout << "Fase : " << faseAtual << " Player : " << p << endl;

		if (p == 1) {
			arq >> player1;
		}
		else {
			arq >> player2;
		}
		if (!arq.eof()) {
			arq >> p;
			if (p == 2) {
				arq >> player2;
			}
			else {
				arq >> player1;
			}
		}
		
		arq.close();
		carregarJogadores();
		carregarInimigos();
		carregarObstaculos();
		carregarProjeteis();
	}

	
	

}
/*Aqui eu salvo tanto atributos que mudam durante o jogo quanto a associacao com o o jogado, quando a mesma existe
void HistoricoJogo::salvarInimigos() {
	std::ofstream arq;
	arq.open("include/Inimigos.dat", std::ios::out);

	if (listInimigos && listInimigos->tamanhoLista() > 0) {

		if (!arq) {
			cout << "ERRO AO SALVAR INIMIGOS, include/Inimigos.dat NAO FOI ENCONTRADO" << endl;
		}
		else {
			for (int i = 0; i < listInimigos->tamanhoLista(); i++) {
				Inimigo* aux = listInimigos->pegar(i);
				Jogador* playerVisto = aux->getJogadorVisto();
				if (playerVisto) {
					arq << playerVisto->getID();
				}
				else {
					arq << -1;
				}
				arq << ' '
					<< aux->getID() << ' '
					<< aux->getTipoObjeto() << ' '
					<< aux->getPosicao()->x << ' '
					<< aux->getPosicao()->y << endl;
			}
		}

	}
	else {
		cout << "LISTA DE INIMIGOS VAZIA" << endl;
		arq << ' ';
	}
	arq.close();
}


bool HistoricoJogo::salvarJogadores() {

	std::ofstream arq;
	arq.open("include/Jogadores.dat", std::ios::out);

	if (!arq) {
		cout << "ERRO AO SALVAR JOGADORES, include/Jogadores.dat NAO FOI ENCONTRADO" << endl;
	}
	else {
		if (player1.size() > 0 && icePlayer) {
			arq << 1 << ' '
				<< icePlayer->getID() << ' '
				<< icePlayer->getTipoObjeto() << ' '
				<< icePlayer->getPosicao()->x << ' '
				<< icePlayer->getPosicao()->y << ' '
				<< icePlayer->getPontuacao() << ' '
				<< icePlayer->getVida() << endl;
		}
		if (player2.size() > 0 && firePlayer) {
			arq << 2 << ' '
				<< firePlayer->getID() << ' '
				<< firePlayer->getTipoObjeto() << ' '
				<< firePlayer->getPosicao()->x << ' '
				<< firePlayer->getPosicao()->y << ' '
				<< firePlayer->getPontuacao() << ' '
				<< firePlayer->getVida() << endl;
		}
	}
	arq.close();
	return true;

}


void HistoricoJogo::salvarObstaculos() {
	if (listObstaculos && listObstaculos->tamanhoLista() > 0) {
		std::ofstream arq;
		arq.open("include/Obstaculos.dat", std::ios::out);

		if (!arq) {
			cout << "ERRO AO SALVAR OBSTACULOS, include/Obstaculos.dat NAO FOI ENCONTRADO" << endl;
		}
		else {
			for (int i = 0; i < listObstaculos->tamanhoLista(); i++) {
				Obstaculos* aux = listObstaculos->pegar(i);
				if (aux && aux->getTipoObjeto()) {
					arq << aux->getID() << ' '
						<< aux->getTipoObjeto() << ' '
						<< aux->getPosicao()->x << ' '
						<< aux->getPosicao()->y << endl;
				}
			}
		}
		arq.close();
	}
	else {
		cout << "LISTA DE OBSTACULOS VAZIA" << endl;
	}
}


void HistoricoJogo::salvarProjeteis() {
	if (listProjeteis && listProjeteis->tamanhoLista() > 0) {
		std::ofstream arq;
		arq.open("include/Projeteis.dat", std::ios::out);

		if (!arq) {
			cout << "ERRO AO SALVAR PROJETEIS, include/Projeteis.dat NAO FOI ENCONTRADO" << endl;
		}
		else {
			for (int i = 0; i < listProjeteis->tamanhoLista(); i++) {
				Projetil* aux = listProjeteis->pegar(i);
				if (aux) {
					arq << aux->getID() << ' '
						<< aux->getTipoObjeto() << ' '
						<< aux->getPosicao()->x << ' '
						<< aux->getPosicao()->y << endl;
				}
			}
		}
		arq.close();
	}
	else {
		cout << "LISTA DE PROJETEIS VAZIA" << endl;
	}
}


void HistoricoJogo::salvar()
{
	std::ofstream arq;
	arq.open("include/Jogo.dat", std::ios::out);

	if (!arq) {
		cout << "ERRO AO CARREGAR include/Jogo.dat, NAO FOI POSSIVEL SALVAR" << endl;
	}
	else {
		//se nao conseguir salvar os jogadores, entao nao salva nada
		if (salvarJogadores()) {
			arq << faseAtual;
			if (player1.size() > 0) {
				arq << ' ' << 1 << ' ' << player1.c_str() << endl;
			}
			if (player2.size() > 0) {
				arq << ' ' << 2 << ' ' << player2.c_str() << endl;
			}
			arq.close();
			salvarInimigos();
			salvarObstaculos();
			salvarProjeteis();
		}
	}

	arq.close();
}

void HistoricoJogo::setListaParaSalvar(Lista<Inimigo>* listaInimigos) {
	listInimigos = listaInimigos;
}

void HistoricoJogo::setListaParaSalvar(Lista<Obstaculos>* listaObstaculos) {
	listObstaculos = listaObstaculos;
}

void HistoricoJogo::setListaParaSalvar(Lista<Projetil>* listaProjeteis) {
	listProjeteis = listaProjeteis;
}

void HistoricoJogo::setIceMan(IceMan* Player) {
	icePlayer = Player;
}
void HistoricoJogo::setFireMan(FireMan* Player) {
	firePlayer = Player;
}
void HistoricoJogo::setPlayerNome(std::string nome) {
	if (player1.size() == 0) {
		player1 = nome;
	}
	else {
		player2 = nome;
	}

}
void HistoricoJogo::adicionarJogadaRanking() {
	std::ifstream entrada;
	entrada.open("include/Ranking.dat", std::ios::in);
	if (entrada) {

		std::string aux;
		int pontos = 0;
		//map aceita mult chaves, ideal para gardar quando existir pontuacoes iguais
		std::multimap<int, std::string> sequenciaDeRankings;
		std::multimap<int, std::string>::iterator itr;

		if (!entrada.eof()) {
			std::ofstream saida;
			saida.open("include/Ranking.dat", std::ios::out);
			if (player1.size() > 0 && icePlayer) {
				saida << player1.c_str() << ' '
					<< icePlayer->getPontuacao() << endl;
			}
			if (player2.size() > 0 && firePlayer) {
				saida << player2.c_str() << ' '
					<< firePlayer->getPontuacao() << endl;
			}
		}
		else {
			while (!entrada.eof()) {
				entrada >> aux >> pontos;
				sequenciaDeRankings.insert(std::pair<int, string>(pontos, aux));
			}
			if (player1.size() > 0 && icePlayer) {
				sequenciaDeRankings.insert(std::pair<int, string>(icePlayer->getPontuacao(), player1));
			}
			if (player2.size() > 0 && firePlayer) {
				sequenciaDeRankings.insert(std::pair<int, string>(firePlayer->getPontuacao(), player2));
			}
			entrada.close();
			std::ofstream saida;
			saida.open("include/Ranking.dat", std::ios::out);
			for (itr = sequenciaDeRankings.begin(); itr != sequenciaDeRankings.end(); itr++) {
				saida << itr->second.c_str() << ' ' << itr->first << endl;
			}
			saida.close();
		}
	}
	else {
		cout << "Arquivo de ranking nao encontrado" << endl;
	}

}
//Recuperar
Lista<Inimigo>* HistoricoJogo::getInimigos()const {
	return listInimigos;
}
Lista<Obstaculos>* HistoricoJogo::getObstaculos()const {
	return listObstaculos;
}
Lista<Projetil>* HistoricoJogo::getProjeteis()const {
	return listProjeteis;
}
IceMan* HistoricoJogo::getIcePlayer()const {
	return icePlayer;
}
FireMan* HistoricoJogo::getFirePLayer()const {
	return firePlayer;
}
const int HistoricoJogo::getFase()const {
	return faseAtual;
}

bool HistoricoJogo::existeJogadaSalva() {
	std::ifstream arq;
	arq.open("include/Jogo.dat");

	if (arq.eof()) {
		arq.close();
		return false;
	}
	else {
		arq.close();
		return true;
	}
}*/