#pragma once
#include <vector>
#include "Neirons.h"

using std::vector;
using std::pair;

class Neiron;
typedef pair<size_t, size_t> act_qua; // пара функция активации и к-во нейронов
typedef vector< act_qua> activations; // пара функция активации и к-во нейронов
//typedef AbstractNeirons Neiron;

class Layer
{
private:
	friend class Builder;
	
	vector<Neiron*> pt_this;
	vector<Neiron*> pt_next;
	vector<Neiron*> pt_prev;
	
	size_t qua_of_neirons;
	void MakeConnectionNext(Layer* next, bool type);
	void MakeConnectionPrev(Layer* prev, bool type);
public:

	Layer();
	Layer(size_t type_of_active, size_t quantity); 
	Layer(size_t type_of_active,double a, double b, size_t quantity);
	Layer(size_t type_of_active, double a, size_t quantity);
	Layer(vector<Neiron*> set);
	~Layer();
	vector<Neiron*> GetThisLayer();// получение вектора указателей на нейроны этого слоя
	vector<Neiron*> GetNextLayer();// получение вектора указателей на нейроны следующего слоя
	vector<Neiron*> GetPrevLayer();// получение вектора указателей на нейроны предыдущего слоя
	//activations GetInformationAboutActivation();// доделать в будущем
	Neiron* GetNeiron(size_t position); // получение вектора указателя на нейрон в позиции (продумать как это реализовать)
	size_t NeironsInLayer();
	void SetPointer(Neiron* some);
	void SetPrevLayer(vector<Neiron*> prev_layer);
	void SetPrevLayer(vector<Neiron*> prev_layer, bool type_connection);
	void SetNextLayer(vector<Neiron*> next_layer);
	void SetNextLayer(vector<Neiron*> next_layer, bool type_connection);
	void WorkLayer();
	void PutValues(vector<double> in);
	vector<double> GetY();
	vector<double> GetDiff();
	void ClearAll(); 
	void ClearX();


};



