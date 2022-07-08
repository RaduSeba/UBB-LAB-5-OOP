#pragma once

typedef struct
{
	char* tip;
	char* destinatie;
	char* data;
	int pret;
} Oferta;

Oferta* createOferta(char* tip, char* destinatie, char* data, int pret);
void destroyOferta(Oferta* o);

char* getTip(Oferta* o);
char* getDestinatie(Oferta* o);
char* getData(Oferta* o);
int getPret(Oferta* o);
int setPret(Oferta* o, int pret_nou);

void toString(Oferta* o, char str[]);
Oferta* copyO(Oferta* o);

void testsOferta();