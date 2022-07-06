#pragma once
#include <stdio.h>

template <class TIPO>
class Lista {
private:
	
	
	bool posicaoValida(const int i)const {
		return (i < tamanho && i >= 0);
	}
	template <class T>
	class Elemento {
	public:
		Elemento<T>* proximo;
		Elemento<T>* anterior;
		T* p;
	
		Elemento() :
			proximo(NULL), anterior(NULL), p(NULL)
		{
		}
		~Elemento() {
		}
		void setProximo(Elemento<T>* prox) {
			proximo = prox;
		}
		void setAnterior(Elemento<T>* ante) {
			anterior = ante;
		}
		void setElemento(T* pont) {
			p = pont;
		}
		Elemento<T>* getProximo()const {
			return proximo;
		}
		Elemento<T>* getAnterior()const {
			return anterior;
		}
		T* getElemento() {
			return p;
		}
	};

	Elemento<TIPO>* primeiro;
	Elemento<TIPO>* ultimo;
	int tamanho;
public:
	Lista(): primeiro(NULL),ultimo(NULL),tamanho(0) {
	}
	~Lista() {
		if (primeiro) {
			limpar();
		}
	}
	void limpar(void) {
		Elemento<TIPO>* aux = NULL;
		while (primeiro) {
			aux = primeiro;
			primeiro = primeiro->getProximo();
			delete aux;
		}
		ultimo = NULL;
		primeiro = NULL;
	}
	void adicionar(TIPO *novo) {
		if(novo){
			Elemento<TIPO>* novoEle = new Elemento<TIPO>();
			novoEle->setElemento(novo);
			novoEle->setAnterior(NULL);
			novoEle->setProximo(NULL);
			if (primeiro != NULL) {
				ultimo->setProximo(novoEle);
				novoEle->setAnterior(ultimo);
				ultimo = novoEle;
			}
			else {
				primeiro = novoEle;
				ultimo = novoEle;

			}
			tamanho++;
		}
	}
	bool remover(TIPO *elem) {
		if (elem && tamanho) {
			for (Elemento<TIPO>* aux = primeiro; aux != NULL; aux = aux->getProximo()) {
				if (aux->getElemento() == elem) {
					
					if (aux == primeiro) {
						primeiro = primeiro->getProximo();
						if (tamanho == 1) {
							ultimo = NULL;
							primeiro = NULL;
						}
					}
					else if (aux == ultimo) {
						ultimo = ultimo->getAnterior();
						if (tamanho == 1) {
							primeiro = NULL;
							ultimo = NULL;
						}
					}
					else{
						Elemento<TIPO>* prox = NULL, * ante = NULL;
						if(aux->getProximo() && aux->getAnterior()){
							prox = aux->getProximo();
							ante = aux->getAnterior();
							prox->setAnterior(ante);
							ante->setProximo(prox);
						}
					}
					delete aux;
					tamanho--;
					return true;
				}
			}
		}
		return false;
	}
	bool remover(const int i) {
		return remover(operator[](i));
	}
	TIPO* operator[](const int i) {
		if(posicaoValida(i)){
			Elemento<TIPO>* aux = primeiro;
			for ( int k = 0 ; k < tamanho ; aux = aux->getProximo() ,k++) {
				if (i == k){
					return (aux->getElemento());
				}
							}
		}
		return NULL;
	}
	//I eh a posicao na lista do elemento
	TIPO* pegar(const int i){
		return operator[](i);
	}
	const int tamanhoLista() const{
		return tamanho;
	}
};