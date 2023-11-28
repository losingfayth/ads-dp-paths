/**
 * Driver file for paths.cpp
 *
 * @author fayth quinn
 */

#include <iostream>
#include <string>
#include "paths.h"

int main(int argc, char *argv[])
{
	if (argc > 0)
	{
		Paths p(std::stoi(argv[1]), std::stoi(argv[2]));

		std::cout << p;
		p.run();
	}
}