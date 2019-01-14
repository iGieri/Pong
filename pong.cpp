#include <iostream>					//cin / cout
#include "Windows.h"				//GetKeyState
#include "conio.h"					//_getch
#include <cstdlib>					//rand          //inutilizzato
#include <thread>					//thread / join //inutilizzato
#include <string>					//string
#include <ctime>
#include "stdlib.h"


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
    flagLato = 0,
    homeScore = 0,
    visitorsScore = 0,
    victory = 5,
    movimento = 0,
    flagVisitors = 0,
    flagGameMode = 0;

unsigned short i, a;

string visitor, player, gameMode;

char campo[20][70];

//Prototipi funzioni

void ball();
void visitors();
void home();
void resetMatrix();
void showCursor(bool);

int main() {
    system("cls");
    cout << "___________________________________________________" << endl;
    cout << "|                                                 |" << endl;
    cout << "|                  (Ping) Pong                    |" << endl;
    cout << "|                                                 |" << endl;
    cout << "|                 Sviluppato da :                 |" << endl;
    cout << "|                                                 |" << endl;
    cout << "|                Federico Gerardi                 |" << endl;
    cout << "|                        &                        |" << endl;
    cout << "|                Gabriele Onorato                 |" << endl;
    cout << "|                                                 |" << endl;
    cout << "|_________________________________________________|" << endl;
    system("pause");
    Beep(600,100);
    while (true) {
        system("cls");
        cout << "___________________________________________________" << endl;
        cout << "|                                                 |" << endl;
        cout << "|               Modalita' di Gioco:               |" << endl;
        cout << "|                                                 |" << endl;
        cout << "|                1) Single Player                 |" << endl;
        cout << "|                                                 |" << endl;
        cout << "|                2) Multi Player                  |" << endl;
        cout << "|                                                 |" << endl;
        cout << "|_________________________________________________|" << endl;
        cout << endl << "Inserisci la modalita' di gioco (Es. 1 o 2) --> ";
        cin >> gameMode;
        Beep(600,100);
        if(gameMode == "1") flagGameMode = 0;
        else if(gameMode == "2") flagGameMode = 1;

        if (!(gameMode == "1" || gameMode == "2")) continue;
        else break;
    }
    system("cls");
    cout << "Inserire il nome del giocatore di casa: ";
    cin >> player;
    Beep(600,100);
    if (flagGameMode == 1){
        cout << "Inserire il nome del giocatore esterno: ";
        cin >> visitor;
        Beep(600,100);
    }
    else {
        visitor = "Visitor";
    }
    while(true) {
        system("cls");
        cout << "Dopo quanti punti viene assegnata la vittoria? (default 5): ";
        cin >> victory;
        Beep(600,100);
        if(cin.fail()){
            cin.clear();
            cin.ignore(256, '\n');

            continue;
        } else break;
    }
	system("cls");
    resetMatrix();
    showCursor(false);
    srand(time(0));

	while (true) {
		for (a = 0; a < 20; a++) {              //Stampa Matrice
			for (i = 0; i < 70; i++) {
				cout << campo[a][i];
			}
			cout << endl;
		}

		resetMatrix();
		home();
		visitors();
		ball();
		cout << player << ": " << homeScore << " " << visitor << ": " << visitorsScore;
		system("cls");


		if(homeScore == victory || visitorsScore == victory) break;
	}

	showCursor(true);

	if(homeScore == victory)
        cout << "il vincitore e' " << player << endl;
	else
        cout << "il vincitore e' " << visitor << endl;

    system("pause");

	return 0;
}

//Implementazione funzioni

void ball() {//Funzione per la palla

	campo [yBall][xBall] = 'O';
	//Primo Movimento
	if (flagRimbalzo == 0) {
        xBall = 35, yBall = 10;
        movimento = rand() % 3;
        flagRimbalzo = 1;
	}
	//Ogni Volta controlla dove deve andare
    //Rimbalzo a lato destro
	if (xBall > 68) {
        if(campo[yBall +1][xBall] == '|'|| (yBall +1) == (yVisitors -1) || (yBall +1) == (yVisitors +4)){
            flagLato = 1;
            movimento = 1;
            Beep(600,40);
        }
        else {
            movimento = 0;
            flagRimbalzo = 0;
            homeScore++;
            Beep(1000,70);
        }
	}
	//Rimbalzo lato sinistro
	if (xBall < 1) {
        if(campo[yBall -1][xBall] == '|' || (yBall -1) == (yHome -1) || (yBall -1) == (yHome +4)){
            flagLato = 0;
            movimento = 0;
            Beep(600,40);
        }
        else {
            flagRimbalzo = 0;
            movimento = 0;
            visitorsScore++;
            Beep(1000,70);
        }

	}
	//Rimbalzo sopra
	if (yBall < 2) {
        if(!flagLato)
            movimento = 0;
        else
            movimento = 1;
        Beep(600,40);
    }
	//Rimbalzo sotto
	if (yBall > 17) {
        if(!flagLato)
            movimento = 2;
        else
            movimento = 3;
        Beep(600,40);


	}
	    switch(movimento){
        case 0: //diagonale destra su
            xBall++;
            yBall++;
            break;
        case 1: //diagonale sinistra su
            xBall--;
            yBall++;
            break;
        case 2: //diagonale destra giu
            xBall++;
            yBall--;
            break;
        case 3: //diagonale sinistra giu
            xBall--;
            yBall--;
            break;
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
    if (flagGameMode == 1){
        if (GetKeyState(VK_DOWN) & 0x8000 && yVisitors < 16) yVisitors++; //Pressione Freccia Giù e spostamento in basso
        if (GetKeyState(VK_UP) & 0x8000 && yVisitors > 0) yVisitors--; //Pressione Freccia Su e spostamento in alto non oltre lo 0 (quindi il bordo della finestra)
    }
    else {
        if (yVisitors < 14 && flagVisitors == 0){
            yVisitors++;
        }
        if (yVisitors > 13) {
            flagVisitors = 1;
            yVisitors--;
        }
        if (flagVisitors == 1) {
            yVisitors--;
        }
        if (yVisitors < 3) {
            flagVisitors = 0;
        }
    }
    campo[yVisitors][69] = '|';
    campo[yVisitors + 1][69]= '|';
    campo[yVisitors + 2][69] = '|';
    campo[yVisitors + 3][69] = '|';
}

void resetMatrix() {

	for (a = 0; a < 20; a++) {                  //Inizializzazione Matrice
			for (i = 0; i < 70; i++) {
				campo[a][i] = ' ';
			}
		}

}

void showCursor(bool visible) {
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = visible;
    SetConsoleCursorInfo(out, &cursorInfo);
}
