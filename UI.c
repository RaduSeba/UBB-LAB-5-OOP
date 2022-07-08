
#include "UI.h"
#include<stdio.h>
#include <stdlib.h>
#include<string.h>

UI* createUI(Service* s)
{
	//Creeare UI

	UI* ui = malloc(sizeof(UI));
	if (ui == NULL)
	{
		return NULL;
	}
	ui->serv = s;
	return ui;
}

void destroyUI(UI* ui)
{
	//Distrugere UI

	if (ui == NULL)
	{
		return;
	}

	destroyService(ui->serv);

	free(ui);
}

void printMenu()
{
	//Printare meniu

	printf("\n-----------------------------\n");
	printf("1 - Adauga oferta\n");
	printf("2 - Actualizeaza oferta\n");
	printf("3 - Sterge oferta\n");
	printf("4 - Afisare oferte\n");
	printf("5 - Sortare\n");
	printf("6 - Filtrare in functie de criteriu\n");
	printf("7 - Undo\n");
	printf("8 - Filtrare in functie de data\n");
	printf("9 - Filtrare in functie de destinatia data si pret <= cel dat\n");
	printf("0 - Iesire\n");
	printf("-------------------------------\n");
}

void printOferte(OfertaRepo* repo)
{
	//Printare oferte dintr-un repository
	//:param: repo (OfertaRepo*)

	printf("\n");
	int len = getLength(repo);
	if (len == 0)
	{
		printf("Nu exista oferte!\n");
		return;
	}

	for (int i = 0; i < len; i++)
	{
		Oferta* oferta = getOfertaOnPos(repo, i);

		char ostring[200];
		toString(oferta, ostring);
		printf("%d) %s\n", i, ostring);

	}
}

int readIntegerNumber(const char* message)
{
	//Citire un numar intreg

	char s[16] = { 0 };
	int res = 0;
	int flag = 0;
	int r = 0;

	while (flag == 0)
	{
		printf(message);
		int scanf_result = scanf("%15s", s);

		if (scanf_result == 0)
		{

		}

		r = sscanf(s, "%d", &res);	
		flag = (r == 1);
		if (flag == 0)
			printf("Introduceti un numar!\n");
	}
	return res;
}

int validCommand(int command)
{
	//Validare comanda	
	//:param: command(int)

	if (command >= 0 && command <= 9)
		return 1;
	return 0;
}

int addOfertaUI(UI* ui)
{
	//Adaugare oferta noua

	char tip[30] = { 0 }, destinatie[30] = { 0 }, data[11] = { 0 };
	int pret=0;
	printf("*Tipuri: munte, mare, city break\n");
	printf("*Data format: dd/mm/yyy\n");
	printf("*Pretul sa fie numar\n\n");

	printf(">>Introduceti un tip: ");
	int s_r = scanf("%29s", tip);
	printf(">>Introduceti o destinatie: ");
	s_r = scanf("%29s", destinatie);
	printf(">>Introduceti o data: ");
	int s_d = scanf("%29s", data);
	if (s_d == 0)
	{

	}
	printf(">>Introduceti un pret: ");
	s_r = scanf("%d", &pret);

	if (strcmp(tip, "munte") != 0 && strcmp(tip, "city break") != 0 && strcmp(tip, "mare") != 0)
	{
		printf("!!! Tip invalid !!!\n");
		return 0;
	}

	if (s_r == 0)
	{
		printf("!!! Pret invalid !!!\n");
		return 0;
	}
	return addOferta(ui->serv, tip, destinatie, data, pret);
}

int deleteOfertaUI(UI* ui)
{
	//Stergere oferta

	int nr;
	printf("--Introduceti numarul ofertei: ");
	int s_r = scanf("%d", &nr);

	if (nr < 0 || nr >= getLen(ui->serv))
	{
		printf("!!! Nu exista oferta cu acest numar !!!\n");
		return 0;
	}
	OfertaRepo* repo = getRepo(ui->serv);
	Oferta* oferta = getOfertaOnPos(repo, nr);

	char ostring[200];
	toString(oferta, ostring);
	printf("%d) %s\n", nr, ostring);
	printf("Sigur vreti sa stergeti aceasta oferta(yes):");

	char answer[10] = { 0 };
	s_r = scanf("%s", answer);
	if (strcmp("yes",answer) == 0)
	{
		return deleteOferta(ui->serv, nr);
	}
	printf("Stergere anulata!\n");
	return 0;
}

int modifyOfertaUI(UI* ui)
{
	//Modificare oferta

	int nr, pret;
	printf("--Introduceti numarul ofertei: ");
	int s_r = scanf("%d", &nr);
	
	if (nr < 0 || nr >= getLen(ui->serv))
	{
		printf("!!! Nu exista oferta cu acest numar !!!\n");
		return 0;
	}
	
	printf("--Introduceti un pret nou: ");
	s_r = scanf("%d", &pret);

	return modifyOferta(ui->serv, nr, pret);
}

