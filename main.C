#include "ANN.h"
#include "neuron.h"
#include "weight.h"
#include <random>
#include <vector>
#include <iostream>
#include <glob.h>
#include "/root/CImg/CImg-1.7.2_pre052316/CImg.h" //replace with local path to CImg.h
using namespace cimg_library;
using std::vector;
using std::cout;
using std::cin;
using std::cerr;
using std::endl;

void initRand(double *arr, int sz); //initiates normalized (between 0 and 1) random data in *arr
void initFruit(double *arr, int sz); //initializes a "fruit" in *arr (a fruit is a set of data such that all the data points are relatively close) 
void print(double *arr, int sz); //print all the elements of an array, space separated
void printMenu(); //prints menu of options for user 
ANN createANN();

int main() {
	srand(time(NULL));

	bool quit = false;
	int option;
	vector<ANN> anns;
	while(!quit) {
		cout << "What would you like to do?" << endl;
		printMenu();
		cin >> option;
		switch(option) {
			case 1: 
				anns.push_back(createANN());
				break;
			case 2: {
				double fruit[anns[0].inputs]; 
				initFruit(fruit, anns[0].inputs);
				cout << "Fruit: ";
				print(fruit, anns[0].inputs);
				anns[0].setInputs(fruit, anns[0].inputs);
				anns[0].processNetwork(true);
				anns[0].printANN(true, true);
				break;
			}
			case 3: {
				glob_t fruitImages;
				glob("images/fruits/training/*", 0, NULL, &fruitImages);
				for(int im = 0; im < fruitImages.gl_pathc; im++) {
					CImg<unsigned char> fruitImage(fruitImages.gl_pathv[im]);				
					double pixels[anns[0].inputs];
					int i = 0;
					cimg_for(fruitImage, ptr, unsigned char) {
						if(i < anns[0].inputs) pixels[i++] = (double)*ptr / 255;
					}
					anns[0].setInputs(pixels, anns[0].inputs);
					anns[0].processNetwork(true);
					anns[0].printANN(true, false);
				}
				break;
			}
			case 4: {
				double meanErr = 0;
				int numTests;
				glob_t testImages;
				glob("images/fruits/test/*", 0, NULL, &testImages);
				for(numTests = 0; numTests < testImages.gl_pathc; numTests++) {
					CImg<unsigned char> image(testImages.gl_pathv[numTests]);
					double pixels[anns[0].inputs];
					int i = 0;
					cimg_for(image, ptr, unsigned char) {
						if(i < anns[0].inputs) pixels[i++] = (double)*ptr / 255;
					}
					anns[0].setInputs(pixels, anns[0].inputs);
					meanErr += anns[0].processNetwork(false);
				}
				meanErr /= numTests;
				cout << "Mean error on tests is: " << meanErr << endl;
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
	cout << "1) Create ANN (RBM)" << endl;
	cout << "2) Feed fruit to selected ANN" << endl;
	cout << "3) Feed fruit images training set to selected ANN" << endl;
	cout << "4) Feed fruit images test set to selected ANN" << endl;
	cout << "5) Quit" << endl;
}

ANN createANN() {
	cout << "How many input nodes?" << endl;
	int inputs;
	cin >> inputs;
	cout << "How many hidden nodes?" << endl;
	int hiddens;
	cin >> hiddens;
	std::string id;
	cout << "Id/name for ANN:" << endl;
	cin >> id;
	ANN ann(inputs, hiddens, id);
	ann.initializeNetwork();
	cout << "ANN created" << endl;
	ann.printANN(true, false);
	return ann;
}


