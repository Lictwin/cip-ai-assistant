#include "neiron.h"
#include "layer.h"



/*
input_neiron :: input_neiron(size_t activation ) {

	switch (activation)
	{
	case lin:
		fun_active = new linear_fun();

		break;
	case sig:
		fun_active = new sigm_fun();

		break;
	default:
		std::cerr << "have not this type \n";
		break;
	}


}


void input_neiron::set_to_next() {




}

*/




classic_neiron::classic_neiron(size_t activation) {

	switch (activation)
	{
	case lin:
		fun_active = new linear_fun();

		break;
	case sig:
		fun_active = new sigm_fun();

		break;
	default:
		std::cout << "have not this type \n";
		break;
	}

	T = 0.1;

}

void classic_neiron::set_to_next() {




}



void classic_neiron::set_values(std::vector<double> input_values)
{//здесь видимо ошибка, потом проверить
	Values = input_values;
}


void classic_neiron::set_pointers_next_level(std::vector<neiron*> next_level)
{
	next_neiron = next_level;
}

void classic_neiron::set_pointers_prev_level(std::vector<neiron*> prev_level)
{
	prev_neiron = prev_level;

	for (size_t i = 0; i < prev_level.size(); i++)
	{
		W.push_back(0.05);
	}
}

void classic_neiron::set_weight(std::vector<double> weight)
{
	W = weight;
}

double classic_neiron::get_diff()
{

	return diff_results[0];
}


void classic_neiron::put_values(double put){


}



void classic_neiron::put_values(std::vector<double> put) {//это пока пустое, но для 



}

/*classic_neiron::~classic_neiron() {

	delete fun_active;
}*/
void classic_neiron::delete_neiron()
{
	delete fun_active;
}