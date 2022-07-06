
#include "Entidade.hpp"
#include "Vetor.hpp"
#define GRAVIDADE 1



Entidade::Entidade():Ente(), ID(),podeDeletar(false) {
    areaOcupada = new VetorF(1, 1);
    velocidade = new VetorF(0, 0);
}
Entidade::Entidade(const int TIPOOBJETO):Ente(),ID() {
    areaOcupada = new VetorF(28, 28);
    setTipoObjeto(TIPOOBJETO);
}
Entidade::~Entidade(){
    delete areaOcupada;
    delete velocidade;
}
bool Entidade::podeDeletarEntidade() {
    return podeDeletar;
}

bool Entidade::operator==(const Entidade *colidivel2) {
    
    VetorF distancia(0, 0);
    distancia.x = abs(posicao->x - colidivel2->posicao->x);
    distancia.y = abs(posicao->y - colidivel2->posicao->y);
    if (distancia.x < ((areaOcupada->x + colidivel2->areaOcupada->x) / 2) && distancia.y < ((areaOcupada->y + colidivel2->areaOcupada->y) / 2)) {
        return true;
    }
    return false;
}
const int Entidade::getID(){
    return ID;
}
const VetorF* Entidade::getAreaOcupada() {
    return areaOcupada;
}

const VetorF* Entidade::getVelocidade(void) {
    return velocidade;
}
void  Entidade::setVelocidade(const VetorF &valor) {
    *velocidade = valor;
}
void Entidade::setAreaOcupada(const VetorF *lugar){
    *areaOcupada = lugar;
}