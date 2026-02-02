#include <iostream>
#include <string>
#include <cstdlib>

#include "Game.h"

#pragma region forwards
void GameLoop();
Game CreateElements();
bool CombatLoop(Game& _game, int _weaponId);
void Shop(Game& _game);
void DisplayList(string _text, const string _list[], int _sizeOfList, bool _printIndexes);
int IntInput(const string& _question, int _min, int _max);
string StringInput(const string& _question);
#pragma endregion

int main() {
	DISPLAY(BRIGHT_YELLOW << "====================");
	DISPLAY("WELCOME TO THE ARENA");
	DISPLAY("====================");
	GameLoop();
	return 0;
}

void GameLoop() {
	Game _game = CreateElements();
	string _response;
	bool _returnMenu = true;
	do {
		DISPLAY(BRIGHT_BLACK << "========MAIN MENU========" << WHITE);
		DISPLAY(">>> You have " << _game.GetPlayer()->GetMoney() << " coins!");
		DISPLAY(">>> HP : " << _game.GetPlayer()->GetHealth());
		DISPLAY(BRIGHT_BLACK << "========" << WHITE);
		DISPLAY("- Fight => Starts a fight");
		DISPLAY("- Inventory => Switches weapon");
		DISPLAY("- Shop => Opens the shop");
		DISPLAY("- Quit => Quit the game" << BRIGHT_CYAN);
		_response = StringInput("What would you like to do?");
		if (_response == "Fight") {
			std::system("cls");
			DISPLAY(BRIGHT_BLACK << "========ENEMIES LIST========" << WHITE);
			_game.DisplayEnemies();
			DISPLAY(BRIGHT_BLACK << "========" << WHITE);
			int _enemyId = IntInput("Enter the ID of the enemy you would like to fight:", 0, _game.GetEnemiesAmount() - 1);
			if (CombatLoop(_game, _enemyId)) {
				_game.GetPlayer()->AddMoney(_game.GetEnemies()[_enemyId].GetReward());
			}
		}
		else if (_response == "Inventory") _game.GetPlayer()->Inventory();
		else if (_response == "Shop") Shop(_game);
		else if (_response == "Quit") _returnMenu = false;
		else DISPLAY(RED << "Invalid choice!");
	} while (_returnMenu);
}

Game CreateElements() {
	Game _game = Game();
	// Name Health Damages Reward
	_game.AddEnemy(Enemy("Enemy 1", 6, 3, 8));
	_game.AddEnemy(Enemy("Enemy 2", 15, 5, 12));
	// Name Damages Precision Price
	_game.AddWeapon(Weapon("Weapon 1", 10, 50, 10));
	return _game;
}

bool CombatLoop(Game& _game, int _enemyId) {
	bool _shouldLoop = true, _actionLoop = true, _won = false;
	Enemy _enemy = _game.GetEnemies()[_enemyId];
	DISPLAY(BRIGHT_RED << "Start of the fight against " << RED << _enemy.GetName() << BRIGHT_RED << "!");
	_enemy.Reset();
	string _actions[] = { "Attack", "Switch weapon", "Heal" };
	do {
		DISPLAY(WHITE << ">>> Enemy's health: " << _enemy.GetHealth());
		DISPLAY(">>> Your health: " << _game.GetPlayer()->GetHealth());
		DISPLAY(BRIGHT_BLACK << "========");
		DisplayList("Select the action to do:", _actions, 3, true);
		_actionLoop = true;
		do {
			switch (IntInput("Enter the number of the action:", 0, 2)) {
			case 0:
				_actionLoop = false;
				srand(time(NULL));
				if ((rand() % 100) < _game.GetPlayer()->GetHeldWeapon().GetPrecision()) {
					_enemy.ApplyDamages(_game.GetPlayer()->GetHeldWeapon().GetDamages());
					DISPLAY(BRIGHT_GREEN << "You attacked the enemy: " << BRIGHT_RED << _game.GetPlayer()->GetHeldWeapon().GetDamages());
				}
				else DISPLAY(BRIGHT_RED << "You missed the enemy!");
				break;
			case 1:
				_game.GetPlayer()->Inventory();
				_actionLoop = false;
				break;
			case 2:
				if (_game.GetPlayer()->UseHealItem()) _actionLoop = false;
				break;
			default:
				DISPLAY(RED << "Invalid choice!");
				break;
			}
		} while (_actionLoop);
		if (_enemy.IsDead()) _won = true;
		if (!_won) {
			_game.GetPlayer()->ApplyDamages(_enemy.GetDamages());
			DISPLAY(YELLOW << "The enemy attacked you, you lost " << RED << _enemy.GetDamages() << YELLOW << " HP!");
		}
		if (_won || _game.GetPlayer()->IsDead()) _shouldLoop = false;
		system("PAUSE");
		system("cls");
	} while (_shouldLoop);
	if (_won) {
		DISPLAY(BRIGHT_GREEN << "You won the fight!");
		_game.GetPlayer()->FightWon();
	}
	else {
		DISPLAY(RED << "You lost the fight!");
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
		DISPLAY(">>> You have " << _game.GetPlayer()->GetMoney() << " coins!");
		DISPLAY(BRIGHT_BLACK << "========" << WHITE);
		DISPLAY("Available :");
		DISPLAY("-2 => Quit the shop");
		DISPLAY("-1 => Buy a healing potion");
		_game.DisplayWeapons();
		DISPLAY(BRIGHT_BLACK << "========" << WHITE);
		_idChoose = IntInput("Enter the ID of the action you would like to do:", -2, _game.GetWeaponsAmount() - 1);
		if (_idChoose == -2) {
			_wantContinue = false;
			system("cls");
		}
		else if (_idChoose == -1) {
			if (_game.GetPlayer()->GetMoney() < 10) {
				DISPLAY(BRIGHT_RED << "You're poor!");
				system("PAUSE");
				continue;
			}
			_game.GetPlayer()->AddHealItem(1);
			_game.GetPlayer()->RemoveMoney(10);
		}
		else {
			if (_game.GetPlayer()->GetMoney() < _game.GetWeapons()[_idChoose].GetPrice()) {
				DISPLAY(BRIGHT_RED << "You're poor!");
				system("PAUSE");
				continue;
			}
			_game.GetPlayer()->RemoveMoney(_game.GetWeapons()[_idChoose].GetPrice());
			_game.BuyWeapon(_idChoose);
			system("PAUSE");
		}
	} while (_wantContinue);
}

#pragma region Inputs
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
#pragma endregion

#pragma region Displays
void DisplayList(string _text, const string _list[], int _sizeOfList, bool _printIndexes) {
	if (_text != "") DISPLAY(WHITE << _text);
	for (int _i = 0; _i < _sizeOfList; _i++) {
		if (_printIndexes) cout << _i;
		DISPLAY(" => " << _list[_i]);
	}
}
#pragma endregion