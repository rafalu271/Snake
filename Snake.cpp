#include "stdafx.h"
#include <iostream>
#include <conio.h> // _getch() - pobieranie znaków z klawiatury
#include <cstdlib> // system ("CLS") - czyszczenie ekranu
#include <time.h> //losowanie (by by³o bardziej losowe)
#include <windows.h> // sleep()
#include <stdlib.h>

using namespace std;

int szerokosc, wysokosc, szybkosc;
int gora, dol, lewo, prawo;
char pole[35][35];
int wspolzednaXw, wspolzednaYw;
int wspolzednaXj, wspolzednaYj;
int dlugosc = 4, historiaX[10000], historiaY[10000];
int ile = 0;
int klawisz;
char kierunek='p';
char waz = 219, jed = 177, pd = 188, pg = 189, lg = 201, ld = 200, poz = 205, pio = 186;

void idzdoxy (int x, int y)
{
	HANDLE hCon;
	COORD dwPos;

	dwPos.X=x;
	dwPos.Y=y;

	hCon = GetStdHandle (STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hCon, dwPos);

}

int zwymyslaj(int &x)
{
	cout << "Tekst upomnienia" << endl;
	cout << "Jeszcze jedna proba" << endl;
	cin >> x;
	if (x < 5 || x > 35) x = 15;

	return 0;
}


int main()
{
	//WPROWADZENIE ROZMIARU PLANSZY I SZYBKOSCI GRY %%%%%%

	cout << "Podaj szerokosc planszy (od 5 do 35):" << endl;
	cin >> szerokosc;
	if (szerokosc < 5 || szerokosc > 35) zwymyslaj(szerokosc);

	cout << "Podaj wysokosc planszy (od 5 do 35):" << endl;
	cin >> wysokosc;
	if (wysokosc < 5 || wysokosc > 35) zwymyslaj(wysokosc);

	cout << "Podaj szybkosc od 1 do 10" << endl;
	cin >> szybkosc;
	if (szybkosc < 1) szybkosc = 1;
	else if (szybkosc > 10) szybkosc = 10;


	//POBIERANIE KLAWISZY ATERUJACYCH %%%%%%

	cout << "Nacisnij klawisze ktorymi chcesz sterowac" << endl;

	cout << "GORA" << endl;
	gora = _getch();
	if (gora == 224) gora+=_getch();
	else if (gora == 0) gora-=_getch(); 

	cout << "DOL" << endl;
	dol = _getch();
	if (dol == 224) dol+=_getch();
	else if (dol == 0) dol-=_getch();

	cout << "LEWO" << endl;
	lewo = _getch();
	if (lewo == 224) lewo+=_getch();
	else if (lewo == 0) lewo-=_getch(); 

	cout << "PRAWO" << endl;
	prawo = _getch();
	if (prawo == 224) prawo+=_getch();
	else if (prawo == 0) prawo-=_getch(); 

	//NADAJEMY WARTOŒÆ p TABLICY pole
	

	/*ile++;
		historiaX[ile] = wspolzednaXw;
		historiaY[ile] = wspolzednaYw;*/

	for (int i = 0; i < wysokosc; i++)
	{
		for (int j = 0; j < szerokosc; j++)
		{
			pole [j][i] = 'p'; 
		}
	}
	
	srand ((unsigned) time(NULL));
	//losowanie miejsca startu weza

	wspolzednaXw = rand()%szerokosc;
	wspolzednaYw = rand()%wysokosc;

	pole[wspolzednaXw][wspolzednaYw]='w';


	//losowanie miejsca jedzenia
	do{
		wspolzednaXj = rand()%szerokosc;
		wspolzednaYj = rand()%wysokosc;
	} while (pole[wspolzednaXj][wspolzednaYj]!='p');
	
		pole[wspolzednaXj][wspolzednaYj]='j';

	//BUDOWANIE PLANSZY %%%%% (z odswierzaniem)
		system("CLS");

		idzdoxy (0,0);

			// gorna ramka
		cout << lg;
		for (int i=0; i<szerokosc; i++)
		{
			cout << poz << poz;
		}
		cout << pg;

	// boczne ramki
		for (int i= 0; i < wysokosc; i++)
		{
			cout << endl << pio; // lewa ramka

			for (int j = 0; j < szerokosc; j++)
			{
				if (pole[j][i]=='p') cout << "  ";
				else if (pole[j][i]=='w') cout << waz << waz;
				else if (pole[j][i]=='j') cout << jed << jed;
			}
			cout << pio; // prawa ramka
		}

	// dolna ramka
		cout << endl;

		cout << ld;
		for (int i=0; i<szerokosc; i++)
		{
			cout << poz << poz;
		}
		cout << pd;

	// rozpoczecie gry
	for (;;)
	{
			ile++;
		historiaX[ile] = wspolzednaXw;
		historiaY[ile] = wspolzednaYw;

		Sleep(1000/szybkosc); //czekaj przed kolejnum krokiem

		if (_kbhit())
		{
			klawisz = _getch();
			if(klawisz==224) klawisz+=_getch();
			if(klawisz==0) klawisz-=_getch();

			if (klawisz==gora && (kierunek=='l' || kierunek=='p')) kierunek = 'g';
			else if (klawisz==dol && (kierunek=='l' || kierunek=='p')) kierunek = 'd';
			else if (klawisz==lewo && (kierunek=='g' || kierunek=='d')) kierunek = 'l';
			else if (klawisz==prawo && (kierunek=='g' || kierunek=='d')) kierunek = 'p';
		}

		// decyzja o kierunku
		if (kierunek=='g') wspolzednaYw--;
		if (kierunek=='d') wspolzednaYw++;
		if (kierunek=='l') wspolzednaXw--;
		if (kierunek=='p') wspolzednaXw++;

		// przechodzenie przez sciany
		if (wspolzednaXw == szerokosc) wspolzednaXw = 0;
		else if (wspolzednaXw == -1) wspolzednaXw = szerokosc - 1;
		if (wspolzednaYw == wysokosc) wspolzednaYw = 0;
		else if (wspolzednaYw == -1) wspolzednaYw = wysokosc - 1;

		//co jesli wpadnie w siebie
		if (pole[wspolzednaXw][wspolzednaYw]=='w')
		{
			idzdoxy(0,wysokosc+4);
			cout << endl << "KONIEC			dlogosc - " << dlugosc+1;
			break;
		}

		// co jeœli zje jedzenie
		else if (pole[wspolzednaXw][wspolzednaYw]=='j')
		{
			dlugosc++;
			do{
				wspolzednaXj = rand()%szerokosc;
				wspolzednaYj = rand()%wysokosc;
			} while (pole[wspolzednaXj][wspolzednaYj]!='p');
	
			pole[wspolzednaXj][wspolzednaYj]='j';
			idzdoxy(wspolzednaXj*2+1,wspolzednaYj+1);
			cout << jed << jed;
		}

		else
		{
			// kasowanie ogona
			pole[historiaX[ile-dlugosc]][historiaY[ile-dlugosc]] = 'p';
			idzdoxy(historiaX[ile-dlugosc]*2+1,historiaY[ile-dlugosc]+1);
			cout << "  ";
		}
		

		pole[wspolzednaXw][wspolzednaYw]='w';
		idzdoxy(wspolzednaXw*2+1,wspolzednaYw+1); 
		cout << waz << waz;
		
	} //koniec pêtli for

	cout << endl;
	_getch();
	//system ("pause");
	return 0;
}