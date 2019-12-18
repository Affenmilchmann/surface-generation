#include "iostream"
#include <string.h>
#include "surface.h"

int main()
{
	int s, water;
	float speed;
	std::cout << "Input the size: ";
	std::cin >> s;
	std::cout << "Input the gradient (or leave it 0 = 0.8): ";
	std::cin >> speed;
	std::cout << "Input water % (or leave it -1 = 50%): ";
	std::cin >> water;

	surface my_surf(s, speed, water);

	my_surf.gen_surf();

	my_surf.open_pic();

	return 0;
}