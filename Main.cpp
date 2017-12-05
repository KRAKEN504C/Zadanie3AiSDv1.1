#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <Windows.h>
#include <string>
#include <sstream>
#include <time.h>

using namespace::std;

string backup[20000] = {};
int kol1 = 0, kol2 = 0;

int hashowanieASCII(string slowo)
{
	int numbers = 0;
	int x = slowo.length(); 
	for (int i = 0; i < x; i++) {
		numbers += slowo[i];
	}
	return numbers % 20000;
}

int hashowanie2(string slowo)
{
	long long int hash = 5381;
	int x = slowo.length();
	for (int i = 0; i < x; i++) {
		hash = (hash * 33 + slowo[i]) % 20000;
	}
	return hash ;
}

int hashowanieWlasne(string slowo)
{
	int numbers = 0;

	int x = slowo.length();

	numbers = slowo[0] + slowo[x - 1];

	return numbers % 20000;
}

void licznikkolizji(string czysto, int zakodowane)
{
	int sukces = 0;
	while (!sukces)
	{
		if (backup[zakodowane] == "")
		{
			backup[zakodowane] = czysto;
			sukces = 1;
		}
		else
		{
			kol1++;
			zakodowane += kol1;
			if (zakodowane >= 20000) zakodowane = 0;
		}
	}
}

void licznikkolizji2(string czysto, long long int &x1, long long int &x2, int &kol)
{
	kol = 0;
	int sukces = 0;
	while (!sukces)
	{
		//cout << backup[x1] << endl;
		if (backup[x1] == "")
		{
			backup[x1] = czysto;
			sukces = 1;
		}
		else
		{
			kol++;
			x1 += (kol*(x2% 101 +1))%103;
			//cout << x1 << endl;
			if (x1 >= 20000) x1 = 0;
		}
	}

}

int szperacz(string * miss, string slowo)
{
	bool good = false;
	int i = 0;
	while (miss[i] != slowo)
	{
		i++;
	}
	return i + 1;
}

void losowanie(int * token)
{
	int x[20000];
	for (int i = 0; i < 20000; i++)
	{
		x[i] = i;
	}
	for (int i = 0; i < 1000; i++)
	{
		token[i] = rand() % 20000;
		while (x[token[i]] <= 0) { token[i] = rand() % 20000; }
		x[token[i]] -= token[i];
	}

}


int main()
{
	srand(time(NULL));
	string tab[10000];
	long long int hashed[20000] = {};
	//int hashed1[20000] = {};
	//int hashed2[20000] = {};
	//int hashed3[20000] = {};
	fstream plik;
	int xs, wybor;
	int token[1000], kol=0;

	long long int x = 0, y = 0;
	int radius = -1, radiusb = 0;
	char te, st;

	int klucz[20000] = {};
	int kolizja = 0,metoda=0;

	plik.open("slowa.txt", ios::in);


	//wpisanie wybranej ilosci elementow z pliku do tablicy.
	do 
	{
		cout << "wybierz ilosc elementow: 1 - 5000\t 2-7000\t 3-9000" << endl;
		cin >> radius;
	} while (radius<1 || radius >3);

	switch (radius)
	{
	case 1:
		radiusb = 5000;
		break;
	case 2:
		radiusb = 7000;
		break;
	case 3:
		radiusb = 9000;
		break;
	}
	radius = radiusb;

	for (int i = 0; i < 10000; i++)
	{
		plik >> tab[i];
		x = tab[i].length();
	}
	plik.close();

	
	fstream zhashowane;
	zhashowane.open("zhashowane.txt", ios::in | ios::out);

	//wybor metody hashowania

	cout << "podaj metode hashowania: 1 ASCII \t\t 2 No druga no: \t\t 3 no trzecia " << endl;
	cin >> metoda;
		if (metoda > 3 || metoda < 0)
		{
			while(metoda > 3 || metoda < 0)
			{
				cout << "wybrano nieprawidlowa opcje." << endl;
				cin >> metoda;
			}
		}

		if (metoda == 1)
		{
			cout << "wybrano opcje 1" << endl;
			for (int i = 0; i < radius; i++)
			{
				//hashowanieASCII(tab[i]);
				zhashowane << hashowanieASCII(tab[i]) << endl;
			}
			for (int i = 0; i < radius; i++)
			{
				hashed[i] = hashowanieASCII(tab[i]);//<< endl;
			}
		}
		else if (metoda == 2)
		{
			cout << "wybrano opcje 2" << endl;
			for (int i = 0; i < radius; i++)
			{
				//hashowanie2(tab[i]);
				zhashowane << hashowanie2(tab[i]) << endl;
			}
			for (int i = 0; i < radius; i++)
			{
				hashed[i] = hashowanie2(tab[i]);
			}
		}
		else if (metoda == 3)
		{
			cout << "wybrano opcje 3" << endl;
			for (int i = 0; i < radius; i++)
			{
				zhashowane << hashowanieWlasne(tab[i]) << endl;
			}
			for (int i = 0; i < radius; i++)
			{
				hashed[i] = hashowanieWlasne(tab[i]);
			}
		}
		metoda = -1;


		//wybor metody sondowania
		cout << "Podaj metode kolizji: 1 - Sondowanie liniowe\t 2 - Podwojne rozpraszanie" << endl;
		do 
		{
			cin >> metoda;
		} while (metoda < 0 || metoda > 2);


		if (metoda == 1)
		{

			{

				for (int i = 0; i < radius; i++)
				{
					licznikkolizji(tab[i], hashed[i] );
				}
				for (int i = radius; i < radius + 1000; i++)
				{
					licznikkolizji(tab[i], hashed[i]);
				}

			}
		}

		if(metoda == 2)
		{

				{	
				int test = radius;

					for (int i = 0; i < radius; i++)
					{
						y = hashowanieWlasne(tab[i]);
						licznikkolizji2(tab[i], hashed[i], y, kol);
					}
					//cout << "opuszczono 1 petle" << endl;
						for (int i = radius; i < radius + 1000; i++)
						{
							y = hashowanieWlasne(tab[i]);
							licznikkolizji2(tab[i], hashed[i], y, kol);
						}
						//cout << "opuszczono 2 petle" << endl;
				}
			}
		

			//wszystko wykonane zostaje formalnosc. Wynik

			fstream wynik;
			wynik.open("wynik.txt", ios::in | ios::out);

			for (int i = 0; i < 20000; i++)
			{
				wynik << i + 1 << ". " << backup[i] << endl;
			}
			wynik.close();

			//wyznaczenie sredniej liczby wstawien oraz wyszukan

			losowanie(token);
			int sr_wysz[1000];
			int licznik_wysz = 0;
			for (int i = 0; i < 1000; i++)
			{
				sr_wysz[i] = szperacz(backup, backup[token[i]]);
				if (sr_wysz[i] >= 10) licznik_wysz++;
			}
			cout << "Srednia liczba wyszukan dla "<< radius << ": " << licznik_wysz << endl;
			if (metoda == 1) cout << "Srednia ilosc wstawien dla " << radius << " (sondowania liniowego): " << kol1 << endl;
			else cout << "Srednia ilosc wstawien dla " << radius << " (podwojnego rozpraszania): " << kol << endl;


		zhashowane.close();
		wynik.close();

	system("pause");
	return 0;
}



















