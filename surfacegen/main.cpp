#include "iostream"
#include <string.h>
#include "surface.h"

int main()
{
	int s;
	float speed;
	std::cin >> s;
	std::cin >> speed;

	surface my_surf(s);

	my_surf.gen_surf();

	my_surf.open_pic();

	return 0;
}