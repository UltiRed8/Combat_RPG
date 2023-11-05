#include <iostream>
#include <string>
#include <cstdlib>

#include "colors.h"

using namespace std;

void DisplayList(string _text, const string _list[], int _sizeOfList, bool _printIndexes);
void Display(string _text);
void DisplayValue(string _text, int _value);
bool CombatLoop(int& _currentHealth, int& _maxHealth, int _weaponId, int _enemyId, string _enemies[], int _enemiesStats[][3], string _weapons[], int _weaponsStats[][3], int& _healItemAmount, bool _playerInventory[], int _weaponsAmount);
int IntInput(string _question, int _min, int _max);
void DisplayWeapons(string _text, const string _weapons[], int _weaponsAmount, bool _printIndexes, bool _showInventoryItems, const bool _hasItem[]);
void GameLoop();
void Shop(int& _playerMoney, string* _weapons, int _weaponsAmount, bool _weaponsInInventory[], int _weaponsStats[][3], int& _healItemAmount);
int Inventory(bool _playerInventory[], int _weaponsAmount, string _weapons[]);
string StringInput(const string _question);

int main() {
	DISPLAY(BRIGHT_YELLOW << "========================");
	DISPLAY("BIENVENUE DANS L'ARENE");
	DISPLAY("========================");
	GameLoop();
	return 0;
}


void GameLoop() {
	const int _weaponsAmount = 2, _enemiesAmount = 2;
	int _playerHealth = 10, _playerMaxHealth = 10;
	int _playerMoney = 0;
	int _playerWeaponId = 0;
	int _healItemAmount = 0;
	bool _weaponsInInventory[_weaponsAmount]{ true };

	string _weapons[_weaponsAmount], _enemies[_enemiesAmount];
	int _weaponsStats[_weaponsAmount][3]; // 0=> Degats  1=> Precision  2=> Prix shop
	int _enemiesStats[_enemiesAmount][3]; // 0=> Vie  1=> Degats  2=>Pièces

	_weapons[0] = "Arme - 5 Degats - 75% Precision"; _weaponsStats[0][0] = 5; _weaponsStats[0][1] = 75; _weaponsStats[0][2] = 0;
	_weapons[1] = "Arme - 10 Degats - 50% Precision"; _weaponsStats[1][0] = 10; _weaponsStats[1][1] = 50; _weaponsStats[1][2] = 10;

	_enemies[0] = "Enemi - 8 Pieces"; _enemiesStats[0][0] = 6; _enemiesStats[0][1] = 3; _enemiesStats[0][2] = 8;
	_enemies[1] = "Enemi - 12 Pieces"; _enemiesStats[1][0] = 15; _enemiesStats[1][1] = 5; _enemiesStats[1][2] = 12;

	string _response;
	bool _returnMenu = true;
	do {
		DISPLAY(BRIGHT_BLACK << "========MENU PRINCIPALE========" << WHITE);
		DISPLAY(">>> Vous avez " << _playerMoney << " pieces !");
		DISPLAY(">>> Votre vie : " << _playerHealth);
		DISPLAY(BRIGHT_BLACK << "========" << WHITE);
		DISPLAY("- Combat => Faire un combat");
		DISPLAY("- Inventaire => Changer d'arme");
		DISPLAY("- Shop => Ouvrir le shop");
		DISPLAY("- Quitter => Quitter le jeu" << BRIGHT_CYAN);
		_response = StringInput("Que voulez vous faire ?");
		if (_response == "Combat") {
			system("cls");
			DISPLAY(BRIGHT_BLACK << "========LISTE ENEMIS========" << WHITE);
			DisplayList("", _enemies, _enemiesAmount, true);
			DISPLAY(BRIGHT_BLACK << "========" << WHITE);
			int _enemyId = IntInput("Rentrez l'ID de l'ennemi a affronter :", 0, _enemiesAmount-1);
			if (CombatLoop(_playerHealth, _playerMaxHealth, _playerWeaponId, _enemyId, _enemies, _enemiesStats, _weapons, _weaponsStats, _healItemAmount, _weaponsInInventory, _weaponsAmount)) {
				_playerMoney += _enemiesStats[_enemyId][2];
			}
		} else if (_response == "Inventaire") _playerWeaponId = Inventory(_weaponsInInventory, _weaponsAmount, _weapons);
		else if (_response == "Shop") Shop(_playerMoney, _weapons, _weaponsAmount, _weaponsInInventory, _weaponsStats, _healItemAmount);
		else if (_response == "Quitter") _returnMenu = false;
		else DISPLAY(RED << "Choix invalide !");
	} while (_returnMenu);
}

