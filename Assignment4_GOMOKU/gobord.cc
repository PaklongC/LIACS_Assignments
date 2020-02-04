// file gobord.cc 
#include <iostream>
#include "gobord.h"
#include <limits>

//functie dat een character inleest en returned
char gobord::leesoptie(char &kar){
    kar = std::cin.get();

    while (kar == '\n'){
        return kar;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return kar;
}

//functie dat een getal inleest en returned
int gobord::leesGetal(){
    char kar;
    int currentnumber = 0;

    kar = std::cin.get();

    while (kar != '\n'){
        if (kar <= '0' || kar <= '9'){
            currentnumber = (10 * currentnumber) + kar - '0';
        }
        kar = std::cin.get();
    }
    return currentnumber;
}

//constructor bordvakje
bordvakje::bordvakje(){
  kleur = '.';

  for (int i = 0; i < 8; i++){
    buren[i] = nullptr;
  }
}

//constructor gobord
gobord::gobord(){
  kiesSpelers();
  kiesSettings();
  maakBord();
}

//functie dat bordvakjes aan elkaar plakt, pointer van de ingang returned
bordvakje* gobord::maakRij(){
  bordvakje* ingangRij = nullptr;
  bordvakje* hulp;

  for (int i = 0; i < breedte; i++){
    hulp = new bordvakje;
    hulp->buren[2] = ingangRij;
    ingangRij = hulp;
  }

  while (hulp->buren[2]){
    hulp->buren[2]->buren[6] = hulp;
    hulp = hulp->buren[2];
  }

  return ingangRij;
}

//fucntie dat bord maakt mbv maakRij functie
void gobord::maakBord(){
  bordvakje* ondersteRij = maakRij();
  bordvakje* hulp = ondersteRij;
  bordvakje* bovenste;
  bordvakje* onderste;
  ingang = ondersteRij;

  for (int i = 0; i < hoogte - 1; i++){
    ondersteRij = maakRij();
    hulp->buren[4] = ondersteRij;
    ondersteRij->buren[0] = hulp;
    bovenste = hulp;
    onderste = ondersteRij;

    while(bovenste){
      bovenste->buren[3] = onderste->buren[2];
      bovenste->buren[4] = onderste;
      bovenste->buren[5] = onderste->buren[6];
      onderste->buren[7] = bovenste->buren[6];
      onderste->buren[0] = bovenste;
      onderste->buren[1] = bovenste->buren[2];
      bovenste = bovenste->buren[2];
      onderste = onderste->buren[2];
    }
    hulp = ondersteRij;
  }
}

//functie dat het bord afdrukt
void gobord::drukaf() {
  std::cout << std::endl;
  bordvakje* rij, *kolom;
  rij = ingang;
  kolom = ingang;

  std::cout << "  ";
  for(int i = 0; i < breedte; i++){
    std::cout << i % 10 << ' ';
  }

  std::cout << std::endl;

  int hteller = 0;

  while(rij){
    std::cout << hteller % 10;

    while(kolom){
      std::cout << ' ' << kolom->kleur;
      kolom = kolom->buren[2];
    }

    hteller++;
    rij = rij->buren[4];
    kolom = rij;
    std::cout << std::endl;
  }
}

//functie dat directe pointer naar bordlocatie returned
bordvakje* gobord::pointVak(int m, int n){
  bordvakje* plek = ingang;

  for(int i = 0; i < m; i++){
    plek = plek->buren[4];
  }

  for(int i = 0; i < n; i++){
    plek = plek->buren[2];
  }

  return plek;
}

//functie die zet vraagt, plaatst, bord drukt
//zet pusht in stack(stapel), check win/vol
//en computerzet indien van toepassing
void gobord::doeZet(char vakkleur, stapel &Stapel, stapel* &in){
  int m, n;
  bool bezet = true;
  bordvakje* plek;

  while(bezet){
    std::cout << "Rij: ";
    m = leesGetal();

    while(m > hoogte-1){
      std::cout << std::endl << "BUITEN BEREIK! ";
      std::cout << std::endl << "Rij: ";
      m = leesGetal();
    }

    std::cout << std::endl << "Kolom: ";
    n = leesGetal();

    while(n > breedte-1){
      std::cout << std::endl << "BUITEN BEREIK! ";
      std::cout << std::endl << "Kolom: ";
      n = leesGetal();
    }

    std::cout << m << n;
    plek = pointVak(m, n);

    if (plek->kleur == '.'){
      plek->kleur = Speler;
      bezet = false;
      zetnummer++;
    }
  }

  drukaf();
  Stapel.push(in, m, n);
  gewonnen();
  wisselSpelers();
  bordvol();

  if(Comp1 || Comp2){
    computerZet(Speler, Stapel, in);
  }
}

//functie die computer tegen computer laat spelen
//statistieken print, array vult, afsluit
void gobord::compvsComp(stapel &Stapel, stapel* &in){
  for(int i = 0; i < aantal; i++){
    while(!win && !vol){
      computerZet(Speler, Stapel, in);
    }

    wisselSpelers();

    if(vol && !win){
      gelijkspel++;
    }

    if(Speler == 'Z' && win){
      zwin++;
      win = false;
    }

    if(Speler == 'W' && win){
      wwin++;
      win = false;
    }

    arrayZetten();
    leegbord();
    gamenummer++;
  }
  printStatistics();
  exit(0);
}

//functie die array vult
void gobord::arrayZetten(){
  zetArray[gamenummer] = zetnummer;
}

//functie die statistics print
void gobord::printStatistics(){
  for(int i = 0; i < aantal; i++){
    std::cout << "Game nummer: " << i+1 << " Aantal zetten: " << zetArray[i] << std::endl;
  }

  std::cout << std::endl << "Z wint: " << zwin << " keer" << std::endl;
  std::cout << std::endl << "W wint: " << wwin << " keer" << std::endl; 
  std::cout << std::endl << "Gelijkspel: " << gelijkspel << " keer" << std::endl; 
}

//functie voor computer zet, bord afdrukt, checkt win/vol, wissel spelers
void gobord::computerZet(char vakkleur, stapel &Stapel, stapel* &in){
  int zetM, zetN;
  bool bezet = true;
  bordvakje* plek;

  while(bezet){
    zetM = rand() % hoogte;
    zetN = rand() % breedte;
    plek = pointVak(zetM, zetN);

    if (plek->kleur == '.'){
      plek->kleur = vakkleur;
      bezet = false;
      zetnummer++;
    }
  }

  if(Speler1 == 'M' || Speler2 == 'M'){
    drukaf();
    Stapel.push(in, zetM, zetN);
  }

  gewonnen();
  bordvol();
  wisselSpelers();
}

//functie die zet ongedaan maakt, bord afdrukt
void gobord::ontdoeZet(stapel* &in, stapel &Stapel){
  bordvakje* plek;

   for(int i = 0; i < 2; i++){
    int m = Stapel.coordinaatRij(in);
    int n = Stapel.coordinaatKolom(in);
    plek = pointVak(m, n);
    plek->kleur = '.';
    Stapel.pop(in);
  }
  drukaf();
}

//functie dat bord leeg maakt
void gobord::leegbord(){
  win = false;
  vol = false;
  Speler = 'Z';
  zetnummer = 0;

  for(int i = 0; i < hoogte; i++){
    for(int j = 0; j < breedte; j++){
      bordvakje* plek;
      plek = pointVak(i, j);
      plek->kleur = '.';
    }
  }
}

//functie die spelers initialiseert
void gobord::kiesSpelers(){
  do{
    std::cout << "Speler 1: (M)ens, (C)omputer?: ";
    leesoptie(Speler1);

    if(Speler1 != 'M' && Speler1 != 'C'){
      std::cout << std::endl << "Kies een correcte optie!" << std::endl;
    }
  }while(Speler1 != 'M' && Speler1 != 'C');

  do{
    std::cout << "Speler 2: (M)ens, (C)omputer?: ";
    leesoptie(Speler2);
    if(Speler2 != 'M' && Speler2 != 'C'){
      std::cout << std::endl << "Kies een correcte optie!" << std::endl;
    }
  }while(Speler2 != 'M' && Speler2 != 'C');

  if(Speler1 == 'C'){
    Comp1 = true;
  }

  if(Speler2 == 'C'){
    Comp2 = true;
  }
}

//functie die bord settings initialiseert
void gobord::kiesSettings(){
  std::cout << "Kies aantal rijen: ";
  hoogte = leesGetal();
  std::cout << std::endl << "Kies aantal kolommen: ";
  breedte = leesGetal();
  std::cout << std::endl << "Kies x op een rij: ";
  winlengte = leesGetal();

  if(Speler1 == 'C' && Speler2 == 'C'){
    std::cout << std::endl << "Hoeveel games moeten er gespeeld worden?: ";
    aantal = leesGetal();
    std::cout << std::endl;
  }
}

//functie die checkt of bord vol is
void gobord::bordvol(){
  if(zetnummer > ((hoogte * breedte))-1){
    if(Speler1 == 'M' || Speler2 == 'M'){
      std::cout << std::endl << "Gelijkspel!";
      exit(0);
    }
    vol = true;
  }
}

//functie die recursief checkt voor win reeks
int gobord::ketting(bordvakje* plek, int i){
  int nummer = 1;

  if(plek->buren[i] == nullptr){
    return nummer;
  }

  else if(plek->kleur != plek->buren[i]->kleur){
    return nummer;
  }

  else{
    nummer = nummer + ketting(plek->buren[i], i);
  }

  return nummer;
}

//functie die checkt of er gewonnen is
void gobord::gewonnen(){
  bordvakje* plek;
  int buurnummer = 0;

  for(int i = 0; i < hoogte; i++){
    for(int j = 0; j < breedte; j++){
      plek = pointVak(i, j);

      while(buurnummer < 8){
        if((winlengte == ketting(plek, buurnummer) && plek->kleur != '.')){
          win = true;
          if(Speler1 == 'M' || Speler2 == 'M'){
            drukaf();
            std::cout << std::endl << Speler << " wint!" << std::endl;
            exit(0);
          }
          return;
        }
        buurnummer++;
      }
      buurnummer = 0;
      win = false;
    }
  }
}

//functie die spelers wisselt
void gobord::wisselSpelers(){
  if(Speler == 'Z'){
    Speler = 'W';
  }

  else{
    Speler = 'Z';
  }
}

//vervolgfunctie die niet werkte :)
void gobord::vervolg(){
  std::cout << std::endl << "Oneindig veel vervolgstappen, gebruik je fantasie!" << std::endl;
}


