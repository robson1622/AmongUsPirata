# pragma once
class GerenciadorEventos;
class Fase1;
class Fase2;
class GerenciadorGrafico;
class MenuNovaFase;
class MenuPrincipal;
class MenuPause;
class VetorF;
class MenuFimJogo;
class MenuClassificacao;
class Jogador;
class HistoricoJogo; 
class IceMan;
class FireMan;

enum class estado_jogo {
	menuPrincipal,
	menuNovoJogo,
	jogando,
	menuPause,
	menuFim,
	menuClassicacao
};


class Jogo
{

private:

	GerenciadorEventos* gE;
	GerenciadorGrafico* gGraficos;

	MenuPrincipal* MenuPri;
	MenuNovaFase* MenuFase;
	MenuPause* MenuP;
	MenuFimJogo* MenuF;
	MenuClassificacao* MenuClas;
	estado_jogo estado;

	Fase1* faseP;
	Fase2* faseS;

	IceMan* jogador1;
	FireMan* jogador2;

	HistoricoJogo* historico;

	int tipo_fase;
	int qtd_player;
	bool existe_carregar;

public:
	Jogo();
	~Jogo();
	void inicializar();
	void loop();
	void criarFase();
	void movimentar(const int player, const VetorF &direcao);
	void setEstado(estado_jogo es);
	void fimJogo();
	void setTipoFase(int idFase);
	int getTipoFase() const ;
	int getQtd_player() const;
	void setqtd_player(int qtd);
	void getPlayerVivo();
	void trocarFase();
	void setIce(IceMan* ice);
	void setFire(FireMan* fire);
	IceMan* getJogador1() const;
	FireMan* getJogador2() const;

	void setfaseP(Fase1* p);
	void setfaseS(Fase2* p);
	Fase1* getFase1() const;
	Fase2* getFase2()const;
	bool getExistecarregar() const;

	estado_jogo getEstado() const;
	GerenciadorGrafico* getGrafico() const;

	void verificarFase();

};

