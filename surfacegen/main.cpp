#include "iostream"
#include <string.h>
#include "surface.h"

void help();
void inp();

int main()
{
	help();

	std::string input = "";
	surface my_surf;

	while (input != "exit")
	{
		inp();
		std::cin >> input;

		if (input == "size")
		{
			std::cout << "(int size of surface. Recommended < 1000)";
			inp();
			int size;
			std::cin >> input;
			try
			{
				size = std::stoi(input);
				if (size > 3) my_surf.set_size(size);
				else std::cout << "Size is too small! \n";
			}
			catch (std::exception e)
			{
				std::cout << "This is not int! \n";
			}
		}
		else if (input == "water")
		{
			std::cout << " (value in interval [0, 1])";
			inp();
			float water;
			std::cin >> input;
			try
			{
				water = std::stof(input);
				if (water >= 0.0f && water <= 1.0f) my_surf.set_water(water);
				else std::cout << "Size is incorrect! \n";
			}
			catch (std::exception e)
			{
				std::cout << "This is not a number! \n";
			}
		}
		else if (input == "sand")
		{
			std::cout << " (value in interval [0, 1])";
			inp();
			float sand;
			std::cin >> input;
			try
			{
				sand = std::stof(input);
				if (sand >= 0.0f && sand <= 1.0f) my_surf.set_sand(sand);
				else std::cout << "Size is incorrect! \n";
			}
			catch (std::exception e)
			{
				std::cout << "This is not a number! \n";
			}
		}
		else if (input == "smooth")
		{
			std::cout << "(int number of smooth itterations. Recommended < 100))";
			inp();
			int smooth;
			std::cin >> input;
			try
			{
				smooth = std::stoi(input);
				if (smooth >= 0) my_surf.set_smooth(smooth);
				else std::cout << "Size is too small! \n";
			}
			catch (std::exception e)
			{
				std::cout << "This is not int! \n";
			}
		}
		else if (input == "grad")
		{
			std::cout << " (value in interval [0, 1])";
			inp();
			float grad;
			std::cin >> input;
			try
			{
				grad = std::stof(input);
				if (grad >= 0.0f && grad <= 1.0f) my_surf.set_grad(grad);
				else std::cout << "Size is incorrect! \n";
			}
			catch (std::exception e)
			{
				std::cout << "This is not a number! \n";
			}
		}
		else if (input == "drawmode")
		{
			std::cout << "1(for landscape) 2(for noise)";
			inp();
			int mode;
			std::cin >> input;
			try
			{
				mode = std::stoi(input);
				if (mode == 1 || mode == 2) my_surf.set_mode(mode);
				else std::cout << "Not existing mode! \n";
			}
			catch (std::exception e)
			{
				std::cout << "This is not int! \n";
			}
		}
		else if (input == "gen")
		{
			my_surf.gen_surf();
			std::cout << "Picture settings: \n" << my_surf.get_status();
			my_surf.open_pic();
		}
		else if (input == "draw")
		{
			my_surf.make_pic();
			std::cout << "Picture settings: \n" << my_surf.get_status();
			my_surf.open_pic();
		}
		else if (input == "seed")
		{
			my_surf.make_seed();
		}
		else if (input == "help") help();
		else if (input != "exit")
			std::cout << "Not existing command \n";
	}
	return 0;
}

void help()
{
	std::cout << "You can setup the map settings with commands:  "
		<< "\n size"
		<< "\n water"
		<< "\n sand"
		<< "\n smooth"
		<< "\n grad"
		<< "\n drawmode"
		<< "\n"
		<< "\nUse this commands to make a picture:"
		<< "\n seed (to generate new seed)"
		<< "\n draw (to draw with ready seed)"
		<< "\n gen (generate seed and draw)"
		<< "\n"
		<< "\nOther commands:"
		<< "\n help"
		<< "\n exit"
		<< "\n input format: >> water";
}

void inp()
{
	std::cout << "\n>> ";
}