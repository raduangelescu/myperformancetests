// speedtesthorner.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <time.h>

#define TEST_MAX (30)
#define TEST_NUMBER_OF_ITERATIONS (100000)
#define TEST_COEFF_MAX (10)
#define X_VALUE (1.2f)
#define CACHE_TESTS (20)

double polyEvalSimple(double x, double *coeff, unsigned int numCoeff)
{
	double xacc = 1;
	double finalValue = 0.0f;
	for (unsigned int i = 0; i < numCoeff; i++)
	{
		finalValue = finalValue + coeff[i] * xacc;
		xacc = xacc * x;
	}
	return finalValue;
}

double polyEvalHorner(double x, double *coeff, unsigned int numCoeff)
{
	double finalValue = 0.0f;
	for (int i = numCoeff-1; i >= 0 ; i--)
	{
		finalValue = finalValue* x + coeff[i];
	}
	return finalValue;
}

void initArrayRandom(double *coeff, unsigned int numCoeff)
{

	for (int i = 0; i < numCoeff; i++)
	{
		coeff[i] = rand()% TEST_COEFF_MAX;
	}
}

// long thin pipeline
double TestHorner(double ** polynome, double *value)
{
	//timing variables
	LARGE_INTEGER frequency;        // ticks per second
	LARGE_INTEGER t1, t2;           // ticks
	double elapsedTime;
	unsigned int i;
	// get ticks per second
	QueryPerformanceFrequency(&frequency);

	QueryPerformanceCounter(&t1);

	for (i = 0; i < TEST_NUMBER_OF_ITERATIONS; i++)
	{
		*value = polyEvalHorner(X_VALUE, polynome[i], TEST_MAX);
	}
	// stop timer
	QueryPerformanceCounter(&t2);
	elapsedTime = (t2.QuadPart - t1.QuadPart) * 1000.0 / frequency.QuadPart;
	return elapsedTime;
}

double TestSimple(double ** polynome, double *value)
{
	//timing variables
	LARGE_INTEGER frequency;        // ticks per second
	LARGE_INTEGER t1, t2;           // ticks
	double elapsedTime;
	unsigned int i;
	// get ticks per second
	QueryPerformanceFrequency(&frequency);

	QueryPerformanceCounter(&t1);

	for (i = 0; i < TEST_NUMBER_OF_ITERATIONS; i++)
	{
		*value = polyEvalSimple(X_VALUE, polynome[i], TEST_MAX);
	}
	// stop timer
	QueryPerformanceCounter(&t2);
	elapsedTime = (t2.QuadPart - t1.QuadPart) * 1000.0 / frequency.QuadPart;
	return elapsedTime;
}

int main()
{
	// test polynomials
	double **polynome;
	//counter variable
	unsigned int i;
	
	// Hold these so the compiler does not optimize the whole block
	double valSimple = 0.0;
	double valHorner = 0.0;
	
	srand(time(NULL));

	// alllocate memory for polynomials
	polynome = (double **)malloc(TEST_NUMBER_OF_ITERATIONS * sizeof(double*));
	for (i = 0; i < TEST_NUMBER_OF_ITERATIONS; i++)
	{
		polynome[i] = (double*)malloc(TEST_MAX * sizeof(double));
	}
	// initialize polynomials
	for (i = 0; i < TEST_NUMBER_OF_ITERATIONS; i++)
	{
		initArrayRandom(polynome[i], TEST_MAX);
	}

	for (unsigned int j = 0; j < CACHE_TESTS; j++)
	{
		double elapsedTimeSimple = TestSimple(polynome, &valSimple);
		double elapsedTimeHorner = TestHorner(polynome, &valHorner);
		
		printf("Simple Time: %f Horner Timer: %f \n Simple Value: %f , Horner Value: %f \n\n", elapsedTimeSimple, elapsedTimeHorner, valSimple, valHorner);
	}

	for (i = 0; i < TEST_NUMBER_OF_ITERATIONS; i++)
	{
		free(polynome[i]);
	}

	free(polynome);

    return 0;
}

