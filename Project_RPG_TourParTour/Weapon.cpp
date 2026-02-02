#include "Weapon.h"

Weapon::Weapon() {
	damages = 4;
	precision = 75;
	price = 10;
}

Weapon::Weapon(const string& _name, const int _damages, const int _precision, const int _price) {
	name = _name;
	damages = _damages;
	precision = _precision;
	price = _price;
}

void Weapon::Display(const bool _withPrice) const {
	if (_withPrice) DISPLAY(name << " | " << damages << " damages | " << precision << "% accuracy | price: " << price << " coins");
	else DISPLAY(name << " | " << damages << " damages | " << precision << "% accuracy");
}
