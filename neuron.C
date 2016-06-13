#include "neuron.h"
#include <iostream>
#include <cmath>
using std::cout;
using std::cerr;
using std::endl;

neuron::neuron(const double& val, vector<neuron>& connections) :connections{connections}, val{val} {
}

void neuron::initWeights() {
	weights.clear();
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
	return sum; //no need to divide by weights.size(), since this is already the weighted average
}

/* The main idea for adjusting a weight is to multiply it by (1 - error). 
This means a weight will decrease a lot with large error, and only a little
with small error. After this step is performed for all weights, the adjusted
weight is divided by the sum of all the newly adjusted weights, to ensure 
their sum remains 1. To maintain a history of past adjustments, the average is 
taken between the newly adjusted weight and all past adjusted weights (the
initial random weight is ignored). Note that we don't need to save every past
adjust weight, since the current weight implicitly carries the average of all
past weights.*/ 
void neuron::adjustWeights() {
	double currentWeights[weights.size()];
	double sumNewWeights = 0;
	for(int i = 0; i < weights.size(); i++) {
		//cerr << "Adjusting weight with val=" << w.val << endl;
		//w.numAdjustments++;
		//cerr << "numAdjustments=" << w.numAdjustments << endl;
		currentWeights[i] = weights[i].val;
	//	cerr << "Error between value and weights[" << i << "] = " << std::abs(this->val - weights[i].pointsFromVal()) << endl;
		weights[i].val *= (1 - std::abs(this->val*this->val - weights[i].pointsFromVal()*weights[i].pointsFromVal()));
		sumNewWeights += weights[i].val;

//		w.val *= w.numAdjustments;
//		w.val += curWval * (1 - std::abs(result - w.pointsFromVal())); 
//		w.val /= ++w.numAdjustments;
	}
	for(int i = 0; i < weights.size(); i++) {
		weights[i].val /= sumNewWeights; //make all new weights add to 1
		currentWeights[i] *= weights[i].numAdjustments; //restore sum of all past weights
		weights[i].val += currentWeights[i]; //add new weight to sum of all past weights
		weights[i].val /= ++weights[i].numAdjustments; //divide by the number of adjustments to get the new average weight
	}
}

void neuron::print() {
	cout << "Neuron val=" << val << ", connected to " << connections.size() << " neurons. Weights: ";
	for(auto& w : weights) {
		cout << w.val << " ";
	}
	cout << endl;
}
