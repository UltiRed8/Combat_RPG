#include <iostream>
#include <string>

using namespace std;

void DisplayList(string _text, const string _list[], int _sizeOfList, bool _printIndexes);
void Display(string _text);
void DisplayValue(string _text, int _value);
bool CombatLoop(int _currentHealth, int _maxHealth, int _weaponId, int _enemyId, string _enemies[], int _enemiesStats[][3], string _weapons[], int _weaponsStats[][3], int _healItemAmount, bool _playerInventory[], int _weaponsAmount);
int IntInput(string _question, int _min, int _max);
void DisplayWeapons(string _text, const string _weapons[], int _weaponsAmount, bool _printIndexes, bool _showInventoryItems, const bool _hasItem[]);
void GameLoop();
void Shop(int& _playerMoney, string* _weapons, int _weaponsAmount, bool _weaponsInInventory[], int _weaponsStats[][3]);
int Inventory(bool _playerInventory[], int _weaponsAmount, string _weapons[]);

int main()
{
	Display("BIENVENUE DANS L'ARENE !");
	GameLoop();
	return 0;
}


void GameLoop()
{
	const int _weaponsAmount = 2, _enemiesAmount = 1;
	int _playerHealth = 10, _playerMaxHealth = 10;
	int _playerMoney = 1000;
	int _playerWeaponId = 0;
	int _healItemAmount = 0;
	bool _weaponsInInventory[_weaponsAmount]{ true };

	string _weapons[_weaponsAmount], _enemies[_enemiesAmount];
	int _weaponsStats[_weaponsAmount][3]; // 0=> Dégats  1=> Precision  2=> Prix shop
	int _enemiesStats[_enemiesAmount][3]; // 0=> Vie  1=> Dégats  2=>Pièces

	_weapons[0] = "Arme 1"; _weaponsStats[0][0] = 5; _weaponsStats[0][1] = 75; _weaponsStats[0][2] = 0; // Arme 1 5dégats 75%précision 0prix
	_weapons[1] = "Arme 2"; _weaponsStats[1][0] = 10; _weaponsStats[1][1] = 50; _weaponsStats[1][2] = 10; // Arme 2 10dégats 50%précision 10prix

	_enemies[0] = "Enemi 1"; _enemiesStats[0][0] = 6; _enemiesStats[0][1] = 3; _enemiesStats[0][2] = 8; // Enemi 1 6pv 3dégats 8pièces

	string _reponse;
	bool _returnMenu = true;
	do
	{
		Display("Ton argent : "); cout << _playerMoney << endl;
		Display("Rentre dans l'arene -> combat \n");
		Display("Ton Inventaire -> inventaire \n");
		Display("Veux tu aller au shop ? -> shop \n");
		cin >> _reponse;
		if (_reponse == "combat")
		{
			system("cls");
			//choix du combat
			DisplayList("Liste d'ennemie : ", _enemies, 1, true);
			int _enemyId = IntInput("Rentrer ID de l'ennemi à affronter", 0, 1);

			if (CombatLoop(_playerHealth, _playerMaxHealth, _playerWeaponId, _enemyId, _enemies, _enemiesStats, _weapons, _weaponsStats, _healItemAmount, _weaponsInInventory, _weaponsAmount)) // si il gagne recompense
			{
				_playerMoney += _enemiesStats[_enemyId][2];
			}
		}
		else if (_reponse == "inventaire")
		{
			//OpenInventaire(); //focntion reutilisable meme en combat

		}
		else if (_reponse == "shop")
		{

			Shop(_playerMoney, _weapons, _weaponsAmount, _weaponsInInventory, _weaponsStats);
		}
		else
		{
			cout << "Choix invalide" << endl;
		}
	} while (_returnMenu);
}

bool CombatLoop(int _currentHealth, int _maxHealth, int _weaponId, int _enemyId, string _enemies[], int _enemiesStats[][3], string _weapons[], int _weaponsStats[][3], int _healItemAmount, bool _playerInventory[], int _weaponsAmount) {
	bool _shouldLoop = true, _actionLoop = true;
	bool _won = false;
	Display("Début du combat contre" + _enemies[_enemyId] + " !");
	int _enemyLife = _enemiesStats[_enemyId][0];
	int _enemyDamages = _enemiesStats[_enemyId][1];
	string _actions[] = { "Attaquer", "Changer d'arme", "Utiliser soin" };
	do {
		DisplayValue("Vie de l'enemi: ", _enemyLife);
		DisplayValue("Votre vie: ", _currentHealth);
		DisplayList("Séléctionnez l'action a effectuer :", _actions, 3, true);
		_actionLoop = true;
		do {
			switch (IntInput("Entrez le numéro de l'action : ", 0, 3)) {
			case 0:
				_actionLoop = false;
				_enemyLife -= _weaponsStats[_weaponId][0];
				DisplayValue("Vous avez attaqué l'enemi : ", _weaponsStats[_weaponId][0]);
				break;
			case 1:
				_weaponId = Inventory(_playerInventory, _weaponsAmount, _weapons);
				_actionLoop = false;
				break;
			case 2:
				if (_healItemAmount - 1 >= 0) {
					_healItemAmount--;
					_currentHealth = _maxHealth;
				} else Display("Vous n'avez pas d'item de soin!");
				_actionLoop = false;
				break;
			default:
				break;
			}
		} while (_actionLoop);
		if (_enemyLife <= 0) _won = true;
		if (!_won) {
			_currentHealth -= _enemyDamages;
			Display("L'enemi vous as attaqué, vous perdez " + to_string(_enemyDamages) + " points de vie!");
		}
		if (_won || _currentHealth == 0) _shouldLoop = false;
		system("PAUSE");
		system("cls");
	} while (_shouldLoop);
	if (_won) Display("Tu as gagné le combat!");
	else Display("Tu as perdu le combat!");
	return _won;
}

int Inventory(bool _playerInventory[], int _weaponsAmount, string _weapons[]) {
	int _wantedWeapon = 0;
	DisplayWeapons("Vos armes :", _weapons, _weaponsAmount, true, true, _playerInventory);
	_wantedWeapon = IntInput("Entrez l'id de l'arme que vous souhaitez utiliser : ", 0, _weaponsAmount);
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
		cout << "- " << _list[_i] << endl;
	}
}

void Shop(int& _playerMoney, string* _weapons, int _weaponsAmount, bool _weaponsInInventory[], int _weaponsStats[][3])
{
	bool _wantContinue = true;
	int _idChoose;
	do
	{
		system("cls");
		DisplayValue("Ton argent est : ", _playerMoney);
		DisplayWeapons("Voici le stock : ", _weapons, _weaponsAmount, true, false, _weaponsInInventory);
		Display("-1 pour quitter le shop");

		cin >> _idChoose;
		if (_idChoose == -1)
		{
			_wantContinue = false;
		}
		else
		{
			if (_weaponsInInventory[_idChoose])
			{
				Display("Tu as deja cette arme");
			}
			else
			{
				_weaponsInInventory[_idChoose] = true;
				_playerMoney -= _weaponsStats[_idChoose][2];
				cout << _weaponsStats[_idChoose][2];
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
			cout << "- " << _weapons[_i] << endl;
		}
	}
}