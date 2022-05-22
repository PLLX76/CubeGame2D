#include "item.h"
#include <vector>
#include <iostream>
#include <string>

std::vector<int> inventaire = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

bool add_item_id(int id) {
	for (int i = 0; i < inventaire.size(); i++)
	{
		if (inventaire[i] == id) 
			return false;
	}
	for (int i = 0; i < inventaire.size(); i++)
	{
		if (inventaire[i] == 0)
		{
			inventaire[i] = id;
			return true;
		}
	}
	return false;
}
std::vector<int> get_item_list() {
	std::vector<int> item_list;
	for (int i = 0; i < inventaire.size(); i++)
	{
		if (inventaire[i] != 0)
			item_list.push_back(inventaire[i]);
			
	}
	std::string text = "";
	for (int i = 0; i < inventaire.size(); i++)
	{
		text += std::to_string(inventaire[i]) + ", ";
		
	}
	return item_list;
}
bool remove_item_id(int id) {
	for (int i = 0; i < inventaire.size(); i++)
	{
		if (inventaire[i] == id)
		{
			inventaire[i] = 0;
			return true;
		}
	}
	return false;
}
void remove_all_item() {
	inventaire = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
}
