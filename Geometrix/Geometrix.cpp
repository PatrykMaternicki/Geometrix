// Including libaries
#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <Windows.h>
#include <stdlib.h>



//Public class

//Out namespacing std;
using namespace std;
// main Function
void menu(int &A, int paramPosX, int paramPosY,  char &Znak);
void validateTriangle(int &A, int paramPosX, int paramPosY , bool &CorectTriangle, int &errorParam);
void drawTriangle(int A, char Znak, int paramPosX, int paramPosY);
void getSizeConsole(int &paramPosX, int &paramPosY, int &maxParamY, int &maxParamX);
void errorLog(int errorParam);
void gotoxy(int paramPosX, int paramPosY);
void menuFunc();
bool funcOperationTriangle(int &A, char &Znak, int &paramPosX, int &paramPosY, int maxParamY, int maxParamX);
void detect(int A ,int paramFuncNum,int &paramPosX, int &paramPosY, int maxParam);
void Color(int colorNum);
void HideCursor();
void showCursor();


int main()
{
	// Kordynaty punktu X i Y. Typ danych: liczby calkowite.
	int posX = 0;
	int posY = 0;
	

	// Pobieramy czasy przerwania procesora, w celu losowania randomowej liczby.
	srand(time(NULL));

	//Nasz bok a trojkata.
	int a = 0;
	
	//Nasz znak za pomoca ktorego bedziemy rysowac. 
	char znak;
	// Sprawdzamy czy dane od uzytkownika sa prawidlowe.
	bool corectTriangle;
	// Numer bledu.
	int errorNum = 0;
	// Znak do zakonczenia programu lub kontynuacji.
	char endProgram;
	// maks kolumn
	int maxY = 0;
	// maks 
	int maxX = 0;
	// zmienna boolowska, okreslajaca punkt wyjsciowy funkcji 0 lub  1.
	bool initFunc;
	// Rób, dopóki u?ytkownik, nie bedzie chcial wyjsc z programu
	do
	{
		// Rób dopoki dane sa bledne gdy dane, gdy sa poprawne wyjdz z do .
		do
		{
			// Pobieramy kordy srodka naszej konsoli.
			getSizeConsole(posX, posY, maxY, maxX);
			//Pobieramy dane od uzytkownika.
			menu(a, posY, posX, znak);
			// Sprawdzamy czy taki trojkat istnieje czy podane dane pozwola nam rysowac figure.
			validateTriangle(a, posY, posX, corectTriangle, errorNum);
			// Jezeli to prawda, rozpoczynamy kolejne operacje.
			if (corectTriangle == true)
			{
				gotoxy(0, 0);
				// Nasze menu :)
				menuFunc();
				// Przesuwamy na srodek nasz kursor i odejmujemy polowe bokow, by figura rozpoczela sie na srodku rysowac.
				gotoxy(posX - a / 2, posY - a / 2); 
				// Rysujemy trojkat :D
				drawTriangle(a, znak, posX, posY);
				
			}
			else
			{
				// Jednakze, gdy trojkat jest bledny, uruchom funckje sprawdz blad i powiedz uzytkownikowi co zle robi.
				errorLog(errorNum);
			}
		} while (corectTriangle == false);
		// Dopóki u?ytkownik chce przeprowadzac operacje na figurze.
		
		do
		
		{
		// Przejdz do punktu 0,0
		// Inicjujemy menu funckji operacji na figurze.
		initFunc = funcOperationTriangle(a, znak, posX, posY, maxY, maxX);
		// Wykonuje dopoki initFunc zwraca true, false oznacza przejscie do innej linijki.
		} while (initFunc);
		gotoxy(0, 0);
		cout << "Czy chcesz zakonczyc program?" << endl;
		Color(10);
		cout << "TAK-t/T" << endl;
		Color(12);
		cout << "NO-n/N" << endl;
		endProgram = _getch();
		system("cls");
		// Wykonuje dopoki uzytkownik nie wcisnie np: T lub male t.
	} while (endProgram == 'n' || endProgram == 'N');
	return 0;
}



