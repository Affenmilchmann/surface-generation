#include "surface.h"


surface::surface(int size, float grad, int amp)
{
	srand(time(0));

	this->grad = grad;
	this->size = size;
	amplitude = amp;
	abs_max = 1.0f * (-100000000);
	seed = new float* [size];
	surf = new float* [size];

	for (int i = 0; i < size; i++)
	{
		seed[i] = new float[size];
		surf[i] = new float[size];
	}

	make_seed();
}

void surface::make_seed()
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			seed[i][j] = (rand() % (2 * amplitude) - amplitude);
			surf[i][j] = 0;
		}
	}
}

void surface::gen_surf()
{
	req_fill(size, 0, 0, grad);
}

void surface::req_fill(int size, int x, int y, float grad)
{
	float localL = size / sqrt(2);

	int start_x = x, start_y = y;

	if (rand() % 1 == 0)
	{
		if (rand() % 2 == 1)
			x += (int)round(size / 2);
		else
			x -= (int)round(size / 2);

		if (rand() % 2 == 1)
			y += (int)round(size / 2);
		else
			y -= (int)round(size / 2);
	}

	for (int i = x; i < x + size; i++)
	{
		int currX = x + (int)round(size / 2);
		if (currX >= this->size || currX < 0 || i >= this->size || i < 0) break;

		for (int j = y; j < y + size; j++)
		{
			int currY = y + (int)round(size / 2);
			int currDist = mymath::dist(i, j, currX, currY);

			if (currY >= this->size || currY < 0 || j < 0 || j >= this->size) break;

			if (currDist < size / 2 || rand() % 2 == 1)
			{
				surf[i][j] += grad * seed[currX][currY] * (1 - (currDist / localL));
				if (abs(surf[i][j]) > abs_max) abs_max = abs(surf[i][j]);
			}
		}
	}

	if (size <= 1) return;

	int step = (int)round(size / 2); if (step < 1) step = 1;
	int temp_size = size - step; if (temp_size < 1) temp_size = 1;
	float regu = grad * this->grad;

	req_fill(temp_size, start_x, start_y, regu);
	req_fill(temp_size, start_x + step, start_y, regu);
	req_fill(temp_size, start_x, start_y + step, regu);
	req_fill(temp_size, start_x + step, start_y + step, regu);
}

void surface::open_pic()
{
	sf::RenderWindow pic_window(sf::VideoMode(unsigned(size), unsigned(size)), "Pic");
	sf::Event ev;
	pic_window.clear(sf::Color(0, 0, 0));
	sf::Image out_img;
	out_img.create(size, size);

	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
		{
			if (surf[i][j] >= 0)
				out_img.setPixel(i, j, sf::Color((int)round(255 * surf[i][j] / abs_max), 0, 0));
			else
				out_img.setPixel(i, j, sf::Color(0, (int)round(abs(255 * surf[i][j] / abs_max)), 0));
		}

	sf::Texture tmp;
	tmp.loadFromImage(out_img);
	sf::Sprite spr;
	spr.setTexture(tmp, true);

	pic_window.draw(spr);
	pic_window.display();

	while (pic_window.isOpen())
		while (pic_window.pollEvent(ev))
			if (ev.type == sf::Event::Closed) pic_window.close();
}