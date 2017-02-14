#include<stdio.h>
#include<omp.h>

int main()
{
	double start, end;
	start = omp_get_wtime();
	long count = 0;
	long i;
#pragma omp parallel for schedule(auto) reduction(+:count) num_threads(100)
	for (i = 1; i <= 2147483647; i++)
		if (i % 2 != 0)	count++;
	end = omp_get_wtime();
	printf("%f seconds, result is %li\n", end-start, count);
	return 0;
}
