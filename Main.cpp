#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <Windows.h>
#include <string>
#include <sstream>

using namespace::std;

int hashowanieASCII(string slowo)
{
	int numbers = 0;
	for (std::string::size_type i = 0; i < slowo.size(); ++i) {
		numbers += slowo[i];
	}
	return numbers;
}

long long int hashowanie2(string slowo)
{
	long long int hash = 5381;
	for (std::string::size_type i = 0; i < slowo.size(); ++i) {
		hash = hash * 33 + slowo[i];
		hash %= 20000;
	}
	return hash;
}

int licznikkolizji(int zakodowane[], int kluczyk)
{
	int tab[10000];
	int indeks, sukces = 0;
	indeks = kluczyk % 20000;

	while (!sukces) // dopoki nie sukces
	{
		if (!tab[indeks]) // jezeli nie ma kolizji, tzn tablica[indeks]=0
		{
			tab[indeks] = kluczyk; // wpisanie do tablicy
			sukces = 1; // wolne, dalej sie while nie wykona w tym wywolanie funkcji
		}
		else // kolizja!
		{
			indeks++; // szukamy nastepnego wolnego miejsca
			if (indeks >= 103) indeks = 0; // jak dojedzie do konca tablicy to zerujemy indeks
		}

	}

	/*
	for (int i = 0; i < 10000; i++)
	{
		tab[i] = zakodowane[i];
	}

	int kolizja = 0;
	for (int i = 0; i < 10000; i++)
	{
		int b = i;
		int sprawdzenie = tab[i];
		for (int z = b + 1; z < 10000; z++)
		{
			if (tab[i] == tab[z])
			{
				if (tab[z] != 0)
				{
					kolizja++;
					tab[z] = 0;
				}

			}
		}
		cout << "escaped " << i << " for\n";
	}
	return kolizja;
	*/
}

int licznikkolizji2(string zakodowane[])
{


	return 0;
}



int meinhash(string slowo)
{
	int numbers = 0;
	int i = slowo.length();
		numbers = slowo[0];
		numbers += slowo[i-1];
	return numbers % 20000;
}


int main()
{
	string tab[20000];
	int hashed1[20000] = {};
	int hashed2[20000] = {};
	fstream plik;
	int x, wybor;
	int klucz[20000] = {};
	int kolizja = 0, metoda = 0, kluczyk;

	int ilosc = 10000;

	plik.open("slowa.txt", ios::in);

	for (int i = 0; i < 20000; i++)
	{
		plik >> tab[i];
		//tab[x] = "costam " + to_string(x) + " costam " + to_string(x);
		//system("pause");
		x = tab[i].length();
	}
	plik.close();



	fstream zhashowane;
	fstream zhashowane2;
	zhashowane.open("zhashowane.txt", ios::in | ios::out);
	zhashowane2.open("zhashowane2.txt", ios::in | ios::out);

	cout << "podaj metode hashowania: 1 ASCII \t\t 2 No druga no: " << endl;
	cin >> metoda;

	cout << "podaj klucz";
	cin >> kluczyk;
	if (metoda > 2 || metoda < 0)
	{
		while (metoda > 2 || metoda < 0)
		{
			cout << "wybrano nieprawidlowa opcje." << endl;
			cin >> metoda;
		}
	}


	if (metoda == 1)
	{
		cout << "wybrano opcje 1" << endl;
		for (int i = 0; i < ilosc; i++)
		{
			zhashowane << hashowanieASCII(tab[i]) << endl;
		}
		for (int i = 0; i < ilosc; i++)
		{
			hashed1[i] = hashowanieASCII(tab[i]);
		}
		cout << "naliczono " << licznikkolizji(hashed1,kluczyk) << " kolizji " << endl;
	}
	else if (metoda == 2)
	{
		cout << "wybrano opcje 2" << endl;
		for (int i = 0; i < ilosc; i++)
		{
			zhashowane2 << hashowanie2(tab[i]) << endl;
		}
		for (int i = 0; i < ilosc; i++)
		{
			hashed2[i] = hashowanie2(tab[i]);
		}
		cout << "naliczono " << licznikkolizji(hashed2,kluczyk) << " kolizji " << endl;
	}

	//cout << meinhash(tab[345]);


	zhashowane.close();
	zhashowane2.close();
	system("pause");
	return 0;
}




/*
int licznikkolizji(int zakodowane[])
{
int tab[10000];

for (int i = 0; i < 10000; i++)
{
tab[i] = zakodowane[i];
}

int kolizja = 0;
for (int i = 0; i < 10000; i++)
{
int b = i;
int sprawdzenie = tab[i];
for (int z = b + 1; z < 10000; z++)
{
if (tab[i] == tab[z])
{
if (tab[z] != 0)
{
kolizja++;
tab[z] = 0;
}

}
}
cout << "escaped " << i << " for\n";
}
return kolizja;
}


*/