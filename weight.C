#include "weight.h"
#include "neuron.h"
//#include <iostream>

weight::weight(const double& val, neuron& pointsFrom, neuron& pointsTo) :val{val}, pointsFrom{pointsFrom}, pointsTo{pointsTo}, numAdjustments{1} {}

double weight::process() {
//	std::cerr << val * pointsFrom.val << std::endl;
	return val * pointsFrom.val;
}

double weight::pointsFromVal() {
	return pointsFrom.val;
}
