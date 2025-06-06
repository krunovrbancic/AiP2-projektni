// Projektni zadatak ALIAS
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <fstream>
#include <map>
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
    Ploca[1][5] = 'X';
}

void ocistiIgraceSaPloce()
{
    for (int i = 0; i < PlocaRedaka; ++i)
    {
        for (int j = 0; j < PlocaStupaca; ++j)
        {
            if (Ploca[i][j] == '$' || Ploca[i][j] == '@' || Ploca[i][j] == 'X')
            {
                Ploca[i][j] = ' ';
            }
        }
    }
}

void pomakniIgraca(int pozicija, char igrac, int pozicijaDrugiIgrac = -1)
{
    int korakaURedku = 5;
    int redak = 1 + (pozicija / korakaURedku);

    if (redak >= PlocaRedaka - 1)
        redak = PlocaRedaka - 2;

    int pozicijaURedku = pozicija % korakaURedku;
    int kolona;

    if ((redak - 1) % 2 == 0)
    {
        kolona = 25 - pozicijaURedku * 5;
    }
    else
    {
        kolona = 5 + pozicijaURedku * 5;
    }

    if (kolona < 1)
        kolona = 1;
    if (kolona >= PlocaStupaca - 1)
        kolona = PlocaStupaca - 2;

    if (pozicija == pozicijaDrugiIgrac)
    {
        Ploca[redak][kolona] = 'X';
    }
    else
    {
        Ploca[redak][kolona] = igrac;
    }
}

void spremiLeaderboard(const string &imePobjednika)
{
    map<string, int> leaderboard;
    ifstream input("leaderboard.txt");
    string ime;
    int pobjede;

    while (input >> ime >> pobjede)
    {
        leaderboard[ime] = pobjede;
    }
    input.close();

    leaderboard[imePobjednika]++;

    ofstream output("leaderboard.txt");
    for (const auto &par : leaderboard)
    {
        output << par.first << " " << par.second << endl;
    }
    output.close();
}

void prikaziLeaderboard()
{
    ifstream datoteka("leaderboard.txt");
    if (!datoteka)
    {
        cout << "Leaderboard je prazan ili nije pronaden.\n";
        return;
    }

    cout << "\n===== LEADERBOARD =====\n";
    string ime;
    int pobjede;
    while (datoteka >> ime >> pobjede)
    {
        cout << ime << " - " << pobjede << " pobjeda" << endl;
    }
    cout << "========================\n\n";
    datoteka.close();
}

void PokrenutiIgru()
{
    srand(static_cast<unsigned int>(time(nullptr)));
    string ime1, ime2;
    cout << "Unesite ime prvog igraca: ";
    getline(cin, ime1);
    cout << "Unesite ime drugog igraca: ";
    getline(cin, ime2);

    char objasnjenje[MaxObjasnjenje];
    char pogadjanje[MaxDuljina];
    int randomI;
    const char *odabranaRijec;
    int pozicijaIgraca1 = 0, pozicijaIgraca2 = 0;
    string trenutniIme = ime1;
    char trenutniIgrac = '$';

    postaviIgracaNaPocetnuPoziciju();

    while (pozicijaIgraca1 < 16 && pozicijaIgraca2 < 16)
    {
        ocistiIgraceSaPloce();

        randomI = rand() % BrRijeci;
        odabranaRijec = rijeci[randomI];

        cout << trenutniIme << ", vasa zadana rijec je: \"" << odabranaRijec << "\"" << endl;
        cout << "Napisite objasnjenje (ne koristiti samu rijec): ";
        cin.getline(objasnjenje, MaxObjasnjenje);

#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif

        string drugiIme = (trenutniIme == ime1) ? ime2 : ime1;
        cout << drugiIme << ", pokusajte pogoditi rijec pomocu objasnjenja:\n\"" << objasnjenje << "\"\n";
        cout << "Unesite rijec: ";
        cin.getline(pogadjanje, MaxDuljina);

        if (strcmp(pogadjanje, odabranaRijec) == 0)
        {
            cout << "Tocno!" << endl;
            if (trenutniIgrac == '$')
            {
                pozicijaIgraca1++;
                pomakniIgraca(pozicijaIgraca1, '$', pozicijaIgraca2);
            }
            else
            {
                pozicijaIgraca2++;
                pomakniIgraca(pozicijaIgraca2, '@', pozicijaIgraca1);
            }

            if (pozicijaIgraca1 >= 16 || pozicijaIgraca2 >= 16)
            {
                string pobjednik = (pozicijaIgraca1 >= 16) ? ime1 : ime2;
                cout << "Igrac " << pobjednik << " je pobijedio!" << endl;
                break;
            }
        }
        else
        {
            cout << "Netocno! Tocan odgovor je bio: " << odabranaRijec << endl;
        }

        prikaziPlocu();

        trenutniIgrac = (trenutniIgrac == '$') ? '@' : '$';
        trenutniIme = (trenutniIme == ime1) ? ime2 : ime1;
        cout << "Pritisnite ENTER za nastavak...";
        cin.get();
    }

    spremiLeaderboard((pozicijaIgraca1 >= 16) ? ime1 : ime2);
}

int main()
{
    int izbor;
    do
    {
        cout << "Dobrodosli u igru ALIAS!\n";
        cout << "1. Pokreni igru\n";
        cout << "2. Pravila igre\n";
        cout << "3. Leaderboard\n";
        cout << "4. Izlaz\n";
        cout << "Unesite vas izbor: ";
        cin >> izbor;
        cin.ignore();

        switch (izbor)
        {
        case 1:
            PokrenutiIgru();
            break;
        case 2:
            prPravila();
            break;
        case 3:
            prikaziLeaderboard();
            break;
        case 4:
            cout << "Hvala na igri! Doviđenja!\n";
            break;
        default:
            cout << "Nepoznata opcija, molimo pokušajte ponovno.\n";
        }
    } while (izbor != 4);

    return 0;
}
