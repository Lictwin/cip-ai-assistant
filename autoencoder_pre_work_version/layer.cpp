#include "layer.h"
#include "neiron.h"
#include <iostream>




layer::layer(size_t type_of_neiro, size_t type_of_active, size_t quantity)
{
	qua_of_neirons = quantity;

	switch (type_of_neiro)
	{
	/*case input_n:

		for (size_t i = 0; i < qua_of_neirons; i++)
			this_neiron.push_back(new input_neiron(type_of_neiro));

		break;
	/case output_n:

		for (size_t i = 0; i < qua_of_neirons; i++)
			this_neiron.push_back(new output_neiron(type_of_neiro));

		break;*/
	case classic_n:

		for (size_t i = 0; i < qua_of_neirons; i++)
			this_neiron.push_back(new classic_neiron(type_of_neiro));

		break;
	default:
		std::cerr << "have not this type \n";
		break;
	}
}

void layer::set_next_layer(std::vector<neiron*> next_layer)
{
	for (size_t i = 0; i < next_layer.size(); i++)
		next_neiron.push_back(next_layer[i]);
	
}

void layer::set_prev_layer(std::vector<neiron*> prev_layer)
{
	for (size_t i = 0; i < prev_layer.size(); i++)
		prev_neiron.push_back(prev_layer[i]);

}

void layer::put_values(std::vector<double> in)
{
	
	for (size_t i = 0; i < qua_of_neirons; i++)
	{
		this_neiron[i]->set_values(in[i]);
	}

}

std::vector<neiron*> layer::get_this_layer() {
	return this_neiron;
}

std::vector<neiron*> layer::get_next_layer() {
	return next_neiron;
}

std::vector<neiron*> layer::get_prev_layer() {
	return prev_neiron;
}

void layer::working_layer()
{
	//здесь прокручиваются нейроны
	for (size_t i = 0; i < qua_of_neirons; i++)
	{
		this_neiron[i]->set_to_next();
		Values_output.push_back(this_neiron[i]->get_results());
		Values_diff.push_back(this_neiron[i]->get_diff());


		this_neiron[i]->clean();
	}
}

std::vector<double> layer::get_result()
{
	return Values_output;
}

void layer::clear_all()
{
	Values_diff.clear();
	Values_output.clear();
}

std::vector<double> layer::get_result_diff()
{
	return Values_diff;
}

void layer::its_working()
{


	std::cout << "its working\n";


}

layer::~layer() {

	for (size_t i = 0; i < this_neiron.size(); i++)
	{
		this_neiron[i]->delete_neiron();
	}
	

}


neiron* layer::get_neiro(size_t position){
	if (position < qua_of_neirons)
		return this_neiron[position];
	else
		std::cout << "error, havent this neiron";
	return NULL;
}



size_t layer::how_many_in_this_layer(){

	return qua_of_neirons;
}

void layer::set_pointer(neiron* some) {
	for (size_t i = 0; i < qua_of_neirons; i++)
	{
		prev_neiron.push_back(some);
	}
}