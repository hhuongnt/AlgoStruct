
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <string.h>

using namespace std;


#include <stdlib.h>
#include <dos.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include <ctime>

const int Enter = 13;
const int dong =10;
const int cot = 50 ;
const int Up = 72;
const int Down = 80;
const int Right = 77;
const int Left = 75;
const int ESC = 27;
const int DEL = 83;
const int Insert = 82;
const int Home = 71;
const int PgUp = 73;
const int PgDn = 81;
const int End = 79;
const int BackSpace = 8;


void gotoxy(short x,short y)
{
        HANDLE hConsoleOutput;
        COORD Cursor_an_Pos = { x,y};
        hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleCursorPosition(hConsoleOutput , Cursor_an_Pos);
}  

int wherex( void )
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
    return screen_buffer_info.dwCursorPosition.X;
}

int wherey( void )
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
    return screen_buffer_info.dwCursorPosition.Y;
}
void clreol( ) {
COORD coord;
DWORD written;
CONSOLE_SCREEN_BUFFER_INFO info;
GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
coord.X = info.dwCursorPosition.X;
coord.Y = info.dwCursorPosition.Y;
FillConsoleOutputCharacter (GetStdHandle(STD_OUTPUT_HANDLE), ' ',
  info.dwSize.X - info.dwCursorPosition.X * info.dwCursorPosition.Y, coord, &written);
gotoxy (info.dwCursorPosition.X , info.dwCursorPosition.Y );
}

void SetColor(WORD color)
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

    WORD wAttributes = screen_buffer_info.wAttributes;
    color &= 0x000f;
    wAttributes &= 0xfff0;
    wAttributes |= color;

    SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
void SetBGColor(WORD color)
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

    WORD wAttributes = screen_buffer_info.wAttributes;
    color &= 0x000f;
    color <<= 4;
    wAttributes &= 0xff0f;
    wAttributes |= color;

    SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
void clrscr() {
	system("cls");
}

void Normal () {
	SetColor(15);
	SetBGColor(0);
}
void HighLight () {
	SetColor(15);
	SetBGColor(2);
}


int MenuDong(char td [][100],int so_item){
  Normal();
  system("cls");   int chon =0;
  int i; 
  for ( i=0; i< so_item ; i++)
  { gotoxy(cot, dong +i);
    cout << td[i];
  }
  HighLight();
  gotoxy(cot,dong+chon);
  cout << td[chon];
  char kytu;
do {
  kytu = getch();
  if (kytu==-32) kytu = getch();
  switch (kytu) {
    case Up :if (chon >0)
  			  {
  		        Normal();
              	gotoxy(cot,dong+chon);cout << td[chon];
              	chon --;
              	HighLight();
              	gotoxy(cot,dong+chon); 	cout << td[chon];  				
  			  }
  			  break;
  	case Down :if (chon+1 <so_item)
  			  {
  		        Normal();
              	gotoxy(cot,dong+chon);	cout << td[chon];
              	chon ++;
              	HighLight();
              	gotoxy(cot,dong+chon); 	cout << td[chon];
  				
  			  }
  			  break;
  	
  	case Enter : return chon+1;
  }  // end switch
  } while (true);
}




