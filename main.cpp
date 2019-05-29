#include <iostream>
#include <fstream>
#include <string>
#include "Graph.h"
#include "BF.h"
#include "mpi.h"

using namespace std;


int main(int argc, char* argv[])
{
	int myid, numprocs, bestCost = 0;
	
	fstream file;
	Graph *graph;
	BF *bf;

	unsigned long long silnia = 1;

	file.open("input.txt", ios::in);
	graph = new Graph(file);
	file.close();

	int count = graph->getCount();

	for (int i = 1; i < count; i++)
		silnia *= i;

	bf = new BF(graph);

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);

	unsigned long long part = silnia / numprocs;
			
	bf->BF_solve(myid * part, (myid + 1) * part - 1, silnia);
	
	bf->get_best_route();

	int cost = bf->get_best_cost();

	MPI_Reduce(&cost, &bestCost, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);

	int od = silnia % numprocs;

	if (myid == 0) {
		if (od != 0) {
			bf->BF_solve(silnia - od, silnia, silnia);
			if (bf->get_best_cost() < bestCost)
				bestCost = bf->get_best_cost();
		}
		cout<<bestCost<<endl;
	}
	
	if(myid == 0){
		delete graph;
		delete bf;
	}

	MPI_Finalize();

	return 0;
}
