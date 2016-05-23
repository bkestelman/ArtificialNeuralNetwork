#ifndef __neuron__
#define __neuron__

#include <vector>
using std::vector;

class weight;

class neuron {
	public:
//		neuron();
//		~neuron();
	private:
		double val;
		vector<neuron> connections;
		vector<weight> weights;
};

#endif
