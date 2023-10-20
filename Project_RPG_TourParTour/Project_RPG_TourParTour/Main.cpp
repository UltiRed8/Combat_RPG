#include <iostream>
#include <string>

using namespace std;

void DisplayList(string _text, const string _list[], int _sizeOfList, bool _printIndexes);
void Display(string _text);
void DisplayValue(string _text, int _value);
void GameLoop(string* _weapons, string* _enemies);

int main()
{
	string _weapons[_weaponsAmount], _enemies[_enemiesAmount];

	GameLoop(_weapons)
	return 0;
}

//Boucle jeu
void GameLoop(string* _weapons, string* _enemies)
{
	//affiche ce que le joueur peut faire en premier
	Display("Bienvenue dans l'arene !");
	Display("Choisi ton opposant :");
		//quel ennemi veut tu affronter
	DisplayList(_enemis);
		//aller au shop
	Display
	//saisie l'index choisi par User

		//boucle repetition de choix

}



void Display(string _text) 
{
	cout << _text << endl;
}

void DisplayValue(string _text, int _value) 
{
	cout << _text << _value << endl;
}

void DisplayList(string _text, const string _list[], int _sizeOfList, bool _printIndexes) 
{
	if (_text != "") cout << _text << endl;
	for (int _i = 0; _i < _sizeOfList; _i++) 
	{
		if (_printIndexes) cout << _i;
		cout << "- " << _list[_i] << endl;
	}
}