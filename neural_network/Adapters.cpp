#include "Adapters.h"

AdapterEnd::AdapterEnd()
{
}

AdapterEnd::~AdapterEnd()
{
}

AdapterBegin::AdapterBegin()
{
	this->type_of_connection = 1;
	this->values_to_layer = 1;
	this->how_many_set = 1;
	this->data_shift = 1;
	this->this_ns = nullptr;

}

AdapterBegin::AdapterBegin(NeuralNetwork* this_ns)
{
	this->this_ns = this_ns;
	this->SetLayer(this->this_ns->GetLayer(0));
	this->neirons = first_layer->GetThisLayer();
	this->how_many_set = this->this_ns->GetLayer(0)->GetThisLayer().size();
	this->values_to_layer = this->how_many_set;
	this->data_shift = 1;
	this->type_of_connection = 1;
}

AdapterBegin::AdapterBegin(NeuralNetwork* this_ns, bool type_connection)
{
	this->this_ns = this_ns;
	this->SetLayer(this->this_ns->GetLayer(0));
	this->neirons = first_layer->GetThisLayer();
	this->how_many_set = this->this_ns->GetLayer(0)->GetThisLayer().size();
	this->values_to_layer = this->how_many_set;
	this->type_of_connection = type_connection;
}

//AdapterBegin::AdapterBegin(bool type_of_connection, size_t values_to_layer, size_t how_many_set, size_t data_shift)
//{
//	this->type_of_connection = type_of_connection;
//	this->values_to_layer = values_to_layer;
//	this->how_many_set = how_many_set;
//	this->data_shift = data_shift;
//
//}
//
//AdapterBegin::AdapterBegin(bool type_of_connection, size_t values_to_layer, size_t how_many_set)
//{
//	this->type_of_connection = type_of_connection;
//	this->values_to_layer = values_to_layer;
//	this->how_many_set = how_many_set;
//
//}

AdapterBegin::~AdapterBegin()
{
}

void AdapterBegin::Work()
{
	
}

void AdapterBegin::SetPointers(vector<Neiron*> neirons)
{
	this->neirons = neirons;
	this->values_to_layer = neirons.size();
}

void AdapterBegin::SetLayer(Layer* first_layer)
{
	this->first_layer = first_layer;
}
