#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <Windows.h>
#include <string>
#include <sstream>

using namespace::std;

int main()
{
	string tab[20000];
	fstream plik;
	int x;
	int klucz[20000] = {};
	int kolizja = 0;

	plik.open("slowa.txt", ios::in);

	for (int i = 0; i < 20000; i++)
	{
		plik >> tab[i];
		//tab[x] = "costam " + to_string(x) + " costam " + to_string(x);
		cout << tab[i];
		//system("pause");
		x = tab[i].length();
	}
	plik.close();




	return 0;
}