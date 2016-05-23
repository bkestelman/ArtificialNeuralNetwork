#ifndef __neuron__
#define __neuron__

#include <vector>
#include "weight.h"
using std::vector;

class neuron {
	public:
//		neuron();
		neuron(const double& val, vector<neuron>& connections);
		void print();
//		~neuron();
	private:
		double val;
		vector<neuron>& connections; //this is a reference because other neurons will have the same connections as this one
		vector<weight> weights; //this is not a reference because this neuron's weights are unique to this neuron
};

#endif
