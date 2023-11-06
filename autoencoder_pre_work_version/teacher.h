#pragma once
#include "layer.h"
#include <vector>
#include "neural_network.h"
#include "neiron.h"
#include "neiron.h"
#include <iostream>
class neiron;
class layer;
class neural_network;

using std::vector;


class teacher {

	friend class neural_network;
	friend class layers;
	friend class neiron;

public:

	void train(vector<double> data_set, neural_network net)
	{
		
	}

};