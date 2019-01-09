// pong.cpp : Questo file contiene la funzione 'main', in cui inizia e termina l'esecuzione del programma.
//
#include "pch.h"
#include <iostream>					//cin / cout
#include "Windows.h"				//GetKeyState
#include "conio.h"					//_getch
#include "stdlib.h"					//rand
#include <thread>					//thread / join

using namespace std;

int yHome = 0, xHome = 0, yBall = 10, xBall = 10, i;

void ball() {
	int var = rand() % 3;
	if (xBall > 0 && yBall > 0) {
		switch (var) {
		case 0:
			xBall++;
			yBall++;
			break;
		case 1:
			xBall--;
			yBall--;
			break;
		case 2:
			xBall++;
			yBall--;
			break;
		case 3:
			xBall--;
			yBall++;
			break;
		}
	}
	for (i = 0; i < yBall; i++) cout << endl;
	for (i = 0; i < yBall; i++) cout << "  ";
	cout << ".";
}

void home() {
	if (GetKeyState(VK_DOWN) & 0x8000) yHome++; //Pressione Freccia Giù e spostamento in basso
	if (GetKeyState(VK_UP) & 0x8000 && yHome > 0) yHome--; //Pressione Freccia Su e spostamento in alto non oltre lo 0 (quindi il bordo della finestra)
	for (i = 0; i < yHome; i++) cout << endl;
	cout << "|" << endl << "|" << endl << "|" << endl << "|";
	_getch();
}

int main() {
	system("cls");
	thread first(home);
	thread second(ball);
	while (1) {
		first.join();
		second.join();
		system("cls");
	}
	return 0;
}


// Per eseguire il programma: CTRL+F5 oppure Debug > Avvia senza eseguire debug
// Per eseguire il debug del programma: F5 oppure Debug > Avvia debug

// Suggerimenti per iniziare: 
//   1. Usare la finestra Esplora soluzioni per aggiungere/gestire i file
//   2. Usare la finestra Team Explorer per connettersi al controllo del codice sorgente
//   3. Usare la finestra di output per visualizzare l'output di compilazione e altri messaggi
//   4. Usare la finestra Elenco errori per visualizzare gli errori
//   5. Passare a Progetto > Aggiungi nuovo elemento per creare nuovi file di codice oppure a Progetto > Aggiungi elemento esistente per aggiungere file di codice esistenti al progetto
//   6. Per aprire di nuovo questo progetto in futuro, passare a File > Apri > Progetto e selezionare il file con estensione sln
