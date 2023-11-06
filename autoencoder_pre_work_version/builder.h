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

public:

	void make_pointers_in_neiron_one_to_all(vector<layer*> pointers, size_t comm_in_first_layer)
	{
		pointers[0]->set_next_layer(pointers[1]->get_this_layer());
		/*switch (comm_in_first_layer)
		{
		case 1:
			pointers[0]->

			break;

		default:
			break;
		}*/
		for (size_t i = 1; i < pointers.size()-1; i++)
		{
			pointers[i]->set_next_layer(pointers[i + 1]->get_this_layer());
			pointers[i]->set_prev_layer(pointers[i - 1]->get_this_layer());
		}

		pointers[pointers.size() - 1]->set_prev_layer(pointers[pointers.size() - 2]->get_this_layer());
	}

};