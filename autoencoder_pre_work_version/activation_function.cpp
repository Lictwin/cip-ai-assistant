//#include "activation_function.h"
#include "layer.h"
#include <math.h>

double linear_fun::activation(double value)
{
	return value;
}

double sigm_fun::activation(double value)
{
	return 1 / (1 + exp(-value));
}



double linear_fun::diff(double value)
{
	return 1;
}

double sigm_fun::diff(double value)
{
	return (1 / (1 + exp(-value))) * (1 - (1 / (1 + exp(-value))));
}