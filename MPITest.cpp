#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "mpi.h"

int pierwsza(int n)
{
	for (int i = 2; i*i <= n; i++)
		if (n%i == 0) return(0);

	return(1);
}


int main(int argc, char **argv)
{
	int myid, numprocs, P, K, N, part, wynik;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);

	
	if (argc != 3) {
		if(myid == 0)
			printf("Z³a iloœæ argumentów!\n");
		return 0;
	}
		
	P = atoi(argv[1]);
	K = atoi(argv[2]);
	N = numprocs;

	part = (P + K - 1) / N;

	int result = 0;

	

	for (int i = P + part * myid; i <= P + part * (myid + 1) - 1; i++) {
		if (pierwsza(i) == 1)
			result++;
	}
	
	MPI_Reduce(&result, &wynik, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

	int od = (K - P + 1) % N;

	if (myid == 0) {
		if (od != 0) {
			for (int i = K - od + 1; i <= K; i++) {
				if (pierwsza(i) == 1)
					wynik++;
			}
		}
		printf("%d\n", wynik);
	}
  
	MPI_Finalize();
}