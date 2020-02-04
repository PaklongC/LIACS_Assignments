#include <iostream>
#include "stapel.h"
#include <limits>
stapel::stapel(){
}

stapel::~stapel(){}

int stapel::coordinaatRij(stapel* &in){
    return in->infoRij;
}

int stapel::coordinaatKolom(stapel* &in){
    return in->infoKolom;
}

void stapel:: push(stapel* &in, int m, int n){
  stapel* p;
  p = new stapel;
  p->infoRij = m;
  p->infoKolom = n;
  p->volgende = in;
  in = p;
}

void stapel:: pop(stapel* &in){
  stapel* p = in;
  if ( in != NULL ) {
    in = in->volgende;

    if ( p->andere != NULL ){
      delete p->andere;
    }
    delete p;
  }
}



