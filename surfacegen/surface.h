#pragma once
#include <SFML\Graphics.hpp>
#include "mymath.h"
#include "iostream"
#include <time.h>

class surface
{
public:
	surface(int size, float grad = 0.9, int amp = 10);

	void make_seed();
	void gen_surf();

	void open_pic();

private:
	float** seed;
	float** surf;
	int size, amplitude;
	float abs_max, grad;

	void req_fill(int size, int x, int y, float grad);
};

