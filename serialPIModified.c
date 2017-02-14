#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

static long num_steps = 1000000000;

int main(){
	int i;
	double step, start, end, pi, sum = 0.0;
	step = 1.0/num_steps;
	omp_set_num_threads(8);
	int n;
	int chunk_size;
	for(chunk_size = 10; chunk_size<=100000; chunk_size*=10){
		start = omp_get_wtime();
		sum = 0;
#pragma omp parallel
		{
			if(omp_get_thread_num() == 0)n=omp_get_num_threads();
			double x; 
#pragma omp for schedule(auto) reduction(+:sum) //num_threads(8)
			for(i = 0; i < (int)num_steps; i++){
				x = (i+0.5)*step;
				sum += 4.0/(1.0+x*x);
			}
		}
		pi = step*sum;
		end = omp_get_wtime();
		printf("CHUNK SIZE %d\nResult is %f, this one has used %d threads, time is %f seconds.\n",chunk_size, pi, n, end - start);
	}
}
