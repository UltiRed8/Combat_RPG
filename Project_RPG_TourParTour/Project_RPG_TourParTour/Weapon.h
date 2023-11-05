#pragma once

#include "colors.h"

#include <string>
#include <iostream>

using namespace std;

class Weapon {
	string name;
	int damages;
	int precision;
	int price;

public:
	int GetPrecision() const {
		return precision;
	}
	int GetDamages() const {
		return damages;
	}
	string GetName() const {
		return name;
	}
	int GetPrice() const {
		return price;
	}

public:
	Weapon();
	Weapon(const string& _name, const int _damages, const int _precision, const int _price);

public:
	void Display(const bool _withPrice) const;
};

