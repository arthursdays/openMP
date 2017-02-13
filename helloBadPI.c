/*This program aims to use 
  multithread to calculate the
  integration of 4/(1+x^2) from 0 to 1
  by dividing the surface to many rectangles
  and calculate the sum of their surface
  area.

  It will be easy to examine the 
  integration since the result
  it suppose to be PI.
  */
#include<stdlib.h>
#include<stdio.h>
#include<omp.h>	
static double num_steps = 100000000;	//the number of rectangles divided
double step, start, end;	//initialization of start and end time and setps
int noomp();	//initialize the function, the same for next instruction
int wiomp();	

//no explaination
int main()
{
	noomp();	//call the functions
	wiomp();
	return 0;


}

//this function calculate the result of this integration
//noomp means no opemMP is used(single thread)
int noomp()
{
	int i; double x,pi,sum = 0.0; 

	step=1.0/(double)num_steps;	//calculate the width of rectangle
	start = omp_get_wtime();	//get the start time
	for(i=0;i<num_steps;i++)	//for loop to calculate every rectangle height
	{
		x = (i+0.5)*step;	//calculate the x-vlaue of rectangle
		sum = sum + 4.0/(1.0+x*x);	//calculate the height of rectanlge and add them tgz
	}
	pi = step*sum;	//use step multiply sum to get the the size of the area
	end = omp_get_wtime();	//get the end time
	printf("Without multithreading, it takes %f seconds to process, result is %f\n", end-start, pi);
	return 0;
}

//this function calculate the result of this integration
//wiomp means with opemMP
int wiomp()
{
	int n;
	for(n=1; n<7; n++)
	{
#define NUM_THREADS n
		double pi=0.0;
		double sum[n];
		int nthrds = 0;
		step=1.0/(double)num_steps;	//calculate the width of rectangle
		omp_set_num_threads(NUM_THREADS);		//openMP command to set the threads to use
		start = omp_get_wtime();	//get the start time
#pragma omp parallel //num_threads(NUM_THREADS)	//command to use multithread
		{
			double x = 0;
			int i = 0;
			int id = omp_get_thread_num();	//get the current thread being used
			int nthreads = omp_get_num_threads();
			if(id == 0){
				nthrds = nthreads;
				printf("This one has used %d threads\n", nthrds);
			}
			for(i = id ,sum[id]=0; i<num_steps;i+=nthreads)	//for loop to assign rectangles by thread number and calculate every rectangle height
			{

				x = (i+0.5)*step;	//calculate the x-vlaue of rectangle assigned to different threads
#pragma omp critical
				pi += 4.0/(1.0+x*x);
			}
		}
		pi *= step;
		end = omp_get_wtime();	//get end time
		printf("%d threads takes %f time to process, result is %f\n", n, end-start, pi);
	}
	return 0;
}
