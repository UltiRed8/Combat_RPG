#pragma once

#include "Player.h"
#include "Enemy.h"
#include "Weapon.h"

class Game {
	Player* player;
	int weaponsAmount;
	Weapon* weapons;
	int enemiesAmount;
	Enemy* enemies;

public:
	int GetWeaponsAmount() const {
		return weaponsAmount;
	}
	int GetEnemiesAmount() const {
		return enemiesAmount;
	}
	Player* GetPlayer() const {
		return player;
	}
	Enemy* GetEnemies() const {
		return enemies;
	}
	Weapon* GetWeapons() const {
		return weapons;
	}

public:
	Game();
	~Game();

private:
	void RemoveWeapon(Weapon& _weapon);

public:
	void AddWeapon(Weapon _weapon);
	void AddEnemy(Enemy _enemy);
	void DisplayEnemies() const;
	void DisplayWeapons() const;
	void BuyWeapon(const int _id);
};