#include "Teacher.h"


Teacher::Teacher()
{
	alfa = 0.1;
	itterations = 1;
}

Teacher::~Teacher()
{
}

Teacher::Teacher(NeuralNetwork train)
{
	network = train;
	alfa = 0.1;
}

void Teacher::SetData(vector<double> data)
{
	this->data = data;
}

void Teacher::TrainBPE()
{
}

void Teacher::TrainAutoencoder()
{
}

void Teacher::TrainDeepAutoencoder()
{
}

void Teacher::TrainDeepBolzman()
{
}
