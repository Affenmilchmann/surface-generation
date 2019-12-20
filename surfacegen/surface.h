#pragma once
#include <SFML\Graphics.hpp>
#include "mymath.h"
#include "iostream"
#include <time.h>
#include <vector>

class surface
{
public:
	surface();

	void gen_surf();

	void open_pic();

	void set_size(int size);
	void set_smooth(int smooth);
	void set_mode(int mode);
	void set_water(float water);
	void set_sand(float sand);
	void set_grad(float grad);

private:
	float** seed;
	float** surf;
	int size;
	float abs_max, grad, sand_percent, water_percentage;
	int smooth_lvl;
	int mode;

	void make_seed();
	void smooth(int deep);
	void get_max();
	void req_fill(int x1, int y1, int x2, int y2, float grad, float* seed[]);
};

