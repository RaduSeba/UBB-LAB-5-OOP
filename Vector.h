#pragma once

typedef void* TElement;
typedef void (*DestroyElementFunctionType)(void*);

typedef struct
{
	TElement* elems;
	int length;
	int capacity;
	DestroyElementFunctionType destroyElemFct;
} Vector;

Vector* createVector(int capacity, DestroyElementFunctionType destroyElemFct);

void destroyVector(Vector* arr);

int resizeVector(Vector* arr);

void addTElement(Vector* arr, TElement t);

void deleteTElement(Vector* arr, int pos);

int getVectorLength(Vector* arr);

void swapTElemets(Vector* arr, int index1, int index2);

TElement get(Vector* arr, int pos);

void testsVector();