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
		hash =hash * 33 + slowo[i];
	}
	return hash;
}

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
				if (tab[z] == 0)
				{
				
				}
				else
				{
					//cout << tab[i] << endl;
					//cout << tab[z] << endl;
					//cout << i << endl;
					//cout << z << endl;
					kolizja++;
					//cout << "kolizja++" << endl;
					//cout << kolizja;
					//system("pause");
					tab[z] = 0;
				}

			}
			else {}
		}
		cout << "escaped "<< i << " for\n";
	}
	return kolizja;
}


int main()
{
	string tab[20000];
	int hashed1[10000] = {};
	int hashed2[10000] = {};
	fstream plik;
	int x, wybor;
	int klucz[20000] = {};
	int kolizja = 0,metoda=0;

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
		if (metoda > 2 || metoda < 0)
		{
			while(metoda > 2 || metoda < 0)
			{
				cout << "wybrano nieprawidlowa opcje." << endl;
				cin >> metoda;
			}
		}


		if (metoda == 1)
		{
			cout << "wybrano opcje 1" << endl;
			for (int i = 0; i < 10000; i++)
			{
				//hashowanieASCII(tab[i]);
				zhashowane << hashowanieASCII(tab[i]) << endl;
			}
			for (int i = 0; i < 10000; i++)
			{
				hashed1[i] = hashowanieASCII(tab[i]);//<< endl;
			}
			cout << "naliczono " << licznikkolizji(hashed1) << " kolizji " << endl;
		}
		else if (metoda == 2)
		{
			cout << "wybrano opcje 2" << endl;
			for (int i = 0; i < 10000; i++)
			{
				//hashowanie2(tab[i]);
				zhashowane2 << hashowanie2(tab[i]) << endl;
			}
			for (int i = 0; i < 10000; i++)
			{
				hashed2[i] = hashowanie2(tab[i]);
			}
			cout << "naliczono " << licznikkolizji(hashed2) << " kolizji " << endl;
		}



		zhashowane.close();
		zhashowane2.close();
	system("pause");
	return 0;
}