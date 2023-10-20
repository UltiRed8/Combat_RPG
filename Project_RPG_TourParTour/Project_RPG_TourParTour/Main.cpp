#include <iostream>
#include <string>
#include <cstdlib>

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

int main()
{
	Display("\x1B[93m========================");
	Display("BIENVENUE DANS L'ARENE !");
	Display("========================");
	GameLoop();
	return 0;
}


void GameLoop()
{
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

	_enemies[0] = "Enemi - 8 Pièces"; _enemiesStats[0][0] = 6; _enemiesStats[0][1] = 3; _enemiesStats[0][2] = 8;
	_enemies[1] = "Enemi - 12 Pièces"; _enemiesStats[1][0] = 15; _enemiesStats[1][1] = 5; _enemiesStats[1][2] = 12;

	string _reponse;
	bool _returnMenu = true;
	do
	{
		Display("\x1B[90m========MENU PRINCIPALE========\x1B[37m");
		DisplayValue(">>> Votre argent : ", _playerMoney);
		DisplayValue(">>> Votre vie : ", _playerHealth);
		Display("\x1B[90m========\x1B[37m");
		Display("- Combat => Faire un combat");
		Display("- Inventaire => Changer d'arme");
		Display("- Shop => Ouvrir le shop");
		Display("- Quitter => Quitter le jeu\x1B[96m");
		cin >> _reponse;
		if (_reponse == "Combat")
		{
			system("cls");
			//choix du combat
			
			Display("\x1B[90m========LISTE ENEMIS========\x1B[37m");
			DisplayList("", _enemies, _enemiesAmount, true);
			Display("\x1B[90m========\x1B[37m");
			int _enemyId = IntInput("\x1B[37mRentrer ID de l'ennemi a affronter : \x1B[96m", 0, 1);

			if (CombatLoop(_playerHealth, _playerMaxHealth, _playerWeaponId, _enemyId, _enemies, _enemiesStats, _weapons, _weaponsStats, _healItemAmount, _weaponsInInventory, _weaponsAmount)) // si il gagne recompense
			{
				_playerMoney += _enemiesStats[_enemyId][2];
			}
		}
		else if (_reponse == "Inventaire")
		{
			_playerWeaponId = Inventory(_weaponsInInventory, _weaponsAmount, _weapons);
		}
		else if (_reponse == "Shop")
		{

			Shop(_playerMoney, _weapons, _weaponsAmount, _weaponsInInventory, _weaponsStats, _healItemAmount);
		}
		else if (_reponse == "Quitter")
		{

			_returnMenu = false;
		}
		else
		{
			Display("\x1B[91mChoix invalide");
		}
	} while (_returnMenu);
}

bool CombatLoop(int& _currentHealth, int& _maxHealth, int _weaponId, int _enemyId, string _enemies[], int _enemiesStats[][3], string _weapons[], int _weaponsStats[][3], int& _healItemAmount, bool _playerInventory[], int _weaponsAmount) {
	bool _shouldLoop = true, _actionLoop = true;
	bool _won = false;
	Display("\x1B[91mDebut du combat contre \x1B[31m" + _enemies[_enemyId] + "\x1B[91m !\x1B[37m");
	int _enemyLife = _enemiesStats[_enemyId][0];
	int _enemyDamages = _enemiesStats[_enemyId][1];
	string _actions[] = { "Attaquer", "Changer d'arme", "Utiliser soin" };
	do {
		DisplayValue(">>>Vie de l'enemi: ", _enemyLife);
		DisplayValue(">>>Votre vie: ", _currentHealth);
		Display("\x1B[90m========\x1B[37m");
		DisplayList("\x1B[37mSelectionnez l'action a effectuer :", _actions, 3, true);
		_actionLoop = true;
		do {
			switch (IntInput("\x1B[37mEntrez le numero de l'action : \x1B[96m", 0, 3)) {
			case 0:
				_actionLoop = false;
				srand(time(NULL));
				if ((rand() % 100) < _weaponsStats[_weaponId][1]) {
					_enemyLife -= _weaponsStats[_weaponId][0];
					DisplayValue("\x1B[92mVous avez attaque l'enemi : \x1B[91m", _weaponsStats[_weaponId][0]);
				} else {
					Display("\x1B[91mVous avez rate l'enemi !");
				}
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
				} else Display("\x1B[91mVous n'avez pas d'item de soin!");
				break;
			default:
				break;
			}
		} while (_actionLoop);
		if (_enemyLife <= 0) _won = true;
		if (!_won) {
			_currentHealth -= _enemyDamages;
			Display("\x1B[33mL'enemi vous as attaque, vous perdez \x1B[31m" + to_string(_enemyDamages) + "\x1B[33m points de vie!");
		}
		if (_won || _currentHealth <= 0) _shouldLoop = false;
		system("PAUSE");
		system("cls");
	} while (_shouldLoop);
	if (_won) {
		Display("\x1B[92mTu as gagne le combat!");
		_maxHealth++;
		_currentHealth = _maxHealth;
	} else {
		Display("\x1B[31mTu as perdu le combat!");
		_currentHealth = _maxHealth / 2;
	}
	return _won;
}

