#ifndef __weight__
#define __weight__

class neuron;

class weight {
	public:
//		weight();
//		~weight();
	private:
		double val;
		neuron &pointsFrom;
		neuron &pointsTo;
};

#endif
