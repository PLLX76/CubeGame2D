#include <SFML/Graphics.hpp>
#include <iostream>
#include "Levels.h"

sf::Vector2f getPortalTp(int y, int x)
{

	sf::Vector2f vector2f;

	for (int y2 = 0; y2 < heightmap; y2++)
	{
		for (int x2 = 0; x2 < withtmap; x2++)
		{
			if (tapmapportal[y2][x2] == tapmapportal[y][x]) {
				if (y2 != y || x2 != x)
				{
					vector2f.x = x2 * 64+10;
					vector2f.y = y2 * 64+10;
					std::cout << "tp : x = " << vector2f.x << ", y = "<< vector2f.y << std::endl;
				}
			}
		}
	}

	return vector2f;
}