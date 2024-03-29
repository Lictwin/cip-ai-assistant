#include "Adapters.h"

AdapterEnd::AdapterEnd(){
	this->this_ns = nullptr;
	this->this_adapter = nullptr;
	this->data_shift = 1;
	forecast_shift = 1;
}

AdapterEnd::AdapterEnd(NeuralNetwork* this_ns, AdapterBegin* connection, size_t data_shift):AdapterEnd(){
	this->this_ns = this_ns;
	this->this_adapter = connection;
	this->data_shift = data_shift;

	//получаем указатели на последние нейроны
	for (size_t i = 0; i < this->this_ns->GetLayer(this->this_ns->GetLayers().size()-1)->NeironsInLayer(); i++){
		this->last_neiro.push_back(this->this_ns->GetLayer(this->this_ns->GetLayers().size() - 1)->GetNeiron(i));
	}
}

AdapterEnd::AdapterEnd(NeuralNetwork* this_ns, AdapterBegin* connection, size_t data_shift, size_t forecast_shift):AdapterEnd(this_ns, connection, data_shift){
	this->forecast_shift = forecast_shift;
}

vector<double> AdapterEnd::GetPredict(){
	vector<double> result;
	for (size_t i = 0; i < last_neiro.size(); i++){
		result.push_back(last_neiro[i]->GetY());	
	}
	return result;
}

size_t AdapterEnd::GetForecastShift()
{
	return forecast_shift;
}

size_t AdapterEnd::GetHowManyEnd(){
	return last_neiro.size();
}

AdapterEnd::~AdapterEnd(){
}

AdapterBegin::AdapterBegin(){
	this->type_of_connection = 1;
	this->neiro_in_layer = 1;
	this->how_many_set = 1;
	this->data_shift = 1;
	this->this_ns = nullptr;
	this->first_layer = nullptr;

}

AdapterBegin::AdapterBegin(NeuralNetwork* this_ns){
	this->this_ns = this_ns;
	this->SetLayer(this->this_ns->GetLayer(0));
	this->neirons = first_layer->GetThisLayer();
	this->how_many_set = this->this_ns->GetLayer(0)->GetThisLayer().size();
	this->neiro_in_layer = this->how_many_set;
	this->data_shift = 1;
	this->type_of_connection = 1;
}

AdapterBegin::AdapterBegin(NeuralNetwork* this_ns, bool type_connection):AdapterBegin(this_ns){
	this->type_of_connection = type_connection;
}

AdapterBegin::AdapterBegin(NeuralNetwork* this_ns, bool type_connection, size_t how_many_set, size_t data_shift):AdapterBegin(this_ns, type_connection){
	this->how_many_set = how_many_set;
	this->data_shift = data_shift;
}

AdapterBegin::AdapterBegin(bool type_of_connection, size_t neiro_in_layer, size_t how_many_set, size_t data_shift):AdapterBegin(type_of_connection, neiro_in_layer, how_many_set){
	this->data_shift = data_shift;
	this->first_layer = nullptr;
}

AdapterBegin::AdapterBegin(bool type_of_connection, size_t neiro_in_layer, size_t how_many_set){
	this->type_of_connection = type_of_connection;
	this->neiro_in_layer = neiro_in_layer;
	this->how_many_set = how_many_set;
}

AdapterBegin::~AdapterBegin(){
}

void AdapterBegin::Work(){
	if (!(data.empty()) && data.size() >= how_many_set){
			if (this->type_of_connection){
				vector <double> set_data;
				for (size_t j = 0; j < how_many_set; j++){
					set_data.push_back(data[j]);
				}
				for (size_t j = 0; j < neirons.size(); j++){
					neirons[j]->SetX(set_data);
				}
			}
			else{
				for (size_t j = 0; j < neirons.size(); j++){
					neirons[j]->SetX(data[j]);
				}
			}
			data.clear();
	}
	else{
		std::cerr << "error with set\n";
	}
}

void AdapterBegin::Work(vector<double> set)
{
	SetData(set);
	Work();
}



size_t AdapterBegin::GetDataShift(){
	return data_shift;
}

size_t AdapterBegin::GetHowManySet(){
	return how_many_set;
}

void AdapterBegin::SetData(vector<double> set){
	data = set;
}

void AdapterBegin::SetPointers(vector<Neiron*> neirons){
	this->neirons = neirons;
	this->neiro_in_layer = neirons.size();
}

void AdapterBegin::SetLayer(Layer* first_layer){
	this->first_layer = first_layer;
	this->neirons = this->first_layer->GetThisLayer();
}

void AdapterBegin::SetNN(NeuralNetwork* this_ns){
	this->this_ns = this_ns;
}
