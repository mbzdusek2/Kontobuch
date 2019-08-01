/****************************************************************
 *  konto.cpp
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

#include <stdio.h>
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstdlib>
#include <limits>
#include "konto.h"


using namespace std;

// Hauptmenü
string hauptMenTitel ("Wilkommen bei Kontobuch\n\n");
string hauptMenNull ("1) Neues Konto eröffnen.\n");
string hauptMenEins ("2) Kontobuch öffnen\n");
string hauptMenZwei ("3) Konto schließen\n");
string hauptMenDrei ("4) Programm beenden\n");

string menNull ("1) Geld einzahlen\n");
string menEins ("2) Geld abheben\n");
string menZwei ("3) Kontostand\n");
string menDrei ("4) Konto Abmelden\n");

// Neues Konto
string neuesKontoNull ("NEUES KONTO ERÖFFNEN\n\n");
string neuesKontoEins ("Name des Kontos bitte schreiben\n");

// Konto öffnen
string kontoNull ("KONTO ÖFFNEN\n\n");
string kontoEins ("Schreiben Sie bitte den Name des Kontos\n");

// Einzahlen
string einNull ("GELD EINZAHLEN\n\n");
string eNull ("Schreiben Sie \"0\" wenn Sie keine haben.\n");
string einEins ("Wie viele Pennies haben Sie?\n");
string einZwei ("Wie viele Nickels haben Sie?\n");
string einDrei ("Wie viele Dimes haben Sie?\n");
string einVier ("Wie viele Quarters haben Sie?\n");
string einFnf ("Wie viele Dollars haben Sie?\n");

string abNull("GELD ABHEBEN\n\n");
string abEins ("Wie viel Geld möchten Sie abheben?\n");

// Konto Löschen
string kLoeschenNull ("Konto Schließen\n\n");
string kLoeschenEins ("Schreiben Sie bitte den Name des Kontos, das Sie schließen möchten\n");

// Nachrichten
string fehler("\nDie Eingabe stimmt doch nicht. Bitte versuchen Sie noch einmal.\n");
string dateiFehler ("\nKonto exisitert doch nicht!. Versuchen Sie bitte noch einmal\n");

enum wFrage: char { ja = 'j', Ja = 'J', nein = 'n', Nein = 'N', };

string dateiName = " ";
string dateiNameEins (".bank");
double penny = 0.01;
double nickel = 0.05;
double dime = 0.10;
double quarter = 0.25;
double usd = 1.00;


void clearScreen()
{
    cout << string(100, '\n');
}

void abheben()
{

    ofstream datei(dateiName.c_str(), ios::out | ios::app);
    
    double betrag;
    int len = int (abNull.length());
    if (len % 2 == 0) { abNull += " "; }
    cout << setfill(' ') << setw((45 / 2) + len / 2) << right
         << abNull;
    cout << abEins;
    cin  >> betrag;
    if (cin.fail())
    { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cout << fehler; abheben(); }
    
    if (!datei) { cout << fehler; zweiteMen(); }
    
    datei.setf(ios::fixed);
    datei.setf(ios::showpoint);
    datei << "Abgehoben " << ' ' << setprecision(2) << '-' << betrag << endl;
    datei.close();
    
    cout << setfill('*') << setw(45) << "*" << endl;
    zweiteMen();
}

void einzahlen()
{

    ofstream datei(dateiName.c_str(), ios::out | ios::app);
    
    double pny = 0, nkl = 0, dm = 0, qtr = 0, dlr = 0;
    double betrag;
    int len = int (einNull.length());
    
    if (len % 2 == 0) { einNull += " "; }
    
    cout << setfill(' ') << setw((45/2) + len/2) << right
         << einNull;
    cout << eNull << einEins;
    cin >> pny;
    if (cin.fail())
    { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cout << fehler; einzahlen(); }
    pny *= penny;
    
    cout << einZwei;
    cin >> nkl;
    if (cin.fail())
    { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cout << fehler; einzahlen(); }
    nkl *= nickel;
    
    cout << einDrei;
    cin >> dm;
    if (cin.fail())
    { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cout << fehler; einzahlen(); }
    dm *= dime;
    
    cout << einVier;
    cin >> qtr;
    if (cin.fail())
    { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cout << fehler; einzahlen(); }
    qtr *= quarter;
    
    cout << einFnf;
    cin >> dlr;
    if (cin.fail())
    { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); cout << fehler; einzahlen(); }
    dlr *= usd;
    betrag = pny + nkl + dm + qtr + dlr;
    
    if (datei.fail()) { cout << fehler; zweiteMen(); }
    datei.setf(ios::fixed);
    datei.setf(ios::showpoint);
    datei << "Eingezahlt " << ' ' << setprecision(2) << betrag << endl;
    datei.close();
    
    cout << setfill('*') << setw(45) << "*" << endl;
    zweiteMen();
}

void kontostand()
{
    ifstream datei(dateiName.c_str());
    string beschreibung;
    double betrag = 0.00;
    double nBetrag = 0.00;
    
    //if (datei.fail()) {cerr << dateiFehler; konto();}
    
    while (datei >> beschreibung >> betrag)
    {
//        cout.setf(ios::fixed);
//        cout.setf(ios::showpoint);
//        cout << setprecision(2) << betrag << endl;
        nBetrag += betrag;
    }
    
    datei.close();
    cout.setf(ios::fixed);
    cout << "\nSaldo des laufenden Kontos: " << setprecision(2) << nBetrag << "$" << endl << endl;
    
    cout << setfill('*') << setw(45) << "*" << endl;
    zweiteMen();
}

void neu()
{
    ofstream datei;
    int len = int (neuesKontoNull.length());
    if (len % 2 == 0) { neuesKontoNull += " "; }
    cout << setfill(' ') << setw((45/2) + len/2) << right
         << neuesKontoNull;
    cout << neuesKontoEins;
    cin  >> dateiName;
    
    dateiName += dateiNameEins;


    datei.open(dateiName.c_str());
    datei.setf(ios::fixed);
    datei << "Eröffnet"  << ' ' << setprecision(2) << "0.00" << endl;
    datei.close();
    
    cout << setfill('*') << setw(45) << "*" << endl;
    
    zweiteMen();
}

void konto()
{
    int len = int (kontoNull.length());
    if (len % 2 == 0) { kontoNull += " "; }
    cout << setfill(' ') << setw((45/2) + len/2) << right
         << kontoNull
         << kontoEins;
    cin  >> dateiName;
    
    dateiName += dateiNameEins;
    
    ifstream datei(dateiName.c_str());
    
    if (datei.fail()) {cerr << dateiFehler; konto();}
    
    cout << setfill('*') << setw(45) << "*" << endl;
    zweiteMen();
}

// Konto gibts schon.
int zweiteMen()
{
    string dName = dateiName;
    int menEingabe = 0;
    int len = int (dateiName.length());
    if (len % 2 == 0) { dName += " "; }
    cout << setfill(' ') << setw((45/2) + len/2) << right
         << dateiName << endl << endl;
    cout << menNull
         << menEins
         << menZwei
         << menDrei;
    cin >> menEingabe;
    
    
    cout << setfill('*') << setw(45) << "*" << endl;
    
    switch (menEingabe)
    {
        case 1: einzahlen();
            break;
        case 2: abheben();
            break;
        case 3: kontostand();
            break;
        case 4: dateiName = " ";
                clearScreen();
                hauptProgramm();;
            break;
        default:
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cerr << fehler;
                cout.flush();
                zweiteMen();
            break;
    }
    return 0;
}

// Hauptmenü switch
void programmSwitch(int wahl)
{
    switch(wahl)
    {
        case 1: neu();
            break;
        case 2: konto();
            break;
        case 4: exit(0);
            break;
        default :
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cerr << fehler;
            cout.flush();
            hauptProgramm();
            break;
    }
}

int hauptProgramm()
{
    int hauptMenEingabe = 0;
    int len = int (hauptMenTitel.length());
    
    while (true)
    {
        cout << setfill('*') << setw(45) << "*" << endl;
        if (len % 2 == 0) { hauptMenTitel += " "; }
        cout << setfill(' ') << setw((45/2) + len/2) << right << hauptMenTitel
             << hauptMenNull
             << hauptMenEins
             << hauptMenDrei;
        cin >> hauptMenEingabe;
        
        programmSwitch(hauptMenEingabe);
        cout << setfill('*') << setw(45) << "*" << endl;
        cout << endl;

        return 0;
    }
}
