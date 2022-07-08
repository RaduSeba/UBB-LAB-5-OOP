#pragma once
#include "OfertaRepository.h"

typedef struct
{
	OfertaRepo* repo;
}Service;

Service* createService(OfertaRepo* r);
void destroyService(Service* s);

OfertaRepo* getRepo(Service* s);

int addOferta(Service* s, char* tip, char* destinatie, char* data, int pret);
int deleteOferta(Service* s, int nr);
int modifyOferta(Service* s, int nr,int pret);
int getLen(Service* s);

OfertaRepo* filterbypret(Service* s, int pret);
OfertaRepo* filterbytip(Service* s, char* tip);
OfertaRepo* filterbydestinatie(Service* s, char* destinatie);

OfertaRepo* sortbydestinatie(Service* s);
OfertaRepo* sortbypret(Service* s);
OfertaRepo* copyOfertaService(Service*);
void undoService(Service* s, Vector* undoList);
OfertaRepo* filterbydata(Service* s, char* data);
OfertaRepo* filterbytot(Service* s, char* destinatie, int pret);
void testsService();