/**********************************************************************************************************************************/
void menu(int &A, int paramPosX, int paramPosY, char &Znak)
{
	char startRand;
	// Funkcja do zmiany koloru.
	HideCursor();
	Color(15);
	cout << "Geo";
	Color(11);
	cout << "metrix" << endl;
	Sleep(2000);
	system("cls");
	Color(15);
	cout << "Program do rysowania trojkata prostokatnego" << endl;
	Sleep(2000);
	system("cls");
	cout << "Program na zaliczenie przedmiotu -";
	Color(11);
	cout <<" Podstawy programowania" << endl;
	Color(15);
	Sleep(2000);
	system("cls");
	cout << "Tworca:";
	Color(11);
	cout << "Maternicki Patryk" << endl;
	Sleep(2000);
	system("cls");
	Color(15);
	cout << "Czy chcesz wylosowac liczby?" << endl;
	Color(10);
	cout << "T/t - TAK" << endl;
	Color(12);
	cout << endl;
	cout << "N/n - NIE" << endl;
	startRand = _getch();
	system("cls");
	Color(15);
	// Jezeli u?ytkownik wybierze opcje tak , wylosuje liczbe dostepnego na poczatek zakresu.
	if (startRand == 't' || startRand == 'T')
	{	
		do
		{
			A = (rand() % paramPosX) + 1;
		} 
		// Oczywi?cie ta liczba nie moze, byc wieksza niz zakres osiY.
		while (paramPosX > paramPosY);
	}
	else
		// Jezeli nie, uzytkownik sam podaje bok.
	{
		Color(15);
		showCursor();
		cout << "Podaj bok trójkata" << endl;
		cin >> A;
	}
	system("cls");
	cout << "Podaj znak z tablicy ASCII za pomoca ktorego narysujesz trojkat" << endl;
	Znak = _getch();
	system("cls");
	cout << "Wartosci bokow trojkata za pomoca ktorych figura bedzie rysowana" << endl;
	HideCursor();
	cout << "Bok a: " << A << endl;
	cout << "Weryfikacja czy taki trojkat istnieje" << endl;
	Sleep(2000);
	system("cls");
}
/**************************************************************************************************************************************/


/********************************************************************************************************************************/

void validateTriangle(int &A, int paramPosX, int paramPosY ,bool &CorectTriangle, int &errorParam)
{
	// W tej funkcji validujemy nasze dane, sprawdzamy czy sa odpowiedniego typu czy nie przekraczaja startowego parametru Y lub X w przypadku gdy user nam poda dane.
	if ( typeid(A) == typeid(int))
	{
		// Je?eli typ danych si? zgadza.
		CorectTriangle = true;
		// Sprawdzamy czy sa w zakresie, jezeli choc jeden warunek zostanie spelniony, przez co niemozliwe bedzie rysowanie figury, przezkaz errorParam = 0 i popros uzytkownika o poprawne dane.
		if (A > paramPosY || A > paramPosX || A == 0 || A < 2)
		{
			CorectTriangle = false;
			errorParam = 0;
		}
		else
		{	
			// Wszystko jest Ok, mozna rysowac trojkat.
			CorectTriangle = true;
		}
	}

}
/******************************************************************************************************/


/*********************************************************************************************************/
// Bardzo wazna funkcja, wrecz najwazniejsza , oprocz rysowania.
//Pobiera wartosci dla srodka X i Yoraz maxX kolumn oraz maxY wierszy, istotne przy walidacji.
//Co wazniejsze, odpalona raz, odswieza bufor danych globalnie (czyli jak zmieniemy rozmiar konsoli posX, posY, maxX, maxY pozycje zostana odswiezone)
void getSizeConsole(int &paramPosX, int &paramPosY, int &maxParamY, int &maxParamX)
{
	CONSOLE_SCREEN_BUFFER_INFO CSBI;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CSBI);
	paramPosX = (CSBI.srWindow.Right - CSBI.srWindow.Left)/2;
	paramPosY = (CSBI.srWindow.Bottom - CSBI.srWindow.Top)/2;
	maxParamY = CSBI.srWindow.Bottom - CSBI.srWindow.Top;
	maxParamX = CSBI.srWindow.Right - CSBI.srWindow.Left;
}
/*****************************************************************************************************************/


