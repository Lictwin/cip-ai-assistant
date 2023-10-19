#pragma once

static class activation_function 
{
	virtual double activation(double value) = 0;
};

static class linear : activation_function
{
	virtual double activation(double value);
};

static class sigmoida : activation_function
{
	virtual double activation(double value);
};