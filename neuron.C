#include "neuron.h"
#include <iostream>
using std::cout;
using std::endl;

neuron::neuron(const double& val, vector<neuron>& connections) :connections{connections}, val{val} {
}

/*void neuron::initWeights() {
	for(int i = 0; i < connections.size(); i++) {
		weights
		*/

void neuron::print() {
	cout << "Neuron val=" << val << ", connected to " << connections.size() << " neurons" << endl;
}
