#include "Vector.h"
#include "Oferta.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
//#include <stdio.h>

Vector* createVector(int capacity, DestroyElementFunctionType destroyElemFct)
{
	Vector* da = (Vector*)malloc(sizeof(Vector));

	da->capacity = capacity;
	da->length = 0;

	da->elems = (TElement*)malloc(capacity * sizeof(TElement));
	if (da->elems == NULL)
		return NULL;

	da->destroyElemFct = destroyElemFct;

	return da;
}

void destroyVector(Vector* arr)
{
	if (arr == NULL)
		return;

	for (int i = 0; i < arr->length; i++)
		arr->destroyElemFct(arr->elems[i]);

	free(arr->elems);
	arr->elems = NULL;

	free(arr);
	arr = NULL;
}


int resizeVector(Vector* arr)
{
	if (arr == NULL)
		return -1;

	arr->capacity *= 2;

	TElement* aux = (TElement*)realloc(arr->elems, arr->capacity * sizeof(TElement));
	if (aux == NULL)
		return - 1;
	//free(arr->elems);
	arr->elems = aux;

	// version 2 - allocate new memory, copy everything and deallocate the old memory
	/*TElement* aux = (TElement*)malloc(arr->capacity * sizeof(TElement));
	if (aux == NULL)
		return -1;
	for (int i = 0; i < getVectorLength(arr); i++)
		aux[i] = arr->elems[i];*/
	//free(arr->elems);
	//arr->elems = aux;

	return 0;
}

void addTElement(Vector* arr, TElement t)
{
	if (arr == NULL)
		return;
	if (arr->elems == NULL)
		return;

	if (arr->length == arr->capacity)
		resizeVector(arr);
	arr->elems[arr->length++] = t;
}

void deleteTElement(Vector* arr, int pos)
{
	if (arr == NULL || pos < 0 || pos >= arr->length)
		return;

	arr->destroyElemFct(arr->elems[pos]);

	if (pos != arr->length - 1)
		arr->elems[pos] = arr->elems[arr->length - 1];
	arr->length--;

}

int getVectorLength(Vector* arr)
{
	if (arr == NULL)
		return -1;

	return arr->length;
}

void swapTElemets(Vector* arr, int index1, int index2)
{
	if (arr == NULL)
	{
		return;
	}
	TElement* aux = arr->elems[index1];
	arr->elems[index1] = arr->elems[index2];
	arr->elems[index2] = aux;
}
TElement get(Vector* arr, int pos)
{
	if (arr == NULL || pos < 0)
		return NULL;
	return arr->elems[pos];
}

// ------------------------------------------------------------------------------------------------------------

void testsVector()
{
	//Vector* v = createVector(10, destroyOferta);
	//Oferta* o1;
	//o1 = createOferta("a", "a", "a", 100);
	//addTElement(v,o1);
	////destroyOferta(o1);
	//destroyVector(v);

	Vector* v = createVector(1,destroyOferta);
	Oferta  *o1, *o2, *o3;
	o1 = createOferta("a", "a", "a", 100);
	o2 = createOferta("b", "b", "b", 200);
	o3 = createOferta("c", "c", "c", 300);
	addTElement(v, o1);
	addTElement(v, o2);
	addTElement(v, o3);
	swapTElemets(v, 1, 2);
	deleteTElement(v, 10);
	destroyVector(v);
	assert(resizeVector(NULL) == -1);
	swapTElemets(NULL, 1, 2);
	assert(get(NULL, 10) == NULL);
	assert(getVectorLength(NULL) == -1);
	addTElement(NULL, NULL);
	destroyVector(NULL);
	/*Vector* v2 = createVector(3, destroyOferta);
	addTElement(v2, o1);
	addTElement(v2, o2);
	addTElement(v2, o3);
	destroyVector(v2);*/
	/*Vector* v3 = createVector(SIZE_MAX, destroyOferta);
	resizeVector(v3);
	destroyVector(v3);*/
}