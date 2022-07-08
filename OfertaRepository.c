#include "OfertaRepository.h"
#include "Oferta.h"
#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>

OfertaRepo* createRepo()
{
	//Creeare repository

	OfertaRepo* r = (OfertaRepo*)malloc(sizeof(OfertaRepo));
	if (r == NULL)
	{
		return NULL;
	}
	r->oferte = createVector(2, destroyOferta);
	return r;
}

void destroyRepo(OfertaRepo* r)
{
	//Distrugere repository - eliberare memorie

	if (r == NULL)
	{
		return;
	}

	destroyVector(r->oferte);
	free(r);
}

int getLength(OfertaRepo* r)
{
	//Returneaza lungimea repository-ului (int)

	return getVectorLength(r->oferte);
}

int add(OfertaRepo* r, Oferta* o)
{
	// Adauga o oferta
	//:param: oferta (Oferta*)
	//:return: -1/1 (not ok, ok)

	if (r == NULL || o == NULL)
	{
		return -1;
	}
	addTElement(r->oferte, o);

	return 1;
}

int deleteO(OfertaRepo* r, int nr)
{
	// Sterge o oferta
	//:param: nr(int)
	//return 0/1 (not ok/ok)

	if (nr < 0 || nr >= getVectorLength(r->oferte))
	{
		return 0;
	}
	deleteTElement(r->oferte, nr);
	return 1;
}

int modifyO(OfertaRepo* r, int nr,int pret)
{
	//Modifica o oferta
	//:param: nr(int)
	//:param: pret(int)
	//return 0/1 (not ok/ ok)

	if (nr < 0 || nr >= getVectorLength(r->oferte))
	{
		return 0;
	}
	
	setPret(get(r->oferte, nr), pret);
	return 1;
}

Oferta* getOfertaOnPos(OfertaRepo* v, int pos)
{
	//Retureaza o oferta in functie de o pozitie
	//:param: pos(int)
	//:return oferta(Oferta*)

	if (v == NULL)
	{
		return NULL;
	}
	if (pos < 0 || pos >= getVectorLength(v->oferte))
	{
		return NULL;
	}
	return get(v->oferte,pos);
}

OfertaRepo* filterbypretRepo(OfertaRepo* r, int pret)
{
	//Returneaza un nou repoistory cu oferte care au un anumit pret
	//:param: pret (int)
	//:return: ^un repository (OfertaRepo*)

	OfertaRepo* repo_nou = createRepo();

	for (int i = 0; i < getLength(r); i++)
	{
		Oferta* oferta = getOfertaOnPos(r, i);
		if (getPret(oferta) == pret)
		{
			add(repo_nou, copyO(oferta));
		}
	}
	return repo_nou;
}

OfertaRepo* filterbydataRepo(OfertaRepo* r, char* data) {

	OfertaRepo* repo_nou = createRepo();

	for (int i = 0; i < getLength(r); i++)
	{
		Oferta* oferta = getOfertaOnPos(r, i);
		if (!strcmp(getData(oferta), data))
		{
			add(repo_nou, copyO(oferta));
		}
	}
	return repo_nou;
}

OfertaRepo* filterbytipRepo(OfertaRepo* r, char* tip)
{
	//Returneaza un nou repository cu oferte care au un anumit tip
	//:param: tip (char*)
	//:return: ^un repository (OfertaRepo*)

	OfertaRepo* repo_nou = createRepo();

	for (int i = 0; i < getLength(r); i++)
	{
		Oferta* oferta = getOfertaOnPos(r, i);
		if (strcmp(tip, getTip(oferta)) == 0)
		{
			add(repo_nou, copyO(oferta));
		}
	}
	return repo_nou;
}

OfertaRepo* filterbydestinatieRepo(OfertaRepo* r, char* destinatie)
{
	//Returneaza un nou repository cu oferte care au o anumita destinatie
	//:param: destinatie (char*)
	//:return: ^un repository (OfertaRepo*)
	OfertaRepo* repo_nou = createRepo();

	for (int i = 0; i < getLength(r); i++)
	{
		Oferta* oferta = getOfertaOnPos(r, i);
		if (strcmp(destinatie, getDestinatie(oferta)) == 0)
		{
			add(repo_nou, copyO(oferta));
		}
	}
	return repo_nou;
}

OfertaRepo* filterbytotRepo(OfertaRepo* r, char* destinatie, int pret) {
	OfertaRepo* repo_nou = createRepo();
	for (int i = 0; i < getLength(r); i++)
	{
		Oferta* oferta = getOfertaOnPos(r, i);
		if (strcmp(destinatie, getDestinatie(oferta)) == 0 && getPret(oferta) <= pret)
		{
			add(repo_nou, copyO(oferta));
		}
	}
	return repo_nou;
}

int compararedestinatie(Oferta* o1, Oferta* o2)
{
	if (strcmp(getDestinatie(o1), getDestinatie(o2)) > 0)
	{
		return 1;
	}
	return 0;
}

