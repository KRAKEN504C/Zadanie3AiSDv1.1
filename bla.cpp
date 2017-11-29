#include <iostream>

using namespace std;

void sondowanie(int tablica[], int klucz);

int main()
{
	int tablica[103] = { 0 }, n, klucz;

	cout << "Podaj n: ";
	cin >> n;

	for (int i = 0; i<103;i++)
	{
		cout << "Podaj element nr: " << i + 1 << ": ";
		cin >> klucz;
		sondowanie(tablica, klucz); // umieszczamy klucz w wyhaszowanym indeksie tablicy
	}

	for (int j = 0; j<103; j++) // po hashowaniu, wypisujemy tablice
	{
		cout << tablica[j] << ", ";
	}
	return 0;
}


void sondowanie(int tablica[], int klucz)

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