
#include "Vetor.hpp"
#include <math.h>

VetorF::VetorF() {
	x = y = -1;
}
VetorF::VetorF(VetorF* vet) {
	x = vet->x;
	y = vet->y;
}
VetorF::VetorF(const float xx, const float yy) {
	x = xx;
	y = yy;
}
VetorF::~VetorF() {

}
sf::Vector2f VetorF::sfml() {
	return (sf::Vector2f({ x,y }));
}
void VetorF::copiar(const VetorF* valor) {
	x = valor->x;
	y = valor->y;
}
VetorF VetorF::vetorUnitario(const VetorF* valor) {
	float adjacente =  x - valor->x;
	float oposto =  y - valor->y;
	float hipotenusa = float(sqrt(pow(adjacente, 2) + pow(oposto, 2)));
	VetorF unitario;
	unitario.x = adjacente / hipotenusa;
	unitario.y = oposto / hipotenusa;
	return unitario;
}
VetorF VetorF::vetorUnitario(const sf::Vector2f& valor) {
	float adjacente = abs(valor.x - x);
	float oposto = abs(valor.y - y);
	float hipotenusa = float(sqrt(pow(adjacente, 2) + pow(oposto, 2)));
	VetorF unitario;
	unitario.x = adjacente / hipotenusa;
	unitario.y = oposto / hipotenusa;
	return unitario;
}
void VetorF::operator=(const float valor) {
	x = y = valor;
}
void VetorF::operator=(const VetorF* valor) {
	x = valor->x;
	y = valor->y;
}
void VetorF::operator+=(const VetorF* valor) {
	x = x + valor->x;
	y = y + valor->y;
}
void VetorF::operator*=(const float valor) {
	x = x * valor;
	y = y * valor;
}
void VetorF::operator=(const sf::Vector2f& valor) {
	x = valor.x;
	y = valor.y;
}
bool VetorF::operator==(const VetorF* valor) {
	return (x == valor->x && y == valor->y);
}
bool VetorF::operator==(const sf::Vector2f& valor) {
	return (x == valor.x && y == valor.y);
}
void VetorF::operator-=(const VetorF* valor) {
	x -= valor->x;
	y -= valor->y;
}
void VetorF::operator-=(const float valor) {
	x -= valor;
	y -= valor;
}
void VetorF::operator-=(const sf::Vector2f& valor) {
	x -= valor.x;
	y -= valor.y;
}
void VetorF::operator+=(const sf::Vector2f& valor) {
	x += valor.x;
	y += valor.y;
}
float VetorF::distancia(const sf::Vector2f& valor) {
	return float (sqrt(pow(x - valor.x, 2) + pow(y - valor.y, 2)));
}
float VetorF::distancia(const VetorF* valor) {
	return float (sqrt(pow(x - valor->x, 2) + pow(y - valor->y, 2)));
}
float VetorF::modulo(void) {
	return float(sqrt(pow(x, 2) + pow(y, 2)));
}
void VetorF::operator++() {
	x += 1;
	y += 1;
}
void VetorF::operator--() {
	x -= 1;
	y -= 1;
}
VetorF VetorF::operator*(const VetorF* valor) {
	return VetorF(x * valor->x, y * valor->y);
}
VetorF VetorF::distancia(const VetorF &valor01, const VetorF &valor02) {
	VetorF dist(0, 0);
	dist.x = valor01.x - valor02.x;
	dist.y = valor01.y - valor02.y;
	return dist;
}