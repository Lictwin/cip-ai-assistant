#pragma once
#pragma once
#include "activation.h"

class neiron 
{

	std::vector<double> W_next;
	std::vector<neiron*> next_neiron;
	std::vector<neiron*> prev_neiron;
	activation_function* fun_active;

public:

	void virtual set_to_next() = 0;

};

class output : neiron
{

	

public:

	void virtual set_to_next() = 0;

};

class input : neiron
{



public:

	void virtual set_to_next() = 0;

};

class some_neiron : neiron
{



public:

	void virtual set_to_next() = 0;

};