#ifndef __weight__
#define __weight__

class neuron;

class weight {
	public:
		double val;
		int numAdjustments; //number of times this weight has been adjusted
//		weight();
		weight(const double& val, neuron& pointsFrom, neuron& pointsTo);
		double process();
		double pointsFromVal();
//		~weight();
	private:
		neuron& pointsFrom;
		neuron& pointsTo;
};

#endif
