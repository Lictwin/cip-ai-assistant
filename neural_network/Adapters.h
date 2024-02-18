#pragma once
#include "Neirons.h"
#include "Layer.h"
#include "Builder.h"
#include "NeuralNetwork.h"
//#include "Director.h"
#include <vector>



using std::vector;
class AdapterBegin;
class AdapterEnd;
class Builder;


class AdapterBegin // адаптер для начала
{
	friend class Builder;
public:
	AdapterBegin();
	AdapterBegin(NeuralNetwork* this_ns);
	AdapterBegin(NeuralNetwork* this_ns, bool type_connection);
	AdapterBegin(bool type_of_connection, size_t values_to_layer, size_t how_many_set, size_t data_shift);
	AdapterBegin(bool type_of_connection, size_t values_to_layer, size_t how_many_set);
	~AdapterBegin();
	void Work();
private:
	void SetPointers(vector<Neiron*> neirons);
	void SetLayer(Layer* first_layer);


	vector<double> data;// потом заменяем на датавектор

    //AdapterEnd* previous_adapter;// указетель на предыдущий адаптер
	//NeuralNetwork* previous_ns;// пока не пригодится

	NeuralNetwork* this_ns;// указатель на нейросеть
	Layer* first_layer;// указатель на первый слой
	vector<Neiron*> neirons;
	
	

	AdapterEnd* this_adapter;// указатель на конечный адаптер (возможно не пригодится)

	bool type_of_connection;// тип подключения к первому слою 1 - все выходы ко всем нейронам, 0 - один выход на один нейрон
	size_t values_to_layer;//сколько у нас нейронов
	size_t how_many_set;// сколько значений отправляем
	size_t data_shift;//сдвиг по данным

};







class AdapterEnd
{
public:
	AdapterEnd();
	~AdapterEnd();

private:
	//здесь напрогнозированое
	vector<double> data;// потом заменяем на датавектор

	//NeuralNetwork* next_ns;
	AdapterBegin* next_adapter;


	//NeuralNetwork* this_ns;
	AdapterBegin* this_adapter;

};