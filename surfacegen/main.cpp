#include "iostream"
#include <string.h>
#include "surface.h"

int main()
{
	int s;
	float speed;
	std::cout << "Input the size: ";
	std::cin >> s;
	std::cout << "Input the gradient (or leave it 0): ";
	std::cin >> speed;

	surface my_surf(s, speed);

	my_surf.gen_surf();

	my_surf.open_pic();

	return 0;
}