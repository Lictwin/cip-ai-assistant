#pragma once
#include "NeuralNetwork.h"
#include <vector>
#include <iostream>
#include <fstream>
#include "Adapters.h"
#include "Builder.h"
//#include "Teacher.h"
#include "NeuralNetwork.h"


using std::vector;
using std::pair;
class AdapterBegin;
class AdapterEnd;
class NeuralNetwork;
struct CotainerNetwork;
typedef CotainerNetwork CnNt;

struct CotainerNetwork
{
	//здесь адаптер на вход и выход и сама сеть
	AdapterBegin* begin;
	NeuralNetwork* network;
	AdapterEnd* end;
	//Information inf;

	~CotainerNetwork() {
		delete[] begin;
		delete[] network;
		delete[] end;
	}
};


typedef CotainerNetwork CnNt;

// пока не ясно, один директор на одну сеть, либо же в директора несколько сетей пойдет
// пока делаю на несколько сетей
//struct Information
//{
//	size_t forecast_shift;//сдвиг по прогнозу (на сколько прогнозируем)
//	size_t data_shift;//сдвиг по данным (на сколько сдвигаемся по данным)
//	size_t qua_layers;//количество слоёв
//};
//struct CotainerNetwork
//{
////здесь адаптер на вход и выход и сама сеть
//	AdapterBegin* begin;
//	NeuralNetwork* network;
//	//AdapterEnd* end;
//	//Information inf;
//	
//	~CotainerNetwork() {
//		/*delete[] begin;
//		delete[] network;*/
//		//delete[] end;
//	}
//};
//
//typedef CotainerNetwork CnNt;

/*
typedef pair<double, double> coef_func_pair;
typedef vector<int> intor;

typedef long long llong;

// заголовок файла конфигурации сети с общими 
struct GeneralTypeNetwork {
	//std::string instruction_type;
	llong output_network_size; // размер выхода сети
	llong input_network_size; // размер входа сети
	//llong hidden_layer_network_quantity; // количество скрытых слоёв
};

struct HandleTN {
	llong hidden_layer_size; // количество нейронов в скрытом слое
	bool type_of_neurons; // тип связи с предыдущим
	bool copy_layer_flag; // скопировать ли описанный слой
	llong copy_layer_quantitu; // сколько слоёв нужно скопировать
};*/

//struct Instruction
//{
//	size_t forecast_shift;//сдвиг по прогнозу (на сколько прогнозируем)
//	size_t data_shift;//сдвиг по данным (на сколько сдвигаемся по данным)
//	size_t qua_layers;//количество слоёв
//	vector <int> qua_of_neirons;//к-во нейронов
//	vector <bool> type_of_pointers;//тип связи
//	vector<pair<size_t,vector<coef_func_pair>>> act_func;//номера функций активации и коофиценты
//};

class Teacher
{
private:
	/*Предварительные переменные*/
	double alfa;
	size_t itterations;//полностью по группам
	CnNt *container;
	double E;
	vector<double> data;

	void BPE(vector<double>set, vector<double>e, vector<double>res);


public:
	Teacher();
	Teacher(CnNt *train);
	Teacher(CnNt *train, size_t itterations);
	Teacher(CnNt *train, double alfa);
	Teacher(CnNt *train, size_t itterations, double alfa);
	~Teacher();

	void SetItterations(size_t itterations);
	void SetAlfa(double alfa);
	void SetData(vector<double> data);
	void SetE(double E);
	void TrainBPE();// Обучение нейросети посредством ОРО (Обратного Распространения Ошибки)
	void TrainAutoencoder();// Обучение нейросети посредством автоэнкодерного метода (не относится к ОРО)
	void TrainDeepAutoencoder();// Обучение нейросети посредством автоэнкодерного метода 
	void TrainDeepBolzman();// Обучение нейросети посредством Ограниченной Машины Больцмана ( План на очень далекое будущее)

};


class Director
{
public:
	Director();
	~Director();

	//void GetInstruction();
	//void BuildNetwork(Instruction set);
	void BuildNetworkHand();
	void Train();
	void Train(int type);
	/*vector<double> Work_();
	vector<double> Work_(vector<double> set);*/
	void Work();
	void Work(vector<double> set);
	/*vector<double> Work_PredictMode();
	vector<double> Work_PredictMode(vector<double> set);
	void WorkPredictMode();
	void WorkPredictMode(vector<double> set);
	*/
	void SetValues(vector<double> set);
	vector<double> GetPredictData();

private:
	size_t how_many_NS;
	CnNt* network;
	vector<double> values;
	vector<double> predict;
};
