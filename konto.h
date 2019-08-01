/****************************************************************
 *  konto.h
 *
 *  Autor: Michael R Bzdusek II
 *  Datum: 24.07.19. Copyright © 2019
 *
 *  Beschreibung
 *  Wie eine Bank kann man aber Geld einzahlen oder Geld abheben.
 *      Man kann auch den Kontostand sehen.
 *
 *
 ****************************************************************/

#ifndef konto_h
#define konto_h

int hauptProgramm();
int zweiteMen();
void clearScreen();
void kontostand();
void abheben();
void einzahlen();
void programmSwitch(int wahl);
void konto();
void neu();


#endif /* konto_h */
