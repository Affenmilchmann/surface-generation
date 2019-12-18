#include "iostream"
#include <time.h>
#include <string.h>
#include <algorithm>
#include <SFML\Graphics.hpp>

const int AMP = 100;
int KOST = 16;

void color_print(int color, std::string text);
void lift(float* surf[], float* matr[], int s, int x, int y, float regulation, float speed_const, int max, float& global_max);
float dist(int x1, int y1, int x2, int y2);

int main()
{
	//for (int i = 0; i < 200; i++) color_print(i, "8\n");
	/*printf("\033[3;42;30mTexting\033[0m\t\t");
	printf("\033[3;42;30mTexting\033[0m\t\t");*/

	int s;
	float max = -1000;
	float speed;
	std::cin >> s;
	std::cin >> speed;

	srand(time(0));

	float** matr = new float* [s];
	float** surf = new float* [s];
	for (int i = 0; i < s; i++)
	{
		matr[i] = new float[s];
		surf[i] = new float[s];
		for (int j = 0; j < s; j++)
		{
			matr[i][j] = (rand() % (2 * AMP) - AMP) /** (rand() % 10) / (rand() % 10 + 1)*/;
			surf[i][j] = 0;
			//std::cout << matr[i][j] << " ";
		}
		//std::cout << std::endl;
	}

	/*int lifts_amount;
	std::cin >> lifts_amount;
	for (int i = 0; i < lifts_amount; i++)
	{
		int size = rand() % (s - 1) + 1;
		int start_x = rand() % (s - size - 1);
		int start_y = rand() % (s - size - 1);
		lift(surf, matr, size, start_x, start_y, 1.0f, speed, s);
	}*/

	lift(surf, matr, s - 1, 0, 0, 1.0f, speed, s, max);

	/*for (int i = 0; i < s; i++)
	{
		for (int j = 0; j < s; j++)
		{
			printf("%3d ", (int)round(surf[i][j]));
		}
		std::cout << std::endl;
	}*/

	sf::RenderWindow pic_window(sf::VideoMode(unsigned(s), unsigned(s)), "Pic");
	sf::Event ev;
	pic_window.clear(sf::Color(0, 0, 0));
	sf::Image out_img;
	out_img.create(s, s);

	for (int i = 0; i < s; i++)
		for (int j = 0; j < s; j++)
		{
			if (surf[i][j] >= 0)
				out_img.setPixel(i, j, sf::Color(std::min((int)round(255 * surf[i][j] / max), 255), 0, 0));
			else
				out_img.setPixel(i, j, sf::Color(0, std::min((int)round(abs(255 * surf[i][j] / max)), 255), 0));
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

	return 0;
}

void lift(float* surf[], float* matr[], int s, int x, int y, float regulation, float speed_const, int max, float& global_max)
{
	float localL = s / sqrt(2);

	int start_x = x, start_y = y;

	if (rand() % 1 == 0)
	{
		if (rand() % 2 == 1)
			x += (int)round(s / 2);
		else
			x -= (int)round(s / 2);

		if (rand() % 2 == 1)
			y += (int)round(s / 2);
		else
			y -= (int)round(s / 2);
	}

	for (int i = x; i < x + s; i++)
	{
		int currX = x + (int)round(s / 2);
		if (currX >= max || currX < 0 || i >= max || i < 0) break; 

		for (int j = y; j < y + s; j++)
		{
			int currY = y + (int)round(s / 2);
			int currDist = dist(i, j, currX, currY);

			if (currY >= max || currY < 0 || j < 0 || j >= max) break;

			if (currDist < s / 2 || rand() % 2 == 1)
			{
				surf[i][j] += regulation * matr[currX][currY] * (1 - (currDist / localL));
				if (abs(surf[i][j]) > global_max) global_max = abs(surf[i][j]);
			}
		}
	}

	if (s <= 1) return;

	//int temp = (int)ceil(s / 2);
	int step = (int)round(s / 2); if (step < 1) step = 1;
	int temp = s - step; if (temp < 1) temp = 1;
	float regu = regulation * speed_const;

	lift(surf, matr, temp, start_x, start_y, regu, speed_const, max, global_max);
	lift(surf, matr, temp, start_x + step, start_y, regu, speed_const, max, global_max);
	lift(surf, matr, temp, start_x, start_y + step, regu, speed_const, max, global_max);
	lift(surf, matr, temp, start_x + step, start_y + step, regu, speed_const, max, global_max);
}

float dist(int x1, int y1, int x2, int y2)
{
	return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

void color_print(int color, std::string text)
{
	printf("\x1B[%dm", color);
	printf(text.c_str());
	printf("\033[0m");
}