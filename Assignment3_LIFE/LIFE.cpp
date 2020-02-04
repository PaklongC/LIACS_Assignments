// Gebruikte compilers : g++ en GNU GCC . Getest op LINUX en WINDOWS.
// Gemaakt door Adam Asraoui en Pak Long Cheung.
// Laatste aanpassing van het programma : 11 november 2019.

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <climits>
using namespace std;

const int MAX = 100; // Array van de wereld

class life { // Klasse met alle memberfuncties en -variabelen
    public:
        life (); // Constructor voor initialiseren van private membervariabelen
        void drukAf (char y, life &mijnLife); // memberfunctie voor het (opnieuw) afdrukken van de view
        void vulRandom (life &mijnLife); // Vult de view opnieuw met behulp van randomgetal() en percentage
        void maakSchoon (life &mijnLife); // Maakt de cellen in de view dood
        void heelSchoon(life &mijnLife); // Maakt de cellen in de wereld dood
        void volgende(char x, life &mijnLife); // Drukt de volgende generatie wereld af
        void een(char w, life &mijnLife); // Berekent en drukt een generatie verder
        void gaan(life &mijnLife); // Berekent en drukt een generatie verder voor [gen] aantal keer
        void start(char z, life &mijnLife); // Start de wereld in het begin door alles dood te maken
        void zetSchuif(int s); // Functie voor aanpassen membervariabele schuif
        void zetPercentage ( ); // Functie voor aanpassen membervariabele percentage
        void zetGen(int n); // Functie voor aanpassen membervariabele gen
        void zetLevend(char a); // Functie voor aanpassen membervariabele leven
        void zetDood(char b); // Functie voor aanpassen membervariabele dood
        int stoppen(); // Functie om uit het hoofdmenu en programma te stappen
        void cursor(life &mijnLife); // Functie om cursorpositie aan te passen
        void toggle(life &mijnLife); // Functie om cel op de cursorpositie te veranderen
        void view(life &mijnLife); // Functie om de view aan te passen
        void glider (life &mijnLife); // (hard-coded) gliderGun array
    private:
        bool wereld[MAX][MAX]; // Huidige wereld -array
        bool extraWereld[MAX][MAX]; // Container array
        int hoogte, breedte; // Dimensies voor view
        char leven, dood; // Karakters die levende of dode cellen vertegenwoordigen
        int percentage; // Percentage levende cellen
        int schuif; // Stapgrootte voor view-verschuiving
        int gen, genTeller; // Het aantal generaties en de teller ervan
        int xView, yView; // Coordinaten
        int spijkerA, spijkerB; // Aanhangpunt view
};

void info(char d){ // Functie voor getoonde info
    if(d == '0'){ // Info algemeen
        cout << "--------------------------------------------------------------------------"
        << "--------------------" << endl;
        cout << "Dit spel werd gespeeld volgens de regels van 'Life' bedacht door de heer Conway:" << endl;
        cout << "- Er ontstaat leven als een cel precies drie directe buren heeft, " << endl;
        cout << "- een cel blijft leven als deze precies twee of drie directe buren heeft, " << endl;
        cout << "- een cel gaat dood in alle overige gevallen." << endl << endl;
        cout << "Het programma is op 11 november 2019 afgemaakt door:" << endl;
        cout << "- Adam Asraoui en " << endl;
        cout << "- Pak long Cheung." << endl << endl;
    } if (d == '1'){ // Info hoofdmenu
        cout << "[HOOFDMENU] s(C)hoon, (H)eelschoon, (R)andom, (E)en, (G)aan, c(U)rsor, (V)iew, " << endl;
        cout << "            Gl(I)der, (P)arameters, (S)top: " << endl;
    } if (d == '2'){ // Info hoofdmenu
        cout << "[HOOFDMENU] s(C)hoon, (H)eelschoon, (R)andom, (E)en, (G)aan, c(U)rsor, (V)iew, " << endl;
        cout << "            Gl(I)der, (P)arameters, (S)top: ";
    } if (d == '3'){ // Info submenu(s)
        cout << "[SUBMENU] (S)tap verschuiving, (P)ercentage levend, (K)arakter, aantal (G)eneraties, (T)erug: ";
    } if (d == '4'){
        cout << "[STAP VERSCHUIVING] Stapgrootte van verschuiving: ";
    } if (d == '5'){
        cout << "[PERCENTAGE] Percentage levend is: ";
    } if (d == '6'){
        cout << "[KARAKTER] Aanpassen voor (L)even of (D)ood: ";
    } if (d == '7'){
        cout << "[KARAKTER: LEVEN] Karakter voor leven is: ";
    } if (d == '8'){
        cout << "[KARAKTER: DOOD] Karakter voor dood moet worden: ";
    } if (d == '9'){
        cout << "[GENERATIES] Het aantal generaties: ";
    } if (d == 'A'){
        cout << "[CURSOR] Beweeg de cursor (W/A/S/D), (T)oggle leven en dood of ga Te(R)ug: ";
    } if (d == 'B'){
        cout << "[VIEW] Beweeg de view (W/A/S/D) of ga Te(R)ug: ";
    }
}

