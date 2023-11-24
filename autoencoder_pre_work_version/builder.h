#pragma once
#include "layer.h"
#include <vector>
#include "neural_network.h"
#include "neiron.h"

#include <iostream>
class neiron;
class layer;

using std::vector;


class builder {

	friend class neural_network;
	friend class layers;
	friend class neiron;

	void make_pointers_in_neiron_one_to_all(vector<layer*> pointers_layer)
	{
		for (size_t i = 0; i < pointers_layer.size(); i++)
		{
			for (size_t j = 0; j < pointers_layer[i]->how_many_in_this_layer(); j++)
			{
				(pointers_layer[i]->get_neiro(j))->set_pointers_next_level(pointers_layer[i]->get_next_layer());
				(pointers_layer[i]->get_neiro(j))->set_pointers_prev_level(pointers_layer[i]->get_prev_layer());

			}
		}
		

	}

public:

	void make_pointers_in_layer_one_to_all(vector<layer*> pointers, size_t comm_in_first_layer)
	{
		pointers[0]->set_next_layer(pointers[1]->get_this_layer());
		for (size_t i = 0; i < 1; i++)
		{
			vector<neiron*> set_prev;
			for (size_t j = 0; j < comm_in_first_layer; j++)
			{
				set_prev.push_back(NULL);
			}
			pointers[0]->set_prev_layer(set_prev);
		}


		for (size_t i = 1; i < pointers.size()-1; i++)
		{
			pointers[i]->set_next_layer(pointers[i + 1]->get_this_layer());
			pointers[i]->set_prev_layer(pointers[i - 1]->get_this_layer());
		}

		pointers[pointers.size() - 1]->set_prev_layer(pointers[pointers.size() - 2]->get_this_layer());
		std::vector<neiron*> set_next{ NULL };
		pointers[pointers.size() - 1]->set_next_layer(set_next);

		make_pointers_in_neiron_one_to_all(pointers);
	}

};