int Inventory(bool _playerInventory[], int _weaponsAmount, string _weapons[]) {
	int _wantedWeapon = 0;
	Display("\x1B[90m========INVENTAIRE========\x1B[37m");
	DisplayWeapons("Vos armes :", _weapons, _weaponsAmount, true, true, _playerInventory);
	Display("\x1B[90m========\x1B[37m");
	_wantedWeapon = IntInput("\x1B[37mEntrez l'id de l'arme que vous souhaitez utiliser :\x1B[96m", 0, _weaponsAmount);
	return _wantedWeapon;
}

int IntInput(string _question, int _min, int _max) {
	while (_min > _max) _min--;
	int _result = _min - 1;
	do {
		cout << _question;
		cin >> _result;
		cout << endl;
	} while (_result < _min || _result > _max);
	return _result;
}

void Display(string _text) {
	cout << _text << endl;
}

void Display(int _text)
{
	cout << _text << endl;
}

void DisplayValue(string _text, int _value) {
	cout << _text << _value << endl;
}

void DisplayList(string _text, const string _list[], int _sizeOfList, bool _printIndexes) {
	if (_text != "") cout << _text << endl;
	for (int _i = 0; _i < _sizeOfList; _i++) {
		if (_printIndexes) cout << _i;
		cout << " => " << _list[_i] << endl;
	}
}

void Shop(int& _playerMoney, string* _weapons, int _weaponsAmount, bool _weaponsInInventory[], int _weaponsStats[][3], int& _healItemAmount)
{
	bool _wantContinue = true;
	int _idChoose;
	do
	{
		system("cls");
		Display("\x1B[90m========SHOP========\x1B[37m");
		DisplayValue("Ton argent est : ", _playerMoney);
		Display("\x1B[90m========\x1B[37m");
		DisplayWeapons("Disponible : ", _weapons, _weaponsAmount, true, false, _weaponsInInventory);
		Display("-1 => Pour acheter potion de soin");
		Display("-2 => Pour quitter le shop");
		Display("\x1B[90m========\x1B[96m");

		cin >> _idChoose;
		if (_idChoose == -2)
		{
			_wantContinue = false;
			system("cls");
		}
		else if (_idChoose == -1)
		{
			if (_playerMoney < 10)
			{
				Display("\x1B[91mT'es trop pauvre!");
				system("PAUSE");
				continue;
			}
			_healItemAmount++;
			_playerMoney -= 10;
		}
		else
		{
			if (_weaponsInInventory[_idChoose])
			{
				Display("\x1B[91mTu as deja cette arme");
			}
			else
			{
				if (_playerMoney < _weaponsStats[_idChoose][2])
				{
					Display("\x1B[91mT'es trop pauvre!");
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

void DisplayWeapons(string _text, const string _weapons[], int _weaponsAmount, bool _printIndexes, bool _showInventoryItems, const bool _hasItem[]) {
	if (_text != "") cout << _text << endl;
	for (int _i = 0; _i < _weaponsAmount; _i++) {
		if (_hasItem[_i] == _showInventoryItems) {
			if (_printIndexes) cout << _i;
			cout << " => " << _weapons[_i] << endl;
		}
	}
}