char inlezen(){ // Leest en returnt invoer karakter voor karakter
    char invoer = '\n'; // Container voor cin.get()
    while(invoer == '\n'){
        invoer = cin.get();
    }
    return invoer;
}

int leesGetal(int maxWaarde){ // Returnt een getal van invoer tot en met [maxWaarde]
    char kar; // Container voor inlezen
    kar = inlezen();
    int getal = 0; // Hulpgetal om cijfers boven de 9 te berekenen
    while(kar != '\n'){
        if(kar >= '0' && kar <= '9'){
            int getal1 = kar - '0';
            getal = getal * 10 + getal1;
            if (getal > maxWaarde){
                getal = getal/10;
            }
        }
        kar = cin.get();
    }
    return getal;
}

int randomGetal () {// Returnt een reeks van 1000 'random' getallen
    static int getal = 22;
    getal = ( 221 * getal + 1 ) % 1000;
    return getal;
}

life::life(){ // Constructor voor initialiseren van private membervariabelen
    hoogte = 26, breedte = 94;
    xView = (breedte/2), yView = (hoogte/2);
    leven = 'x', dood = '.';
    percentage = 50;
    gen = 100, genTeller = 0;
    schuif = 1;
    spijkerA = 1, spijkerB = 1;
}

void life::drukAf(char y, life &mijnLife){ // memberfunctie voor het (opnieuw) afdrukken van de view
    // Header van screen met getoonde info
    cout << "Coordinaten (" << xView << ", " << yView << ")  |  Breedte view: " << breedte
         << " hoogte view: " << hoogte <<  "  |  Current generation: " << genTeller << endl;
    // Het afdrukken van de wereld
    for(int i = spijkerA; i < hoogte+spijkerA; i++){
        for(int j = spijkerB; j < breedte+spijkerB; j++){
            if (i == yView && j == xView){
                cout << "#";
            } else if(wereld[i][j]){
                cout << leven;
            } else {
                cout << dood;
            }
        } cout << endl;
    }
    cout << "--------------------------------------------------------------------------"
    << "--------------------" << endl;
    // Informatie menumogelijkheden
    info(y);
}

void life::vulRandom(life &mijnLife){ // Vult de view opnieuw met behulp van randomgetal() en percentage
    int c, procent = percentage * 10; // Random getal heeft 3 cijfers --> percentage * 10
    for (int i = spijkerA; i < hoogte+spijkerA; i++){
        for(int j = spijkerB; j < breedte+spijkerB; j++){
            c = randomGetal();
            if (c >= procent){;
                wereld[i][j] = false;
            } else {
                wereld[i][j] = true;
            }
        }
    }
    drukAf('2', mijnLife);
}

void life::maakSchoon(life &mijnLife){ // Maakt de cellen in de view dood
    for (int i = spijkerA; i < hoogte+spijkerA; i++){
        for(int j = spijkerB; j < breedte+spijkerB; j++){
            wereld[i][j] = false;
        }
    }
    drukAf('2', mijnLife);
}

void life::heelSchoon(life &mijnLife){ // Maakt de cellen in de wereld dood
    for (int i = 1; i < (MAX-1); i++){
        for(int j = 1; j < (MAX-1); j++){
            wereld[i][j] = false;
        }
    }
    genTeller = 0;
    drukAf('2', mijnLife);
}

void life::volgende(char x, life &mijnLife){ // Drukt de volgende generatie wereld af
    for (int i = 1; i < (MAX-1); i++) {
        for (int j = 1; j < (MAX-1); j++) {
            wereld[i][j] = extraWereld[i][j];
        }
    }
    drukAf(x, mijnLife);
}

