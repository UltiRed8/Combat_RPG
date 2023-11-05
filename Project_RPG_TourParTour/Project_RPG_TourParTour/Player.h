#pragma once

#include <iostream>

#include "colors.h"
#include "Weapon.h"

using namespace std;

class Player {
	int health;
	int maxHealth;
	int money;
	int heldWeaponId;
	int ownedWeaponsAmount;
	Weapon* ownedWeapons;
	int healItemAmount;

public:
	int GetMoney() const {
		return money;
	}
	int GetHealth() const {
		return health;
	}
	Weapon GetHeldWeapon() const {
		return ownedWeapons[heldWeaponId];
	}

public:
	Player();
	Player(const int _maxHealth);
	~Player();

private:
	int IntInput(string _question, int _min, int _max);

public:
	void AddMoney(const int _byAmount);
	void RemoveMoney(const int _byAmount);
	void Inventory();
	void AddWeapon(Weapon& _weapon);
	bool UseHealItem();
	bool IsDead() const;
	void ApplyDamages(const int _amount);
	void FightWon();
	void FightLost();
	void AddHealItem(const int _amount);
};

