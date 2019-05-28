#include "Graph.h"

using namespace std;

Graph::Graph(std::fstream &data) {
	
	data >> count;

	matrix = new int *[count];

	for (int i = 0; i < count; i++) {
		matrix[i] = new int[count];

			for (int j = 0; j < count; j++) {
				
					data >> matrix[i][j];

					if (i == j)
						matrix[i][j] = INT_MAX;
				
			}
		
	}

}

Graph::Graph(int n) {
	
	count = n;

	matrix = new int *[count];

	for (int i = 0; i < count; i++) {
		matrix[i] = new int[count];

		for (int j = 0; j < count; j++) {
				
			if (i != j) 
				matrix[i][j] = rand() % 99 + 1;
			else
				matrix[i][j] = INT_MAX;
					
			}
	}
}

Graph::~Graph() {

	for (int i = 0; i < count; i++) 
		delete matrix[i];
	
	delete matrix;
}

int **Graph::getMatrix() {
	return matrix;
}
int Graph::getCount() {
	return count;
}