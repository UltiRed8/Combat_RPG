#pragma once

#include <string>
#include "colors.h"

using namespace std;

class Enemy {
	string name;
	int health;
	int damages;
	int reward;
	int currentHealth;

public:
	int GetReward() const {
		return reward;
	}
	string GetName() const {
		return name;
	}
	int GetHealth() const {
		return currentHealth;
	}
	int GetDamages() const {
		return damages;
	}

public:
	Enemy();
	Enemy(const string& _name, const int _health, const int _damages, const int _reward);

public:
	void Display() const;
	void Reset();
	void ApplyDamages(const int _amount);
	bool IsDead() const;
};