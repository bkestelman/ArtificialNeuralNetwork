#ifndef __neuron__
#define __neuron__

#include <vector>
#include "weight.h"
using std::vector;

class neuron {
	public:
		double val;
		vector<weight> weights;
//		neuron();
		neuron(const double& val, vector<neuron>& connections);
		void initWeights(); //initialize weights to random values. Sum of weights will be 1
		double process(); //process incoming signals. Multiply incoming values by their weights and calculate the average
		void adjustWeights(); //calculates error of each connection compared to this neuron's value and adjusts weights from each connection according to the error
		void print();
//		~neuron();
	private:
		vector<neuron>& connections; //vector of neurons connected to this one (neurons pointing to this one). This is a reference because other neurons will have the same connections as this one
		//vector<weight> weights; //vector of weights pointing to this neuron. This is not a reference because this neuron's weights are unique to this neuron
};

#endif
