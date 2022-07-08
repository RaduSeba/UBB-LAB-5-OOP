#pragma once
#include "Oferta.h"
#include "Vector.h"

typedef struct
{
	Vector* oferte;
}OfertaRepo;

OfertaRepo* createRepo();
void destroyRepo(OfertaRepo* r);

int getLength(OfertaRepo* r);

Oferta* getOfertaOnPos(OfertaRepo* v, int pos);
int add(OfertaRepo* r, Oferta* o);
int deleteO(OfertaRepo* r, int nr);
int modifyO(OfertaRepo* r, int nr, int pret);

OfertaRepo* filterbypretRepo(OfertaRepo* r, int pret);
OfertaRepo* filterbytipRepo(OfertaRepo* r, char* tip);
OfertaRepo* filterbydestinatieRepo(OfertaRepo* r, char* destinatie);
//Returneaza un nou repository cu oferte care au o anumita destinatie si pretul <= pret dat
//:param: destinatie (char*)
//:return: ^un repository (OfertaRepo*)
OfertaRepo* filterbytotRepo(OfertaRepo* r, char* destinatie, int pret);
OfertaRepo* sort(OfertaRepo* r, int (*cmp)(Oferta* o1, Oferta* o2));
int compararepret(Oferta* o1, Oferta* o2);
int compararedestinatie(Oferta* o1, Oferta* o2);
OfertaRepo* copyOfertaRepo(OfertaRepo*);
OfertaRepo* undo(OfertaRepo* r, Vector* undoList);
//Returneaza un nou repoistory cu oferte care au o anumita data
//:param: data (char)
//:return: un repository (OfertaRepo*)
OfertaRepo* filterbydataRepo(OfertaRepo* r, char* data);
void testsrepo();
