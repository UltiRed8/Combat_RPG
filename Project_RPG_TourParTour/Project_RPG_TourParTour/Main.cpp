#include <iostream>
#include <string>
#include <cstdlib>

#include "Game.h"

void DisplayList(string _text, const string _list[], int _sizeOfList, bool _printIndexes);
void Display(string _text);
void DisplayValue(string _text, int _value);
bool CombatLoop(Game& _game, int _weaponId);
int IntInput(const string& _question, int _min, int _max);
void DisplayWeapons(string _text, const string _weapons[], int _weaponsAmount, bool _printIndexes, bool _showInventoryItems, const bool _hasItem[]);
void GameLoop();
void Shop(Game& _game);
string StringInput(const string& _question);

int main() {
	DISPLAY(BRIGHT_YELLOW << "========================");
	DISPLAY("BIENVENUE DANS L'ARENE");
	DISPLAY("========================");
	GameLoop();
	return 0;
}

void GameLoop() {
	Game _game = Game();
	_game.AddEnemy(Enemy("Enemi 1", 6, 3, 8));
	_game.AddEnemy(Enemy("Enemi 2", 15, 5, 12));
	_game.AddWeapon(Weapon("Arme 1", 10, 50, 10));
	string _response;
	bool _returnMenu = true;
	do {
		DISPLAY(BRIGHT_BLACK << "========MENU PRINCIPALE========" << WHITE);
		DISPLAY(">>> Vous avez " << _game.GetPlayer()->GetMoney() << " pieces !");
		DISPLAY(">>> Votre vie : " << _game.GetPlayer()->GetHealth());
		DISPLAY(BRIGHT_BLACK << "========" << WHITE);
		DISPLAY("- Combat => Faire un combat");
		DISPLAY("- Inventaire => Changer d'arme");
		DISPLAY("- Shop => Ouvrir le shop");
		DISPLAY("- Quitter => Quitter le jeu" << BRIGHT_CYAN);
		_response = StringInput("Que voulez vous faire ?");
		if (_response == "Combat") {
			std::system("cls");
			DISPLAY(BRIGHT_BLACK << "========LISTE ENEMIS========" << WHITE);
			_game.DisplayEnemies();
			DISPLAY(BRIGHT_BLACK << "========" << WHITE);
			int _enemyId = IntInput("Rentrez l'ID de l'ennemi a affronter :", 0, _game.GetEnemiesAmount() - 1);
			if (CombatLoop(_game, _enemyId)) {
				_game.GetPlayer()->AddMoney(_game.GetEnemies()[_enemyId].GetReward());
			}
		} else if (_response == "Inventaire") _game.GetPlayer()->Inventory();
		else if (_response == "Shop") Shop(_game);
		else if (_response == "Quitter") _returnMenu = false;
		else DISPLAY(RED << "Choix invalide !");
	} while (_returnMenu);
}

bool CombatLoop(Game& _game, int _enemyId) {
	bool _shouldLoop = true, _actionLoop = true;
	bool _won = false;
	DISPLAY(BRIGHT_RED << "Debut du combat contre " << RED << _game.GetEnemies()[_enemyId].GetName() << BRIGHT_RED << " !");
	_game.GetEnemies()[_enemyId].Reset();
	string _actions[] = { "Attaquer", "Changer d'arme", "Utiliser soin" };
	do {
		DISPLAY(WHITE << ">>> Vie de l'enemi: " << _game.GetEnemies()[_enemyId].GetHealth());
		DISPLAY(">>> Votre vie: " << _game.GetPlayer()->GetHealth());
		DISPLAY(BRIGHT_BLACK << "========");
		DisplayList("Selectionnez l'action a effectuer :", _actions, 3, true);
		_actionLoop = true;
		do {
			switch (IntInput("Entrez le numero de l'action :", 0, 2)) {
			case 0:
				_actionLoop = false;
				srand(time(NULL));
				if ((rand() % 100) < _game.GetPlayer()->GetHeldWeapon().GetPrecision()) {
					_game.GetEnemies()[_enemyId].ApplyDamages(_game.GetPlayer()->GetHeldWeapon().GetDamages());
					DISPLAY(BRIGHT_GREEN << "Vous avez attaque l'enemi : " << BRIGHT_RED << _game.GetPlayer()->GetHeldWeapon().GetDamages());
				} else DISPLAY(BRIGHT_RED << "Vous avez rate l'enemi !");
				break;
			case 1:
				_game.GetPlayer()->Inventory();
				_actionLoop = false;
				break;
			case 2:
				if (_game.GetPlayer()->UseHealItem()) _actionLoop = false;
				break;
			default:
				DISPLAY(RED << "Choix invalide !");
				break;
			}
		} while (_actionLoop);
		if (_game.GetEnemies()[_enemyId].IsDead()) _won = true;
		if (!_won) {
			_game.GetPlayer()->ApplyDamages(_game.GetEnemies()[_enemyId].GetDamages());
			DISPLAY(YELLOW << "L'enemi vous as attaque, vous perdez " << RED << _game.GetEnemies()[_enemyId].GetDamages() << YELLOW << " points de vie !");
		}
		if (_won || _game.GetPlayer()->IsDead()) _shouldLoop = false;
		system("PAUSE");
		system("cls");
	} while (_shouldLoop);
	if (_won) {
		DISPLAY(BRIGHT_GREEN << "Tu as gagne le combat !");
		_game.GetPlayer()->FightWon();
	} else {
		DISPLAY(RED << "Tu as perdu le combat !");
		_game.GetPlayer()->FightLost();
	}
	return _won;
}

void Shop(Game& _game) {
	bool _wantContinue = true;
	int _idChoose;
	do {
		system("cls");
		DISPLAY(BRIGHT_BLACK << "========SHOP========" << WHITE);
		DISPLAY(">>> Vous avez " << _game.GetPlayer()->GetMoney() << " pieces !");
		DISPLAY(BRIGHT_BLACK << "========" << WHITE);
		DISPLAY("Disponible :");
		DISPLAY("-2 => Pour quitter le shop");
		DISPLAY("-1 => Pour acheter potion de soin");
		_game.DisplayWeapons();
		DISPLAY(BRIGHT_BLACK << "========" << WHITE);
		_idChoose = IntInput("Entrez l'id de ce que vous souhaitez faire :", -2, _game.GetWeaponsAmount() - 1);
		if (_idChoose == -2) {
			_wantContinue = false;
			system("cls");
		} else if (_idChoose == -1) {
			if (_game.GetPlayer()->GetMoney() < 10) {
				DISPLAY(BRIGHT_RED << "Tu est trop pauvre !");
				system("PAUSE");
				continue;
			}
			_game.GetPlayer()->AddHealItem(1);
			_game.GetPlayer()->RemoveMoney(10);
		} else {
			if (_game.GetPlayer()->GetMoney() < _game.GetWeapons()[_idChoose].GetPrice()) {
				DISPLAY(BRIGHT_RED << "Tu est trop pauvre !");
				system("PAUSE");
				continue;
			}
			_game.GetPlayer()->RemoveMoney(_game.GetWeapons()[_idChoose].GetPrice());
			_game.BuyWeapon(_idChoose);
			system("PAUSE");
		}
	} while (_wantContinue);
}

int IntInput(const string& _question, int _min, int _max) {
	while (_min > _max) _min--;
	int _result = _min - 1;
	do {
		DISPLAY(endl << YELLOW << _question << BRIGHT_CYAN);
		cout << "> ";
		cin >> _result;
	} while (_result < _min || _result > _max);
	return _result;
}

string StringInput(const string& _question) {
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