#pragma once

#include <vector>
#include "Layer.h"
#include "Adapters.h"
#include "Director.h"

class NeuralNetwork;
class Builder;
class AdapterEnd;
struct CotainerNetwork;
typedef CotainerNetwork CnNt;


using std::vector;
using std::cout;

class NeuralNetwork
{
public:
	NeuralNetwork();
	~NeuralNetwork();
	void Work();
	void TrainWork();
	vector<Layer*> GetLayers();
	Layer* GetLayer(size_t position);
	
private:
	friend class Builder;
	vector<Layer*> layers;
	size_t qua_layers;//количество слоёв
    


	void PutLayer(Layer* set);
	void MakeConnection(size_t number_layer, size_t type_of_connection);

	void ClearAll();
    void PutLayer(Layer* set, size_t type_of_connection);// не доведено до ума

};