bool CombatLoop(int& _currentHealth, int& _maxHealth, int _weaponId, int _enemyId, string _enemies[], int _enemiesStats[][3], string _weapons[], int _weaponsStats[][3], int& _healItemAmount, bool _playerInventory[], int _weaponsAmount) {
	bool _shouldLoop = true, _actionLoop = true;
	bool _won = false;
	DISPLAY(BRIGHT_RED << "Debut du combat contre " << RED << _enemies[_enemyId] << BRIGHT_RED << " !");
	int _enemyLife = _enemiesStats[_enemyId][0];
	int _enemyDamages = _enemiesStats[_enemyId][1];
	string _actions[] = { "Attaquer", "Changer d'arme", "Utiliser soin" };
	do {
		DISPLAY(WHITE << ">>>Vie de l'enemi: " << _enemyLife);
		DISPLAY(">>>Votre vie: " << _currentHealth);
		DISPLAY(BRIGHT_BLACK << "========");
		DisplayList("Selectionnez l'action a effectuer :", _actions, 3, true);
		_actionLoop = true;
		do {
			switch (IntInput("Entrez le numero de l'action :", 0, 2)) {
			case 0:
				_actionLoop = false;
				srand(time(NULL));
				if ((rand() % 100) < _weaponsStats[_weaponId][1]) {
					_enemyLife -= _weaponsStats[_weaponId][0];
					DISPLAY(BRIGHT_GREEN << "Vous avez attaque l'enemi :" << BRIGHT_RED << _weaponsStats[_weaponId][0]);
				} else DISPLAY(BRIGHT_RED << "Vous avez rate l'enemi !");
				break;
			case 1:
				_weaponId = Inventory(_playerInventory, _weaponsAmount, _weapons);
				_actionLoop = false;
				break;
			case 2:
				if (_healItemAmount - 1 >= 0) {
					_healItemAmount--;
					_currentHealth = _maxHealth;
					_actionLoop = false;
				}
				else DISPLAY(BRIGHT_RED << "Vous n'avez pas d'item de soin !");
				break;
			default:
				DISPLAY(RED << "Choix invalide !");
				break;
			}
		} while (_actionLoop);
		if (_enemyLife <= 0) _won = true;
		if (!_won) {
			_currentHealth -= _enemyDamages;
			DISPLAY(YELLOW << "L'enemi vous as attaque, vous perdez " << RED << _enemyDamages << YELLOW << " points de vie !");
		}
		if (_won || _currentHealth <= 0) _shouldLoop = false;
		system("PAUSE");
		system("cls");
	} while (_shouldLoop);
	if (_won) {
		DISPLAY(BRIGHT_GREEN << "Tu as gagne le combat !");
		_maxHealth++;
		_currentHealth = _maxHealth;
	} else {
		DISPLAY(RED << "Tu as perdu le combat !");
		_currentHealth = _maxHealth / 2;
	}
	return _won;
}

int Inventory(bool _playerInventory[], int _weaponsAmount, string _weapons[]) {
	int _wantedWeapon = 0;
	DISPLAY(BRIGHT_BLACK << "========INVENTAIRE========" << WHITE);
	DisplayWeapons("Vos armes :", _weapons, _weaponsAmount, true, true, _playerInventory);
	DISPLAY(BRIGHT_BLACK << "========" << WHITE);
	_wantedWeapon = IntInput("Entrez l'id de l'arme que vous souhaitez utiliser :", 0, _weaponsAmount-1);
	return _wantedWeapon;
}

void Shop(int& _playerMoney, string* _weapons, int _weaponsAmount, bool _weaponsInInventory[], int _weaponsStats[][3], int& _healItemAmount) {
	bool _wantContinue = true;
	int _idChoose;
	do {
		system("cls");
		DISPLAY(BRIGHT_BLACK << "========SHOP========" << WHITE);
		DISPLAY(">>> Vous avez " << _playerMoney << " pieces !");
		DISPLAY(BRIGHT_BLACK << "========" << WHITE);
		DISPLAY("Disponible :");
		DISPLAY("-2 => Pour quitter le shop");
		DISPLAY("-1 => Pour acheter potion de soin");
		DisplayWeapons("", _weapons, _weaponsAmount, true, false, _weaponsInInventory);
		DISPLAY(BRIGHT_BLACK << "========" << WHITE);
		_idChoose = IntInput("Entrez l'id de ce que vous souhaitez faire :", -2, _weaponsAmount-1);
		if (_idChoose == -2) {
			_wantContinue = false;
			system("cls");
		} else if (_idChoose == -1) {
			if (_playerMoney < 10) {
				DISPLAY(BRIGHT_RED << "Tu est trop pauvre !");
				system("PAUSE");
				continue;
			}
			_healItemAmount++;
			_playerMoney -= 10;
		} else {
			if (_weaponsInInventory[_idChoose]) {
				DISPLAY(BRIGHT_RED << "Tu as deja cette arme !");
				system("PAUSE");
			} else {
				if (_playerMoney < _weaponsStats[_idChoose][2]) {
					DISPLAY(BRIGHT_RED << "Tu est trop pauvre !");
					system("PAUSE");
					continue;
				}
				_weaponsInInventory[_idChoose] = true;
				_playerMoney -= _weaponsStats[_idChoose][2];
				system("PAUSE");
			}
		}
	} while (_wantContinue);
}

int IntInput(string _question, int _min, int _max) {
	while (_min > _max) _min--;
	int _result = _min - 1;
	do {
		DISPLAY(endl << YELLOW << _question << BRIGHT_CYAN);
		cout << "> ";
		cin >> _result;
	} while (_result < _min || _result > _max);
	return _result;
}

string StringInput(const string _question) {
	DISPLAY(endl << YELLOW << _question << BRIGHT_CYAN);
	cout << "> ";
	string _result;
	cin >> _result;
	return _result;
}

void DisplayWeapons(string _text, const string _weapons[], int _weaponsAmount, bool _printIndexes, bool _showInventoryItems, const bool _hasItem[]) {
	if (_text != "") DISPLAY(WHITE << _text);
	for (int _i = 0; _i < _weaponsAmount; _i++) {
		if (_hasItem[_i] == _showInventoryItems) {
			if (_printIndexes) cout << _i;
			DISPLAY(" => " << _weapons[_i]);
		}
	}
}

void Display(string _text) {
	cout << _text << endl;
}

void Display(int _text) {
	cout << _text << endl;
}

void DisplayValue(string _text, int _value) {
	cout << _text << _value << endl;
}

void DisplayList(string _text, const string _list[], int _sizeOfList, bool _printIndexes) {
	if (_text != "") DISPLAY(WHITE << _text);
	for (int _i = 0; _i < _sizeOfList; _i++) {
		if (_printIndexes) cout << _i;
		DISPLAY(" => " << _list[_i]);
	}
}