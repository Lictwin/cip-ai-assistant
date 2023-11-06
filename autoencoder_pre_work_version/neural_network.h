#pragma once
#include "layer.h"
#include "neiron.h"
#include "builder.h"
#include "vector"
#include <iostream>
class neiron;
class builder;
class teacher;
using std::vector;

class neural_network
{
	size_t numb_of_layers;
	//vector<size_t> numb_in_layer; // возможно пригодится

	vector<layer*> layers; 
	vector<double> values_to_set;
	size_t comm_in_first_layer;

public:

	neural_network() {


		std::cout << "set num of layers\n";
		std::cin >> numb_of_layers;

		vector<size_t> activation_by_layers;
		std::cout << "\nset activation by layers\n\n";

		for (size_t i = 0; i < numb_of_layers; i++) {
			size_t activation;
			std::cout << "set activation by "<< i+1 << " layer\n";
			std::cin >> activation;
			activation_by_layers.push_back(activation);	
		}


		vector<size_t> neirons_by_layers;
		std::cout << "\nset neirons by layers\n\n";

		for (size_t i = 0; i < numb_of_layers; i++) {
			size_t neirons;
			std::cout << "set neirons by " << i + 1 << " layer\n";
			std::cin >> neirons;
			neirons_by_layers.push_back(neirons);
		}

		for (size_t i = 0; i < numb_of_layers; i++)
		{
			layers.push_back(new layer(2, activation_by_layers[i], neirons_by_layers[i]));
		}

		std::cout << "how make communications in first layer\n 1 - one to one \n 2 - one to all\n";
		std::cin >> comm_in_first_layer;

		make_pointers();
		

		std::cout << "end\n";
	}


	void working() {

		for (size_t i = 0; i < numb_of_layers; i++)
		{
			layers[i]->working_layer();
		}


	}


	void make_pointers(){

		builder ser_build;
		ser_build.make_pointers_in_neiron_one_to_all(layers, comm_in_first_layer);
	}

	~neural_network(){

		for (size_t i = 0; i < numb_of_layers; i++)
		{
			layers[i]->~layer();
		}
	}
};