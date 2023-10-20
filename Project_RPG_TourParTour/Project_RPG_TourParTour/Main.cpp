#include <iostream>
#include <string>

using namespace std;

void DisplayList(string _text, const string _list[], int _sizeOfList, bool _printIndexes);
void Display(string _text);
void DisplayValue(string _text, int _value);
void GameLoop();

int main()
{
	//string _weapons[_weaponsAmount], _enemies[_enemiesAmount];
	Display("BIENVENUE DANS L'ARENE !");
	GameLoop();
	return 0;
}

//Boucle jeu
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