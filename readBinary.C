#include <fstream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <iostream>
using std::cout;
using std::endl;

int main() {
	std::cout << "sizeof(unsigned int): " << sizeof(unsigned int) << std::endl;

	std::ifstream input("train-labels-idx1-ubyte", std::ios::binary);
	std::ofstream output("output", std::ios::binary);

	std::istream_iterator<unsigned char> begin(input), end;
	std::vector<unsigned char> buffer(begin, end);

	std::copy(buffer.begin(),
		buffer.end(),
		std::ostream_iterator<int>(output, ","));

/*	std::vector<unsigned char> eightBytes(8);
	input.read(&eightBytes[0], eightBytes.size());
	std::string first8(eightBytes.begin(), eightBytes.end());
	cout << first8 << endl;*/

/*	std::copy(buffer.begin(),
		buffer.end(),
		std::ostream_iterator<unsigned int>(output, ","));
	std::copy_n(buffer, 8, std::out);*/

/*	std::copy(eightBytes.begin(),
		eightBytes.end(),
		std::ostream_iterator<unsigned char>(output, ","));*/

	/*std::copy(
		std::istreambuf_iterator<char>(input),
		std::istreambuf_iterator<char>(),
		std::ostreambuf_iterator<char>(output));*/
}
