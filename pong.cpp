#include <iostream>					//cin / cout
#include "Windows.h"				//GetKeyState
#include "conio.h"					//_getch
#include "stdlib.h"					//rand          //inutilizzato
#include <thread>					//thread / join //inutilizzato
#include <string>					//string

using namespace std;

//Dichiarazione Variabili

int yHome = 0,
    xHome = 0,
    yBall = 10,
    xBall = 10,
    yVisitors = 0,
    xVisitors = 0,
    flag = 0;

unsigned short i, a;

char campo[20][70];

//Prototipi funzioni

void ball();
void visitors();
void home();
void initializeMatrix();


int main() {
	system("cls");
    	initializeMatrix();

	while (true) {
		for (a = 0; a < 20; a++) {              //Stampa Matrice
			for (i = 0; i < 70; i++) {
				cout << campo[a][i];
			}
			cout << endl;
		}

		for (a = 0; a < 20; a++) {              //Reset Matrice
			for (i = 0; i < 70; i++) {
				campo[a][i] = ' ';
			}
		}
		home();
		visitors();
		ball();

		cout << xBall;
		system("cls");
		Sleep(20);
	}
	return 0;
}

//Implementazione funzioni

void ball() {//Funzione per la palla

	campo [yBall][xBall] = '.';
	if (xBall < 61 && flag == 0){
        xBall+=3;
	}
    /*switch(xBall){
        case 61:
            xBall = 62;
        case 62:
            xBall = 63;
        case 63:
            xBall = 64;
    }*/
	if (xBall > 60) {
        flag = 1;
        xBall-=3;
	}
	if (flag == 1) {
        xBall-=3;
	}
    /*if (xBall < 3 && flag == 1) {
        flag = 0;
        xBall += 3;
	}*/
}

//Funzione per il giocatore di casa

void home() {
	if (GetKeyState('S') & 0x8000 && yHome < 16) yHome++; //Pressione Freccia Giù e spostamento in basso
	if (GetKeyState('W') & 0x8000 && yHome > 0) yHome--; //Pressione Freccia Su e spostamento in alto non oltre lo 0 (quindi il bordo della finestra)
	campo[yHome][0] = '|';
	campo[yHome + 1][0]= '|';
	campo[yHome + 2][0] = '|';
	campo[yHome + 3][0] = '|';
}

//Funzione per il giocatore ospite

void visitors() {
	if (GetKeyState(VK_DOWN) & 0x8000 && yVisitors < 16) yVisitors++; //Pressione Freccia Giù e spostamento in basso
	if (GetKeyState(VK_UP) & 0x8000 && yVisitors > 0) yVisitors--; //Pressione Freccia Su e spostamento in alto non oltre lo 0 (quindi il bordo della finestra)
	campo[yVisitors][69] = '|';
	campo[yVisitors + 1][69]= '|';
	campo[yVisitors + 2][69] = '|';
	campo[yVisitors + 3][69] = '|';
}

void initializeMatrix() {

	for (a = 0; a < 20; a++) {                  //Inizializzazione Matrice
			for (i = 0; i < 70; i++) {
				campo[a][i] = ' ';
			}
		}

}
