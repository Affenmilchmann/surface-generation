#include "surface.h"

float snow_line = 0.7, smooth_parameter = 2.0f;

surface::surface()
{
	srand(time(0));
	size = 200;

	seed = new float* [size]; 
	surf = new float* [size];
	for (int i = 0; i < size; i++)
	{
		seed[i] = new float[size];
		surf[i] = new float[size];
	}

	gen_seed();

	smooth_lvl = 20;
	sand_percent = 0.1f;
	water_percentage = 0.5f;
	grad = 0.7f;
	mode = 1;
}

void surface::make_pic()
{
	if (size <= 3)
	{
		std::cout << "\nSize is too small ERROR. \n";
		return;
	}

	delete_array(surf);

	surf = new float* [size];

	for (int i = 0; i < size; i++)
	{
		surf[i] = new float[size];
		for (int j = 0; j < size; j++)
			surf[i][j] = 0.0f;
	}

	surf[0][0] = seed[0][0];
	surf[size - 1][0] = seed[size - 1][0];
	surf[0][size - 1] = seed[0][size - 1];
	surf[size - 1][size - 1] = seed[size - 1][size - 1];

	req_fill(0, 0, size - 1, size - 1, grad, seed);

	smooth(smooth_lvl);
}

void surface::make_seed()
{
	delete_array(surf);
	delete_array(seed);
	gen_seed();
}

void surface::gen_seed()
{
	if (size <= 3)
	{
		std::cout << "\nSize is too small ERROR. \n";
		return;
	}

	seed = new float* [size];
	surf = new float* [size];

	for (int i = 0; i < size; i++)
	{
		seed[i] = new float[size];
		surf[i] = new float[size];
		for (int j = 0; j < size; j++)
		{
			surf[i][j] = 0.0f;
			seed[i][j] = (float)(rand() % 1000) / (float)1000;
		}
	}
}

void surface::gen_surf()
{
	gen_seed();
	make_pic();
}


void surface::smooth(int deep)
{
	if (deep <= 0) return;
	float avrg = 0.0f;
	int count = 0;
	for (int i = 0; i < size; i++) // smoothing anomalys
	{
		for (int j = 0; j < size; j++)
		{
			avrg += surf[i][j];
			count++;
		}
	}

	avrg /= count;

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (surf[i][j] / avrg > smooth_parameter || surf[i][j] / avrg < 1.0f / smooth_parameter)
				surf[i][j] = (surf[i][j] + avrg) / 2.0f;
		}
	}

	for (int k = 0; k < deep; k++)
	{
		if (size >= 3) // main smoothing 
		{
			for (int f = 1; f < size - 1; f++) //lines
			{
				avrg = (surf[f - 1][size - 1] + surf[f - 1][0] + //upper line
					surf[f - 1][0 + 1] + surf[f][size - 1] +
					surf[f][0 + 1] + surf[f + 1][size - 1] +
					surf[f + 1][0] + surf[f + 1][0 + 1]) / 8;
				if (surf[f][0] / avrg < smooth_parameter / 2.0f) surf[f][0] = avrg;

				avrg = (surf[f - 1][size - 2] + surf[f - 1][size - 1] + //bottom line
					surf[f - 1][0] + surf[f][size - 2] +
					surf[f][0] + surf[f + 1][size - 2] +
					surf[f + 1][size - 1] + surf[f + 1][0]) / 8;
				if (surf[f][size - 1] / avrg < smooth_parameter / 2.0f) surf[f][size - 1] = avrg;

				avrg = (surf[size - 2][f - 1] + surf[size - 2][f] + //right wall
					surf[size - 2][f + 1] + surf[size - 1][f - 1] +
					surf[size - 1][f + 1] + surf[0][f - 1] +
					surf[0][f] + surf[0][f + 1]) / 8;
				if (surf[size - 1][f] / avrg < smooth_parameter / 2.0f) surf[size - 1][f] = avrg;

				avrg = (surf[size - 1][f - 1] + surf[size - 1][f] + //left wall
					surf[size - 1][f + 1] + surf[0][f - 1] +
					surf[0][f + 1] + surf[0 + 1][f - 1] +
					surf[0 + 1][f] + surf[0 + 1][f + 1]) / 8;
				if (surf[0][f] / avrg < smooth_parameter / 2.0f) surf[0][f] = avrg;
			}

			// corners
			//* - - 
			//- - -
			//- - -
			avrg = (surf[1][0] + surf[0][1] + //left wall
				surf[1][1] + surf[size - 1][size - 1] +
				surf[size - 1][0] + surf[size - 1][1] +
				surf[0][size - 1] + surf[1][size - 1]) / 8;
			if (surf[0][0] / avrg < smooth_parameter / 2.0f) surf[0][0] = avrg;
			//- - *
			//- - -
			//- - -
			avrg = (surf[size - 2][0] + surf[size - 2][1] + //left wall
				surf[size - 1][1] + surf[size - 1][size - 1] +
				surf[size - 2][size - 1] + surf[0][0] +
				surf[0][1] + surf[0][size - 1]) / 8;
			if (surf[size - 1][0] / avrg < smooth_parameter / 2.0f) surf[size - 1][0] = avrg;
			//- - - 
			//- - -
			//* - -
			avrg = (surf[0][0] + surf[1][0] + //left wall
				surf[size - 1][0] + surf[0][size - 2] +
				surf[1][size - 2] + surf[1][size - 1] +
				surf[size - 1][size - 1] + surf[size - 1][size - 2]) / 8;
			if (surf[0][size - 1] / avrg < smooth_parameter / 2.0f) surf[0][size - 1] = avrg;
			//- - - 
			//- - -
			//- - *
			avrg = (surf[0][0] + surf[size - 2][0] + //left wall
				surf[size - 1][0] + surf[0][size - 2] +
				surf[0][size - 1] + surf[size - 1][size - 2] +
				surf[size - 2][size - 1] + surf[size - 2][size - 2]) / 8;
			if (surf[size - 1][size - 1] / avrg < smooth_parameter / 2.0f) surf[size - 1][size - 1] = avrg;

			for (int i = 1; i < size - 1; i++) // inner square
			{
				for (int j = 1; j < size - 1; j++)
				{
					avrg = (surf[i - 1][j - 1] + surf[i - 1][j] +
						surf[i - 1][j + 1] + surf[i][j - 1] +
						surf[i][j + 1] + surf[i + 1][j - 1] +
						surf[i + 1][j] + surf[i + 1][j + 1]) / 8;
					if (surf[i][j] / avrg < smooth_parameter / 2.0f) surf[i][j] = avrg;
				}
			}

		}

		float min = 10000.0f, max = -10000.0f; //normalasing after smooth into [0, 1]
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				if (surf[i][j] > max) max = surf[i][j];
				if (surf[i][j] < min) min = surf[i][j];
			}
		}

		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				surf[i][j] = (surf[i][j] - min) / (max - min);
			}
		}
	}
}

