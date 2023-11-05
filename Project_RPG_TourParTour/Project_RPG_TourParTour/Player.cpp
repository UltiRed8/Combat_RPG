#include "Player.h"

Player::Player() {
	health = 10;
	maxHealth = 10;
	money = 0;
	healItemAmount = 0;
	heldWeaponId = 0;
	ownedWeaponsAmount = 0;
	ownedWeapons = new Weapon[ownedWeaponsAmount];
	Weapon _tempWeapon = Weapon("Arme par defaut", 5, 75, 0);
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
	Weapon _tempWeapon = Weapon("Arme par defaut", 5, 75, 0);
	AddWeapon(_tempWeapon);
}

Player::~Player() {
	delete[] ownedWeapons;
}

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
	else DISPLAY(BRIGHT_RED << "Vous n'avez pas d'item de soin !");
	return false;
}

void Player::Inventory() {
	DISPLAY(BRIGHT_BLACK << "========INVENTAIRE========" << WHITE << endl << "Vos armes :");
	for (int _i = 0; _i < ownedWeaponsAmount; _i++) {
		cout << _i << " => ";
		ownedWeapons[_i].Display(false);
	}
	DISPLAY(BRIGHT_BLACK << "========" << WHITE);
	heldWeaponId = IntInput("Entrez l'id de l'arme que vous souhaitez utiliser :", 0, ownedWeaponsAmount - 1);
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