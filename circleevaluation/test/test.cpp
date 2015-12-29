// test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "math.h"
#include "Brofiler.h"
#include <stdlib.h>

#define OFFSET_X 10
#define OFFSET_Y 10
#define NUM_STEPS 200.0

#define ANGLE360 6.28318531
#define ANGLE180 (ANGLE360/2.0)
#define ANGLE_STEP (ANGLE90/NUM_STEPS)
#define ANGLE90 (ANGLE180/2.0)
#define t_STEP	   (1.0/NUM_STEPS)
#define NUMBER_OF_TESTS 1

typedef  double real ;
typedef  long time_;

FILE *file;

void pointsNoSinCos(real &sum)
{
	//PROFILE

	sum = 0.0;
	
	for (real t = 0; t < 1; t += t_STEP)
	{
		real _2t = 2 * t;
		real _1mtp = 1 - t*t;
		real _1ptp = 1 + t*t;

        real x = _1mtp / _1ptp;
        real y = _2t/ _1ptp;

        fprintf(file,"%f %f %f\n",t, x, y);
       // fprintf(file,"%f %f %f\n",t, -x, y);

		sum += x;
		sum += y;
	}
}

void pointSinCos(real &sum)
{
	//PROFILE
    sum = 0.0;

	for (real t = 0.0; t < ANGLE90; t += ANGLE_STEP)
	{
        float y = sin(t);
        float x = cos(t);
		sum += x;
		sum += y;

        //fprintf(file,"%f %f %f\n",t, x, y);
        
	}
}

int main()
{
   // fopen_s(&file,"output.txt","w");
	{
	//	BROFILER_THREAD("Worker")

		real sum1 = (real)0.0;
        real sum2 = (real)0.0;
        time_ msec1 = 0;
        time_ msec2 = 0;

		real tempsum;

        for (unsigned int i = 0; i < NUMBER_OF_TESTS; i++)
		{
           
			time_ time1 = (time_)Profiler::GetTimeMicroSeconds();
			pointsNoSinCos(sum1);
            msec1 = (time_)Profiler::GetTimeMicroSeconds() - time1;
           
            time_ time2 = (time_)Profiler::GetTimeMicroSeconds();
			pointSinCos(sum2);  
			msec2 = (time_)Profiler::GetTimeMicroSeconds() - time2;
            

         
            printf("NoSinCos Timp %d  suma %f\n", msec1, sum1);
            printf("SinCos   Timp %d  suma %f\n", msec2, sum2);
            printf("-----\n");
		}
  
	
	}
    //fclose(file);
    scanf_s("%d");
    return 0;
}

