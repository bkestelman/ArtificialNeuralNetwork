#include "neuron.h"

class ANN {
	public:
		int inputs, hiddens; //sizes of inputL and hiddenL
		ANN(int inputs, int hiddens);
		void initializeNetwork();
		void setInputs(double *data, int sz);
		double processNetwork();
	private:
		vector<neuron> inputL;
		vector<neuron> hiddenL;	
};
