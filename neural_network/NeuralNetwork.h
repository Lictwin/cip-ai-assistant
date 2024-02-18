#pragma once

#include <vector>
#include "Layer.h"
//#include "Builder.h"

class Builder;

using std::vector;
using std::cout;

class NeuralNetwork
{
public:
	NeuralNetwork();
	NeuralNetwork(size_t forecast_shift, size_t data_shift, size_t qua_layers);
	~NeuralNetwork();
	void Work();
	void PutLayer(Layer* set);
	
	vector<Layer*> GetLayers();
	Layer* GetLayer(size_t position);
	void GetInformation();
	void GetWideInformation();

	void MakeConnection(size_t number_layer, size_t type_of_connection);

private:
	friend class Builder;
	vector<Layer*> layers;
	size_t forecast_shift;//сдвиг по прогнозу (на сколько прогнозируем)
	size_t data_shift;//сдвиг по данным (на сколько сдвигаемся по данным)
	size_t qua_layers;//количество слоёв


	friend Builder;
	void MakeConnection(size_t first_layer, size_t second_layer, size_t type_of_connection);
    void PutLayer(Layer* set, size_t type_of_connection);// не доведено до ума

};


