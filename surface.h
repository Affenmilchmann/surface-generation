#pragma once
#include <SFML/Graphics.hpp>
#include <math.h>
#include "iostream"
#include <time.h>
#include <vector>

#ifdef __linux__ 
#include <unistd.h>
#endif
#ifdef WINDOWS
#include <windows.h>
#endif

class surface
{
public:
	surface();

	void gen_surf();
	void make_seed();
	void make_pic();

	void open_pic();

	void set_size(int size);
	void set_smooth(int smooth);
	void set_mode(int mode);
	void set_water(float water);
	void set_sand(float sand);
	void set_grad(float grad);

	std::string get_status();

private:
	float** seed;
	float** surf;
	int size;
	float grad, sand_percent, water_percentage;
	int smooth_lvl;
	int mode;
	float sleep_time_seconds;

	void smooth(int deep);
	void gen_seed();
	void delete_array(float** arra);
	void req_fill(int x1, int y1, int x2, int y2, float grad, float* seed[]);
};

