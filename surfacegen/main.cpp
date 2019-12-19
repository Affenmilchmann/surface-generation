#include "iostream"
#include <string.h>
#include "surface.h"

int main()
{
	int s, water, smooth;
	float speed;
	std::cout << "Input the size: ";
	std::cin >> s;
	std::cout << "Input the gradient (or leave it 0 = 0.8): ";
	std::cin >> speed;
	std::cout << "Input water % (or leave it -1 = 50%): ";
	std::cin >> water;
	std::cout << "Input smooth level (0 - 100): ";
	std::cin >> smooth;

	surface my_surf(s, speed, water, smooth);

	my_surf.live_draw();

	return 0;
}