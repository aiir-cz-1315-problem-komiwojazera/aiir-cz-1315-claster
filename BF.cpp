#include "BF.h"
#include <vector>

using namespace std;

/* CONSTRUCTOR AND DESTRUCTOR */
BF::BF(Graph *graph) : cost(INT_MAX), best_cost(INT_MAX) {
	matrix = graph->getMatrix();
	count = graph->getCount();
	route = new int[count + 1];
	best_route = new int[count + 1];
	for (int i = 0; i < count; i++) {
		route[i] = i;
	}
	route[count] = 0;
	route_copy();
}

BF::~BF() {
	delete[] route;
	delete[] best_route;

	for (int i = 0; i < count; i++)
		delete matrix[i];

	delete matrix;
}

/* METHODS */

/* Print route rt */
void BF::route_print(int* rt) {
	for (int i = 0; i <= count; i++) 
		std::cout << rt[i] << endl;
	
}



void BF::BF_solve(unsigned long long perm_start, unsigned long long perm_end, unsigned long long silnia) {
	long long start = perm_start;
	calcStartRoute(perm_start, silnia);
	do {
		cost = calcCost();	// calculate cost for given permutation
		if (cost < best_cost) {		// if better solution - it's new best cost and route
			best_cost = cost;
			route_copy();
		}
		perm_start++;
	} while (std::next_permutation(route + 1, route + count) && perm_start <= perm_end); // const position of city 1 
	std::cout << "Skonczono czesc " <<start<<" - "<<perm_end<<endl;
}

/* Calculate cost for given permutation */
int BF::calcCost() {
	int tempCost = 0;

	for (int i = 0; i < count; i++)
		tempCost += matrix[route[i]][route[i + 1]];

	return tempCost;

}
/* Copy permutation route to best_route */
void BF::route_copy() {
	for (int i = 0; i <= count; i++) 
		best_route[i] = route[i];
	
}

void BF::calcStartRoute(unsigned long long start, unsigned long long silnia) {
	unsigned long long oldPart = 0, part = silnia / (count - 1);
	
	vector <int> q;

	for (int i = 1; i < count; i++)
		q.push_back(i);

	for (int i = 1; i < count - 1; i++) {
		for (int j = 1; j < count; j++) {
			if (j * part + oldPart >= start) {
				route[i] = q[j - 1];
				q.erase(q.begin() + (j - 1));

				if (i + 1 == count - 1)
					break;

				long long tmp = part * (j - 1);
				oldPart += tmp;
				tmp = count - i - 1;
				part /=tmp;
				break;
			}
		}
	}
	
	route[count - 1] = q.back();
	q.pop_back();


}

int* BF::get_route() {
	return route;
}

int* BF::get_best_route() {
	return best_route;
}

int BF::get_cost() {
	return cost;
}

int BF::get_best_cost() {
	return best_cost;
}