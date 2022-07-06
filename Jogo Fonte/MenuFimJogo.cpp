#include "MenuFimJogo.hpp"
#include "Vetor.hpp"
#include "Botao.hpp"
#include "GerenciadorGrafico.hpp"
#include "HistoricoJogo.hpp"
#include "Fase1.hpp"
#include "Fase2.hpp"
#include "Inimigo.hpp"
#include "IceMan.hpp"
#include "FireMan.hpp"
#include "Projetil.hpp"
#define PATH_BACK_MENU "art/BackgroundMenu.jpg"


MenuFimJogo::MenuFimJogo(Jogo* jogo, estado_jogo est,HistoricoJogo* hJ): Menu(jogo,1,0,est),his(hJ)
{
	VetorF* posicao = new VetorF(1280 / 2.0f, 720 / 2.0f);
	Botao* bot = new Botao(posicao, "MENU");
	bot->animacao();
	ListaBotao->adicionar(bot);

	VetorF* posicao2 = new VetorF(1280 / 2.0f, 860 / 2.0f);
	Botao* bot1 = new Botao(posicao2, "FIM DE JOGO");
	ListaBotao->adicionar(bot1);

	selecionado = 0;
	font.loadFromFile("Art/Montserrat-ExtraBold.ttf");
	setFundo_Menu_Local(PATH_BACK_MENU);

	gG = pJogo->getGrafico();

}

MenuFimJogo::~MenuFimJogo()
{
}

void MenuFimJogo::executar()
{
	if(qtd_player==0)
		qtd_player=pJogo->getQtd_player();

	if (selecionado == 0) {
		salvar();
		if(qtd_player <=1)
		pJogo->setEstado(estado_jogo::menuPrincipal);
	}
	else
	if (selecionado == 1) {
		salvar();
		if (qtd_player <= 1)
		pJogo->fimJogo();
	}
	
}

void MenuFimJogo::atualizarText()
{
	text.setString("NOME:" + gG->getNome());
	text.setFont(font);
	text.setCharacterSize(24);
	text.setOrigin(text.getLocalBounds().left + text.getLocalBounds().width /
		2.0f, text.getLocalBounds().top + text.getLocalBounds().height / 2.0f);

	text.setPosition(sf::Vector2f(1280 / 2.0f, 420 / 2.0f));
	text.setFillColor(sf::Color::White);
}


void MenuFimJogo::exibirMenu()
{
	Ente::desenhar();
	for (int i = 0; i < ListaBotao->tamanhoLista(); i++) {
		ListaBotao->operator[](i)->desenhar();
	}
	Ente::desenhartext();
}

