#pragma once
#include "NeuralNetwork.h"



/*
План:

Добавить глубокое обучение 
через автоэнкодерный метод

*/

class Teacher
{
public:
	Teacher();
	~Teacher();
	Teacher(NeuralNetwork train);
	void SetData(vector<double> data);
	void TrainBPE();// Обучение нейросети посредством ОРО (Обратного Распространения Ошибки)
	void TrainAutoencoder();// Обучение нейросети посредством автоэнкодерного метода (не относится к ОРО)
	void TrainDeepAutoencoder();// Обучение нейросети посредством автоэнкодерного метода 
	void TrainDeepBolzman();// Обучение нейросети посредством Ограниченной Машины Больцмана ( План на очень далекое будущее)
private:
	/*Предварительные переменные*/
	double alfa;
	size_t itterations;//полностью по группам
	//vector <Layer*> layers;
	NeuralNetwork network;
	vector<double> data;
};


