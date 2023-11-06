#pragma once
#include <vector>
#include "layer.h"
#include "activation_function.h"


class neiron
{
public:
	void virtual set_to_next() = 0;
	void virtual delete_neiron() = 0;
   
};


class classic_neiron : public neiron
{
	size_t numb_of_entrance;
	double T;
	std::vector<double> W;
	std::vector<double> Values;
	std::vector<double> results;
	std::vector<double> diff_results;
	std::vector<neiron*> next_neiron;
	std::vector<neiron*> prev_neiron;
	//std::vector<double> Values_diff;
	//std::vector<double> Values_output;
	activation_function* fun_active;

public:

	classic_neiron();
	classic_neiron(size_t activation);



	void set_to_next();
	void set_values(std::vector<double> input_values);
	void set_pointers_next_level(std::vector<neiron*> next_level);
	void set_pointers_prev_level(std::vector<neiron*> prev_level);
	void put_values(double put);
	void put_values(std::vector<double> put);
	void set_weight(std::vector<double> weight);
	double get_diff();
	void delete_neiron();
};

/*class input_neiron : public neiron
{
	std::vector<neiron*> next_neiron;
	double T;
	std::vector<double> W;
	std::vector<double> Values;
	std::vector<double> results;
	std::vector<double> diff_results;

	activation_function* fun_active;

public:
	input_neiron(size_t activation);
	void set_to_next();
};

class output_neiron : public neiron
{
	std::vector<double> W;
	std::vector<double> Values;
	std::vector<double> results;
	std::vector<double> diff_results;

	activation_function* fun_active;

	double out_value();

public:
	output_neiron();
	output_neiron(size_t activation);
	void set_to_next();
	void get_value();
};*/