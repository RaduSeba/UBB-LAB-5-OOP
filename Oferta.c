#include "Oferta.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>

Oferta* createOferta(char* tip, char* destinatie, char* data, int pret)
{
	//Creare oferta
	//:param: tip(char*)
	//:param: destinatie(char*)
	//:param: data(char*)
	//:param: pret(int)
	//:retrun: oferta(Oferta*)

	Oferta* o = malloc(sizeof(Oferta));
	if (o == NULL)
	{
		return NULL;
	}
	o->tip = malloc(sizeof(char) * (strlen(tip) + 1));
	if (o->tip != NULL)
	{
		strcpy(o->tip, tip);
	}
	o->destinatie = malloc(sizeof(char) * (strlen(destinatie) + 1));
	if (o->destinatie != NULL)
	{
		strcpy(o->destinatie, destinatie);
	}
	o->data = malloc(sizeof(char) * (strlen(data) + 1));
	if (o->data != NULL)
	{
		strcpy(o->data, data);
	}
	o->pret = pret;

	return o;
}

void destroyOferta(Oferta* o)
{
	//Distrugere oferta si eliberare memorie

	if (o == NULL)
	{
		return;
	}

	free(o->tip);
	//o->tip = NULL;
	free(o->destinatie);
	//o->destinatie = NULL;
	free(o->data);
	//o->data = NULL;

	free(o);
	//o = NULL;
}

char* getTip(Oferta* o)
{
	//Returneaza tipul ofertei
	//:param: o(Oferta*)
	//:return: tip(char*)

	if (o == NULL)
	{
		return NULL;
	}
	return o->tip;
}

char* getDestinatie(Oferta* o)
{
	//Returneaza destinatia ofertei
	//:param: o(Oferta*)
	//:return: destinatie(char*)

	if (o == NULL)
	{
		return NULL;
	}
	return o->destinatie;
}

char* getData(Oferta* o)
{
	//Returneaza data ofertei
	//:param: o(Oferta*)
	//:return: data(char*)

	if (o == NULL)
	{
		return NULL;
	}
	return o->data;
}

int getPret(Oferta* o)
{	//Returneaza pretul ofertei
	//:param: o(Oferta*)
	//:return: pret(int)
	if (o == NULL)
	{
		return -1;
	}
	return o->pret;
}

int setPret(Oferta* o, int pret_nou)
{	//Seteaza pretul ofertei
	//:param: o(Oferta*)
	//:param: pret_nou(int)
	//:return: NULL/1 (not ok/ok)

	if (o == NULL)
	{
		return -1;
	}

	o->pret = pret_nou;

	return 1;
}

Oferta* copyO(Oferta* o)
{
	return createOferta(getTip(o), getDestinatie(o), getData(o), getPret(o));
}
void toString(Oferta* o, char str[])
{
	//Transforma oferta in string

	if (o == NULL)
	{
		return;
	}
	sprintf(str, "Oferta de tipul %s cu destinatia %s din data %s are pretul %d", getTip(o),getDestinatie(o), getData(o), getPret(o));
}

//-------------------Tests-------------------
void testget()
{
	Oferta* o = createOferta("munte", "Fagaras", "1/1/2021", 200);
	assert(strcmp(getData(o),"1/1/2021")==0);
	assert(strcmp(getDestinatie(o),"Fagaras") == 0);
	assert(getPret(o) == 200);
	assert(setPret(o, 100) == 1);
	assert(strcmp(getTip(o),"munte")==0);
	assert(strcmp(getData(o), "1/1/202") != 0);
	assert(strcmp(getDestinatie(o), "Fagas") != 0);
	assert(getPret(o) != 230);
	assert(setPret(o, 200) == 1);
	assert(strcmp(getTip(o), "mare") != 0);
	assert(setPret(NULL,100) == -1);
	assert(getData(NULL) == NULL);
	assert(getDestinatie(NULL) == NULL);
	assert(getPret(NULL) == -1);
	assert(getTip(NULL) == NULL);
	toString(NULL, "a");
	destroyOferta(o);
	destroyOferta(NULL);

}

void testsOferta()
{
	testget();
}
