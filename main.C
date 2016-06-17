#include "ANN.h"
#include "neuron.h"
#include "weight.h"
#include <random>
#include <vector>
#include <iostream>
#include <glob.h>
#include <string>
#include <fstream>
using std::vector;
using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::string;
using std::ifstream;
using std::ofstream;
using std::ios;

#define TEST_IMAGES 1000
#define TRAIN_IMAGES 50000
#define HIDDENS 10

void initRand(double *arr, int sz); //initiates normalized (between 0 and 1) random data in *arr
void initFruit(double *arr, int sz); //initializes a "fruit" in *arr (a fruit is a set of data such that all the data points are relatively close) 
void print(double *arr, int sz); //print all the elements of an array, space separated
void printMenu(); //prints menu of options for user 
ANN createANN();

int main() {
	srand(time(NULL));

	bool quit = false;
	int option;
	int RESULT_NUM = 0;
	vector<ANN> anns;
	while(!quit) {
		cout << "What would you like to do?" << endl;
		printMenu();
		cin >> option;
		switch(option) {
			case 1:
				cout << "Creating 10 RBM's..." << endl;
				for(int i = 0; i < 10; i++) {
					cout << "Creating RBM" << i << "..." << endl;
					anns.push_back(ANN{28*28, HIDDENS});
				}
				break;
			case 2:
			{
				//read train-images and train-labels in parallel
				//if an image has label 0, input image to RBM0, etc.
				//process networks

				//open test dataset
				ifstream images("t10k-images-idx3-ubyte", ios::binary);
				ifstream labels("t10k-labels-idx1-ubyte", ios::binary);

				//read off headers
				char magic_number[4];
				char imagesN[4];
				char img[28*28];
				char label[1];
				images.read(magic_number, 4);
				images.read(imagesN, 4);
				images.read(imagesN, 4);
				images.read(imagesN, 4);
				labels.read(magic_number, 4);
				labels.read(magic_number, 4);
				
				//read images and labels, feed input to all RBM's, note the one which produces least error (this is our guess), count %success rate
				double smallestError = 1;
				double error;
				int guess;
				int successes = 0;
				ofstream guesses("guesses.txt");
				for(int i = 0; i < TEST_IMAGES; i++) {
					cout << "Testing image " << i << endl;
					ofstream output("image" + std::to_string(i) + ".gray", ios::binary);
					images.read(img, 28*28);
					labels.read((char*)label, 1);
					output.write(img, 28*28);
					//cout << "Setting inputs for anns[" << (int)label[0] << endl;
					for(int rbm = 0; rbm < 10; rbm++) {
						anns[rbm].setInputs(img, 28*28);
						error = anns[rbm].processNetwork(false);
						anns[rbm].numTests[(int)label[0]]++;
						anns[rbm].errors[(int)label[0]] += error;
						if(error < smallestError) {
							smallestError = error;
							guess = rbm;
						}
					}
					smallestError = 1;
					if(guess == (int)label[0]) successes++;
					guesses << guess << endl;
					//cout << "Error reproducing inputs: " << anns[(int)label[0]].processNetwork(false) << endl;
					output.close();
				}
				cout << "Success rate: " << (double)successes / TEST_IMAGES << endl;	

				ofstream results("results" + std::to_string(RESULT_NUM) + ".txt");
				
				for(int i = 0; i < 10; i++) {
					for(int j = 0; j < 10; j++) {
						anns[i].errors[j] /= anns[i].numTests[j];
						results << anns[i].errors[j] << endl;
						anns[i].errors[j] = 0;
						anns[i].numTests[j] = 0;
					}
					results << endl;
				}
				RESULT_NUM++;
				results.close();
				break;
			}
			case 3:
			{
				ifstream images("train-images-idx3-ubyte", ios::binary);
				ifstream labels("train-labels-idx1-ubyte", ios::binary);

				char magic_number[4];
				char imagesN[4];
				char img[28*28];
				char label[1];
				images.read(magic_number, 4);
				images.read(imagesN, 4);
				images.read(imagesN, 4);
				images.read(imagesN, 4);
				labels.read(magic_number, 4);
				labels.read(magic_number, 4);

				for(int i = 0; i < TRAIN_IMAGES; i++) {
//					cout << "Training image " << i;
					images.read(img, 28*28);
					labels.read(label, 1);
//					cout << "\tTraining RBM " << (int)label[0] << endl;
					anns[(int)label[0]].setInputs(img, 28*28);
					anns[(int)label[0]].processNetwork(true);
				}
				break;
			}
			case 4: //obtain difference between results
			{
				ofstream diff("difference.txt");
				ifstream res0("results0.txt");
				ifstream res1("results1.txt");

				double r0, r1;
				int i = 0;
				while(res0 >> r0 && res1 >> r1) {
					diff << r0 - r1 << endl;
					i++;
					if(i == 10) {
						diff << endl;
						i = 0;
					}
				}
				diff.close();
				res0.close();
				res1.close();
				break;
			}
			case 5:
				quit = true;
				break;
			default:
				break;
		}
	}
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
		cout << arr[i] << " ";
	}
	cout << endl;
}

void printMenu() {
	cout << "1) Create 10 RBM's" << endl;
	cout << "2) Test all RBM's" << endl;
	cout << "3) Train RBM's" << endl;
	cout << "4) Calculate diffs" << endl;
	cout << "5) Quit" << endl;
}

ANN createANN() {
	cout << "How many input nodes?" << endl;
	int inputs;
	cin >> inputs;
	cout << "How many hidden nodes?" << endl;
	int hiddens;
	cin >> hiddens;
	ANN ann(inputs, hiddens);
	ann.initializeNetwork();
	cout << "ANN created" << endl;
	ann.printANN(true, false);
	return ann;
}


