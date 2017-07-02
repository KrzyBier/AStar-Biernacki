// Biernacki Astar.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <math.h>
using namespace std;

bool wyswietlZawartoscPliku(std::string sNazwaPliku)
{
	std::ifstream plik;
	plik.open(sNazwaPliku.c_str());
	if (!plik.good())
		return false;

	std::string wiersz;
	while (std::getline(plik, wiersz))
		std::cout << wiersz << std::endl;

	plik.close();
	return true;
}

void wypiszTab(int tablicaDoWypis[20][20] ) {
	for (int i = 19; i >= 0 ; i--)
	{
		for (int j = 0; j < 20; j++)
		{
			std::cout << tablicaDoWypis[i][j] << " ";
		}
		std::cout << endl;
	}
	std::cout << endl;
}

double heurestykaEuklidesa(double pozX, double pozY, int g) {
	
	double h = sqrt((pow((pozX - 5), 2) + pow((pozY - 4), 2)));

	return h;
}


struct droga {
	int pozx;
	int pozy;
	int rodzicX;
	int rodzicY;
	double h;
	double gkoszt;
};

int wyszukajMinH(vector<droga> listaOtwarta) {
	double minF = listaOtwarta[0].h + listaOtwarta[0].gkoszt;
	int iterator = 0;

	for (int j = 0; j < listaOtwarta.size(); j++)
	{
		if (minF > listaOtwarta[j].h + + listaOtwarta[j].gkoszt)
		{
			minF = listaOtwarta[j].h + listaOtwarta[j].gkoszt;
			iterator = j;
		}
	}
	return iterator;
};

bool przeszukajListeZamknieta(vector<droga> listaZamknieta, droga obiekt) {

	for (size_t i = 0; i < listaZamknieta.size(); i++)
	{
		if ((listaZamknieta[i].pozy == obiekt.pozx) && (listaZamknieta[i].pozx == obiekt.pozx))
		{
			return false;
		}
	}
	return true;
};

void przeszukajListe(vector<droga> listaZam, vector <droga> listaOt, droga obiekt, bool &dol, bool &lewa, bool &gora, bool &prawa) {
	dol = lewa = gora = prawa = false;
	for (size_t i = 0; i < listaZam.size(); i++)
	{
		//w dól
		if (listaZam[i].pozy == obiekt.rodzicY - 1 && listaZam[i].pozx == obiekt.rodzicX)
		{
			dol = true;
		}
		 
		// w lewo
		if (listaZam[i].pozy == obiekt.rodzicY && listaZam[i].pozx == obiekt.rodzicX - 1)
		{
			lewa = true;
		}

		// w gore
		if (listaZam[i].pozy == obiekt.rodzicY + 1 && listaZam[i].pozx == obiekt.rodzicX)
		{
			gora = true;
		}

		// w prawo
		if (listaZam[i].pozy == obiekt.rodzicY && listaZam[i].pozx == obiekt.rodzicX + 1)
		{
			prawa = true;
		}
				
	}

	for (size_t j = 0; j < listaOt.size(); j++)
	{
		//w dól
		if (listaOt[j].pozy == obiekt.rodzicY - 1 && listaOt[j].pozx == obiekt.rodzicX)
		{
			dol = true;
		}

		// w lewo
		if (listaOt[j].pozy == obiekt.rodzicY && listaOt[j].pozx == obiekt.rodzicX - 1)
		{
			lewa = true;
		}

		// w gore
		if (listaOt[j].pozy == obiekt.rodzicY + 1 && listaOt[j].pozx == obiekt.rodzicX)
		{
			gora = true;
		}

		// w prawo
		if (listaOt[j].pozy == obiekt.rodzicY && listaOt[j].pozx == obiekt.rodzicX + 1)
		{
			prawa = true;
		}
	}

	
};


void nowePolaOtwarta(droga & obiekt, vector<droga> & listaOtwarta, int plansza[20][20], vector<droga>  & listaZamknieta) 
{ 

	bool dol = false, lewa = false, gora = false, prawa = false;
	
	przeszukajListe(listaZamknieta, listaOtwarta, obiekt, dol, lewa, gora, prawa);

	// obliczam heurestyke w dół // 
	if (!(obiekt.rodzicY - 1 < 0))
		if (!(plansza[obiekt.rodzicY - 1][obiekt.rodzicX] == 5) && !(dol))
		{
			obiekt.pozx = obiekt.pozx;
			obiekt.pozy = obiekt.pozy - 1; 
			obiekt.h = heurestykaEuklidesa(obiekt.pozx, obiekt.pozy, obiekt.gkoszt);
			listaOtwarta.push_back(obiekt);
		}

	//obliczam pierwsza heurestyke w lewo

	if (!(obiekt.rodzicX - 1 < 0))
		if (!(plansza[obiekt.rodzicY][obiekt.rodzicX - 1] == 5) && !(lewa))
		{
			obiekt.pozx = obiekt.rodzicX - 1;
			obiekt.pozy = obiekt.rodzicY;
			obiekt.h = heurestykaEuklidesa(obiekt.pozx, obiekt.pozy, obiekt.gkoszt);
			listaOtwarta.push_back(obiekt);
		}

	//obliczam pierwsza heurestyke w górę

	if (!(obiekt.rodzicY + 1 > 19) && !gora)
		if (!(plansza[obiekt.rodzicY + 1][obiekt.rodzicX] == 5))
		{
			obiekt.pozx = obiekt.rodzicX; // <----- jak tutaj
			obiekt.pozy = obiekt.rodzicY + 1;
			obiekt.h = heurestykaEuklidesa(obiekt.pozx, obiekt.pozy, obiekt.gkoszt);
			listaOtwarta.push_back(obiekt);
		}

	// obliczam pierwszą heurestykę w prawo

	if (!(obiekt.rodzicX + 1 > 19) && !(prawa))
		if (!(plansza[obiekt.rodzicY][obiekt.rodzicX + 1] == 5))
		{
			obiekt.pozx = obiekt.rodzicX + 1;
			obiekt.pozy = obiekt.rodzicY;
			obiekt.h = heurestykaEuklidesa(obiekt.pozx, obiekt.pozy, obiekt.gkoszt);
			listaOtwarta.push_back(obiekt);
		}
};

