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

	T = GetRandomNumberFloat();

}

void classic_neiron::set_to_next() {
	double summ = 0;
	for (size_t i = 0; i < W.size(); i++)
	{
		summ += W[i] * Values[i];
	}
	Values.clear();
	summ -= T;
	results.push_back(fun_active->activation(summ));
	diff_results.push_back(fun_active->diff(summ));


	if(!next_neiron.empty() && next_neiron[0] != NULL)
		for (size_t i = 0; i < next_neiron.size(); i++)
		{
			next_neiron[i]->set_values(results[results.size() - 1]);
		}
}



void classic_neiron::set_values(std::vector<double> input_values)
{//здесь видимо ошибка, потом проверить
	Values = input_values;
}

void classic_neiron::set_values(double input)
{//здесь видимо ошибка, потом проверить
	Values.push_back(input);
}

void classic_neiron::set_pointers_next_level(std::vector<neiron*> next_level)
{
	next_neiron = next_level;
}

double classic_neiron::GetRandomNumberFloat()
{
	double min = -0.15;
	double max = 0.15;
	int precision = 3;
	// Установить стартовую точку
	srand(time(NULL));

	double value;

	
	value = rand();

	while (value > 0.3)
		value /= 10;
	// получить вещественное число
	return value;
}


void classic_neiron::set_pointers_prev_level(std::vector<neiron*> prev_level)
{
	prev_neiron = prev_level;

	for (size_t i = 0; i < prev_level.size(); i++)
	{
		W.push_back(GetRandomNumberFloat());
	}
}

void classic_neiron::set_weight(std::vector<double> weight)
{
	W = weight;
}

void classic_neiron::set_T(double new_T)
{
	T = new_T;
}

double classic_neiron::get_T()
{
	return T;
}

std::vector<double> classic_neiron::get_weight_pointers()
{
	return W;
}

void classic_neiron::teach(double gamma, double alfa, double diff, std::vector<double> output)
{
	for (size_t i = 0; i < W.size(); i++)
	{
		W[i] = W[i] - alfa * gamma * diff * output[i];
	}
	T = T + alfa * gamma * diff;
}


double classic_neiron::get_diff()
{
	double diff;
	diff = diff_results[0];
	diff_results.clear();
	return diff;
}

void classic_neiron::clean()
{
	results.clear();
	diff_results.clear();

}

double classic_neiron::get_results()
{
	double res;
	res = results[0];
	results.clear();
	return res;
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