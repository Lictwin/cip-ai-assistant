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
struct layer_wrapper_bp
{
	std::vector<neiron*> this_neiron;
	std::vector<double> Values_diff;
	std::vector<double> Values_output;
	size_t qua_of_neirons;
};

using std::vector;


class teacher {

	friend class neural_network;
	friend class layers;
	friend class neiron;
	vector<double> data;
	vector<layer*> layers;
	size_t numb_of_layers;


public:
	teacher(vector<double> data_set, neural_network net)
	{
		data = data_set;
		layers = net.get_layers();
		numb_of_layers = net.get_numb_of_layers();
	}



	void train(vector<double> out, vector<double> prop, vector<double> in)
	{
		vector<double> next_gamma, now_gamma;
		vector<neiron*> neiro;
		double alfa = 0.1;

		for (size_t i = 0; i < out.size(); i++)
		{
			now_gamma.push_back(out[i] - prop[i]);
		}

		neiro = layers[layers.size() - 1]->get_this_layer();

		for (size_t i = 0; i < neiro.size(); i++)
		{
			vector<double> diff = layers[layers.size() - 1]->get_result_diff();
			vector<double> res = layers[layers.size() - 2]->get_result();
			double now_T = neiro[i]->get_T();
			vector<double> Wh;
			Wh = neiro[i]->get_weight_pointers();
			for (size_t j = 0; j < Wh.size(); j++)
			{
				Wh[j] = Wh[j] - alfa * now_gamma[i] * diff[i] * res[j];
			}
			now_T = now_T + alfa * now_gamma[i] * diff[i];
			neiro[i]->set_T(now_T);
			neiro[i]->set_weight(Wh);
		}
		next_gamma = now_gamma;

		
		for (size_t z = layers.size()-2; z > 0; z--)
		{
			now_gamma.clear();
			neiro = layers[z]->get_this_layer();
            vector<double> diff = layers[z+1]->get_result_diff();
			vector<double> Wh;
			

			for (size_t i = 0; i < neiro.size(); i++)	 
			{
				
				vector<neiron*> next_neiro = layers[z + 1]->get_this_layer();
				double gamma = 0;
				for (size_t j = 0; j < next_gamma.size(); j++)
				{
					Wh = next_neiro[j]->get_weight_pointers();
					gamma += next_gamma[j] * Wh[i] * diff[j];
				}
                
				now_gamma.push_back(gamma);
			}

			diff = layers[z]->get_result_diff();
			vector<double> res = layers[z - 1]->get_result();

			for (size_t i = 0; i < neiro.size(); i++)
			{
				
				double now_T = neiro[i]->get_T();
				Wh = neiro[i]->get_weight_pointers();
				for (size_t j = 0; j < Wh.size(); j++)
				{
					Wh[j] = Wh[j] - alfa * now_gamma[i] * diff[i] * res[j];
				}
				now_T = now_T + alfa * now_gamma[i] * diff[i];
				neiro[i]->set_T(now_T);
				neiro[i]->set_weight(Wh);
			}
			next_gamma = now_gamma;
		}


		now_gamma.clear();
		neiro = layers[0]->get_this_layer();
		vector<double> diff = layers[0]->get_result_diff();
		vector<double> Wh;


		for (size_t i = 0; i < neiro.size(); i++)
		{

			vector<neiron*> next_neiro = layers[1]->get_this_layer();
			double gamma = 0;
			for (size_t j = 0; j < next_gamma.size(); j++)
			{
				Wh = next_neiro[j]->get_weight_pointers();
				gamma += next_gamma[j] * Wh[i] * diff[j];
			}

			now_gamma.push_back(gamma);
		}

		diff = layers[0]->get_result_diff();
		vector<double> res = in;

		for (size_t i = 0; i < neiro.size(); i++)
		{

			double now_T = neiro[i]->get_T();
			Wh = neiro[i]->get_weight_pointers();
			for (size_t j = 0; j < Wh.size(); j++)
			{
				Wh[j] = Wh[j] - alfa * now_gamma[i] * diff[i] * res[i];
			}
			now_T = now_T + alfa * now_gamma[i] * diff[i];
			neiro[i]->set_T(now_T);
			neiro[i]->set_weight(Wh);
		}


	}

	void back_propogation(vector<double> data_set)
	{
		
		bool status;
		const double E = 0.001;
		double Ek;
		size_t itterator;
		while (1)
		{
			    status = true;
			    itterator = 0;
				std::vector<double> in;
				for (size_t i = itterator; i < layers[0]->how_many_in_this_layer() + itterator; i++)
				{
					in.push_back(data[i]);
				}
				
				
				for (size_t j = 0; j < (data.size() - layers[0]->how_many_in_this_layer()) / layers[layers.size() - 1]->how_many_in_this_layer(); j++)
				{
					std::vector<double> prop;
					for (size_t i = layers[0]->how_many_in_this_layer() + itterator; i < layers[0]->how_many_in_this_layer() + itterator 
						+ layers[layers.size() - 1]->how_many_in_this_layer(); i++)
					{
						prop.push_back(data[i]);
					}


					Ek = 0;
					layers[0]->put_values(in);

					for (size_t i = 0; i < numb_of_layers; i++)
					{
						layers[i]->working_layer();
					}
					std::vector<double> out;
					out = layers[layers.size() - 1]->get_result();

					for (size_t i = 0; i < out.size(); i++)
					{
						Ek += pow(out[i] - prop[i], 2) / 2;			
					}


					if (Ek > E)
					{
						status = false;
						train(out, prop, in);

					}
					
					itterator += layers[layers.size() - 1]->how_many_in_this_layer();
					in.clear();
					out.clear();
					prop.clear();
					for (size_t i = itterator; i < layers[0]->how_many_in_this_layer() + itterator; i++)
					{
						in.push_back(data[i]);
					}
				}
				
				if (status)
					break;
			
		}
	
	}
};


