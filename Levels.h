#pragma once

#include <iostream>
#include <string>
#include <fstream>

std::string resourcespack = "default";
int level = 1;

#pragma region Levels

int tapmap[14][15] = {
	{0,0,0,0,8,0,0,5,0,6,0,0,0,0,0},
	{4,0,0,1,1,1,1,1,0,1,0,0,1,1,1},
	{1,1,0,0,0,0,3,0,0,3,0,4,0,0,0},
	{6,6,4,0,0,0,1,0,1,1,1,1,0,0,0},
	{1,1,1,1,2,0,0,0,0,0,1,0,6,6,6},
	{0,0,9,1,0,0,5,0,7,0,1,0,0,4,0},
	{1,1,1,1,1,0,1,0,1,1,1,1,1,1,1},
	{0,0,0,0,3,0,0,0,0,0,0,1,0,0,1},
	{7,0,0,0,2,6,6,6,0,7,0,1,0,0,1},
	{1,0,0,0,0,0,0,4,0,1,1,1,1,1,1},
	{0,1,0,1,1,1,1,1,1,1,0,1,0,0,0},
	{0,0,0,0,0,1,0,0,0,1,0,1,0,0,0},
	{0,0,1,0,0,0,0,3,0,1,0,1,0,0,0},
	{6,6,1,1,1,1,1,1,1,1,0,1,0,0,0},
};
int tapmapportal[14][15] = {
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,1,0,0,2,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,2,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
	{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0} };

#pragma endregion

int heightmap = 14;
int withtmap = 15;

void ChargeLevels(int niveau) {
	std::ifstream ifs(("resourcespack/" + resourcespack + "/Levels/level"+ std::to_string(niveau) +".txt").c_str());

	if (ifs.is_open())
	{
		ifs >> heightmap;
		ifs >> withtmap;

		for (int y = 0; y < heightmap; y++)
		{
			for (int x = 0; x < withtmap; x++)
			{
				ifs >> tapmap[y][x];
			}
		}
		ifs.close();
	}
	else
	{
		level = 0;
	}
	

}
void ChargePortal(int niveau) {
	std::ifstream ifs(("resourcespack/" + resourcespack + "/Levels/level" + std::to_string(niveau) + "portal.txt").c_str());

	if (ifs.is_open())
	{

		for (int y = 0; y < heightmap; y++)
		{
			for (int x = 0; x < withtmap; x++)
			{
				ifs >> tapmapportal[y][x];
			}
		}
		ifs.close();
	}
	else
	{
		level = 0;
	}
	

}