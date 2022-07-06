#pragma once
#include <stdlib.h>

template <class T>
class Elemento {
private:
	Elemento<T>* proximo;
	Elemento<T>* anterior;
	T* p;
public:
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