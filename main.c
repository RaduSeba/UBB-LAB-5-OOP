#include<stdio.h>
#include "OfertaRepository.h"
#include "UI.h"
#include "Oferta.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h> 

int main()
{
	//Functia principala main

	testsrepo();
	testsService();
	testsOferta();
	testsVector();

	OfertaRepo* repo = createRepo();
	Service* serv = createService(repo);

	UI* ui = createUI(serv);
	Vector* undoList = createVector(2, destroyRepo);


	addOferta(serv, "munte", "Fagaras", "20/10/2020", 200);
	addOferta(serv, "mare", "Marea Neagra", "10/10/2020", 600);
	addOferta(serv, "munte", "Brasov", "1/3/2019", 400);
	addOferta(serv, "mare", "Delta", "4/4/2018", 700);
	addOferta(serv, "munte", "Sinaia", "4/4/2018", 800);
	addOferta(serv, "munte", "Sinaia", "5/9/2021", 600);
	startUI(ui, undoList);

	destroyVector(undoList);
	destroyUI(ui);
	_CrtDumpMemoryLeaks();
	return 0;
}