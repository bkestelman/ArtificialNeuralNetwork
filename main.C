#include "neuron.h"
#include "weight.h"
#include <random>
#include <vector>
#include <iostream>
using std::vector;
using std::cout;
using std::cerr;
using std::endl;

#define INPUTS 4 //number of input nodes
#define HIDDENS 2 //number of hidden nodes

void initRand(double *arr, int sz); //initiates normalized (between 0 and 1) random data in *arr
void initFruit(double *arr, int sz); //initializes a "fruit" in *arr (a fruit is a set of data such that all the data points are relatively close) 
void print(double *arr, int sz); //print all the elements of an array, space separated
void processLayer(vector<neuron> layer); //process the inputs going into each neuron in layer (multiply them by their weights and take the average)
void initializeNetwork(vector<neuron>& inputs, vector<neuron>& hiddens); //initialize network of neurons with input layer and one hidden layer. Neuron values initialized to 0. 
void setInputs(vector<neuron>& inputs, double *data, int sz); 
double processNetwork(vector<neuron>& inputs, vector<neuron>& hiddens); //attempt to recreate inputs by processing through weights and hidden layer. Use error to adjust weights from hidden layer to output. Returns the average error between recreation and inputs. 

int main() {
	srand(time(NULL));
	
	vector<neuron> inputs;
	//vector<neuron> outputs;
	vector<neuron> hiddens;


//Training
	double initialError = 0;
	double errSumTen = 0; 
	double errSumHun = 0;
	double errSumK = 0; 
	double errSumTenK = 0;
	double error = 0;
	double data[INPUTS];
	//to play around with one ANN, get rid of these loops, uncomment some useful couts in this file, and use the print functions here and in neuron.C
	for(int j = 0; j < 1000; j++) {
		initializeNetwork(inputs, hiddens);
	for(int i = 0; i < 10000; i++) {
		initFruit(data, INPUTS);
		setInputs(inputs, data, INPUTS);
	//	print(data, INPUTS);

		error = processNetwork(inputs, hiddens);
		//cout << "Error: " << error << endl << endl;
		if(i == 0) initialError = error;
		if(i < 10) errSumTen += error;
		if(i < 100) errSumHun += error;
		if(i < 1000) errSumK += error;
		if(i < 10000) errSumTenK += error;
	}
	}
//	initRand(data, INPUTS);
//	setInputs(inputs, data, INPUTS);
//	print(data, INPUTS);
//	error = processNetwork(inputs, hiddens);
//	//cout << "Error: " << error << endl << endl;
	//cout << "Initial error: " << initialError << endl;

	cout << "Average error (first 10 trials): " << errSumTen / 10000 << endl;
	cout << "Average error (first 100 trials): " << errSumHun / 100000 << endl;
	cout << "Average error (first 1000 trials): " << errSumK / 1000000 << endl;
	cout << "Average error (first 10000 trials): " << errSumTenK / 10000000 << endl;
	cout << "Difference between error in first 10 and error in first 1000: " << errSumTen/10000 - errSumK/1000000 << endl;
}

void initRand(double *arr, int sz) {
	for(int i = 0; i < sz; i++) {
		arr[i] = (double) rand() / RAND_MAX;
	}
}

void initFruit(double *arr, int sz) {
	std::default_random_engine generator;
	std::normal_distribution<double> N((double)rand()/RAND_MAX, 0.1); //normal distribution with random mean between 0 and 1, and standard deviation 0.1
	for(int i = 0; i < sz; i++) {
		arr[i] = N(generator); //random number from normal distribution
		if(arr[i] < 0) arr[i] = 0;
		else if(arr[i] > 1) arr[i] = 1;
	}
}

void print(double *arr, int sz) {
	for(int i = 0; i < sz; i++) {
		//cout << arr[i] << " ";
	}
	//cout << endl;
}

void processLayer(vector<neuron> layer) {
	for(auto& n : layer) {
		n.process();
	}
}

void initializeNetwork(vector<neuron>& inputs, vector<neuron>& hiddens) {
	inputs.clear();
	hiddens.clear();
	//cout << "Initializing inputs" << endl;
	for(int i = 0; i < INPUTS; i++) {
		inputs.push_back(neuron(0, hiddens));
		//inputs[i].print();
	}
	//inputs[0].print();
	//cout << "Initializing hiddens" << endl;
	for(int i = 0; i < HIDDENS; i++) {
		hiddens.push_back(neuron(0, inputs));
		//hiddens[i].print();
	}
	//set up weights
	//cout << "Initializing weights from inputs to hiddens" << endl;
	for(auto& h : hiddens) {
		h.initWeights();
		//h.print();
	}
	//cout << "Initializing weights from hiddens to inputs" << endl;
	for(auto& n : inputs) {
		n.initWeights();
		//n.print();
	}
}

void setInputs(vector<neuron>& inputs, double *data, int sz) {
	if(sz != inputs.size()) cerr << "ERROR: data and inputs size mismatch" << endl;
	for(int i = 0; i < sz; i++) {
		inputs[i].val = data[i];
	}
}

double processNetwork(vector<neuron>& inputs, vector<neuron>& hiddens) {
	//cout << "Processing from inputs to hiddens (and changing values of hiddens)" << endl;
	for(auto& h : hiddens) {
		h.val = h.process();	
		//h.print();
	}
	//cout << "Processing from hiddens to inputs (without changing values of inputs), calculating error, and adjusting weights from hiddens to inputs" << endl;
	int i = 0;
	double error = 0;
	for(auto& n : inputs) {
		double result = n.process();
		//cout << "Result " << i++ << ": " << result << endl; //error is abs(n.process() - n.val)
		error += std::abs(result - n.val); //going to divide by inputs.size() later to get average error
		//cout << "Neuron before weight adjustment: " << endl;
		//n.print();
		n.adjustWeights(); //adjust weights pointing to n
		//cout << "Neuron after weight adjustment: " << endl;
		//n.print();
	}
	return error / inputs.size();
}
