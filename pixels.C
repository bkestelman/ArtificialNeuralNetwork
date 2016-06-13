#include <iostream>
#include "/root/CImg/CImg-1.7.2_pre052316/CImg.h"
using namespace cimg_library;

int main() {
	CImg<unsigned char> image("fruit-salad.png");
	CImgDisplay disp(image,"Fruit salad");
	unsigned char pixels[4000];
	unsigned char* x = pixels;
	int y = 0;
	unsigned char test = 0;
	cimg_for(image,ptr,unsigned char) { std::cout << y++ << ": " << static_cast<unsigned>(*ptr) << std::endl; if(*ptr > test) test = *ptr; }
	std::cout << test << std::endl;
	while(!disp.is_closed()) disp.wait();
}
