#include "neuron.h"
#include "weight.h"
#include <random>
#include <vector>
#include <iostream>
using std::vector;
using std::cout;
using std::cerr;
using std::endl;

#define INPUTS 4
#define HIDDENS 2

void initRand(double *arr, int sz); //initiates normalized (between 0 and 1) random data in *arr
void initFruit(double *arr, int sz); //initializes a "fruit" in *arr (a fruit is a set of data such that all the data points are relatively close) 
void print(double *arr, int sz); //print all the elements of an array, space separated

int main() {
	srand(time(NULL));
	
	vector<neuron> inputs;
	//vector<neuron> outputs;
	vector<neuron> hiddens;

	double data[INPUTS];
	initFruit(data, INPUTS);
	print(data, INPUTS);

	//set up neurons
	for(int i = 0; i < INPUTS; i++) {
		inputs.push_back(neuron(data[i], hiddens));
	}
	inputs[0].print();
	for(int i = 0; i < HIDDENS; i++) {
		hiddens.push_back(neuron(0, inputs));
	}

	//set up weights
	for(auto& n : inputs) {
		n.initWeights();
	}

	inputs[0].print();
}

void initRand(double *arr, int sz) {
	for(int i = 0; i < sz; i++) {
		arr[i] = (double) rand() / RAND_MAX;
	}
}

void initFruit(double *arr, int sz) {
	std::default_random_engine generator;
	std::normal_distribution<double> N((double)rand()/RAND_MAX, 0.1); //normal distribution with random mean between 0 and 1, and standard deviation 0.1
	for(int i = 0; i < sz; i++) {
		arr[i] = N(generator); //random number from normal distribution
		if(arr[i] < 0) arr[i] = 0;
		else if(arr[i] > 1) arr[i] = 1;
	}
}

void print(double *arr, int sz) {
	for(int i = 0; i < sz; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}
