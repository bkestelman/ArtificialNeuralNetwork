#include <fstream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <iostream>
using std::cout;
using std::endl;

int main() {
	std::cout << "sizeof(unsigned int): " << sizeof(unsigned int) << std::endl;

	std::ifstream input("image0.gray", std::ios::binary);
	std::ofstream output("output0", std::ios::binary);

	std::istream_iterator<unsigned char> begin(input), end;
	std::vector<unsigned char> buffer(begin, end);

	std::copy(buffer.begin(),
		buffer.end(),
		std::ostream_iterator<int>(output, ","));
}
