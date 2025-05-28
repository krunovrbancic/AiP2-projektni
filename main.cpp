//Projektni zadatak ALIAS
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<string.h>
#include<time.h>
#include <array>

using namespace std;

#define BrRijeci 52
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

void PokrenutiIgru()
{
    srand(static_cast<unsigned int>(time(nullptr)));
    int brIgraca;
    cout << "Unesite broj igraca: ";
    cin >> brIgraca;

    if (brIgraca < 2)
    {
        cout << "Za ovu igru je potrebno BAREM dva igraca!" << endl;
        return;
    }

    char objasnjenje[MaxObjasnjenje];
    char pogadjanje[MaxDuljina];
    int randomI;
    const char *odabranaRijec;
    int pozicijaIgraca1 = 0, pozicijaIgraca2 = 0;
    int igrac1 = 1, igrac2 = 2;
    int tocnoPogodjeno = 0;
    char trenutniIgrac = '$';

    postaviIgracaNaPocetnuPoziciju();
    cin.ignore();

    while (pozicijaIgraca1 < 16 && pozicijaIgraca2 < 16)
    {
        randomI = rand() % BrRijeci;
        odabranaRijec = rijeci[randomI];

        cout << "Igrac " << igrac1 << ", trebate objasniti zadanu rijec: " << odabranaRijec << endl;
        cout << "Napisite objasnjenje zadane rijeci: ";
        cin.getline(objasnjenje, MaxObjasnjenje);
        system("clear");

        prikaziPlocu();

        cout << "Igrac " << igrac2 << ", pokusajte pogoditi rijec pomocu objasnjenja: \"" << objasnjenje << "\"" << endl;
        cout << "Unesite rijec za koju smatrate da je rjesenje: ";
        cin >> pogadjanje;

        if (strcmp(pogadjanje, odabranaRijec) == 0)
        {
            cout << "Bravo! Vas odgovor je tocan" << endl;
            if (trenutniIgrac == '$')
            {
                pozicijaIgraca1++;
            }
            else
            {
                pozicijaIgraca2++;
            }
            tocnoPogodjeno = 1;
        }
        else
        {
            cout << "Vise srece drugi put, Vas odgovor je netocan. Tocan odgovor je: " << odabranaRijec << endl;
            tocnoPogodjeno = 0;
        }

        if (tocnoPogodjeno)
        {
            if (trenutniIgrac == '$')
            {
                pomakniIgraca(pozicijaIgraca1, '$');
            }
            else
            {
                pomakniIgraca(pozicijaIgraca2, '@');
            }
            prikaziPlocu();
        }

        trenutniIgrac = (trenutniIgrac == '$') ? '@' : '$';
        swap(igrac1, igrac2);
        cin.ignore();
    }

    cout << "Igrac " << ((pozicijaIgraca1 >= 16) ? 1 : 2) << " je pobijedio!" << endl;
    cout << "Stigli ste do samog kraja igre te Vam povodom tog cestitamo, pobijedili ste u drustvenoj igri sa vise tocnih odgovora!" << endl;
}

#include <iostream>
using namespace std;

int main()
{
    int izbor;

    cout << "//////  Made by Kruno Vrbancic and Marko Vrbancic  \\\\\\\\\\\\\\\n\n";
    cout << "                  _      _____           _____ \n"
            "            /\\   | |    |_   _|   /\\    / ____|\n"
            "           /  \\  | |      | |    /  \\  | (___ \n"
            "          / /\\ \\ | |      | |   / /\\ \\ \\ \\   \\ \n"
            "         / ____ \\| |____ _| |_ /_____ \\ ___)  |\n"
            "        /_/    \\_\\______|_____/_/    \\_\\_____/\n\n";

    while (true)
    {
        cout << "1. Pravila\n";
        cout << "2. Igraj\n";
        cout << "3. Izlaz\n";
        cout << "Unesite Vas izbor: ";
        cin >> izbor;
        cout << "\n";

        if (izbor == 1)
        {
            prPravila();
        }
        else if (izbor == 2)
        {
            PokrenutiIgru();
        }
        else if (izbor == 3)
        {
            cout << "Hvala sto ste igrali nasu igru alias!\n";
            break;
        }
        else
        {
            cout << "Krivi unos.\n";
        }

        cout << "\n\n\n";
    }

    return 0;
}