void life::een(char w, life &mijnLife){ // Berekent en drukt een generatie verder
    int levend = 0;
    for (int i = 1; i < (MAX-1); i++) {
        for (int j = 1; j < (MAX-1); j++) {
            if (wereld[i-1][j-1])
                levend++;
            if (wereld[i-1][j])
                levend++;
            if (wereld[i-1][j+1])
                levend++;
            if (wereld[i][j-1])
                levend++;
            if (wereld[i][j+1])
                levend++;
            if (wereld[i+1][j-1])
                levend++;
            if (wereld[i+1][j])
                levend++;
            if (wereld[i+1][j+1])
                levend++;
            if (wereld[i][j] && (levend == 2 || levend == 3)){
                extraWereld[i][j] = true;
            } if (levend == 3) {
                extraWereld[i][j] = true;
            } else {
                extraWereld[i][j] = false;
            }
            levend = 0;
        }
    }
    genTeller++;
    volgende(w, mijnLife);
}

void life::gaan(life &mijnLife) { // Berekent en drukt een generatie verder voor [gen] aantal keer
    for (int i = 0; i < gen; i++) {
        een('1', mijnLife);
    }
}

void life::start(char z, life &mijnLife) { // Start de wereld in het begin door alles dood te maken
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            wereld[i][j] = false;
        }
    }
    drukAf('2', mijnLife);
}

void life::toggle(life &mijnLife){ // Functie om cel op de cursorpositie te veranderen
    if (wereld[yView][xView]) {
        wereld[yView][xView] = false;
    } else {
        wereld[yView][xView] = true;
    }
    mijnLife.drukAf('A', mijnLife);
}

void life::zetSchuif(int s){ // Functie voor aanpassen membervariabele schuif
    schuif = s;
}

void life::zetPercentage(){ // Functie voor aanpassen membervariabele percentage
    percentage = leesGetal(100); // [maxWaarde] gezet op 100
}

void life::zetGen(int n){ // Functie voor aanpassen membervariabele gen
    gen = n;
}

void life::zetLevend(char a){ // Functie voor aanpassen membervariabele leven
    leven = a;
}

void life::zetDood(char b){ // Functie voor aanpassen membervariabele dood
    dood = b;
}

int life::stoppen(){ // Functie om uit het hoofdmenu en programma te stappen
    return 1;
}

void parameters(life & mijnLife){ // Submenu
    char code = 0, choice = 0;
    while(code != 'T' && code != 't'){ // Submenu
        mijnLife.drukAf('3', mijnLife);
        code = inlezen();
        switch(code){
            case 's': // Stapgrootte van schuif aanpassen  (geinitialiseerd op 1)
            case 'S': {
                mijnLife.drukAf('4', mijnLife);
                mijnLife.zetSchuif(leesGetal(100)); // [maxWaarde] gezet op 100
                break;
            }
            case 'p': // Percentage levende cellen aanpassen (geinitialiseerd op 50)
            case 'P': {
                mijnLife.drukAf('5', mijnLife);
                mijnLife.zetPercentage();
                break;
            }
            case 'k': // Karakters voor Levende en Dode cellen aanpassen (geinitialiseerd op L = x, D = .)
            case 'K':{
                mijnLife.drukAf('6', mijnLife);
                choice = inlezen();
                if (choice == 'L' || choice == 'l'){
                    mijnLife.drukAf('7', mijnLife);
                    mijnLife.zetLevend(inlezen());
                } if (choice == 'D' || choice == 'd'){
                    mijnLife.drukAf('8', mijnLife);
                    mijnLife.zetDood(inlezen());
                }
                break;
            }
            case 'g': // Aantal generaties aanpassen (geinitialiseerd op 100)
            case 'G': {
                mijnLife.drukAf('9', mijnLife);
                mijnLife.zetGen(leesGetal(1000));
                break;
            }
        }
    }
}

