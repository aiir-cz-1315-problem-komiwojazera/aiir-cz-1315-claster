#include <iostream>
#include <fstream>
#include <string>
#include "Graph.h"
#include "BF.h"
#include "mpi.h"

using namespace std;

int calcCost(int count, int *route, int **matrix) {
	int tempCost = 0;
	for (int i = 0; i < count; i++) 
		tempCost += matrix[route[i]][route[i + 1]];
		
	return tempCost;

}

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
	
	int **routes = new int *[numprocs];

	for (int i = 0; i < numprocs; i++) {
		routes[i] = new int[count + 1];
	}

	bf->BF_solve(myid * part, (myid + 1) * part - 1, silnia);

	int cost = bf->get_best_cost();

	if (myid == 0) {
		routes[0] = bf->get_best_route();

		for (int i = 1; i < numprocs; i++) 
			MPI_Recv(routes[i], count + 1, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		
	}
	else 
		MPI_Send(bf->get_best_route(), count + 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
	
	
	MPI_Reduce(&cost, &bestCost, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);
	
	int od = silnia % numprocs;

	if (myid == 0) {
		if (od != 0) {
			bf->BF_solve(silnia - od, silnia, silnia);
			if (bf->get_best_cost() < bestCost)
				bestCost = bf->get_best_cost();
		}

		int *finalRoute = bf->get_best_route();
		
		for (int i = 0; i < numprocs; i++) {
			if (calcCost(count, finalRoute, graph->getMatrix()) > calcCost(count, routes[i], graph->getMatrix())) {
				finalRoute = routes[i];
			}
		}
		
		for (int i = 0; i <= count; i++)
			cout << finalRoute[i] << endl;

		cout<<bestCost<<endl;
		
		delete bf;
	}

	MPI_Finalize();

	return 0;
}
