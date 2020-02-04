
// Gebruikte compilers: g++ en GNU GCC. Getest op LINUX en WINDOWS.
// Gemaakt door Rob te Nijenhuis en Pak Long Cheung.
// Laatste aanpassing van het programma: 13 oktober 2019.

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <climits>
using namespace std;

int omdraaien(int x){
    int rest, y = 0;
    for(; x > 0; x = x/10){
        rest =  x % 10;
        y = (y * 10) + rest;
    }
    return y;
}
int lychrel(int getal1){
    int getal2, iterations=0;
    bool palindroom = false;
    while(getal1 != 0 && getal1<(INT_MAX -getal2) && getal2<(INT_MAX-getal1)
          && palindroom==false){
        getal2 = omdraaien(getal1);
        if (getal2>INT_MAX -getal1){
            cout<<"INT_MAX overschreden."<<endl;
            cout<<"Het getal is waarschijnlijk een Lychrel-getal."<<endl;
            cout<<"Aantal gemaakte iteraties: ";
            return iterations;
        }
        if (getal1 == getal2){
            cout<<"Het tegengekomen getal wordt een palindroom."<<endl;
            palindroom = true;
            cout<<"Aantal benodigde iteraties: ";
            return iterations;
        }
        else{
            getal1 += getal2; //het nieuwe getal dat gevormd wordt uit de vorige twee
            cout<<getal2<<"  "<<getal1<<endl;
            iterations ++;
        }
        if (getal1 > INT_MAX -getal2 || getal2 > INT_MAX -getal1){
            cout<<"INT_MAX overschreden."<<endl;
            cout<<"Het getal is waarschijnlijk een Lychrel-getal."<<endl;
            cout<<"Aantal gemaakte iteraties: ";
            return iterations;
        }
    }
    return iterations;
}
void infoblokje(){
    cout << "Dit programma maakt een (aangepaste) kopie van een bestand "<<endl;
    cout << "naar keuze. Het programma is op 14-10-2019 afgemaakt door:" <<endl;
    cout << "- Pak Long Cheung en " << endl;
    cout << "- Rob te Nijhenhuis." << endl << endl;
    cout << "De gemaakte kopie kunt u vinden onder de naam 'kopie.txt'." <<endl;
    cout << "---------------------------------------------------------" << endl;
    cout << "Wat is de naam van het te kopieren bestand?" << endl;
    cout << "Vergeet de extensie niet! Bijvoorbeeld: 'example.txt'." << endl
         << endl;
}
string file_nm(){
    string filenaam;
    cout << "Geef de naam van de file die gecorrigeerd moet worden: ";
    cin >> filenaam;
    return filenaam;
}
int tabL(){
    int tabLengte;
    cout << "Geef de verlangde tablengte: ";
    cin >> tabLengte;
    cout << endl << endl;
    return tabLengte;
}
int cod_decod(int tabLengte, string bestand){ //bestand is de bestandnaam van het te lezen bestand
    char kar, prevKar = '~';
    int getal = 0, totaal = 1, behouden = 1, diepte = 0;
    bool comment = false, newLine = true; //booleans die aangeven of het karakter zich op een nieuwe regel of in
    ifstream invoer;                      //commentaar bevindt of niet
    ofstream uitvoer;
    invoer.open(bestand.c_str(), ios::in);
    if(invoer.fail()){
        cout << "Bestand niet geopend." << endl;
        return 1;
    }
    uitvoer.open("kopie.txt",ios::out); //de naam van het document waarin de uitvoer gestopt wordt.
    kar = invoer.get();
    while (! invoer.eof()){
        totaal++;
        if(prevKar >= '0' && prevKar <= '9'){//prevKar is het vorige karakter, kar is het huidige karakter
            getal = getal * 10 + (prevKar - '0');
        }
        if((kar < '0' || kar > '9') && getal != 0){
            cout << "-------------------------------------------------" << endl;
            cout << "Tegengekomen getal: " << getal;
            cout << ". Is dit een Lychrel getal?" << endl;
            cout<<lychrel(getal)<<endl;
            getal = 0;
        }
        if (prevKar == '/' && !comment && kar =='\n')
        {
            uitvoer.put('/');
            behouden ++;
        }

        if(kar == '/'){
            if(prevKar == '/'){
                comment = true;
            }
        }

        if (kar == '\n')
        {
            comment = false;
        }
        if (kar != '\t' && kar != ' ')
        {
            if (!newLine && kar == '}')
            {
                diepte--;
                if (diepte <0)
                    diepte = 0;
            }
            if (kar != '}' && newLine){
                int indent = tabLengte * diepte;
                for (int i = 0; i < indent; i++) {
                    uitvoer.put(' ');
                    behouden++;
                }
            }
            if(kar == '}' && newLine) {
                diepte--;
                if (diepte <0)
                    diepte = 0;
                int indent = tabLengte * diepte;
                for (int i = 0; i < indent; i++) {
                    uitvoer.put(' ');
                    behouden++;
                }
            }
            newLine = false;
        }

        if (!comment && kar != '/'){
            if (kar == '{'){
                diepte++;
            }
            if (prevKar == '/'&& kar!= '\n'){
                uitvoer.put('/');
                behouden ++;
            }
            if(!newLine) {
                uitvoer.put(kar);
                behouden++;
            }
        }

        if (kar =='\n')
            newLine =true;
        prevKar = kar;
        kar = invoer.get();
    }
    invoer.close();
    uitvoer.close();
    cout << " " << endl;
    cout << "Totaal aantal gekopieerde karakters: "<< behouden << endl;;
    cout << "Totaal aantal ingelezen karakters: "<<totaal<<endl;
    return 0;
}
int main(){
    infoblokje();
    cod_decod(tabL(),file_nm());
    return 0;
}