/*******************************************************************************************************************/
// Moja funkcja rysujaca :)
void drawTriangle(int A, char Znak ,int paramPosX, int paramPosY)
{
	// pointer wskazuje o ile ma sie przesunac o osX lub osY nasz rysik :)
	for (int pointer = 1 ; pointer <= A; pointer++)
	{
		gotoxy(paramPosX + pointer, paramPosY);
		// Nasz rysik :)
		cout << Znak << endl;
	}
	//Wazne, musimy zaktualizowac nasze dane o przesuniecie osiX o bok a.
	paramPosX = paramPosX + A;
	for (int pointer = 1; pointer <= A-1; pointer++)
	{
		
		gotoxy(paramPosX, paramPosY-pointer);
		cout << Znak << endl;
	}
	paramPosY = paramPosY - A +1;

	
	for (int pointer = 1; pointer <= A-2; pointer++)
	{
		gotoxy(paramPosX - pointer, paramPosY + pointer);
		cout << Znak << endl;
	}

	
}

void errorLog(int errorParam)
{
	// Jaki blad
	switch (errorParam)
	{
	// Pierwszy mozliwy blad do wykonania. Bok A nie jest liczba lub jest za duza.
	case 0:
	{
		system("cls");
		Color(12);
		cout << "Wykryto b?ad, podczas prowadzania danych" << endl;
		cout << endl;
		cout << "Flaga b?edow [corectTriangle] = false " << endl;
		cout << "Flaga bledow [errorNum] = 0" << endl;
		cout << endl;
		cout << "Wielkosc boku A jest za duza" << endl;
		cout << "lub" << endl;
		cout << "Dany podany bok nie jest liczba" << endl;
		Sleep(2000);
		break;
	}
	case 1: {
		cout << "Nie mozna powiekszyc figury" << endl;
		cout << "Flaga bledow [errorNum] = 1" << endl;
		Sleep(2000);
		break;
	}
	case 2: {
		cout << "Nie mozna pomniejszyc figury" << endl;
		cout << "Flaga bledu [errorNum] = 2" << endl;
		Sleep(2000);
		break;
	}
	
	}
	Color(15);
}
/*************************************************************************************************/


