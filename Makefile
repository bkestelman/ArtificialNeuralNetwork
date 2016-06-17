ANN: main.o ANN.o weight.o neuron.o
	g++ $(CFLAGS) -o ANN ANN.o main.o weight.o neuron.o 
main.o: ANN.h weight.h neuron.h main.C
	g++ $(CFLAGS) -c weight.h neuron.h ANN.h main.C
ANN.o: ANN.h ANN.C neuron.h
	g++ $(CFLAGS) -c ANN.h ANN.C neuron.h
neuron.o: weight.h neuron.h neuron.C
	g++ $(CFLAGS) -c weight.h neuron.h neuron.C
weight.o: weight.h neuron.h weight.C
	g++ $(CFLAGS) -c weight.h neuron.h weight.C

clean: 
	rm *.o
