#include "Enemy.h"

#include <iostream>

#pragma region ConstructorsAndDeconstructors
Enemy::Enemy() {
	name = "null";
	health = 10;
	damages = 5;
	reward = 8;
	currentHealth = health;
}

Enemy::Enemy(const string& _name, const int _health, const int _damages, const int _reward) {
	name = _name;
	health = _health;
	damages = _damages;
	reward = _reward;
	currentHealth = health;
}
#pragma endregion

void Enemy::Display() const {
	DISPLAY(name << " | " << health << " HP | " << damages << " Damages | " << reward << " coins");
}

void Enemy::Reset() {
	currentHealth = health;
}

void Enemy::ApplyDamages(const int _amount) {
	currentHealth -= _amount;
}

bool Enemy::IsDead() const {
	return currentHealth <= 0;
}