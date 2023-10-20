#include <iostream>
#include <string>

using namespace std;

void DisplayList(string _text, const string _list[], int _sizeOfList, bool _printIndexes);
void Display(string _text);
void DisplayValue(string _text, int _value);
int UpdateHealth(int _currentHealth, int _addValue, int _maxPlayerHealth);
void CombatLoop();
int IntInput(string _question, int _min, int _max);
void GameLoop();

int main()
{
	const int _weaponsAmount = 2, _enemiesAmount = 1;
	int _playerHealth = 10, _playerMaxHealth = 10;
	int _playerMoney = 0;
	int _playerWeaponId = 0;
	int _healItemAmount = 0;

	string _weapons[_weaponsAmount], _enemies[_enemiesAmount];
	int _weaponsStats[_weaponsAmount][3]; // 0=> Dégats || 1=> Precision || 2=> Prix shop
	int _enemiesStats[_enemiesAmount][3]; // 0=> Vie || 1=> Dégats || 2=>Pièces

	_weapons[0] = "Arme 1"; _weaponsStats[0][0] = 5; _weaponsStats[0][1] = 75; _weaponsStats[0][2] = 0; // Arme 1 5dégats 75%précision 0prix
	_weapons[1] = "Arme 2"; _weaponsStats[1][0] = 10; _weaponsStats[1][1] = 50; _weaponsStats[0][2] = 10; // Arme 2 10dégats 50%précision 10prix

	_enemies[0] = "Enemi 1"; _enemiesStats[0][0] = 6; _enemiesStats[0][1] = 3; _enemiesStats[0][2] = 8; // Enemi 1 6pv 3dégats 8pièces

	Display("BIENVENUE DANS L'ARENE !");
	GameLoop();

	return 0;
}


void GameLoop()
{
	string _reponse;
	bool _returnMenu = true;
	do
	{
		Display("Rentre dans l'arene -> combat");
		Display("Ton Inventaire -> inventaire");
		Display("Veux tu aller au shop ? -> shop");
		cin >> _reponse;

		if (_reponse == "combat")
		{

		}
		else if (_reponse == "inventaire")
		{

		}
		else if (_reponse == "shop")
		{

		}
		else
		{
			cout << "Choix invalide" << endl;
		}

	} while (_returnMenu);

}

int UpdateHealth(int _currentHealth, int _addValue, int _maxPlayerHealth) {
	_currentHealth += _addValue;
	if (_currentHealth > _maxPlayerHealth) _currentHealth = _maxPlayerHealth;
	if (_currentHealth < 0) _currentHealth = 0;
	return _currentHealth;
}

bool CombatLoop(int _currentHealth, int _weaponId, int _enemyId, string _enemies[], int _enemiesStats[][3], string _weapons[], int _weaponsStats[][3]) {
	bool _shouldLoop = true;
	bool _won = false;
	Display("Début du combat contre" + _enemies[_enemyId] + " !");
	int _enemyLife = _enemiesStats[_enemyId][0];
	int _enemyDamages = _enemiesStats[_enemyId][1];
	string _actions[] = { "Attaquer", "Changer d'arme", "Utiliser soin" };
	do {
		DisplayList("Séléctionnez l'action a effectuer :", _actions, 3, true);
		switch (IntInput("Entrez le numéro de l'action : ", 0, 3)) {
			case 0:
				break;
			case 1:
				break;
			case 2:
				break;
			default:
				break;
		}
		if (_currentHealth == 0) _shouldLoop = false;
	} while (_shouldLoop);
	if (_won) Display("Tu as gagné le combat!");
	else Display("Tu as perdu le combat!");
	return _won;
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