void hoofdmenu(life &mijnLife){ // Hoofdmenu
    char code = 0;
    while(code != 'S' && code != 's'){ // Hoofdmenu
        code = inlezen();
        switch(code){
            case 'c': case 'C': mijnLife.maakSchoon(mijnLife); break; // View doodmaken
            case 'h': case 'H': mijnLife.heelSchoon(mijnLife); break; // Wereld doodmaken
            case 'r': case 'R': mijnLife.vulRandom(mijnLife); break; // Percentage levende cellen aanpassen in de wereld
            case 'e': case 'E': mijnLife.een('2', mijnLife); break; // Een generatie verder tonen
            case 'g': case 'G': mijnLife.gaan(mijnLife); break; // [gen] Aantal generaties draaien
            case 'u': case 'U': mijnLife.cursor(mijnLife); break; // [gen] Aantal generaties draaien
            case 'v': case 'V': mijnLife.view(mijnLife); break; // [gen] Aantal generaties draaien
            case 'i': case 'I': mijnLife.glider(mijnLife); break; // [gen] Aantal generaties draaien
            case 'p': case 'P': parameters(mijnLife); // Submenu openen
                      mijnLife.drukAf('2', mijnLife); break;
            case 's': case 'S': mijnLife.stoppen(); break; // Life stoppen
        }
    }
}

void life::cursor(life &mijnLife){ // Functie om cursorpositie aan te passen
    char code = 0;
    while (code != 'r' && code != 'R'){
        mijnLife.drukAf('A', mijnLife);
        code = inlezen();
        switch (code){
            case 'w': case 'W' : yView--; break;
            case 's': case 'S' : yView++; break;
            case 'a': case 'A' : xView--; break;
            case 'd': case 'D' : xView++; break;
            case 't': case 'T' : mijnLife.toggle(mijnLife); break;
        }
    }
    drukAf(2, mijnLife); // Hoofdmenutekst wordt in de main afgedrukt. Dit om niet de start functie in te komen elke keer als men in het hoofdmenu komt. Dit zou het moeten verhelpen.
    return;
}

void life::view(life &mijnLife){ // Functie om de view aan te passen
    char code = 0;
    while (code != 'R' && code != 'r'){
        mijnLife.drukAf('B', mijnLife);
        code = inlezen();
        switch (code){
            case 'w': case 'W' : spijkerA = spijkerA-schuif; break;
            case 's': case 'S' : spijkerA = spijkerA+schuif; break;
            case 'a': case 'A' : spijkerB = spijkerB-schuif; break;
            case 'd': case 'D' : spijkerB = spijkerB+schuif; break;
        }
    }
    return;
}

void life::glider(life &mijnLife){ // Glidergun array
    mijnLife.wereld[6][10] = true;
    mijnLife.wereld[6][11] = true;
    mijnLife.wereld[7][11] = true;
    mijnLife.wereld[7][10] = true;
    mijnLife.wereld[6][10] = true;
    mijnLife.wereld[15][10] = true;
    mijnLife.wereld[15][11] = true;
    mijnLife.wereld[15][12] = true;
    mijnLife.wereld[16][13] = true;
    mijnLife.wereld[17][14] = true;
    mijnLife.wereld[18][14] = true;
    mijnLife.wereld[19][13] = true;
    mijnLife.wereld[20][12] = true;
    mijnLife.wereld[20][11] = true;
    mijnLife.wereld[20][10] = true;
    mijnLife.wereld[21][11] = true;
    mijnLife.wereld[24][8] = true;
    mijnLife.wereld[24][9] = true;
    mijnLife.wereld[24][10] = true;
    mijnLife.wereld[25][8] = true;
    mijnLife.wereld[25][9] = true;
    mijnLife.wereld[25][10] = true;
    mijnLife.wereld[26][7] = true;
    mijnLife.wereld[28][7] = true;
    mijnLife.wereld[28][6] = true;
    mijnLife.wereld[26][11] = true;
    mijnLife.wereld[28][11] = true;
    mijnLife.wereld[28][12] = true;
    mijnLife.wereld[37][8] = true;
    mijnLife.wereld[37][9] = true;
    mijnLife.wereld[38][8] = true;
    mijnLife.wereld[38][9] = true;
    mijnLife.wereld[16][9] = true;
    mijnLife.wereld[17][8] = true;
    mijnLife.wereld[18][9] = true;
    mijnLife.wereld[19][8] = true;
    mijnLife.wereld[18][11] = true;
    mijnLife.drukAf(2, mijnLife);
}


int main (){ // Main
    life mijnLife;
    mijnLife.start('2', mijnLife);
    hoofdmenu(mijnLife);
    info('0');
    return 0;
}
