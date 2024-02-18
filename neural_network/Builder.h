#pragma once
#include "Neirons.h"
#include "Layer.h"
#include "NeuralNetwork.h"
//#include "Director.h"


//struct Instruction
//{
//	int quantity;
//};

class FactoryNeirons
{
public:

	SimpleNeirons* SetNeirons()
	{
		return new SimpleNeirons();
	}

	SimpleNeirons* SetNeirons(size_t activation)
	{
		return new SimpleNeirons(activation);
	}

	SimpleNeirons* SetNeirons(size_t activation, double a)
	{
		return new SimpleNeirons(activation, a);
	}

	SimpleNeirons* SetNeirons(size_t activation, double a, double b)
	{
		return new SimpleNeirons(activation, a, b);
	}
};

class FactoryLayers
{
public:

	Layer* SetLayer()
	{
		return new Layer();
	}

	Layer* SetLayer(size_t activation, size_t quantity)
	{
		return new Layer(activation, quantity);
	}

	Layer* SetLayer(vector<Neiron*> set)
	{
		return new Layer(set);
	}

	/*Layer* SetLayer(size_t activation, double a, double b)
	{
		return new Layer();
	}*/
};


class Builder
{
public:
	Builder();
	~Builder();
	//NeuralNetwork* GetNN(Instruction set);
	NeuralNetwork* GetNNHand();
	
	void hand();

private:
	FactoryNeirons NeironsMaker;
	FactoryLayers LayersMaker;
	Layer* GetLayer(size_t numb_of_neiron, size_t activation);
	Neiron* GetNeiron(size_t activation);
	void MakeConnection(Layer* prev, Layer* next);
	Layer* GetLayer();
	Neiron* GetNeiron();
};