void filtrareCriteriuUI(UI* ui)
{
	//Filtrare dupa un criteriu

	if (ui == NULL)
	{
		return;
	}

	printf(">>Introduceti un criteriu: destinatie, tip, pret: ");
	char criteriu[100] = { 0 };
	int res_scanf = scanf("%s", &criteriu);

	OfertaRepo* repo = NULL;
	if (strcmp("destinatie", criteriu) == 0)
	{
		printf(">>Introduceti o destinatie: ");
		char destinatie[100] = { 0 };
		res_scanf = scanf("%s", &destinatie);
		repo = filterbydestinatie(ui->serv, destinatie);
	}
	else if (strcmp("tip", criteriu) == 0)
	{
		printf(">>Introduceti un tip: ");
		char tip[100] = { 0 };
		res_scanf = scanf("%s", &tip);
		repo = filterbytip(ui->serv, tip);
	}
	else if (strcmp("pret", criteriu) == 0)
	{
		printf(">>Introduceti un pret: ");
		int pret;
		res_scanf = scanf("%d", &pret);
		repo = filterbypret(ui->serv, pret);
	}
	else
	{
		printf("Criteriu invalid!");
		return;
	}
	printOferte(repo);
	destroyRepo(repo);
}

void filtrareDataUI(UI* ui)
{
	//Filtrare dupa un criteriu

	if (ui == NULL)
	{
		return;
	}

	OfertaRepo* repo = NULL;
	printf(">>Introduceti o data: ");
	char data[11] = { 0 };
	int res_scanf;
	res_scanf = scanf("%10s", &data);
	repo = filterbydata(ui->serv, data);
	printOferte(repo);
	destroyRepo(repo);
}

void filtrareTotUi(UI* ui) 
{
	//Filtrare dupa un criteriu

	if (ui == NULL)
	{
		return;
	}

	OfertaRepo* repo = NULL;
	printf(">>Introduceti o destinatie: ");
	char destinatie[100] = { 0 };
	int res_scanf;
	res_scanf = scanf("%s", &destinatie);
	printf(">>Introduceti un pret: ");
	int pret, res_scanf2;
	res_scanf2 = scanf("%d", &pret);
	repo = filterbytot(ui->serv, destinatie, pret);
	printOferte(repo);
	destroyRepo(repo);
} 

void sortareUI(UI* ui)
{
	//Sortare oferte

	printf("1 - pret\n");
	printf("2 - destinatie\n");
	printf("Alegeti in functie de ce sa sortati: ");
	int command;
	int res_scan = scanf("%d", &command);
	if (res_scan == 0)
	{

	}

	OfertaRepo* repo = NULL;
	if (command == 1)
	{
		repo = sortbypret(ui->serv);
	}
	else if (command == 2)
	{
		repo = sortbydestinatie(ui->serv);
	}
	else
	{
		printf("Numa 1 si 2 este....\n");
		return ;
	}
	
	printOferte(repo);
	destroyRepo(repo);
}

void undoUI(UI* ui, Vector* undoList) {
	undoService(ui->serv, undoList);
}

void startUI(UI* ui, Vector* undoList)
{	
	//Start UI
	addTElement(undoList, copyOfertaService(ui->serv));

	while (1)
	{
		printMenu();

		int comanda = readIntegerNumber("Introduceti o comanda: ");
		while (validCommand(comanda) == 0)
		{
			printf("Comanda nu este valida!\n");
			comanda = readIntegerNumber("Introduceti o comanda: ");
		}
		if (comanda == 0)
		{
			break;
		}
		switch (comanda)
		{
			case 1:
			{
				int res = addOfertaUI(ui);
				if (res == 1)
				{
					printf("Adaugare efectuata cu succes!");
					addTElement(undoList, copyOfertaService(ui->serv));
				}
				else
				{
					printf("Eroare la adaugare!");
				}
				break;
			}
			case 2:
			{
				int res = modifyOfertaUI(ui);
				if (res == 1)
				{
					printf("Modificare efectuata cu succes!");
					addTElement(undoList, copyOfertaService(ui->serv));
				}
				else
				{
					printf("Eroare la modificare!");
				}
				break;
			}
			case 3:
			{
				int res = deleteOfertaUI(ui);
				if (res == 1)
				{
					printf("Stergere efectuata cu succes!");
					addTElement(undoList, copyOfertaService(ui->serv));
				}
				else
				{
					printf("Eroare la stergere!");
				}
				break;
			}
			case 4:
			{
				OfertaRepo* repo = getRepo(ui->serv);
				printOferte(repo);
				break;
			}
			case 5:
			{
				sortareUI(ui);
				break;
			}
			case 6:
			{
				filtrareCriteriuUI(ui);
				break;
			}
			case 7:
			{
				undoUI(ui, undoList);
				break;
			}
			case 8:
			{
				filtrareDataUI(ui);
				break;
			}
			case 9: 
			{
				filtrareTotUi(ui);
				break;
			}
		}
	}
}