#pragma once
#include "Service.h"

typedef struct
{
	Service* serv;
}UI;

void printOferte(OfertaRepo*);

UI* createUI(Service* s);

void destroyUI(UI* ui);

void startUI(UI* ui, Vector* undoList);