#pragma once
#include <vector>

bool add_item_id(int id);
std::vector<int> get_item_list();
bool remove_item_id(int id);
void remove_all_item();
void latence_item_change(bool latence, int latence_max);