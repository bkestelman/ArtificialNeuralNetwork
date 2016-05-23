# ArtificialNeuralNetwork
Image classifying ANN built from scratch

Final Objective: Create and train and ANN that will take an image input (perhaps every tenth pixel or so) and classify it as either a 
fruit or an animal. 

Approach:
Initially, I had planned on doing a straight-forward ANN with a layer for inputs, a hidden layer, and a single output node. After 
processing the inputs through weights and the hidden layer, the ouput would hold the probability of an image being a fruit or an animal
(maybe 0=fruit, 1=animal, 0.7=70% chance animal, 30% chance fruit). However, upon thinking through the problem, I decided this approach 
would not work out, since in training the ANN to detect animals, it would simply increase the weight of the highest valued inputs, and 
vice versa for fruits. This does not make sense, since classifying images can't possibly depend on which images have higher valued 
pixels. A better approach would be to use a Restricted Boltzmann Machine. 
An RBM is a type of ANN that works essentially the same as the above described ANN, except that instead of the hidden layer neurons all
pointing to a single output node, they map back to the inputs. This allows comparing each original input with a unique, corresponding
output. The error between the two is back-propagated through the network and weights are adjusted, such that the network is trained
to immitate the input with its output. Thus, if an RBM is trained with thousands of fruit images, it will get very good at reproducing
(no pun intended) fruit images, and will thus report minimal error when fed a fruit image as input. Hopefully, the RBM will report
a relatively high error when fed an animal image as input, allowing us to distinguish between animals and fruits. 

This is a good read on RBM's: (note that my implementation is a bit different)
http://deeplearning4j.org/restrictedboltzmannmachine.html

Current Progrees:
To start off simple, I first wanted to create an ANN that would distinguish between an image of a fruit and random noise. To start off 
even simpler, I'm representing a fruit as an array of numbers normally distributed about some random double between 0 and 1 with 
standard deviation 0.1 (so a fruit might look something like {.31, .32, .25, .34}). I decided this was a reasonable sort of pattern, 
since compared to random noise, a fruit will have colors much more similar to each other (although this is generally true for all 
images). My initial goal was to see if my ANN could pick up on this simple pattern. I will later discuss a problem with this idea. 
  I've set up the neural network as a vector of neurons for the inputs and another vector of neurons for the hidden layer. Each neuron has 
a reference to a vector of the neurons connected to it (sending signals to it/pointing to it), and also has a unique 
vector of the weights pointing to it. Weights are initially randomized. 
In one training cycle, the algorithm is:
  Each hidden node receives weighted inputs (all inputs map to each hidden node through some weight; each weighted input is the input 
    times the weight), and adds them together (resulting in the weighted average of the inputs)
  Each output node (which is actually each input node, since I'm using an RBM; that is, each input node points to all the hidden nodes,
  and each hidden node points to all the input nodes, but I'll call them output nodes when I discuss them processing outputs sent by 
  the hidden nodes, and I'll call them input nodes when I discuss their input being sent to the hidden nodes)... each output node 
  calculates the error between the weighted average of the hidden nodes and the corresponding original input, and adjusts the weights 
  going from the hidden nodes to the output nodes according to which one had the least error. The exact algorithm is as follows:
    Multiply the current weight from each hidden node by (1 - error). Adjust this value so that the sum of all these new weights equals
    1. Then, add this new weight to the previous weight times the number of times it has been adjusted, and divide by the number of 
    times the weight has been adjusted, so as to take a sort of weighted average of all historical (1 - error) values, and not just let 
    the most recent result dictate the new weight.
  So far, I only perform weight adjustment on the weights going from the hidden nodes to the output, so weight adjustment still has to
  be implemented for the weights going from the input nodes to the hidden nodes. 
    
Results, Problems, and Plans:
The biggest success of this RBM is that there tends to be improvement (shrinking error) throughout a training set of randomly 
generated fruits (as described above). I created 1000 RBM's with randomly initialized weights and rand 10,000 fruits through each, and 
found that the average error of each RBM when attempting to reproduce a fruit is 1.9% better over all 10,000 fruits than over the first
10 fruits given to the RBM. It's also 1.4% better over all 10,000 fruits than over the first 100, and 0.7% better over all 10,000 than
over the first 1,000. The improvement is small - indeed, if you only create a single RBM and feed it 10,000 fruits there is a 
considerable chance that the average error will be smaller for the first 10 fruits than for all 10,000, which is why it's necessary to
test 1000 RBM's to see results - but it's there, and it shows that the RBM is working. Further tests have to be made with a larger 
input size, more hidden nodes, and of course, real image data. 
My biggest concerns are that the pattern I chose to represent a fruit is first of all, too general, which means that the RBM's 
success at this stage in no way guarantees it will be able to classify images that do not consist of pure random noise, and second of 
all, too easy. What I mean by this is that in order to reproduce inputs that are similar to each other, the RBM hardly has to do 
anything, since taking the weighted average of similar numbers will always give a pretty consistent value, regardless of their weights.
This explains the minute improvement over so many trials - the RBM is already quite successful at reproducing similar inputs from the 
get-go, by taking their weighted average with randomly initialized weights. In fact, I'd really like to see a rigorous proof that this 
design actually will tend to improve the error during the training phase. I'm convinced by the data that it does, but such a proof
would definitely help to understand how the RBM works from a mathematical perspective, and maybe give ideas for how it can be optimized.
Future tests (prior to actually using image data as input) might use an array of mostly similar numbers, with a few random ones, or 
perhaps contain clumps of similar numbers. Then the RBM's pattern recognition and improvement over time will really be put to the test.

Another concern is I am not using any kind of activation function anywhere, just taking weighted averages. Maybe this would help, if I 
knew what to do with it?

For the images part: I ran into trouble downloading bulk images from google, because google blocks wget downloads except of its home
page (I tried changing the wget user agent, didn't work). So... use Yahoo! Still, I had a bit of a hiccup because wget downloads the
raw HTML, prior to Javascript changing it, so my downloaded source was different from the one I saw in the browser. So I just copied 
the browser source and put it in a text file. I've successfully used sed regular expressions to isolate 253 image links of fruits
(although many are duplicates, but this is from just a one page search) and tested that I can download the first one, so I just gotta
write a BASH script to download all of them. 
