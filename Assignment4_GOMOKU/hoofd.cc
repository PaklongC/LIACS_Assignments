/*Assignment 4: Gomoku; Makers: Zahir Bingen (s2436647), Pak Long Cheung (s2712040);
Datum: 09/12/2019; Compiler: GCC 8.3.0;
Careful! Compile with -std=c++11 or higher!
This program simulates multiple MxN in a row games. User can make set their own parametes
and play the game or let computer play it (for statisticcs check)
*/

#include <iostream>
#include "gobord.h"

//functie dat het infoscherm weergeeft
void infoblock(){
    std::cout << "****************************************************************\n";
    std::cout << "* Assignment 4 (Gomoku)                                        *\n";
    std::cout << "* Creators: Zahir Bingen, Pak Long Cheung (04/12/2019)         *\n";
    std::cout << "* Startyear study: 2019                                        *\n";
    std::cout << "* Major: Computer Science, Integrated Product Design           *\n";
    std::cout << "* Student number: s2436647, s2712040                           *\n";
    std::cout << "*                                                              *\n";
    std::cout << "* Dit is een programma dat verschillende x op een rij spellen  *\n";
    std::cout << "* kan spelen. Je kiest eerst een bordgrootte, en daarna        *\n";
    std::cout << "* hoeveel keer op een rij. Je kan tegen een computer spelen    *\n";
    std::cout << "* of tegen iemand anders. Ook kan je 2 computers tegen elkaar  *\n";
    std::cout << "* laten spelen. In dat geval komen er wat statistieken op het  *\n";
    std::cout << "* scherm. LET OP! Bij grote berekeningen duurt dit wat langer  *\n";
    std::cout << "* Druk op enter om te starten.                                 *\n";
    std::cout << "****************************************************************\n";
    std::cin.get();
}

//functie dat het hoofd menu doet
void menu(){
  char choice;
    gobord Gobord;
    stapel Stapel;
    stapel* in = nullptr;

    if(Gobord.Speler1 == 'C' && Gobord.Speler2 == 'C'){
      Gobord.compvsComp(Stapel, in);
    }

    Gobord.drukaf();

    if((Gobord.Speler1 == 'M' && Gobord.Speler2 == 'C') || (Gobord.Speler1 == 'C' && Gobord.Speler2 == 'M')
        || (Gobord.Speler1 == 'M' && Gobord.Speler2 == 'M')){
      if(Gobord.Comp1){
        Gobord.computerZet(Gobord.Speler, Stapel, in);
      }

      do{
        std::cout << std::endl << "Speler: " << Gobord.Speler << " Zetnummer: " << Gobord.zetnummer + 1
                  << std::endl << "(D)oe zet, (O)ntdoe zet, (V)ervolgpartijen, (S)top: "; 
        switch(Gobord.leesoptie(choice)){
          case 'D':
          case 'd':
            Gobord.doeZet(Gobord.Speler, Stapel, in);
            break;
          case 'O':
          case 'o':
            if(Gobord.Speler1 == 'C' || Gobord.Speler2 == 'C'){
              if(Gobord.zetnummer > 1){
                Gobord.ontdoeZet(in, Stapel);
                Gobord.zetnummer--;
                Gobord.zetnummer--;
              }
              else{
                std::cout << std::endl << "Kan niet verder terug!" << std::endl;
                Gobord.drukaf();
              }
            }
            else{
              Gobord.drukaf();
              std::cout << std::endl << "Niet valsspelen!" << std::endl;
            }
            break;
          case 'V':
          case 'v':
            Gobord.vervolg();
            break;
          case '\n':
            break;
          default:
            break;
        }
      }while(choice != 's' && choice != 'S');
    }
}


int main(){
  srand(time(0));
  infoblock();
  menu();
  return 0;
}//main

