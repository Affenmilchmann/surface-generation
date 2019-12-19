#pragma once
#include <SFML\Graphics.hpp>
#include "mymath.h"
#include "iostream"
#include <time.h>
#include <thread>

class surface
{
public:
	surface(int size, float grad, int water_percent, int smooth, int amp = 100);

	void make_seed();
	void gen_surf();
	void smooth_surf();
	
	void live_draw();
	void open_pic();

private:
	float** seed;
	float** surf;
	int size, amplitude, water_percentage, smooth_level;
	float abs_max, grad;

	bool is_in_procces;

	void req_fill(int size, int x, int y, float grad);
	void live_gen();
};

