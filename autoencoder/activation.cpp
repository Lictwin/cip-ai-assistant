#include "activation.h"
#include <math.h>

double linear::activation(double value)
{
	return value;
}

double sigmoida::activation(double value)
{
	return 1/(1+exp(-value));
}