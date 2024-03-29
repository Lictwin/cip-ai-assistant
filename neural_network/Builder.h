#pragma once
#include "Neirons.h"
#include "Layer.h"
#include "NeuralNetwork.h"

class NeuralNetwork;
struct CotainerNetwork;
typedef CotainerNetwork CnNt;


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


	Layer* SetLayer(vector<Neiron*> set)
	{
		return new Layer(set);
	}
};

class Builder
{
public:
	Builder();
	~Builder();
	CnNt* GetNN();
	CnNt* NNFromFile(std::string file);
	
private:
	FactoryNeirons NeironsMaker;
	FactoryLayers LayersMaker;
	//Layer* GetLayer(size_t numb_of_neiron, size_t activation);
	Neiron* GetNeiron(size_t activation);
	Layer* GetLayer();
	Neiron* GetNeiron();
};









