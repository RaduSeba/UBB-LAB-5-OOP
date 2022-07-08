#include "Service.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

Service* createService(OfertaRepo* r)
{
	//Creeare service

	Service* s = malloc(sizeof(Service));
	if (s == NULL)
	{
		return NULL;
	}
	s->repo = r;
	
	return s;
}

void destroyService(Service* s)
{
	//Distrugere service - eliberare memorie
	//:param: s (Service*)

	if (s == NULL)
	{
		return;
	}

	destroyRepo(s->repo);

	free(s);
}

int addOferta(Service* s, char* tip, char* destinatie, char* data, int pret)
{
	//Creeaza si adauga o oferta
	//:param: tip (char*)
	//:param: destinatie (char*)
	//:param: data (char*)
	//:param: pret (int)
	//:return: oferta (Oferta*)

	Oferta* o = createOferta(tip, destinatie, data, pret);
	
	int res = add(s->repo, o);

	if (res == -1)
	{
		destroyOferta(o);
	}

	return res;
}

int deleteOferta(Service* s, int nr)
{	
	//Sterge o oferta data de un numar
	//:param: nr (int)
	//:return: res(int) 1/0

	int res = deleteO(s->repo, nr);

	return res;
}

int modifyOferta(Service* s, int nr, int pret)
{
	//Modifca pretul unei oferte data de un numar
	//:param: nr (int)
	//:param: pret (int)
	//:return: res (int) 1/0

	int res = modifyO(s->repo, nr, pret);

	return res;
}

int getLen(Service* s)
{
	//Returneaza lungimea

	return getLength(s->repo);
}

OfertaRepo* getRepo(Service* s)
{
	//Returneaza repository-ul service-ului

	return s->repo;
}

OfertaRepo* filterbypret(Service* s, int pret)
{
	//Filtreaza ofertele care au un anumit pret
	//:param: pret (int)
	//:return: ^un repository (OfertaRepo*)

	if (s == NULL)
	{
		return NULL;
	}
	return filterbypretRepo(s->repo, pret);
}

OfertaRepo* filterbydata(Service* s, char* data) {

	if (s == NULL)
	{
		return NULL;
	}
	return filterbydataRepo(s->repo, data);
}

OfertaRepo* filterbytip(Service* s, char* tip)
{
	//Filtreaza ofertele care au un anumit tip
	//:param: tip (char*)
	//:return: ^un repository (OfertaRepo*)

	if (s == NULL)
	{
		return NULL;
	}
	return filterbytipRepo(s->repo, tip);
}

OfertaRepo* filterbydestinatie(Service* s, char* destinatie)
{
	//Filtreaza ofertele care au o anumita destinatie
	//:param: destinatie (char*)
	//:return: ^un repository (OfertaRepo*)

	if (s == NULL)
	{
		return NULL;
	}
	return filterbydestinatieRepo(s->repo, destinatie);
}

OfertaRepo* filterbytot(Service* s, char* destinatie, int pret) {

	if (s == NULL)
	{
		return NULL;
	}
	return filterbytotRepo(s->repo, destinatie, pret);
}

OfertaRepo* sortbydestinatie(Service* s)
{
	//Sorteaza dupa destinatie
	//:return: ^un repository (OfertaRepo*)

	if (s == NULL)
	{
		return NULL;
	}
	return sort(s->repo,compararedestinatie);
}

OfertaRepo* sortbypret(Service* s)
{
	//Sorteaza dupa pret
	//:return: ^un repository (OfertaRepo*)

	if (s == NULL)
	{
		return NULL;
	}
	//Oferta* o1 = NULL;
	//Oferta* o2 = NULL;
	return sort(s->repo,compararepret);
}

OfertaRepo* copyOfertaService(Service* s) {
	if (s == NULL) {
		return NULL;
	}
	return copyOfertaRepo(s->repo);
}

void undoService(Service* s, Vector* undoList) {
	s->repo = undo(s->repo, undoList);
}

//-----------Tests-------------
void testaddOferta()
{
	OfertaRepo* r = createRepo();
	Service* s = createService(r);
	assert(addOferta(s, "munte", "Fagaras", "1/1/1000", 100) == 1);
	assert(getLen(s) == 1);
	assert(getRepo(s) == r);
	destroyService(s);
}

