#include "ANN.h"
#include <iostream>
#include <cmath>

ANN::ANN(int inputs, int hiddens) :inputs{inputs}, hiddens{hiddens} {}

void ANN::initializeNetwork() {
	inputL.clear();
	hiddenL.clear();
	//cout << "Initializing inputs" << endl;
	for(int i = 0; i < inputs; i++) {
		inputL.push_back(neuron(0, hiddenL));
		//inputs[i].print();
	}
	//inputs[0].print();
	//cout << "Initializing hiddens" << endl;
	for(int i = 0; i < hiddens; i++) {
		hiddenL.push_back(neuron(0, inputL));
		//hiddens[i].print();
	}
	//set up weights
	//cout << "Initializing weights from inputs to hiddens" << endl;
	for(auto& h : hiddenL) {
		h.initWeights();
		//h.print();
	}
	//cout << "Initializing weights from hiddens to inputs" << endl;
	for(auto& n : inputL) {
		n.initWeights();
		//n.print();
	}
}

void ANN::setInputs(double *data, int sz) {
	if(sz != inputs) std::cerr << "ERROR: data and inputs size mismatch" << std::endl; //should make this throw an exception
	for(int i = 0; i < sz; i++) {
		inputL[i].val = data[i];
	}
}

double ANN::processNetwork() {
	//cout << "Processing from inputs to hiddens (and changing values of hiddens)" << endl;
	for(auto& h : hiddenL) {
		h.val = h.process(); //store the weighted average of inputs pointing to h
		//h.print();
	}
	//cout << "Processing from hiddens to inputs (without changing values of inputs), calculating error, and adjusting weights from hiddens to inputs" << endl;
	int i = 0;
	double error = 0;
	for(auto& n : inputL) {
		double result = n.process(); //store the weighted average of hidden nodes pointing to n
		//cout << "Result " << i++ << ": " << result << endl; //error is abs(n.process() - n.val)
		error += std::abs(result - n.val); //going to divide by inputs.size() later to get average error
		//cout << "Neuron before weight adjustment: " << endl;
		//n.print();
		n.adjustWeights(); //adjust weights pointing to n
		//cout << "Neuron after weight adjustment: " << endl;
		//n.print();
	}
	return error / inputL.size();
}
