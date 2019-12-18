#pragma once
#include <SFML\Graphics.hpp>
#include "mymath.h"
#include "iostream"
#include <time.h>

class surface
{
public:
	surface(int size, float grad, int water_percent, int amp = 10);

	void make_seed();
	void gen_surf();

	void open_pic();

private:
	float** seed;
	float** surf;
	int size, amplitude, water_percentage;
	float abs_max, grad;

	void req_fill(int size, int x, int y, float grad);
};

