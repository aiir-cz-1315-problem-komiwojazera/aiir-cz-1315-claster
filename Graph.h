#pragma once

#include <iostream>
#include <fstream>
#include <climits>

using namespace std;


class Graph {
	
	private:
		int **matrix;
		int count;

	public:
		Graph(int n);
		Graph(std::fstream &data);
		~Graph();

		int **getMatrix();
		int getCount();

};