/*

void test_sondowania(int tablica[], int klucz)
{
	int indeks, sukces = 0;
	indeks = klucz % 103; // wyliczenie indeksu

	while (!sukces) // dopoki nie sukces
	{
		if (!tablica[indeks]) // jezeli nie ma kolizji, tzn tablica[indeks]=0
		{
			tablica[indeks] = klucz; // wpisanie do tablicy
			sukces = 1; // wolne, dalej sie while nie wykona w tym wywolanie funkcji
		}
		else // kolizja!
		{
			indeks++; // szukamy nastepnego wolnego miejsca
			if (indeks >= 103) indeks = 0; // jak dojedzie do konca tablicy to zerujemy indeks
		}
	}
}

void test_podwojne_hashowanie(int tablica[], int klucz)
{
	int indeks, sukces = 0, licznik_kolizji = 0, indeks_bez_kolizji;
	indeks = klucz % 103; // obliczenie indeksu
	indeks_bez_kolizji = indeks; // zapamietanie pierwszego indeksu, potrzebny do wzoru na drugie haszowanie

	while (!sukces) // dopoki nie znajdziemy wolnego miejsca w tablicy
	{
		if (!tablica[indeks]) // jezeli nie ma kolizji
		{
			tablica[indeks] = klucz; // wpisanie klucza pod wyhaszowanym indeksem
			sukces = 1;
		}
		else // kolizja!
		{
			licznik_kolizji++;
			indeks = (indeks_bez_kolizji + licznik_kolizji*(klucz % 101 + 1)) % 103; // haszujemy drugi raz
			if (indeks >= 103) indeks = 0; // jak indeks przekracza rozmiary tablicy, to go zerujemy
		}
	}
}

*/





/*


switch (metoda)
{
case 1:
{

for (int i = 0; i < radius; i++)
{
licznikkolizji(hashed[i], tab[i]);
}
for (int i = radius; i < radius + 1000; i++)
{
licznikkolizji(hashed[i], tab[i]);
}

}
break;

case 2:
{
int test = radius;
string tabtest[10000];
for (int i = 0; i < 10000; i++)
{
tabtest[i] = tab[i];
}

for (int i = 0; i < radius; i++)
{
y = hashowanieWlasne(tab[i]);
licznikkolizji2(tab[i], hashed[i], y, kol);
}
cout << "opuszczono 1 petle" << endl;
for (int i = test; i < test + 1000; i++)
{
cout << "uruchomiono druga petle" << endl;
y = hashowanieWlasne(tabtest[i]);
cout << "Przeszlo y" << endl;
//y = 1;
licznikkolizji2(tab[i], hashed[i], y, kol);
}

}
break;
}


*/











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


*/