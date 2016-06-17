#include "ANN.h"
#include <iostream>
#include <cmath>
using std::cout;
using std::cerr;
using std::endl;

ANN::ANN(int inputs, int hiddens) :inputs{inputs}, hiddens{hiddens} {initializeNetwork();}

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
	for(int i = 0; i < 10; i++) {
		errors[i] = 0;
		numTests[i] = 0;
	}
}

void ANN::setInputs(double *data, int sz) {
	if(sz != inputs) {
		std::cerr << "ERROR: data and inputs size mismatch" << std::endl; //should make this throw an exception
		return;
	}
	for(int i = 0; i < sz; i++) {
		inputL[i].val = data[i];
	}
}

void ANN::setInputs(char *data, int sz) {
	for(int i = 0; i < sz; i++) {
		inputL[i].val = (double)(unsigned char)data[i] / 255;
		if(inputL[i].val > 1 || inputL[i].val < 0) {
			cout << "char: " << data[i] << "\t(int)(unsigned char)char: " << (int)(unsigned char)data[i] << "\t(double)(unsigned char)char: " << (double)(unsigned char)data[i] / 255 << endl;
			std::cerr << "ERROR: invalid input value" << std::endl;
		}
	}
}

void ANN::addInput(double d) {
	inputL.push_back(neuron{d, hiddenL});
}

double ANN::processNetwork(bool adjust_weights) {
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
		if(adjust_weights) n.adjustWeights(); //adjust weights pointing to n
		//cout << "Neuron after weight adjustment: " << endl;
		//n.print();
	}
	////////
	for(auto& h : hiddenL) {
		double result = h.process();
		error += std::abs(result - h.val);
		if(adjust_weights) h.adjustWeights();
	}
	////////
	//std::cout << inputL.size() << endl;
	return error / inputL.size();
}

void ANN::printANN(bool show_node_values, bool show_weights) {
	cout << "Inputs: " << inputs << "\tHiddens: " << hiddens << endl;
	if(!show_node_values) return;
	int i = 0; 
	int j = 0;
	for(auto& n : inputL) {
		cout << "Input[" << i << "] value: " << n.val << endl;
		if(!show_weights) {
			i++;
			continue;
		}
		for(auto& w : n.weights) { 
			cout << "\tWeight[" << i << "][" << j++ << "]: " << w.val << endl;
		}
		i++;
		j = 0;
	}
	i = 0;
	for(auto& h : hiddenL) {
		cout << "Hidden[" << i << "] value: " << h.val << endl;
		if(!show_weights) {
			i++;
			continue;
		}
		for(auto& w : h.weights) { 
			cout << "\tWeight[" << i << "][" << j++ << "]: " << w.val << endl;
		}
		i++;
		j = 0;
	}
}

/*void printANN(void) {
	printANN(true);
}*/
