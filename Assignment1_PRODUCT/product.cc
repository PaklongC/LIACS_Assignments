
// Gebruikte compilers: g++ en GNU GCC. Getest op LINUX en WINDOWS.
// Gemaakt door Pak Long Cheung en Rolien van de Geer (gestopt na de eerste week).
// Laatste aanpassing van het programma: 23 sept 2019.

#include <cstdlib>
#include <climits>
#include <iostream>
using namespace std;
int main ( ) {
  // Peilvariabelen aan te passen naar huidige datum.
  const int jaarPeil = 2019, maandPeil = 9, dagPeil = 23;
  // Hulpvariabele aa wordt gebruikt i.c.m %4 om de geboortedag te bepalen.
  // jaar, maand en dag worden ingevuld door de gebruiker.
  // x en y wordt gebruikt bij de som
  int jaar, maand, dag, aa, x, y;
  int jaarVerschil, maandVerschil, dagVerschil;
  const int jan = 31, feb = 28, maa = 31, apr = 30, mei = 31, jun = 30, jul = 31,
  aug = 31, sep = 30, okt = 31, nov = 30;
  // schrikkeldagen + dagenIncompleet = dagenJaar.
  // aantalDagen = dagenDag + dagenMaand + dagenJaar
  int schrikkelDagen, dagenIncompleet, dagenJaar, dagenMaand, dagenDag, aantalDagen;
  // dag1 en dag2 zijn invoerwaardes om de geboortedag te controleren.
  // result is het antwoord op de meerkeuzevraag gegeven door de participant.
  // B en b zijn de goede antwoorden
  char dag1, dag2, B, b, result;
  // antwoord is de oplossing gegeven door de participant in de rekensom.
  // epsilon is de foutmarge (10%).
  double antwoord, epsilon;

  cout << "'Ben ik geschikt voor een studie aan de Universiteit?'" << endl;
  cout << " " << endl;
  cout << "Dit programma geeft advies over of men geschikt is voor een" << endl;
  cout << "universitaire studie door het stellen van enkele vragen." << endl;
  cout << "Lees de vragen goed door en let op de format van" << endl;
  cout << "het in te voeren antwoord. Veel succes!" << endl;
  cout << "---------------------------------------------------------------------";
  cout << "----" << endl;
  cout << "Het programma is afgemaakt op: 23 september 2019 door:" << endl;
  cout << "- Pak Long Cheung (2018, MSc Integrated Product Design voltijd,";
  cout << " S2712040) en" << endl;
  cout << "- Rolien van de Geer* (2016, BSc Psychologie deeltijd, S1788248)"
  << endl;
  cout << "*Gestopt met het vak 'Programmeermethoden' na de eerste week." << endl;
  cout << " "<< endl;
  cout << " "<< endl;  cout << "Geef als eerste het geboortejaar op (als geheel getal)." << endl;
  cout << "Daarna de maand waarin je geboren bent (als geheel getal)." << endl;
  cout << "Tenslotte de dag waarop je geboren bent (als geheel getal)." << endl;

  // Validaties bij invoer.
  cin >> jaar;
  // uitsluiting bij gekke jaartallen.
  if (jaar > 2019){
    cout <<"Het ingevoerde jaartal moet nog komen. Kijk dit nog even na." << endl;
    return 1;
  }
  if (jaar < 1901){
    cout << "U bent een aantal decennia geboren voor de Eerste Wereldoorlog...?";
    cout << "Kijk dit nog even na" << endl;
    return 1;
  }
  cin >> maand;
  // uitsluiting bij gekke maanden.
  if ((maand > 12) || (maand < 1)){
    cout << "De ingevoerde maand bestaat niet. Kijk dit nog even na." << endl;
    cout << " " << endl;
    return 1;
  }
  cin >> dag;
  // uitsluiting bij gekke dagen i.c.m. de ingevoerde maand.
  if ((maand == 1 || 3 || 5 || 7 || 8 || 10 || 12) && (dag < 1 || dag > 31)){
    cout << "De ingevoerde datum klopt niet met de maand. Kijk dit nog even na"
    << endl;
    cout << " " << endl;
    return 1;
  }
  cout << " "<< endl;
  if ((maand == 4 || 6 || 9 || 11 ) && (dag < 1 || dag > 30)){
    cout << "De ingevoerde datum klopt niet met de maand. Kijk dit nog even na"
    << endl;
    cout << " " << endl;
    return 1;
  // Schrikkeljaar.
  }
  if((maand == 2) && (jaar %4 == 0) && (dag < 1 || dag > 29)){
    cout << "De ingevoerde datum klopt niet met de maand. Kijk dit nog even na"
    << endl;
    cout << " " << endl;
    return 1;
  }
  if((maand == 2) && (jaar %4 != 0) && (dag < 1 || dag > 28)){
    cout << "De ingevoerde datum klopt niet met de maand. Kijk dit nog even na"
    << endl;
    cout << " " << endl;
    return 1;
  }

  // Berekening leeftijd en extra features.
  jaarVerschil = jaarPeil - jaar;
  maandVerschil = maandPeil - maand;
  dagVerschil = dagPeil - dag;
  // Leeftijd.
  if ((maandVerschil < 0) || ((maandVerschil == 0) && (dagVerschil < 0))){
    jaarVerschil--;
    maandVerschil--;
    maandVerschil = maandVerschil + 12;
    if (jaarVerschil <= 30){
      cout << "Je";
    }
    else {
      cout << "U";
    }
    cout << " bent ";
    cout << jaarVerschil;
    cout << " jaar en ";
    cout << maandVerschil;
    cout << " maand(en) oud ";
    cout << "(";
    cout << ((jaarVerschil * 12) + maandVerschil);
    cout << " maanden in totaal)." << endl;
    if (jaarVerschil <= 30){
      cout << "Je ";
    }
    else {
      cout << "U ";
    }
    cout << "moet nog jarig worden dit jaar." << endl;
    cout << " "<< endl;
    maandVerschil = maandVerschil - 12;
  }
  if ((maandVerschil > 0) || ((maandVerschil == 0) && (dagVerschil >= 0))){
    if (jaarVerschil <= 30){
      cout << "Je";
    }
    else {
      cout << "U";
    }
    cout << " bent ";
    cout << jaarVerschil;
    cout << " jaar en ";
    cout << maandVerschil;
    cout << " maand(en) oud ";
    cout << "(";
    cout << ((jaarVerschil * 12) + maandVerschil);
    cout << " maanden in totaal)." << endl;
    if (jaarVerschil <= 30){
      cout << "Je";
    }
    else {
      cout << "U";
    }
    cout << " bent al jarig geweest dit jaar." << endl;
    cout << " "<< endl;
  }
  // Felicitaties.
  if ((maandVerschil) == 0 && (dag - dagPeil == 0)){
    cout << "Gefeliciteerd, ";
    if (jaarVerschil <= 30){
      cout << "Je";
    }
    else{
      cout << "U";
    }
    cout << " bent jarig!" << endl;
    cout << " "<< endl;
  }
  if (dagVerschil == 0){
    cout << "Gefeliciteerd, ";
    if (jaarVerschil <= 30){
      cout << "Je";
    }
    else{
      cout << "U";
    }
    cout << " bent maandig!" << endl;
    cout << " " << endl;
  }
  // Uitsluitingen.
  if (jaarVerschil < 10){
    cout << "Je bent helaas te jong voor deze test." << endl;
    cout << "Nog even wachten:)." << endl;
    return 1;
  }
  if ((jaarVerschil == 10) && (maandVerschil < 0)){
    cout << "Je bent helaas nog iets te jong voor deze test." << endl;
    cout << "Nog een (aantal) maand(en) wachten:)." << endl;
    return 1;
  }
  if ((jaarVerschil == 10) && (maandVerschil == 0) && (dagVerschil > 0)){
    cout << "Je bent helaas nog iets te jong voor deze test." << endl;
    cout << "Nog een (aantal) dag(en) wachten:)." << endl;
    return 1;
  }
  if (jaarVerschil > 101){
    cout << "U bent helaas te oud voor test." << endl;
    return 1;
  }
  if ((jaarVerschil == 101) && (maandVerschil < 0 )){
    cout << "U bent helaas te oud voor test." << endl;
    return 1;
  }
  if ((jaarVerschil == 101) && (maandVerschil == 0) && (dagVerschil <= 0)){
    cout << "U bent helaas te oud voor test." << endl;
    return 1;
  }

  // Q1: Wat is jouw/Uw geboortedag?
  schrikkelDagen = (jaar-1901)/4;
  dagenIncompleet = (jaar-1901) * 365;
  dagenJaar = dagenIncompleet + schrikkelDagen;
  dagenMaand = maand - 1;
  // Berekening aantal dagen.
  if (dagenMaand == 0){
    dagenMaand = 0;
  }
  if (dagenMaand == 1){
    dagenMaand = jan;
  }
  if (dagenMaand == 2){
    dagenMaand = (jan + feb);
  }
  if (dagenMaand == 3){
    dagenMaand = (jan + feb + maa);
  }
  if (dagenMaand == 4){
    dagenMaand = (jan + feb + maa + apr);
  }
  if (dagenMaand == 5){
    dagenMaand = (jan + feb + maa + apr + mei);
  }
  if (dagenMaand == 6){
    dagenMaand = (jan + feb + maa + apr + mei + jun);
  }
  if (dagenMaand == 7){
    dagenMaand = (jan + feb + maa + apr + mei + jun + jul);
  }
  if (dagenMaand == 8){
    dagenMaand = (jan + feb + maa + apr + mei + jun + jul + aug);
  }
  if (dagenMaand == 9){
    dagenMaand = (jan + feb + maa + apr + mei + jun + jul + aug + sep);
  }
  if (dagenMaand == 10){
    dagenMaand = (jan + feb + maa + apr + mei + jun + jul + aug + sep + okt);
  }
  if (dagenMaand == 11){
    dagenMaand = (jan + feb + maa + apr + mei + jun + jul + aug + sep + okt +
    nov);
  }
  dagenDag = dag - 1;
  aantalDagen = dagenDag + dagenMaand + dagenJaar;
  aa = aantalDagen % 7;
  // Vraagstelling.
  cout << "Wat is ";
  if (jaarVerschil <= 30){
    cout << "jouw";
  }
  else {
    cout << "uw";
  }
  cout << " geboortedag? Het antwoord dient te worden ingevuld ";
  cout << "met 1 letter." << endl;
  cout << "Mijn geboortedag is (m/d/w/v/z): ";
  cin >> dag1;
  cout << " " << endl;
  // Uitzonderingen.
  if (dag1 == 'd' || dag1 == 'z'){
    cout << "De letters d en z zijn (zoals ";
    if (jaarVerschil <= 30){
      cout << "je";
    }
    else {
      cout << "U";
    }
    cout << " misschien al had verwacht) problematisch." << endl;
    cout << "Om een onderscheid te kunnen maken tussen dinsdag & donderdag"
    << endl;
    cout << "en zaterdag & zondag vragen we om een ";
    cout << "extra letter (i/o/a)." << endl;
    cout << "De tweede letter van mijn geboortedag is: ";
    cin >> dag2;
    cout << " " << endl;
  }
  // Antwoord.
  if (aa == 0 && dag1 == 'd' && dag2 == 'i'){
    cout << "Dat klopt! ";
    if (jaarVerschil <= 30){
      cout << "Je";
    }
    else {
      cout << "U";
    }
    cout << " bent geboren op een dinsdag." << endl;
  }
  else if (aa == 1 && dag1 == 'w'){
    cout << "Dat klopt! ";
    if (jaarVerschil <= 30){
      cout << "Je";
    }
    else {
      cout << "U";
    }
    cout << " bent geboren op een woensdag." << endl;
  }
  else if (aa == 2 && dag1 == 'd' && dag2 == 'o'){
    cout << "Dat klopt! ";
    if (jaarVerschil <= 30){
      cout << "Je";
    }
    else {
      cout << "U";
    }
    cout << " bent geboren op een donderdag." << endl;
  }
  else if (aa == 3 && dag1 == 'v'){
    cout << "Dat klopt! ";
    if (jaarVerschil <= 30){
      cout << "Je";
    }
    else {
      cout << "U";
    }
    cout << " bent geboren op een vrijdag." << endl;
  }
  else if (aa == 4 && dag1 == 'z' && dag2 == 'a'){
    cout << "Dat klopt! ";
    if (jaarVerschil <= 30){
      cout << "Je";
    }
    else {
      cout << "U";
    }
    cout << " bent geboren op een zaterdag." << endl;
  }
  else if (aa == 5 && dag1 == 'z' && dag2 == 'o'){
    cout << "Dat klopt! ";
    if (jaarVerschil <= 30){
      cout << "Je";
    }
    else {
      cout << "U";
    }
    cout << " bent geboren op een zondag." << endl;
  }
  else if (aa == 6 && dag1 == 'm'){
    cout << "Dat klopt! ";
    if (jaarVerschil <= 30){
      cout << "Je";
    }
    else {
      cout << "U";
    }
    cout << " bent geboren op een maandag." << endl;
  }
  else {
    cout <<"Dat klopt helaas niet, ";
    if (jaarVerschil <= 30){
      cout << "je";
    }
    else {
      cout << "U";
    }
    cout << " bent geboren op een andere dag." << endl;
    return 1;
  }

  // Q2: Rekensom.
  epsilon = 0.1;
  srand(maand); // als srand met 8 word geseed, is het antwoord van y 1
  x = (rand() %200000000);
  y = 1+(rand() %10);
  if (x > INT_MAX - y){
    cout << "Product te groot";
  }
  if (y == 1){
    y = 0;
  }
  // Vraagstelling.
  cout << " " << endl;
  cout << "Wat is het antwoord van deze som: ";
  cout << x;
  cout << " x ";
  cout << y << endl;
  cin >> antwoord;
  cout << " " << endl;
  // Antwoord als het product groter is dan 0.
  if (x * y != 0){
    if (x * y == antwoord) {
      cout << "Heel goed! ";
      if (jaarVerschil <= 30){
        cout << "Je";
      }
      else {
        cout << "U";
      }
      cout << " bent geschikt voor een beta-studie aan de universiteit.";
      cout << " " << endl;
      return 1;
    }
    else if (((antwoord/(x*y)) >= (1 - epsilon)) &&  ((antwoord/(x*y)) <= 1)){
      cout << "Het gegeven antwoord is goed met een fout-marge van -10%." << endl;
      cout << "Het exacte antwoord had moeten zijn: ";
      cout << x * y;
      cout << ". " << endl;
      if (jaarVerschil <= 30){
        cout << "Je";
      }
      else {
        cout << "U";
      }
      cout << " bent geschikt voor een beta-studie aan de universiteit.";
      cout << " " << endl;
      return 1;
    }
    else if ((antwoord/(x*y) >= 1) && ((antwoord/(x*y)) <= (1 + epsilon))){
      cout << "Het gegeven antwoord is goed met een fout-marge van +10%." << endl;
      cout << "Het exacte antwoord had moeten zijn: ";
      cout << x * y;
      cout << ". " << endl;
      if (jaarVerschil <= 30){
        cout << "Je";
      }
      else {
        cout << "U";
      }
      cout << " bent geschikt voor een beta-studie aan de universiteit.";
      cout << " " << endl;
      return 1;
    }
    else if (x * y !=0 && x * y != antwoord){
      cout << "Dit antwoord is helaas fout. Het antwoord had moeten zijn: ";
      cout << x * y;
      cout << ". " << endl;
      if (jaarVerschil <= 30){
        cout << "Je";
      }
      else {
        cout << "U";
      }
      cout << " bent niet geschikt voor een beta-studie." << endl;
      cout << " " << endl;
    }
  }
  // Antwoord als het product gelijk is aan 0.
  if (x * y == 0){
    if (x * y == antwoord){
      cout << "Heel goed! ";
      if (jaarVerschil <= 30){
        cout << "Je";
      }
      else {
        cout << "U";
      }
      cout << " bent geschikt voor een beta-studie aan de universiteit." << endl;
      cout << " " << endl;
      return 1;
    }
    else if (x * y == 0 && x * y != antwoord){
      cout << "Dit antwoord is helaas fout. Het antwoord had moeten zijn: ";
      cout << x * y;
      cout << ". " << endl;
      if (jaarVerschil <= 30){
        cout << "Je";
      }
      else {
        cout << "U";
      }
      cout << " bent niet geschikt voor een beta-studie." << endl;
      cout << " " << endl;
    }
  }

  // Q3: Meerkeuzevraag.
  cout << "De volgende meerkeuzevraag gaat over kunst en bepaalt of ";
  if (jaarVerschil <= 30){
    cout << "je,";
  }
  else {
    cout << "U,";
  }
  cout << " " << endl;
  cout << "ondanks dat ";
  if (jaarVerschil <= 30){
    cout << "je";
  }
  else {
    cout << "U";
  }
  cout << " niet geschikt bent voor een beta-studie," << endl;
  cout << "wel geschikt bent voor aan alpha-studie aan de universiteit." << endl;
  cout << " " << endl;
  //Vraagstelling.
  if (jaarVerschil <= 30){
    cout << "In de moderne kunst is het dadaisme vooral bekend geworden vanwege: "
    << endl;
    cout << "   A: Barack Obama en het popnummer 'Oops I did it again'." << endl;
    cout << "   B: Marcel Duchamp en zijn urinoir." << endl;
    cout << "   C: Mark Rutte en zijn autobiografie 'Mark Rutte is lesbisch'."
    << endl;
    cout << "   D: Alle bovenstaande antwoorden zijn correct." << endl;
    cout << " " << endl;
  }
  else {
    cout << "De auteur van het episch dierdicht 'Van den vos Reynaerde' is: "
    << endl;
    cout << "   A: Nicci French" << endl;
    cout << "   B: Willem die Madoc maecte" << endl;
    cout << "   C: Paul van Loon" << endl;
    cout << "   D: Roald Dahl" << endl;
    cout << " " << endl;
  }
  // Antwoord
  cout << "Het juiste antwoord op de vraag is: ";
  cin >> result;
  if ((result == 'B') || (result == 'b')){
    cout << "Dat klopt! Gefeliciteerd, ";
    if (jaarVerschil <= 30){
      cout << "je";
    }
    else {
      cout << "U";
    }
    cout << " kunt toegelaten worden tot een alpha-studie aan de universiteit.";
    cout <<" " << endl;
    return 1;
  }
  else {
    cout <<"Helaas, optie B was het correcte antwoord." << endl;
    if (jaarVerschil <= 30){
      cout << "Je";
    }
    else {
      cout << "U";
    }
    cout <<" bent niet geschikt voor een universitaire studie." << endl;
  }

  return 0;
}