void surface::req_fill(int x1, int y1, int x2, int y2, float grad, float* seed[])
{
	std::vector<short*> square_list = {};
	std::vector<short*> next_deep = {};

	square_list.push_back(new short[5]);
	square_list[0][0] = x1;
	square_list[0][1] = y1;
	square_list[0][2] = x2;
	square_list[0][3] = y2;

	bool finish = false;

	while (!finish)
	{
		finish = true;

		for (short* i : square_list)
		{
			int next_pointX = (int)round((i[0] + i[2]) / 2.0f);
			int next_pointY = (int)round((i[1] + i[3]) / 2.0f);

			if (surf[next_pointX][next_pointY] == 0.0f)
				surf[next_pointX][next_pointY] = seed[next_pointX][next_pointY] * grad +
				(surf[i[0]][i[1]] + surf[i[0]][i[3]] + surf[i[2]][i[1]] + surf[i[2]][i[3]]) / 4;
		}

		for (short* i : square_list)
		{
			int next_pointX = (int)round((i[0] + i[2]) / 2.0f);
			int next_pointY = (int)round((i[1] + i[3]) / 2.0f);

			int tempX = next_pointX + 1, tempY = next_pointY + 1, tempXn = next_pointX - 1, tempYn = next_pointY - 1;

			while (tempX % size != next_pointX && surf[tempX % size][next_pointY] == 0.0f) tempX++;
			while (tempY % size != next_pointY && surf[next_pointX][tempY % size] == 0.0f) tempY++;
			while (tempXn != next_pointX && surf[tempXn][next_pointY] == 0.0f)
			{
				tempXn--;
				if (tempXn == -1) tempXn = size - 1;
			}
			while (tempYn != next_pointY && surf[next_pointX][tempYn] == 0.0f)
			{
				tempYn--;
				if (tempYn == -1) tempYn = size - 1;
			}

			tempX %= size;
			tempY %= size;

			if (surf[i[2]][next_pointY] == 0.0f)
				surf[i[2]][next_pointY] = seed[i[2]][next_pointY] * grad +
				(surf[i[2]][i[1]] + surf[i[2]][i[3]] + surf[next_pointX][next_pointY] + surf[tempX][next_pointY]) / 4;

			if (surf[i[0]][next_pointY] == 0.0f)
				surf[i[0]][next_pointY] = seed[i[0]][next_pointY] * grad +
				(surf[i[0]][i[1]] + surf[i[0]][i[3]] + surf[next_pointX][next_pointY] + surf[tempXn][next_pointY]) / 4;

			if (surf[next_pointX][i[1]] == 0.0f)
				surf[next_pointX][i[1]] = seed[next_pointX][i[1]] * grad +
				(surf[i[0]][i[1]] + surf[i[2]][i[1]] + surf[next_pointX][next_pointY] + surf[next_pointX][tempYn]) / 4;

			if (surf[next_pointX][i[3]] == 0.0f)
				surf[next_pointX][i[3]] = seed[i[0]][next_pointY] * grad +
				(surf[i[0]][i[3]] + surf[i[2]][i[3]] + surf[next_pointX][next_pointY] + surf[next_pointX][tempYn]) / 4;

			if (abs(i[0] - i[2]) > 2 || abs(i[1] - i[3]) > 2) finish = false;


			next_deep.push_back(new short[4]);
			next_deep[next_deep.size() - 1][0] = i[0];
			next_deep[next_deep.size() - 1][1] = i[1];
			next_deep[next_deep.size() - 1][2] = next_pointX;
			next_deep[next_deep.size() - 1][3] = next_pointY;
			next_deep.push_back(new short[4]);
			next_deep[next_deep.size() - 1][0] = next_pointX;
			next_deep[next_deep.size() - 1][1] = next_pointY;
			next_deep[next_deep.size() - 1][2] = i[2];
			next_deep[next_deep.size() - 1][3] = i[3];
			next_deep.push_back(new short[4]);
			next_deep[next_deep.size() - 1][0] = next_pointX;
			next_deep[next_deep.size() - 1][1] = i[1];
			next_deep[next_deep.size() - 1][2] = i[2];
			next_deep[next_deep.size() - 1][3] = next_pointY;
			next_deep.push_back(new short[4]);
			next_deep[next_deep.size() - 1][0] = i[0];
			next_deep[next_deep.size() - 1][1] = next_pointY;
			next_deep[next_deep.size() - 1][2] = next_pointX;
			next_deep[next_deep.size() - 1][3] = i[3];
		}

		grad *= this->grad;

		for (short* k : square_list) delete k;
		square_list.clear();
		square_list = next_deep;
		next_deep.clear();
	}

	for (short* k : square_list) delete k;
	square_list.clear();
	for (short* k : next_deep) delete k;
	next_deep.clear();
}

