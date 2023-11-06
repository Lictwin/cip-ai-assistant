#pragma once

class activation_function
{
public:
	virtual double activation(double value) = 0;

	virtual double diff(double value) = 0;
};

class linear_fun : public activation_function
{
public:
	virtual double activation(double value);

	virtual double diff(double value);
};

class sigm_fun : public activation_function
{
public:
	virtual double activation(double value);

	virtual double diff(double value);
};