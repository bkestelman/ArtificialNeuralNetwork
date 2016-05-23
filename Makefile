ANN: main.o weight.o neuron.o
	g++ $(CFLAGS) -o ANN main.o weight.o neuron.o
main.o: weight.h neuron.h main.C
	g++ $(CFLAGS) -c weight.h neuron.h main.C
neuron.o: weight.h neuron.h neuron.C
	g++ $(CFLAGS) -c weight.h neuron.h neuron.C
weight.o: weight.h neuron.h weight.C
	g++ $(CFLAGS) -c weight.h neuron.h weight.C

clean: 
	rm *.o
