#pragma once
#include <vector>
#include "neiron.h"
#include <iostream>
class neiron;

class activation_function;

enum // перечисление для функций активации
{
	lin = 1,
	sig,
	mix

};

enum // перечисление для типов нейронов
{
	input_n = 1,
	classic_n,
	output_n
};


class layer
{
	std::vector<neiron*> this_neiron;
	std::vector<neiron*> next_neiron;
	std::vector<neiron*> prev_neiron;
	std::vector<double> Values_diff;
	std::vector<double> Values_output;

	size_t qua_of_neirons;

public:


	layer(size_t type_of_neiro = classic_n, size_t type_of_active = lin, size_t quantity = 6);

	std::vector<neiron*> get_this_layer();
	std::vector<neiron*> get_next_layer();
	std::vector<neiron*> get_prev_layer();
	neiron* get_neiro(size_t position);
	size_t how_many_in_this_layer();
	void set_pointer(neiron* some);
	void set_prev_layer(std::vector<neiron*> prev_layer);
	void set_next_layer(std::vector<neiron*> next_layer);
	void working_layer();
	void put_values(std::vector<double> in);
	void its_working();
	std::vector<double> get_result();
	std::vector<double> get_result_diff();
	void clear_all();
	~layer();
};