void MenuFimJogo::salvar()
{
	int fase = pJogo->getTipoFase();

	Lista<Obstaculos>* listObs = pJogo->getFase1()->getObstaculos();
	Lista<Inimigo>* listInim = pJogo->getFase1()->getInimigo();
	Lista<Projetil>* listProj = pJogo->getFase1()->getProjetil();

	HistoricoJogo histo;
	ObjetoPadrao aux;
	if (fase == 1) {
		histo.apagarSave();

		if (pJogo->getJogador1()) {
			IceMan* ice = pJogo->getJogador1();
			aux.fase = fase;
			aux.id = ice->getID();
			aux.idAssociacao = -1;
			aux.idTipo = ice->getTipoObjeto();
			aux.nome = gG->getNome();
			aux.pontuacao = ice->getPontuacao();
			aux.px = ice->getPosicao()->x;
			aux.py = ice->getPosicao()->y;
			aux.vida = ice->getVida();
			histo.salvar(aux);
			histo.adicionarJogadaRanking(aux);
		}
		if (pJogo->getJogador1()) {
			FireMan* ice = pJogo->getJogador2();
			aux.fase = fase;
			aux.id = ice->getID();
			aux.idAssociacao = -1;
			aux.idTipo = ice->getTipoObjeto();
			aux.nome = gG->getNome();
			aux.pontuacao = ice->getPontuacao();
			aux.px = ice->getPosicao()->x;
			aux.py = ice->getPosicao()->y;
			aux.vida = ice->getVida();
			histo.salvar(aux);
			histo.adicionarJogadaRanking(aux);
		}
		
		for(int i = 0 ; i < listInim->tamanhoLista() ; i++){
			Inimigo* po = listInim->pegar(i);
			aux.fase = fase;
			aux.id = po->getID();
			if (po->getJogadorVisto()) {
				aux.idAssociacao = po->getJogadorVisto()->getID();
			}
			else {
				aux.idAssociacao = -1;
			}
			aux.idTipo = po->getTipoObjeto();
			aux.nome = "N";
			aux.pontuacao = 124;
			aux.px = po->getPosicao()->x;
			aux.py = po->getPosicao()->y;
			aux.vida = po->getVida();
			histo.salvar(aux);
		}

		for (int i = 0; i < listObs->tamanhoLista(); i++) {
			Obstaculos* po = listObs->pegar(i);
			aux.fase = fase;
			aux.id = po->getID();
			aux.idAssociacao = -1;
			aux.idTipo = po->getTipoObjeto();
			aux.nome = "N";
			aux.pontuacao = 124;
			aux.px = po->getPosicao()->x;
			aux.py = po->getPosicao()->y;
			aux.vida = -1;
			histo.salvar(aux);
		}

		for (int i = 0; i < listProj->tamanhoLista(); i++) {
			Projetil* po = listProj->pegar(i);
			aux.fase = fase;
			aux.id = po->getID();
			aux.idAssociacao = -1;
			aux.idTipo = po->getTipoObjeto();
			aux.nome = "N";
			aux.pontuacao = 124;
			aux.px = po->getPosicao()->x;
			aux.py = po->getPosicao()->y;
			aux.vida = -1;
			histo.salvar(aux);
		}
		gG->reniciarNome();
	}
	if (fase == 2) {
		histo.apagarSave();
		if (pJogo->getJogador1()) {
			IceMan* ice = pJogo->getJogador1();
			aux.fase = fase;
			aux.id = ice->getID();
			aux.idAssociacao = -1;
			aux.idTipo = ice->getTipoObjeto();
			aux.nome = gG->getNome();
			aux.pontuacao = ice->getPontuacao();
			aux.px = ice->getPosicao()->x;
			aux.py = ice->getPosicao()->y;
			aux.vida = ice->getVida();
			histo.salvar(aux);
			histo.adicionarJogadaRanking(aux);
		}
		if (pJogo->getJogador1()) {
			FireMan* ice = pJogo->getJogador2();
			aux.fase = fase;
			aux.id = ice->getID();
			aux.idAssociacao = -1;
			aux.idTipo = ice->getTipoObjeto();
			aux.nome = gG->getNome();
			aux.pontuacao = ice->getPontuacao();
			aux.px = ice->getPosicao()->x;
			aux.py = ice->getPosicao()->y;
			aux.vida = ice->getVida();
			histo.salvar(aux);
			histo.adicionarJogadaRanking(aux);
		}

		for (int i = 0; i < listInim->tamanhoLista(); i++) {
			Inimigo* po = listInim->pegar(i);
			aux.fase = fase;
			aux.id = po->getID();
			if (po->getJogadorVisto()) {
				aux.idAssociacao = po->getJogadorVisto()->getID();
			}
			else {
				aux.idAssociacao = -1;
			}
			aux.idTipo = po->getTipoObjeto();
			aux.nome = "N";
			aux.pontuacao = 124;
			aux.px = po->getPosicao()->x;
			aux.py = po->getPosicao()->y;
			aux.vida = po->getVida();
			histo.salvar(aux);
		}

		for (int i = 0; i < listObs->tamanhoLista(); i++) {
			Obstaculos* po = listObs->pegar(i);
			aux.fase = fase;
			aux.id = po->getID();
			aux.idAssociacao = -1;
			aux.idTipo = po->getTipoObjeto();
			aux.nome = "N";
			aux.pontuacao = 124;
			aux.px = po->getPosicao()->x;
			aux.py = po->getPosicao()->y;
			aux.vida = -1;
			histo.salvar(aux);
		}

		for (int i = 0; i < listProj->tamanhoLista(); i++) {
			Projetil* po = listProj->pegar(i);
			aux.fase = fase;
			aux.id = po->getID();
			aux.idAssociacao = -1;
			aux.idTipo = po->getTipoObjeto();
			aux.nome = "N";
			aux.pontuacao = 124;
			aux.px = po->getPosicao()->x;
			aux.py = po->getPosicao()->y;
			aux.vida = -1;
			histo.salvar(aux);
		}
		gG->reniciarNome();
	}

	
}

