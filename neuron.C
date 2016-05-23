#include "neuron.h"
#include <iostream>
using std::cout;
using std::endl;

neuron::neuron(const double& val, vector<neuron>& connections) :connections{connections}, val{val} {
}

void neuron::initWeights() {
	double sum = 0;
	//initialize random weights from 0 to 1
	for(int i = 0; i < connections.size(); i++) {
		weights.push_back(weight((double)rand()/RAND_MAX, connections[i], *this));
		sum += weights[i].val;
	}
	//divide each weight by the sum of weights, so that the sum of weights = 1
	for(int i = 0; i < connections.size(); i++) {
		weights[i].val /= sum;
	}
}

double neuron::process() {
	double sum = 0;
	for(int i = 0; i < weights.size(); i++) {
		sum += weights[i].process(); //product of weight and input through weight
	}
	return sum / weights.size();
}


void neuron::print() {
	cout << "Neuron val=" << val << ", connected to " << connections.size() << " neurons. Weights: ";
	for(auto& w : weights) {
		cout << w.val << " ";
	}
	cout << endl;
}
