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
    flag = 0,
    flagRimbalzo = 0,
    movimento = 0;

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
		Sleep(1);
	}
	return 0;
}

//Implementazione funzioni

void ball() {//Funzione per la palla

	campo [yBall][xBall] = '.';
	//Primo Movimento
	if (flagRimbalzo == 0) {
        movimento = rand() % 3;
        flagRimbalzo = 1;
	}
	//Ogni Volta controlla dove deve andare
    switch(movimento){
        case 0:
            xBall++;
            yBall++;
            break;
        case 1:
            xBall--;
            yBall++;
            break;
        case 2:
            xBall++;
            yBall--;
            break;
        case 3:
            xBall--;
            yBall--;
            break;
    }
    //Rimbalzo a lato destro
	if (xBall > 68) {
        switch (rand() % 1) {
            case 0:
                movimento = 3;
                break;
            case 1:
                movimento = 1;
                break;

        }
	}
	//Rimbalzo lato sinistro
	if (xBall < 3) {
        switch (rand() % 1) {
            case 0:
                movimento = 2;
                break;
            case 1:
                movimento = 0;
                break;
        }
	}
	//Rimbalzo sopra
	if (yBall < 3) {
        switch (rand() % 1){
            case 0:
                movimento = 1;
                break;
            case 1:
                movimento = 0;
                break;
        }
	}
	//Rimbalzo sotto
	if (yBall > 17) {
        switch (rand() % 1) {
            case 0:
                movimento = 3;
                break;
            case 1:
                movimento = 1;
        }
	}
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