void testfilter_sort()
{
	OfertaRepo* r = createRepo();
	Service* s = createService(r);
	assert(sortbypret(NULL) == NULL);
	assert(sortbydestinatie(NULL) == NULL);
	assert(filterbydestinatie(NULL,"Fagaras") == NULL);
	assert(filterbytip(NULL,"munte") == NULL);
	assert(filterbypret(NULL,100) == NULL);
	assert(sortbypret(NULL) == NULL);
	assert(sortbydestinatie(NULL) == NULL);
	assert(filterbydestinatie(NULL,"a") == NULL);
	assert(filterbytip(NULL,"a") == NULL);
	assert(filterbypret(NULL,200) == NULL);
	assert(filterbydata(NULL, "1/1/1000") == NULL);
	assert(filterbytot(NULL, "Brasov", 100) == NULL);
	destroyService(s);

	OfertaRepo* r2 = createRepo();
	Service* s2 = createService(r2);
	addOferta(s2, "munte", "Fagaras", "1/1/1000", 100);
	addOferta(s2, "munte", "Brasov", "1/1/1000", 50);

	OfertaRepo* rs1 = sortbypret(s2);
	assert(rs1 != NULL);
	destroyRepo(rs1);

	OfertaRepo* rs2 = sortbydestinatie(s2);
	assert(rs2 != NULL);
	destroyRepo(rs2);

	OfertaRepo* rf1 = filterbydestinatie(s2,"Fagaras");
	assert(rf1 != NULL);
	destroyRepo(rf1);

	OfertaRepo* rf2 = filterbytip(s2,"munte");
	assert(rf2 != NULL);
	destroyRepo(rf2);

	OfertaRepo* rf3 = filterbypret(s2,50);
	assert(rf3 != NULL);
	destroyRepo(rf3);

	OfertaRepo* rf4 = filterbydata(s2, "1/1/1000");
	assert(rf4 != NULL);
	destroyRepo(rf4);

	OfertaRepo* rf5 = filterbytot(s2, "Brasov", 60);
	assert(rf5 != NULL);
	destroyRepo(rf5);

	destroyService(s2);

}
void testdeleteOferta()
{
	OfertaRepo* r = createRepo();
	Service* s = createService(r);
	assert(addOferta(s, "munte", "Fagaras", "1/1/1000", 100) == 1);
	assert(deleteOferta(s, 0) == 1);
	destroyService(s);
	destroyService(NULL);
}

void testmodifyOferta()
{
	OfertaRepo* r = createRepo();
	Service* s = createService(r);
	assert(addOferta(s, "munte", "Fagaras", "1/1/1000", 100) == 1);
	assert(modifyOferta(s, 0, 100) == 1);
	destroyService(s);
}

void test_srv_copyOfertaRepo() {
	assert(copyOfertaService(NULL) == NULL);
	OfertaRepo* repo1 = createRepo();
	Service* serv = createService(repo1);
	addOferta(serv, "munte", "Fagaras", "20/10/2020", 200);
	OfertaRepo* repo = copyOfertaService(serv);

	assert(repo->oferte->length == serv->repo->oferte->length);
	assert(repo->oferte->capacity == serv->repo->oferte->capacity);
	assert(repo->oferte->destroyElemFct == serv->repo->oferte->destroyElemFct);

	destroyRepo(repo);
	destroyService(serv);
}

void test_srv_undo() {
	Vector* undoList_t = createVector(2, destroyRepo);
	OfertaRepo* repo = createRepo();
	Service* serv = createService(repo);

	addOferta(serv, "munte", "Fagaras", "20/10/2020", 200);
	addTElement(undoList_t, copyOfertaRepo(serv->repo));
	addOferta(serv, "mare", "Marea Neagra", "10/10/2020", 600);
	addTElement(undoList_t, copyOfertaRepo(serv->repo));
	addOferta(serv, "munte", "Brasov", "1/3/2019", 400);
	addTElement(undoList_t, copyOfertaRepo(serv->repo));

	assert(undoList_t->length == 3);
	assert(serv->repo->oferte->length == 3);
	undoService(serv, undoList_t);
	assert(serv->repo->oferte->length == 2);
	assert(undoList_t->length == 2);
	undoService(serv, undoList_t);
	assert(serv->repo->oferte->length == 1);
	assert(undoList_t->length == 1);
	undoService(serv, undoList_t);
	assert(serv->repo->oferte->length == 1);
	assert(undoList_t->length == 1);
	undoService(serv, undoList_t);
	assert(serv->repo->oferte->length == 1);
	assert(undoList_t->length == 1);

	destroyService(serv);
	destroyVector(undoList_t);
}

void testsService()
{
	testdeleteOferta();
	testmodifyOferta();
	testaddOferta();
	testfilter_sort();
	test_srv_copyOfertaRepo();
	test_srv_undo();
}