int szukajRodzicaIteratora(vector<droga>  & listaZamknieta, int rodzicX, int rodzicY)
{
	for (size_t i = 0; i < listaZamknieta.size(); i++)
	{
		if (listaZamknieta[i].pozx == rodzicX && listaZamknieta[i].pozy == rodzicY)
			return i;
	}
};



int main()
{


	const int y = 20;
	const int x = 20;
	int i = 0, j = 0, k = 0, dl;
	string dane;
	char znak;
	int plansza[y][x];
	bool czyJest; 

	//wczytywanie mapy
	fstream plik;
	plik.open("grid.txt", ios::in);
	if (plik.good() == true)
	{
		j = y - 1;
		do {
			getline(plik, dane);
			dl = dane.length();
			for (k = 0; k < dl; k++)
			{

				znak = dane[k];
				if (znak != ' ')
					plansza[j][i++] = znak - '0';

			}
			i = 0;
			j--;
		} while (!plik.eof());

		plik.close();

	}
	else 
		std::cout << "plik nie zostal otwarty" << endl;



	if (plansza[0][0] != 5 && plansza[19][19] != 5)
	{
		plansza[0][0] = 3; // [y][x] START
		plansza[19][19] = 99; // [Y][X] CEL

		wypiszTab(plansza);

		//inicjalizacja list otwartych i zamknietych
		vector<droga> listaZamknieta;
		vector<droga> listaOtwarta;

		//inicjalizuje start
		droga obiekt;
		obiekt.pozx = 0;
		obiekt.pozy = 0;
		obiekt.gkoszt = 0;
		obiekt.rodzicX = 0;
		obiekt.rodzicY = 0;

		listaZamknieta.push_back(obiekt);

		// dodajemy poczatkowy koszt
		obiekt.gkoszt = obiekt.gkoszt + 1;

		nowePolaOtwarta(obiekt, listaOtwarta, plansza, listaZamknieta);

		//przeszukuje najmniejszej wartosci

		int iterator = wyszukajMinH(listaOtwarta);

		//nastepna heurestyka 

		obiekt.rodzicX = listaOtwarta[iterator].pozx;
		obiekt.rodzicY = listaOtwarta[iterator].pozy;
		obiekt.pozx = listaOtwarta[iterator].pozx;
		obiekt.pozy = listaOtwarta[iterator].pozy;
		obiekt.h = listaOtwarta[iterator].h;
		obiekt.gkoszt = listaOtwarta[iterator].gkoszt + 1;

		//przerzucanie do list
		listaZamknieta.push_back(listaOtwarta[iterator]);
		listaOtwarta.erase(listaOtwarta.begin() + iterator);

		bool flaga = true;

		do {

			nowePolaOtwarta(obiekt, listaOtwarta, plansza, listaZamknieta);
			
			if (listaOtwarta.size() == 0)
			{
				cout << "Nie mozna dotrzec do celu" << endl;
				break;
			}
			iterator = wyszukajMinH(listaOtwarta);


			obiekt.rodzicX = listaOtwarta[iterator].pozx;
			obiekt.rodzicY = listaOtwarta[iterator].pozy;
			obiekt.pozx = listaOtwarta[iterator].pozx;
			obiekt.pozy = listaOtwarta[iterator].pozy;
			obiekt.h = listaOtwarta[iterator].h;
			obiekt.gkoszt = listaOtwarta[iterator].gkoszt + 1;

			listaZamknieta.push_back(listaOtwarta[iterator]);
			
			if (listaOtwarta.size() == 0)
			{
				flaga = false;
				cout << "nie mozna dojsc do celu" << endl;
			}
			listaOtwarta.erase(listaOtwarta.begin() + iterator);


			if (listaZamknieta.back().pozx == 19 && listaZamknieta.back().pozy == 19)
			{
				cout << "udalo sie!" << endl;
				cout << "koszt drogi to: " << listaZamknieta.back().gkoszt << endl;

				flaga = false;

				int k = listaZamknieta.size() - 1;
				int l = k;
				plansza[listaZamknieta[l].rodzicY][listaZamknieta[l].rodzicX] = 3;
				do
				{
					k = szukajRodzicaIteratora(listaZamknieta, listaZamknieta[l].rodzicX, listaZamknieta[l].rodzicY);
					l = k;
					plansza[listaZamknieta[l].rodzicY][listaZamknieta[l].rodzicX] = 3;
				} while (!(listaZamknieta[l].rodzicX == 0 && listaZamknieta[l].rodzicY == 0));
				wypiszTab(plansza);
				cout << endl;
				cout << "OTO NAJKROTSZA DROGA" << endl;
				getchar();
			}


		} while (flaga);
	}
	else
	{
		cout << "napotkano przeszkode na starcie bądz na mecie" << endl;
	}


	getchar();

    return 0;
}

