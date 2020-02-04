#include "stapel.h"
#include <vector>

//voor comments die bij functies horen check gobord.cc
class bordvakje {
  public:
    char kleur;
    bordvakje* buren[8];        
    bordvakje();


};

//voor comments die bij functies horen check gobord.cc
class gobord{
  private:
    bordvakje* ingang; //ingang pointer van bord;
    int zetArray[100000]; //array voor opslaan zetnummers per game

  public:

    gobord();
    bordvakje* pointVak(int m, int n);
    bordvakje* maakRij();
    int leesGetal();
    char leesoptie(char &kar);  
    void gewonnen();
    int ketting(bordvakje* plek, int i);
    void bordvol();
    void doeZet(char vakkleur, stapel &Stapel, stapel* &in);
    void ontdoeZet(stapel* &in, stapel &Stapel);
    void computerZet(char vakkleur, stapel &Stapel, stapel* &in);
    void maakBord();
    void drukaf();
    void menu();
    void leegbord();
    void arrayZetten();
    void printStatistics();
    void compvsComp(stapel &Stapel, stapel* &in);
    void kiesSpelers();
    void kiesSettings();
    void wisselSpelers();
    void vervolg();
    char Speler1; //speler 1
    char Speler2; //speler 2
    char Speler = 'Z'; //speler op het moment
    int hoogte, breedte, winlengte, aantal; //parameters van bord en aantal games
    int zetnummer = 0;
    int gamenummer = 0;
    bool win = false, vol = false; //bools die checken voor win of volbord
    int zwin = 0, wwin = 0, gelijkspel = 0; //tellers
    bool Comp1 = false, Comp2 = false; //check voor speler combinaties
};
 
