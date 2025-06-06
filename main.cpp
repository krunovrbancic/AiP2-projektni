// Projektni zadatak ALIAS
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <time.h>

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
    "#                           #",
    "#                           #",
    "#                           #",
    "#                           #",
    "#                           #",
    "#                           #",
    "#                           #",
    "#                           #",
    "#############################"};

void prPravila()
{
    cout << "Ovo su pravila:\n\n";
    cout << "1. Za igru su potrebna dva igraca.\n\n";
    cout << "2. Jedan igrac dobiva zadanu rijec i pise objasnjenje zadare rijeci.\n\n";
    cout << "3. Drugi igrac pokusava pogoditi zadanu rijec pomocu objasnjenja.\n\n";
    cout << "4. U objasnjenju se ne smije koristiti dio zadane rijeci.\n\n";
    cout << "5. Kada upisujete rijec koju smatrate tocnim odgovorom koristite mala slova i znakove engleske abecede\n\n";
}

void prikaziPlocu()
{
    for (int i = 0; i < PlocaRedaka; i++)
    {
        cout << Ploca[i];
        if (i == 1)
            cout << "  <-- POCETAK";
        if (i == PlocaRedaka - 2)
            cout << "  <-- KRAJ";
        cout << endl;
    }
}

void postaviIgracaNaPocetnuPoziciju()
{
    Ploca[1][5] = '$';
    Ploca[1][25] = '@';
}

void pomakniIgraca(int pozicija, char igrac)
{
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

    int redak = 1 + pozicija / 5;
    int kolona = 1 + (pozicija % 5) * 6;

    if (redak >= PlocaRedaka - 1)
        redak = PlocaRedaka - 2;
    if (kolona >= PlocaStupaca - 1)
        kolona = PlocaStupaca - 2;

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
    char trenutniIgrac = '$';

    postaviIgracaNaPocetnuPoziciju();
    cin.ignore();

    while (pozicijaIgraca1 < 16 && pozicijaIgraca2 < 16)
    {
        randomI = rand() % BrRijeci;
        odabranaRijec = rijeci[randomI];

        cout << "IGRAC " << igrac1 << ", vasa zadana rijec je: \"" << odabranaRijec << "\"" << endl;
        cout << "Napisite objasnjenje (ne koristiti samu rijec): ";
        cin.getline(objasnjenje, MaxObjasnjenje);

#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif

        cout << "IGRAC " << igrac2 << ", pokusajte pogoditi rijec pomocu objasnjenja:\n\"" << objasnjenje << "\"\n";
        cout << "Unesite rijec: ";
        cin.getline(pogadjanje, MaxDuljina);

        if (strcmp(pogadjanje, odabranaRijec) == 0)
        {
            cout << "Tocno!" << endl;
            if (trenutniIgrac == '$')
            {
                pozicijaIgraca1++;
                pomakniIgraca(pozicijaIgraca1, '$');
            }
            else
            {
                pozicijaIgraca2++;
                pomakniIgraca(pozicijaIgraca2, '@');
            }
        }
        else
        {
            cout << "Netocno! Tocan odgovor je bio: " << odabranaRijec << endl;
        }

        prikaziPlocu();

        trenutniIgrac = (trenutniIgrac == '$') ? '@' : '$';
        swap(igrac1, igrac2);
        cout << "Pritisnite ENTER za nastavak...";
        cin.get();
    }

    cout << "Igrac " << ((pozicijaIgraca1 >= 16) ? 1 : 2) << " je pobijedio!" << endl;
    cout << "Cestitamo!" << endl;
}

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
        cin.ignore();

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

        cout << "\n\n";
    }

    return 0;
}
