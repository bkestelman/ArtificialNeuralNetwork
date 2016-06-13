#include "neuron.h"
#include <string>

class ANN {
	public:
		int inputs, hiddens; //sizes of inputL and hiddenL
		std::string id;
		ANN(int inputs, int hiddens, std::string id);
		void initializeNetwork();
		void setInputs(double *data, int sz);
		double processNetwork(bool adjust_weights); //returns mean error in reproducing each input given the current weights distribution. 
		void printANN(bool show_node_values, bool show_weights);
	private:
		vector<neuron> inputL;
		vector<neuron> hiddenL;	
};