/******************************************************************************************************/
// Mowiac najlatwiej, przesuwa nasz kursor w odpowiedni punkt.
void gotoxy(int paramPosX, int paramPosY)
{
	COORD c;
	c.X = paramPosX;
	c.Y = paramPosY;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
/***************************************************************************************************/



/**************************************************************************************************/
void menuFunc()
{
	Color(13);
	cout << "---MENU---" << endl;
	Color(13);
	cout << "'+'";
	Color(15);
	cout<< ": Powiekszanie figury " << endl;
	Color(13);
	cout << "'-'";
	Color(15);
	cout << ": Pomniejszanie figury" << endl;
	Color(13);
	cout << "'c'";
	Color(15);
	cout<< ": Losowa litera" << endl;
	Color(13);
	cout << "'z'";
	Color(15);
	cout << ": Zmiana litery" << endl;
	Color(13);
	cout << "'r'";
	Color(15);
	cout << ":Losowy kolor" << endl;
	cout << endl;
	cout << endl;
	cout << "^  " << endl;
	cout << "| -> | <-" << endl;
	cout << "|    |     : poruszanie figura" << endl;
	cout << "|    v" << endl;
	cout << endl;
	cout << endl;
	Color(10);
	cout << "'ESC'  :Wyjscie z menu" << endl;
	Color(14);
	cout << "'h'    :Wyswietlenie menu" << endl;
	Color(15);
	cout << "----------" << endl;
	Sleep(5000);
	system("cls");
}
/********************************************************************************************************/


/********************************************************************************************************/
//Funkcja umozliwiajace wszystkie mozliwe inicjacje (przesuwanie,kolorowanie,etc)
bool funcOperationTriangle(int &A, char &Znak, int &paramPosX, int &paramPosY, int maxParamY, int maxParamX)
{
	HideCursor();
	// Numer bledu.
	int errorNum;
	char funcChar = _getch();
	// Numer znaku w tablicy ASCII.
	switch (funcChar)
	{




		case 45: // Pomniejszanie i przekazywanie odswiezonego pomariu do main i oczywiscie kontrola kodu w razie gdy zakres zostanie przekroczony.
		{
			if (A <= 2)
			{
				errorNum = 2;
				errorLog(errorNum);
				A++;
			}
			
			gotoxy(paramPosX - A / 2, paramPosY - A / 2);
			A--;
			system("cls");
			drawTriangle(A, Znak, paramPosX, paramPosY);
			break;
		}	
		case 61: // Powiekszanie figury i przekazywanie odswiezonych danych do main i oczywiscie kontrola kodu w razie gdy zakres zostanie przekroczony
		{
			if (A > paramPosY)
			{
				errorNum = 1;
				errorLog(errorNum);
				A--;
			}
			gotoxy(paramPosX - A / 2, paramPosY - A / 2);
			A++;
			system("cls");
			drawTriangle(A, Znak, paramPosX, paramPosY);
			break;
		}
		case 99:
		{
		int randomChar = (rand() % 254) + 1;
		char newChar = randomChar;
		Znak = newChar;
		drawTriangle(A, Znak, paramPosX, paramPosY);
		break;
		}
		// Nowy znak.
		case 122:
		{
		showCursor();
		gotoxy(0, 0);
		cout << "Podaj nowa litere" << endl;
		char newChar = _getch();
		Znak = newChar;
		system("cls");
		drawTriangle(A, Znak, paramPosX, paramPosY);
		break;
		}
		// random Color
		case 114:
		{
			int randomColor = (rand() % 15) + 1;
			Color(randomColor);
			system("cls");
			drawTriangle(A, Znak, paramPosX, paramPosY);
			break;
		}
		//Help
		case 104:
		{
			menuFunc();
			break;
		}
		//Wyjscie.
		case 27:
		{
			return 0;
			break;
		}
		
		// Jezeli zostal wybrany znak specjalny, u mnie -32 a u niektorych 225, sprawdzamy czy bufor danych cos ma dla nas istotnego :)
		case -32:
		{	
			// Jesli jest true to pobieramy co ma dla nas :)
			if (_kbhit())
			{	
				funcChar = _getch();
				switch (funcChar)
				{
					// Wywolujemy odpowiedni case.
					case 72:
					{
						// numer funkcji, odpalajacy odpowiedni case w detect
						// Do gory
						int funcNum = 0;
						system("cls");
						// Zmieniamy miejsce rysowania do main.
						--paramPosY;
						// Sprawdzamy detekcje, czy nasza figura siega juz krawedzi. Jesli korygujemy punkt przesuniecia.
						detect(A, funcNum, paramPosX, paramPosY, maxParamY);
						// Ustawiamy na zaktualizowanym srodku
						gotoxy(paramPosX - A / 2, paramPosY - A / 2);
						// Rysujemy.
						drawTriangle(A, Znak, paramPosX, paramPosY);
						break;
					}
					case 80:
					{
						// Na dol.
						int funcNum = 1;
						system("cls");
						++paramPosY;
						detect(A, funcNum, paramPosX, paramPosY,maxParamY);
						gotoxy(paramPosX - A / 2, paramPosY - A / 2);
						drawTriangle(A, Znak, paramPosX, paramPosY);
						break;
					}
					case 75:
					{	
						// W lewo.

						int funcNum = 2;
						system("cls");
						--paramPosX;
						detect(A, funcNum, paramPosX, paramPosY, maxParamY);
						gotoxy(paramPosX - A / 2, paramPosY - A / 2);
						drawTriangle(A, Znak, paramPosX, paramPosY);
						break;
					}
					case 77:
					{
						// W prawo.
						int funcNum = 3;
						system("cls");
						++paramPosX;
						detect(A, funcNum, paramPosX, paramPosY, maxParamX);
						gotoxy(paramPosX - A / 2, paramPosY - A / 2);
						drawTriangle(A, Znak, paramPosX, paramPosY);
						break;

					}
				


				}
			}
			break;
		}
		
				
	}

	return 1;
}
/*****************************************************************************************************************/


/*******************************************************************************************************************/
// No i najtrudniejsza rzecz w projekcie, detekcja...
// By dokladnie ja wyliczyc potrzebujemy obecne posX i pos Y oraz numer funkcji i max kolumn lub wierszy mozliwych.
void detect(int A, int paramFuncNum, int &paramPosX, int &paramPosY, int maxParam)
{

	switch (paramFuncNum)
	{
		case 0:
		{
			// jezeli jestesmy na gorze to max jaki mozemy przesunac do gory, to o tyle ile bok naszej figury A (wysokosc wynosi), jezeli jest mniejszy posY od bok A, korygujemy.
			if (paramPosY+1 < A)
			{
				paramPosY = paramPosY + 1;
			}
			break;
		}
		case 1:
		{	
			// W dol za to mamy inaczej, gdyz nasz bok lezy poziomo, korygujemy go o to , ze nie moze sie przesunac dalej niz max ilosc kolumn, jezeli probuje cofamy go 1 wyzej.
			if (paramPosY > maxParam)
			{
				paramPosY = paramPosY - 1;
			}
			break;
		}
			// Zauwazmy , ze i ten bok stanowi nie lada problem. Nie mozemy korygowac go o wysokosc, ani o parametrMax. Podeszlem do temtu inaczej
			// przesuwajac caly czas w lewo, w koncu uzyskamy wartosci ujemne, czyli wychodzenie poza konsole. 
			// By to skorygowac, nie pozwolilem posX, przypomne wspolrzedne osiX o wyjscie ponizej 0.
		case 2:
			if (paramPosX+1 < 0)
			{
				++paramPosX;
			}
			break;
		case 3:
			// Tu jeszcze inaczej!
			// teraz nie mamy magicznej granicy, za to pada wartosc maxKolumn.
			// Gdybysmy pozwoli by parametrX rownal sie maxKolumn, moglibysmy spokojnie przesuwac dalej, az figura by zniknela
			// Dopiero wtedy by skorygowal.
			// Dlatego osiX plus poziomy bok A, gdy sa wieksze o maxParam, koryguje. Ten bok A stanowi granice miedzy poczatkiem boku A a krawedzia konsoli
			if (paramPosX+A > maxParam)
			{
				--paramPosX;
			}
			break;
	}
}

/*****************************************************************************************************************/


/*******************************************************************************************************************/
//Funkcja zmieniajaca kolor napisu.
void Color(int colorNum)

{
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOut, colorNum);
}

/*****************************************************************************************************************/


/*******************************************************************************************************************/
// Funckja ukrywajaca kursor
void HideCursor()
{
	HANDLE hOut; 
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO hCCI;
	GetConsoleCursorInfo(hOut, &hCCI);
	hCCI.bVisible = FALSE;
	SetConsoleCursorInfo(hOut, &hCCI);
}
/*****************************************************************************************************************/


/*******************************************************************************************************************/
// Funckja pokazujaca kursor.
void showCursor()
{
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO hCCI;
	GetConsoleCursorInfo(hOut, &hCCI);
	if (hCCI.bVisible != TRUE)
	{
		hCCI.bVisible = TRUE;
		SetConsoleCursorInfo(hOut, &hCCI);
	}
}