void surface::open_pic()
{
	if (size <= 3) return;

	sf::RenderWindow pic_window(sf::VideoMode(size, size), "Surface generator");
	sf::Image out_img;
	sf::Event ev;
	sf::Texture tmp;
	sf::Sprite spr;

	pic_window.clear(sf::Color(0, 0, 0));

	out_img.create(size, size);

	if (mode == 2)
		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++)
			{
				out_img.setPixel(i, j, sf::Color(255 * surf[i][j], 255 * surf[i][j], 255 * surf[i][j]));
			}

	if (mode == 1)
		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++)
			{
				float sized_k = (surf[i][j] - water_percentage) / (1 - water_percentage);
				if (surf[i][j] > water_percentage)
					if (sized_k < sand_percent)
						out_img.setPixel(i, j, sf::Color((int)round(255 * (sized_k / sand_percent)), (int)round(255 * (sized_k / sand_percent)), 0));
					else if (sized_k > snow_line + water_percentage)
						out_img.setPixel(i, j, sf::Color((int)round(255 * (1.0f / 3) * (2 + (sized_k - snow_line) / (1 - snow_line))), (int)round(255 * (1.0f / 3) * (2 + (sized_k - snow_line) / (1 - snow_line))), (int)round(255 * (1.0f / 3) * (2 + (sized_k - snow_line) / (1 - snow_line)))));
					else
						out_img.setPixel(i, j, sf::Color(0, (int)round(255 * sized_k), 0));
				else
					out_img.setPixel(i, j, sf::Color(0, 0, (int)round(255 * (1 - (water_percentage - surf[i][j]) / water_percentage))));
			}

	tmp.loadFromImage(out_img);
	spr.setTexture(tmp, true);

	pic_window.draw(spr);
	pic_window.display();

	while (pic_window.isOpen())
	{
		pic_window.draw(spr);
		pic_window.display();
		while (pic_window.pollEvent(ev))
			if (ev.type == sf::Event::Closed) pic_window.close();
	}

	pic_window.close();
}

void surface::delete_array(float** arra)
{
	for (int i = 0; i < size; i++)
		delete arra[i];
	delete arra;
}

void surface::set_size(int size)
{
	delete_array(surf);
	delete_array(seed);
	this->size = size;
	gen_seed();
}

void surface::set_smooth(int smooth)
{
	this->smooth_lvl = smooth;
}

void surface::set_mode(int mode)
{
	this->mode = mode;
}

void surface::set_water(float water)
{
	this->water_percentage = water;
}

void surface::set_sand(float sand)
{
	this->sand_percent = sand;
}

void surface::set_grad(float grad)
{
	this->grad = grad;
}

std::string surface::get_status()
{
	std::string ans = "";

	ans += "size = ";
	ans += std::to_string(size);
	ans += "\n";

	ans += "water = ";
	ans += std::to_string(water_percentage);
	ans += "\n";

	ans += "sand = ";
	ans += std::to_string(sand_percent);
	ans += "\n";

	ans += "smooth = ";
	ans += std::to_string(smooth_lvl);
	ans += "\n";

	ans += "grad = ";
	ans += std::to_string(grad);
	ans += "\n";

	ans += "drawmode = ";
	ans += std::to_string(mode);
	ans += "\n";

	return ans;
}