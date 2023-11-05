#include "Game.h"

#include <iostream>

using namespace std;

#pragma region ConstructorsAndDeconstructors
Game::Game() {
	weaponsAmount = 0;
	enemiesAmount = 0;
	weapons = new Weapon[weaponsAmount];
	enemies = new Enemy[enemiesAmount];
	player = new Player();
}

Game::~Game() {
	delete player;
	delete[] weapons;
	delete[] enemies;
}
#pragma endregion

void Game::RemoveWeapon(Weapon& _weapon) {
	weaponsAmount--;
	int _offset = 0;
	Weapon* _newList = new Weapon[weaponsAmount];
	for (int _i = 0; _i < weaponsAmount; _i++) {
		if (weapons[_i].GetName() == _weapon.GetName()) _offset++;
		_newList[_i] = weapons[_i + _offset];
	}
	delete[] weapons;
	weapons = _newList;
}

void Game::AddWeapon(Weapon _weapon) {
	weaponsAmount++;
	Weapon* _newList = new Weapon[weaponsAmount];
	for (int _i = 0; _i < weaponsAmount - 1; _i++) _newList[_i] = weapons[_i];
	_newList[weaponsAmount - 1] = _weapon;
	delete[] weapons;
	weapons = _newList;
}

void Game::AddEnemy(Enemy _enemy) {
	enemiesAmount++;
	Enemy* _newList = new Enemy[enemiesAmount];
	for (int _i = 0; _i < enemiesAmount - 1; _i++) _newList[_i] = enemies[_i];
	_newList[enemiesAmount - 1] = _enemy;
	delete[] enemies;
	enemies = _newList;
}

void Game::DisplayEnemies() const {
	for (int _i = 0; _i < enemiesAmount; _i++) {
		cout << _i << " => ";
		enemies[_i].Display();
	}
}

void Game::DisplayWeapons() const {
	for (int _i = 0; _i < weaponsAmount; _i++) {
		cout << _i << " => ";
		weapons[_i].Display(true);
	}
}

void Game::BuyWeapon(const int _id) {
	player->AddWeapon(weapons[_id]);
	RemoveWeapon(weapons[_id]);
}