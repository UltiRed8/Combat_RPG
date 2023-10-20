#include <iostream>
#include <string>

using namespace std;

void DisplayList(string _text, const string _list[], int _sizeOfList, bool _printIndexes);
void Display(string _text);
void DisplayValue(string _text, int _value);

int main()
{

	return 0;
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