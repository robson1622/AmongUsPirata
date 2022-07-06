#pragma once
#include "SFML/Graphics.hpp"

class VetorF {
public:
	float x;
	float y;
	VetorF();
	VetorF(VetorF* vet);
	VetorF(const float xx, const float yy);
	~VetorF();
	sf::Vector2f sfml();
	void copiar(const VetorF *valor);
	float distancia(const VetorF *valor);
	float distancia(const sf::Vector2f& valor);
	static VetorF distancia(const VetorF &valor01, const VetorF &valor02);
	float modulo(void);
	VetorF vetorUnitario(const VetorF *valor);
	VetorF vetorUnitario(const sf::Vector2f& valor);
	void operator++();
	void operator+=(const sf::Vector2f& valor);
	void operator+=(const VetorF *valor);
	void operator=(const float valor);
	void operator=(const VetorF* valor);
	void operator=(const sf::Vector2f& valor);
	bool operator==(const VetorF* valor);
	bool operator==(const sf::Vector2f& valor);
	void operator*=(const float valor);
	void operator-=(const VetorF* valor);
	void operator-=(const float valor);
	void operator-=(const sf::Vector2f& valor);
	void operator--();
	VetorF operator*(const VetorF* valor);
};
