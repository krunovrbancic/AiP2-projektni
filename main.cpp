//Projektni zadatak ALIAS
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<string.h>
#include<time.h>
#include <array>

using namespace std;

#define BrRijeci 50
#define MaxDuljina 50
#define MaxObjasnjenje 345
#define PlocaRedaka 10
#define PlocaStupaca 32

const char rijeci[BrRijeci][MaxDuljina] = {
    "programiranje", "racunalo", "igra", "sport", "knjiga", "kuca", "stolac", "svicarski nozic", "baterija", "plivanje",
    "dimnjak", "tipkovnica", "zid", "slika", "bicikl", "krema", "olovka", "naocale", "biljka", "siljilo",
    "karte", "svijetlo", "auto", "torba", "torta", "pas", "zirafa", "slon", "prozor", "kalkulator",
    "matematika", "stol", "slusalice", "ljecnik", "papir", "marker", "zvucnik", "kvaka", "skare",
    "monitor", "voda", "pikado", "dres", "biljeznica", "trofej", "tenisice", "razrednik", "punjac", "upaljac", "deka", "jastuk"};
char Ploca[PlocaRedaka][PlocaStupaca + 1] = {
    "#############################",
    "# POCETAK                   #",
    "#                           #",
    "#                           #",
    "#                           #",
    "#                           #",
    "#                           #",
    "#                           #",
    "# KRAJ                      #",
    "################################"
};

void prPravila() 
{
    cout << "Ovo su pravila:\n\n";
    cout << "1. Za igru su potrebna dva igraca.\n\n";
    cout << "2. Jedan igrac dobiva zadanu rijec i pise objasnjenje zadare rijeci.\n\n";
    cout << "3. Drugi igrac pokusava pogoditi zadanu rijec pomocu objasnjenja.\n\n";
    cout << "4. U objasnjenju se ne smije koristiti dio zadane rijeci.\n\n";
    cout << "5. Kada upisujete rijec koju smatrate tocnim odgovorom koristite mala slova i znakove engleske abecede\n\n";
}

void prikaziPlocu() {
    for (int i = 0; i < PlocaRedaka; i++)
    {
        cout << Ploca[i] << endl;
    }
}

void postaviIgracaNaPocetnuPoziciju(){
    Ploca[1][10] = '$';
    Ploca[1][21] = '@';
}

void pomakniIgraca(int pozicija, char igrac)
{
    int redak = 1;
    int kolona = (igrac == '$') ? 10 : 21;
    int kretanje = pozicija * 5;

    for (int i = 0; i < kretanje; ++i)
    {
        kolona += 5;
        if (kolona >= PlocaStupaca - 1)
        {
            ++redak;
            kolona = 1;
        }
    }
    for (int i = 0; i < PlocaRedaka; ++i)
    {
        for (int j = 0; j < PlocaStupaca; ++j)
        {
            if (Ploca[i][j] == igrac)
            {
                Ploca[i][j] = ' ';
            }
        }
    }
    Ploca[redak][kolona] = igrac;
}
