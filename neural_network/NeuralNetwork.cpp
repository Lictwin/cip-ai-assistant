#include "NeuralNetwork.h"


NeuralNetwork::NeuralNetwork()
{
	forecast_shift = 1;
	data_shift = 1;
	qua_layers = 0;
}

NeuralNetwork::NeuralNetwork(size_t forecast_shift, size_t data_shift, size_t qua_layers)
{
	this->forecast_shift = forecast_shift;
	this->data_shift = data_shift;
	this->qua_layers = 0;
}

NeuralNetwork::~NeuralNetwork()
{
}

void NeuralNetwork::Work()
{
	for (size_t i = 0; i < qua_layers; i++)
	{
		layers[i]->WorkLayer();
	}
}

void NeuralNetwork::PutLayer(Layer* set)
{
	layers.push_back(set);
	qua_layers++;
}

void NeuralNetwork::PutLayer(Layer* set, size_t type_of_connection)// не доведено до ума
{
	layers.push_back(set);
	qua_layers++;
}

vector<Layer*> NeuralNetwork::GetLayers()
{
	return layers;
}

Layer* NeuralNetwork::GetLayer(size_t position)// просмотреть оставим как есть или будем уменьшать позитион на -1 и тогда 
{
	if (position >= layers.size())
		return nullptr;
	else
		return layers[position];
}

void NeuralNetwork::GetInformation()
{
	cout << "Layers Quantity: " << qua_layers << "\n";
}

void NeuralNetwork::GetWideInformation()
{

}

void NeuralNetwork::MakeConnection(size_t number_layer,  size_t type_of_connection)
{
	if (number_layer == 0)
	{
		//vector<Neiron*> prev_pointer;
		//layers[number_layer]->SetPrevLayer(prev_pointer);
		if (type_of_connection)
		{
			for (size_t i = 0; i < layers[number_layer]->NeironsInLayer(); i++)
			{
				layers[number_layer]->GetNeiron(i)->SetW(layers[number_layer]->NeironsInLayer());
			}
		}
		else
		{
			for (size_t i = 0; i < layers[number_layer]->NeironsInLayer(); i++)
			{
				layers[number_layer]->GetNeiron(i)->SetW(1);
			}
		}

		
		


	}
	else
	{
		//vector<Neiron*> prev_pointer = layers[number_layer - 1]->GetThisLayer();
		vector<Neiron*> next_pointer = layers[number_layer]->GetThisLayer();
		//layers[number_layer]->SetPrevLayer(prev_pointer);
		layers[number_layer-1]->SetNextLayer(next_pointer);

		if (type_of_connection)
		{
			for (size_t i = 0; i < layers[number_layer]->NeironsInLayer(); i++)
		    {
				layers[number_layer]->GetNeiron(i)->SetW(layers[number_layer - 1]->NeironsInLayer());
		    }

			for (size_t i = 0; i < layers[number_layer-1]->NeironsInLayer(); i++)
			{
				layers[number_layer-1]->GetNeiron(i)->SetPointersNextLevel(next_pointer);
			}


		}
		else
		{
			for (size_t i = 0; i < layers[number_layer]->NeironsInLayer(); i++)
			{
				layers[number_layer]->GetNeiron(i)->SetW(1);
			}

			for (size_t i = 0; i < layers[number_layer-1]->NeironsInLayer(); i++)
			{
				vector<Neiron*> next_set{ next_pointer[i] };
				layers[number_layer - 1]->GetNeiron(i)->SetPointersNextLevel(next_pointer);
			}
		}


		



	}

}

