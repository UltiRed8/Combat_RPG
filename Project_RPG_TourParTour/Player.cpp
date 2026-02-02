#include "Player.h"

#pragma region ConstructorsAndDeconstructors
Player::Player() {
	health = 10;
	maxHealth = 10;
	money = 0;
	healItemAmount = 0;
	heldWeaponId = 0;
	ownedWeaponsAmount = 0;
	ownedWeapons = new Weapon[ownedWeaponsAmount];
	Weapon _tempWeapon = Weapon("Default weapon", 5, 75, 0);
	AddWeapon(_tempWeapon);
}

Player::Player(const int _maxHealth) {
	health = _maxHealth;
	maxHealth = _maxHealth;
	money = 0;
	healItemAmount = 0;
	heldWeaponId = 0;
	ownedWeaponsAmount = 0;
	ownedWeapons = new Weapon[ownedWeaponsAmount];
	Weapon _tempWeapon = Weapon("Default weapon", 5, 75, 0);
	AddWeapon(_tempWeapon);
}

Player::~Player() {
	delete[] ownedWeapons;
}
#pragma endregion

void Player::AddMoney(const int _byAmount) {
	money += _byAmount;
}

void Player::AddWeapon(Weapon& _weapon) {
	ownedWeaponsAmount++;
	Weapon* _newList = new Weapon[ownedWeaponsAmount];
	for (int _i = 0; _i < ownedWeaponsAmount - 1; _i++) _newList[_i] = ownedWeapons[_i];
	_newList[ownedWeaponsAmount - 1] = _weapon;
	delete[] ownedWeapons;
	ownedWeapons = _newList;
}

void Player::RemoveMoney(const int _byAmount) {
	money -= _byAmount;
}

bool Player::UseHealItem() {
	if (healItemAmount - 1 >= 0) {
		healItemAmount--;
		health = maxHealth;
		return true;
	}
	else DISPLAY(BRIGHT_RED << "You don't have any healing item!");
	return false;
}

void Player::Inventory() {
	DISPLAY(BRIGHT_BLACK << "========INVENTORY========" << WHITE << endl << "Your weapons:");
	for (int _i = 0; _i < ownedWeaponsAmount; _i++) {
		cout << _i << " => ";
		ownedWeapons[_i].Display(false);
	}
	DISPLAY(BRIGHT_BLACK << "========" << WHITE);
	heldWeaponId = IntInput("Enter the ID of the weapon you would like to use: ", 0, ownedWeaponsAmount - 1);
}

int Player::IntInput(string _question, int _min, int _max) {
	while (_min > _max) _min--;
	int _result = _min - 1;
	do {
		DISPLAY(endl << YELLOW << _question << BRIGHT_CYAN);
		cout << "> ";
		cin >> _result;
	} while (_result < _min || _result > _max);
	return _result;
}

bool Player::IsDead() const {
	return health <= 0;
}

void Player::ApplyDamages(const int _amount) {
	health -= _amount;
}

void Player::FightWon() {
	maxHealth++;
	health = maxHealth;
}

void Player::FightLost() {
	health = maxHealth / 2;
}

void Player::AddHealItem(const int _amount) {
	healItemAmount += _amount;
}