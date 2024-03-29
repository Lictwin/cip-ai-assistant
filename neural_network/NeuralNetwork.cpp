#include "NeuralNetwork.h"


NeuralNetwork::NeuralNetwork(){
	qua_layers = 0;
}

NeuralNetwork::~NeuralNetwork(){
	for (size_t i = 0; i < qua_layers; i++) {
		delete layers[i];
	}
}

void NeuralNetwork::Work(){
	for (size_t i = 0; i < qua_layers; i++){
		layers[i]->WorkLayer();
	}
}

void NeuralNetwork::TrainWork(){
	for (size_t i = 0; i < qua_layers; i++){
		layers[i]->TrainWorkLayer();
	}
}

void NeuralNetwork::PutLayer(Layer* set){
	layers.push_back(set);
	qua_layers++;
}

void NeuralNetwork::PutLayer(Layer* set, size_t type_of_connection){// не доведено до ума
	layers.push_back(set);
	qua_layers++;
}

vector<Layer*> NeuralNetwork::GetLayers(){
	return layers;
}

Layer* NeuralNetwork::GetLayer(size_t position){// просмотреть оставим как есть или будем уменьшать позитион на -1 и тогда 
	if (position >= layers.size())
		return nullptr;
	else
		return layers[position];
}

//Information NeuralNetwork::GetInformation(){
//	Information result;
//	result.forecast_shift = this->forecast_shift;
//	result.data_shift = this->data_shift;
//	result.qua_layers = this->qua_layers;
//	return result;
//}



void NeuralNetwork::MakeConnection(size_t number_layer,  size_t type_of_connection){
	
		vector<Neiron*> next_pointer = layers[number_layer]->GetThisLayer();
		layers[number_layer-1]->SetNextLayer(next_pointer);
		layers[number_layer]->SetTypeOfConnection(type_of_connection);

		if (type_of_connection){
			for (size_t i = 0; i < layers[number_layer]->NeironsInLayer(); i++){
				layers[number_layer]->GetNeiron(i)->SetW(layers[number_layer - 1]->NeironsInLayer());
		    }

			for (size_t i = 0; i < layers[number_layer-1]->NeironsInLayer(); i++){
				layers[number_layer-1]->GetNeiron(i)->SetPointersNextLevel(next_pointer);
			}
		}
		else{
			for (size_t i = 0; i < layers[number_layer]->NeironsInLayer(); i++){
				layers[number_layer]->GetNeiron(i)->SetW(1);
			}

			for (size_t i = 0; i < layers[number_layer-1]->NeironsInLayer(); i++){
				vector<Neiron*> next_set{ next_pointer[i] };
				layers[number_layer - 1]->GetNeiron(i)->SetPointersNextLevel(next_set);
			}
		}

}

void NeuralNetwork::ClearAll(){
	for (size_t i = 0; i < qua_layers; i++){
		layers[i]->ClearAll();
	}
}

