#ifndef __weight__
#define __weight__

class neuron;

class weight {
	public:
		double val;
//		weight();
		weight(const double& val, neuron& pointsFrom, neuron& pointsTo);
		double process();
//		~weight();
	private:
		neuron &pointsFrom;
		neuron &pointsTo;
};

#endif
