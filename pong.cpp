#include <iostream>					//cin / cout
#include "Windows.h"				//GetKeyState
#include <string>					//string
#include <ctime>          //rand e srand


using namespace std;

//Dichiarazione Variabili

int yHome = 0,          //coordinate X e Y del giocatore di casa
    xHome = 0,
    yBall = 10,         //coordinate X e Y della palla
    xBall = 10,
    yVisitors = 0,      //coordinate X e Y del giocatore ospite
    xVisitors = 0,
    homeScore = 0,      //statistiche per il punteggio
    visitorsScore = 0,
    victory = 5,
    movimento = 0,
    flagRimbalzo = 0,   //Definiamo le caratteristiche del rimbalzo
    flagLato = 0,       //Definiamo il lato di rimbalzo
    flagVisitors = 0,   //Caratteristiche per il single player
    flagGameMode = 0;

unsigned short i, //contatori
               a;

string visitor, //Stringhe per i Nomi
       player,
       gameMode;

char campo[20][70]; //Matrice per il campo

//Prototipi funzioni

void ball();    //funzione palla
void visitors();//funzione per il giocatore ospite
void home();    //funzione per il giocatore di casa
void resetMatrix(); //funzione per l'azzeramento della matrice
void showCursor(bool);//disattivazione del cursore "_"

int main() {
    system("cls");    //stampa della schermata iniziale
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
        system("cls");  //scelta della modalita' di gioco
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
        if(gameMode == "1") flagGameMode = 0; //determiniamo se e' single player o multi player
        else if(gameMode == "2") flagGameMode = 1;

        if (!(gameMode == "1" || gameMode == "2")) continue;
        else break;
    }
    system("cls");  //inserire i nomi dei giocatori
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
        system("cls");    //chiediamo i punti per la vittoria
        cout << "Dopo quanti punti viene assegnata la vittoria? (default 5): ";
        cin >> victory;
        Beep(600,100);
        if(cin.fail()){
            cin.clear();
            cin.ignore(256, '\n');

            continue;
        } else break;
    }
    system("cls");       //eseguiamo le istruzioni per l'inizio del gioco
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

		resetMatrix();      //eseguiamo le istruzioni fondamentali
		home();
		visitors();
		ball();
		cout << player << ": " << homeScore << " " << visitor << ": " << visitorsScore;
		system("cls");


		if(homeScore == victory || visitorsScore == victory) break; //opzioni per la vittoria
	}

	showCursor(true);

	if(homeScore == victory)
        cout << "il vincitore e' " << player << endl; //determiniamo il vincitore
	else
        cout << "il vincitore e' " << visitor << endl;
    Beep(523,1050); //canzone We Are The Champions
    Beep(494,600);
    Beep(523,600);
    Beep(494,600);
    Beep(392,600);
    Beep(330,600);
    Beep(440,600);
    Beep(330,1050);
    system("pause");

	return 0;
}

//Implementazione funzioni

void ball() {//Funzione per la palla

	campo [yBall][xBall] = 'O';
	//Primo Movimento e reset in caso di punto
	if (flagRimbalzo == 0) {
        xBall = 35, yBall = 10;     //facciamo partire la palla sempre dalla stessa coordinata.
        if(flagLato == 0) flagLato = 1;     //invertiamo periodicamente il lato da cui deve partire la palla
        else flagLato = 0;

        if(!flagLato){          //in base al lato decidiamo i due soli movimenti possibili
            if((rand() % 2) == 1) movimento = 0;
            else movimento = 2;
        }
        else {
            if((rand() % 2) == 1) movimento = 1;
            else movimento = 3;
        }
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
        else {  //in caso di punto segnato.
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
        else {  //in caso di punto segnato.
            flagRimbalzo = 0;
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
	    switch(movimento){  //ogni volta controlla dove deve andare
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
	campo[yHome + 2][0] = '|';  //si mette in listening dei comandi di movimento e stampa la barra del giocatore
	campo[yHome + 3][0] = '|';
}

//Funzione per il giocatore ospite

void visitors() {
    if (flagGameMode == 1){
        if (GetKeyState(VK_DOWN) & 0x8000 && yVisitors < 16) yVisitors++; //Pressione Freccia Giù e spostamento in basso
        if (GetKeyState(VK_UP) & 0x8000 && yVisitors > 0) yVisitors--; //Pressione Freccia Su e spostamento in alto non oltre lo 0 (quindi il bordo della finestra)
    }
    else {  //funzione di movimento per il singleplayer
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
    campo[yVisitors + 2][69] = '|'; //stampa la barra del giocatore
    campo[yVisitors + 3][69] = '|';
}

 //Funzione per il reset Matrice

void resetMatrix() {

	for (a = 0; a < 20; a++) {
			for (i = 0; i < 70; i++) {
				campo[a][i] = ' ';
			}
		}

}

//Funzione per il controllo del cursore della console

void showCursor(bool visible) {
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = visible;
    SetConsoleCursorInfo(out, &cursorInfo);
}
