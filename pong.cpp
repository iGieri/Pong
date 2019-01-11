#include <iostream>					//cin / cout
#include "Windows.h"				//GetKeyState
#include "conio.h"					//_getch
#include "stdlib.h"					//rand
#include <thread>					//thread / join
#include <string>					//string

using namespace std;

int yHome = 0, xHome = 0, yBall = 10, xBall = 10, i, a;
const char* campo[20][20];

void ball() {
	campo [yBall][xBall] = ".";
}

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
	while (1) {
		home();
		for (a = 0; a < 20; a++) {
			for (i = 0; i < 20; i++) {
				cout << campo[a][i];
			}
			cout << endl;
		}
		//system("cls");
	}
	return 0;
}