int compararepret(Oferta* o1, Oferta* o2)
{
	if (getPret(o1) > getPret(o2))
	{
		return 1;
	}
	return 0;
}
OfertaRepo* sort(OfertaRepo* r, int (*cmp)(Oferta* o1, Oferta* o2))
{
	
		//Returneaza un repository nou sortat dupa destinatie
		//:return: ^un repository (OfertaRepo*)

		OfertaRepo* repo_nou = createRepo();
		int len = getLength(r);

		for (int i = 0; i < len; i++)
		{
			add(repo_nou, copyO(get(r->oferte, i)));
		}
		int ok = 0;
		while (ok == 0)
		{
			ok = 1;
			for (int i = 0; i < len - 1; i++)
			{
				Oferta* st = get(repo_nou->oferte, i);
				Oferta* dr = get(repo_nou->oferte, i + 1);
				if (cmp(st,dr))
				{
					swapTElemets(repo_nou->oferte, i, i + 1);
					ok = 0;
				}
			}
		}
		return(repo_nou);
	
}

OfertaRepo* copyOfertaRepo(OfertaRepo* r) {
	OfertaRepo* copy = createRepo();
	int i = 0;
	for (; i < r->oferte->length; i++)
		addTElement(copy->oferte, copyO(r->oferte->elems[i]));
	copy->oferte->destroyElemFct = r->oferte->destroyElemFct;
	return copy;
}


OfertaRepo* undo(OfertaRepo* r, Vector* undoList) {
	if (undoList->length > 1) {
		OfertaRepo* l = copyOfertaRepo(undoList->elems[undoList->length - 2]);
		deleteTElement(undoList, undoList->length - 1);
		destroyRepo(r);
		return l;
	}
	return r;
}

///---------------------TESTS------------------

void testgetOpos()
{
	OfertaRepo* tr = createRepo();
	Oferta* o = createOferta("munte", "Fagaras", "1/1/2021", 200);
	add(tr, o);
	o = getOfertaOnPos(tr, 0);
	assert(o->pret == 200);
	assert(getOfertaOnPos(tr, 10) == NULL);
	assert(getOfertaOnPos(tr, 20) == NULL);
	assert(getOfertaOnPos(NULL, 10) == NULL);
	destroyRepo(tr);
}

void testadd()
{
	OfertaRepo* tr = createRepo();
	Oferta* o = createOferta("munte", "Fagaras", "1/1/2021", 200);
	add(tr, o);
	assert(getLength(tr)== 1);
	o = createOferta("mare", "Marea Neagra", "1/1/2020", 300);
	assert(add(tr, o) == 1);
	assert(getLength(tr) == 2);
	assert(getLength(tr) != 3);
	assert(add(tr, NULL) == -1);
	destroyRepo(tr);
}

void testdelete()
{
	OfertaRepo* tr = createRepo();
	Oferta* o = createOferta("munte", "Fagaras", "1/1/2021", 200);
	add(tr, o);
	assert(getLength(tr) == 1);
	o = createOferta("mare", "Marea Neagra", "1/1/2020", 300);
	assert(add(tr, o) == 1);
	assert(getLength(tr) == 2);

	assert(deleteO(tr, 0) == 1);
	assert(deleteO(tr, 100) == 0);
	assert(getLength(tr) == 1);

	assert(deleteO(tr, 0) == 1);
	assert(deleteO(tr, 100) == 0);
	assert(getLength(tr) == 0);

	destroyRepo(tr);

	destroyRepo(NULL);
}

void testmodify()
{
	OfertaRepo* tr = createRepo();
	Oferta* o = createOferta("munte", "Fagaras", "1/1/2021", 200);
	add(tr, o);
	assert(getLength(tr) == 1);
	o = createOferta("mare", "Marea Neagra", "1/1/2020", 300);
	assert(add(tr, o) == 1);
	assert(getLength(tr) == 2);

	assert(modifyO(tr, 0, 100) == 1);
	assert(modifyO(tr, 100, 100) == 0);

	assert(modifyO(tr, 0, 200) == 1);
	assert(modifyO(tr, 200, 100) == 0);
	destroyRepo(tr);
}

void test_copyOfertaRepo() {
	OfertaRepo* repo1 = createRepo();
	OfertaRepo* repo = copyOfertaRepo(repo1);

	assert(repo->oferte->length == repo->oferte->length);
	assert(repo->oferte->capacity == repo->oferte->capacity);
	assert(repo->oferte->destroyElemFct == repo->oferte->destroyElemFct);

	destroyRepo(repo);
	destroyRepo(repo1);
}

void test_undo() {
	Vector* undoList_t = createVector(2, destroyRepo);
	OfertaRepo* repo = createRepo();

	add(repo, createOferta("munte", "Fagaras", "20/10/2020", 200));
	addTElement(undoList_t, copyOfertaRepo(repo));
	add(repo, createOferta("mare", "Marea Neagra", "10/10/2020", 600));
	addTElement(undoList_t, copyOfertaRepo(repo));
	add(repo, createOferta("munte", "Brasov", "1/3/2019", 400));
	addTElement(undoList_t, copyOfertaRepo(repo));

	assert(undoList_t->length == 3);
	assert(repo->oferte->length == 3);
	repo = undo(repo, undoList_t);
	assert(repo->oferte->length == 2);
	assert(undoList_t->length == 2);
	repo = undo(repo, undoList_t);
	assert(repo->oferte->length == 1);
	assert(undoList_t->length == 1);
	repo = undo(repo, undoList_t);
	assert(repo->oferte->length == 1);
	assert(undoList_t->length == 1);
	repo = undo(repo, undoList_t);
	assert(repo->oferte->length == 1);
	assert(undoList_t->length == 1);

	destroyRepo(repo);
	destroyVector(undoList_t);
}

void testsrepo()
{
	testadd();
	testdelete();
	testmodify();
	testgetOpos();
	test_copyOfertaRepo();
	test_undo();
}