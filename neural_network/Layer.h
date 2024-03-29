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
	

	/*указатели на нейроны*/
	vector<Neiron*> pt_this;
	vector<Neiron*> pt_next;
	vector<Neiron*> pt_prev;


	bool type_connection;// какой тип подключения
	
	size_t qua_of_neirons;

	//функции для строителя
	void MakeConnectionNext(Layer* next, bool type);
	void SetPrevLayer(vector<Neiron*> prev_layer);
	void SetPrevLayer(vector<Neiron*> prev_layer, bool type_connection);
	
	void SetPointer(Neiron* some);
	
public:
	Layer();
	Layer(vector<Neiron*> set);
	Layer(vector<Neiron*> set, bool type_connection);
	~Layer();
	vector<Neiron*> GetThisLayer();// получение вектора указателей на нейроны этого слоя
	vector<Neiron*> GetNextLayer();// получение вектора указателей на нейроны следующего слоя
	vector<Neiron*> GetPrevLayer();// получение вектора указателей на нейроны предыдущего слоя
	void TrainWorkLayer();
	Neiron* GetNeiron(size_t position); // получение вектора указателя на нейрон в позиции 
	size_t NeironsInLayer();
	bool GetTypeOfConnection();
	void WorkLayer();
	void PutValues(vector<double> in);
	vector<double> GetY();
	vector<double> GetDiff();
	void ClearAll(); 
	void ClearX();
	void SetNextLayer(vector<Neiron*> next_layer);
	void SetNextLayer(vector<Neiron*> next_layer, bool type_connection);
	void SetTypeOfConnection(bool type);


};



