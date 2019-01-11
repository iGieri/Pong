#include <iostream>					//cin / cout
#include "Windows.h"				//GetKeyState
#include "conio.h"					//_getch
#include "stdlib.h"					//rand
#include <thread>					//thread / join
#include <string>					//string

using namespace std;

//Dichiarazione Variabili

int yHome = 0, xHome = 0, yBall = 10, xBall = 10, i, a;
const char* campo[20][20];

//Funzione per la palla
//TODO: Completarla

void ball() {
	campo [yBall][xBall] = ".";
}

//Funzione per il giocatore di casa

void home() {
	campo[0][yHome] = " ";
	if (GetKeyState(VK_DOWN) & 0x8000 && yHome < 16) yHome++; //Pressione Freccia Giù e spostamento in basso
	if (GetKeyState(VK_UP) & 0x8000 && yHome > 0) yHome--; //Pressione Freccia Su e spostamento in alto non oltre lo 0 (quindi il bordo della finestra)
	campo[yHome][0] = "|";
	campo[yHome + 1][0]= "|";
	campo[yHome + 2][0] = "|";
	campo[yHome + 3][0] = "|";
	_getch();
}

int main() {
	system("cls");
	for (a = 0; a < 20; a++) {                  //Inizializzazione Matrice
			for (i = 0; i < 20; i++) {
				campo[a][i] = " ";
			}
		}
	while (1) {
		for (a = 0; a < 20; a++) {              //Stampa Matrice
			for (i = 0; i < 20; i++) {
				cout << campo[a][i];
			}
			cout << endl;
		}
		for (a = 0; a < 20; a++) {              //Reset Matrice
			for (i = 0; i < 20; i++) {
				campo[a][i] = " ";
			}
		}
		home();
		system("cls");
	}
	return 0;
}
