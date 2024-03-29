#pragma once
#include "Neirons.h"
#include "Layer.h"
#include "Builder.h"
#include "NeuralNetwork.h"
#include <vector>

using std::vector;
class AdapterBegin;
class AdapterEnd;
class Builder;
class NeuralNetwork;

class AdapterBegin // адаптер дл€ начала
{	
public:
	AdapterBegin();
	AdapterBegin(NeuralNetwork* this_ns);
	AdapterBegin(NeuralNetwork* this_ns, bool type_connection);
	AdapterBegin(NeuralNetwork* this_ns, bool type_connection, size_t how_many_set, size_t data_shift);
	AdapterBegin(bool type_of_connection, size_t values_to_layer, size_t how_many_set, size_t data_shift);
	AdapterBegin(bool type_of_connection, size_t values_to_layer, size_t how_many_set);
	~AdapterBegin();
	void Work();
	void Work(vector<double> set);
	size_t GetDataShift();
	size_t GetHowManySet();
	void SetData(vector<double> set);

private:
	void SetPointers(vector<Neiron*> neirons);
	void SetLayer(Layer* first_layer);
	void SetNN(NeuralNetwork* this_ns);
    friend class Builder;

	vector<double> data;// потом замен€ем на датавектор

	NeuralNetwork* this_ns;// указатель на нейросеть
	Layer* first_layer;// указатель на первый слой
	vector<Neiron*> neirons;//нейроны первого сло€
	AdapterEnd* this_adapter;// указатель на конечный адаптер (возможно не пригодитс€)

	bool type_of_connection;// тип подключени€ к первому слою 1 - все выходы ко всем нейронам, 0 - один выход на один нейрон
	size_t neiro_in_layer;//сколько у нас нейронов
	size_t how_many_set;// сколько значений отправл€ем
	size_t data_shift;//сдвиг по данным

};







class AdapterEnd
{
public:
	AdapterEnd();
	AdapterEnd(NeuralNetwork* this_ns, AdapterBegin* type_connection, size_t data_shift);
	AdapterEnd(NeuralNetwork* this_ns, AdapterBegin* type_connection, size_t data_shift, size_t forecast_shift);
	vector<double> GetPredict();
	size_t GetForecastShift();
	size_t GetHowManyEnd();
	~AdapterEnd();

private:

	friend class Builder;

	//здесь напрогнозированое
	vector<double> data;// потом замен€ем на датавектор

	size_t data_shift;// сдвиг по данным
	size_t forecast_shift;// сдвиг по прогназированию
	vector <Neiron*> last_neiro;

	NeuralNetwork* this_ns;
	AdapterBegin* this_adapter;

};