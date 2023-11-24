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
		switch (comm_in_first_layer)
		{
		case 1:
			comm_in_first_layer = 1;
			break;
		case 2:
			comm_in_first_layer = layers[0]->how_many_in_this_layer();
			break;
		default:
			std::cout << "invalid communications\n";
			std::exit;
			break;
		}

		make_pointers();
		

		std::cout << "end\n";
	}

	vector<layer*> get_layers() {
		return layers;
	}

	size_t get_numb_of_layers() {
		return numb_of_layers;
	}

	void working() {
		std::vector<double> in;
		for (size_t i = 0; i < layers[0]->how_many_in_this_layer(); i++)
		{
			in.push_back(values_to_set[i]);
		}
		for (size_t i = 0; i < layers.size(); i++)
		{
			layers[layers.size() - 1]->clear_all();
		}
		for (size_t j = 0; j < values_to_set.size() - layers[0]->how_many_in_this_layer(); j++)
		{
			layers[0]->put_values(in);

			for (size_t i = 0; i < numb_of_layers; i++)
			{
				layers[i]->working_layer();
			}
			std::vector<double> out;
			std::vector<double> out_true;
			
			out = layers[layers.size() - 1]->get_result();
			layers[layers.size() - 1]->clear_all();
			for (size_t i = 0; i < out.size(); i++)
			{
				out_true.push_back(values_to_set[i + j + layers[0]->how_many_in_this_layer()]);
			}
			
			for (size_t i = 0; i < out.size(); i++)
			{
				std::cout << "gen " << out[i] << " real " << out_true[i] << " error " << pow(out[i] - out_true[i], 2) / 2 << "\n";
			}
			std::vector<double> set_new;
			for (size_t i = layers[layers.size()-1]->how_many_in_this_layer(); i < layers[0]->how_many_in_this_layer(); i++)
			{
				set_new.push_back(in[i]);
			}
			in = set_new;
			for (size_t i = 0; i < layers[layers.size() - 1]->how_many_in_this_layer(); i++)
			{
				in.push_back(out[i]);
			}
			out.clear();
		}
	}


	void make_pointers(){

		builder ser_build;
		ser_build.make_pointers_in_layer_one_to_all(layers, comm_in_first_layer);
	}

	void set_data(std::vector<double> set)
	{
		values_to_set = set;
	}

	void train(vector<double> out, vector<double> prop, vector<double> in)
	{
		vector < vector <double>> gammas;
		vector<double> next_gamma, now_gamma;
		vector <vector <double>> res;
		vector <vector <double>> diff_res;
		vector<neiron*> neiro;
		double alfa = 0.2;

		res.push_back(layers[layers.size() - 2]->get_result());
		diff_res.push_back(layers[layers.size() - 1]->get_result());
		for (size_t i = 0; i < out.size(); i++)
		{
			now_gamma.push_back(out[i] - prop[i]);
		}
		gammas.push_back(now_gamma);
		/*neiro = layers[layers.size() - 1]->get_this_layer();

		for (size_t i = 0; i < neiro.size(); i++)
		{
			vector<double> diff = layers[layers.size() - 1]->get_result_diff();
			vector<double> res = layers[layers.size() - 2]->get_result();
			neiro[i]->teach(now_gamma[i], 0.01, diff[i], res);
		}*/
		next_gamma = now_gamma;


		for (size_t z = layers.size() - 2; z > 0; z--)
		{
			now_gamma.clear();
			neiro = layers[z]->get_this_layer();
			vector<double> diff = layers[z]->get_result_diff();//здесь исправить получение
			vector<double> Wh;
			diff_res.push_back(diff);
			res.push_back(layers[z-1]->get_result());

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

			gammas.push_back(now_gamma);




			/*diff = layers[z]->get_result_diff();
			vector<double> res = layers[z - 1]->get_result();

			for (size_t i = 0; i < neiro.size(); i++)
			{
				neiro[i]->teach(now_gamma[i], 0.01, diff[i], res);
			}*/
			next_gamma = now_gamma;
		}


		now_gamma.clear();
		neiro = layers[0]->get_this_layer();
		vector<double> diff = layers[0]->get_result_diff();
		vector<double> Wh;
		diff_res.push_back(diff);
		res.push_back(in);
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
		gammas.push_back(now_gamma);

		/*diff = layers[0]->get_result_diff();
		vector<double> res = in;

		for (size_t i = 0; i < neiro.size(); i++)
		{
			neiro[i]->teach(now_gamma[i], 0.01, diff[i], res);
		}*/

		for(size_t i = 0; i < layers.size(); i++)
		{
			neiro = layers[layers.size() - i - 1]->get_this_layer();
			for (size_t j = 0; j < neiro.size(); j++)
			{
				neiro[j]->teach(gammas[i][j], alfa, diff_res[i][j], res[i]);
			}
		}
	}

	void back_propogation(vector<double> data_set)
	{
		vector<double> data = data_set;
		bool status;
		const double E = 0.00001;
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
					layers[i]->clear_all();
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
				else
				{
					//std::cout << "win " << itterator << " " << out[0] << " " << prop[0] << "\n";
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


	~neural_network(){

		for (size_t i = 0; i < numb_of_layers; i++)
		{
			layers[i]->~layer();
		}
	}
};