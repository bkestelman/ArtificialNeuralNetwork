#include "neuron.h"
#include <string>

class ANN {
	public:
		int inputs, hiddens; //sizes of inputL and hiddenL
		ANN(int inputs, int hiddens);
		void initializeNetwork();
		void addInput(double d); //add an input node 
		void setInputs(double *data, int sz);
		void setInputs(char *data, int sz);
		double processNetwork(bool adjust_weights); //returns mean error in reproducing each input given the current weights distribution. 
		void printANN(bool show_node_values, bool show_weights);
		double errors[10]; //error at reproducing each digit of MNIST
		int numTests[10]; //number of tests against each digit of MNIST
	private:
		vector<neuron> inputL;
		vector<neuron> hiddenL;	
};
