#pragma once
#include <iostream>
#include <vector>
#include "ActivationFunction.h"
#include "Layer.h"


using std::vector;

enum // номера функиций активации
{
	Linn = 1,
	BLinn,
	TLinn,
	Logg,
	BLogg,
	Sigmm,
	BSigmm,
	HypTann,
	SoftSignn,
	Sinn,
	LSinn,
	Coss,
	LCoss,
	Sincc,
	Gauss,
	Relu

};




//class AbstractNeirons;
//typedef AbstractNeirons Neiron;

class Neiron
{
public:
/*
	virtual void Work() = 0;
	virtual void ClearAll() = 0;

	virtual void SetPointersNextLevel(std::vector<Neiron*> p_next);
	virtual void SetPointersPrevLevel(std::vector<Neiron*> p_prev);


	virtual void Train() = 0;


	virtual double GetT() = 0;
	virtual double GetDiff() = 0;
*/


    //AbstractNeirons();
	//virtual ~Neiron() = 0;

	// не ясно необходимы ли они

	virtual vector<double> GetX() = 0;// получение вектора X
	virtual double GetY() = 0;// получение вектора Y
	virtual double GetT() = 0;// получение порога
	virtual double GetDiff() = 0;// получение дифференциала


	//функции записи векторов изначальных значений

	virtual void SetX(double X) = 0;// записывает в вектор Х значение 
	virtual void SetX(vector<double> X) = 0;// тоже, что и выше, но может пригодится

	// проставляем изначальные связи

	virtual void SetW(size_t quantity) = 0;// задаём количество весов
	virtual void SetPointersNextLevel(std::vector<Neiron*> p_next) = 0;// ложим указатели на следующий слой нейроны
	//virtual void SetPointersPrevLevel(std::vector<Neiron*> p_prev) = 0;// ложим указатели на предыдущие нейроны

	// функции работы

	virtual void Work() = 0;// работа нейрона

	// функции очищения         можно перенести в приват, посмотреть как будет в реализации

	virtual void ClearAll() = 0;// очищение всех показателей
	virtual void ClearX() = 0;// очищение вектора X
	virtual void ClearY() = 0;// очищение вектора Y


	// функции для обучения

	virtual void TrainWork() = 0;// работа в обучающем режиме
	virtual void Train(double gamma, double alfa, double diff, std::vector<double> output) = 0;//  обучение нейронов посредством ОРО (Обратное Распространение Ошибки)


	//замена фиртуальному деструктору, пока не разберусь как его починить
	virtual void DeleteNeiron() = 0;

private:

};

//Neiron::~Neiron(){}





class SimpleNeirons : public Neiron
{
public:
	SimpleNeirons();
	SimpleNeirons(size_t activation);
	SimpleNeirons(size_t activation, double a);// номер фуекции и коофициент активирующие функции
	SimpleNeirons(size_t activation, double a, double b);
	//~SimpleNeirons();
	
	// не ясно необходимы ли они

	vector<double> GetX();// получение вектора X
	//vector<double> GetY();// возможно понадобится потом
	double GetY();// получение вектора Y
	double GetT();// получение порога
	double GetDiff();// получение дифференциала


	//функции записи векторов изначальных значений
	  
	void SetX(double X);// записывает в вектор Х значение 
	void SetX(vector<double> X);// тоже, что и выше, но может пригодится

	// проставляем изначальные связи

	void SetW(size_t quantity);// задаём количество весов
	void SetPointersNextLevel(std::vector<Neiron*> p_next);// ложим указатели на следующий слой нейроны
	//void SetPointersPrevLevel(std::vector<Neiron*> p_prev);// ложим указатели на предыдущие нейроны

	// функции работы

	void Work();// работа нейрона

	// функции очищения         можно перенести в приват, посмотреть как будет в реализации

	void ClearAll();// очищение всех показателей
	void ClearX();// очищение вектора X
	void ClearY();// очищение вектора Y


	// функции для обучения

	void TrainWork();// работа в обучающем режиме
	void Train(double gamma, double alfa, double diff, std::vector<double> output);//  обучение нейронов посредством ОРО (Обратное Распространение Ошибки)

	//замена фиртуальному деструктору, пока не разберусь как его починить
	void DeleteNeiron();

private:

	double Y;// напрогнозировано
	double T;// порог
	vector<double> X;// входные значения
	vector<double> W;// веса
	vector<Neiron*> p_next;// указатели на следующие нейроны
	//vector<Neiron*> p_prev;// указатели на предыдущие нейроны
	ActivateFunc* activate;// функия активации


	// получение рандомных весов 

	double GetRandomDouble(); //просто рандом, в котором я проставил изначальные параметры
	//double GetRandomDouble(double max);// задаём максимальное значение, минимальное имевертированый макс
	//double GetRandomDouble(double min, double max);// задаём оба значения
};


/*class LightNeirons : public AbstractNeirons // облегченная версия нейронов для меньшего потребления намяти и полносязной сети
{
public:
	LightNeirons();
	~LightNeirons();

private:
	double y;
	vector<double> x;
	vector<double> W;
	//vector<Neiron*> p_next;
	//vector<Neiron*> p_prev;
	ActivateFunc* activate;
	Layer* parent;

};*/



//предыдущее состоние файла до переделки

//#pragma once
//#include <iostream>
//#include <vector>
//#include "ActivationFunction.h"
//#include "Layer.h"
//
//
//using std::vector;
//
//enum // номера функиций активации
//{
//	Linn = 1,
//	BLinn,
//	TLinn,
//	Logg,
//	BLogg,
//	Sigmm,
//	BSigmm,
//	HypTann,
//	SoftSignn,
//	Sinn,
//	LSinn,
//	Coss,
//	LCoss,
//	Sincc,
//	Gauss,
//	Relu
//
//};
//
//
//
//
////class AbstractNeirons;
////typedef AbstractNeirons Neiron;
//
//class Neiron
//{
//public:
//	/*
//		virtual void Work() = 0;
//		virtual void ClearAll() = 0;
//
//		virtual void SetPointersNextLevel(std::vector<Neiron*> p_next);
//		virtual void SetPointersPrevLevel(std::vector<Neiron*> p_prev);
//
//
//		virtual void Train() = 0;
//
//
//		virtual double GetT() = 0;
//		virtual double GetDiff() = 0;
//	*/
//
//
//	//AbstractNeirons();
//	//virtual ~Neiron() = 0;
//
//	// не ясно необходимы ли они
//
//	virtual vector<double> GetX() = 0;// получение вектора X
//	virtual double GetY() = 0;// получение вектора Y
//	virtual double GetT() = 0;// получение порога
//	virtual double GetDiff() = 0;// получение дифференциала
//
//
//	//функции записи векторов изначальных значений
//
//	virtual void SetX(double X) = 0;// записывает в вектор Х значение 
//	virtual void SetX(vector<double> X) = 0;// тоже, что и выше, но может пригодится
//
//	// проставляем изначальные связи
//
//	virtual void SetW(size_t quantity) = 0;// задаём количество весов
//	virtual void SetPointersNextLevel(std::vector<Neiron*> p_next) = 0;// ложим указатели на следующий слой нейроны
//	virtual void SetPointersPrevLevel(std::vector<Neiron*> p_prev) = 0;// ложим указатели на предыдущие нейроны
//
//	// функции работы
//
//	virtual void Work() = 0;// работа нейрона
//
//	// функции очищения         можно перенести в приват, посмотреть как будет в реализации
//
//	virtual void ClearAll() = 0;// очищение всех показателей
//	virtual void ClearX() = 0;// очищение вектора X
//	virtual void ClearY() = 0;// очищение вектора Y
//
//
//	// функции для обучения
//
//	virtual void TrainWork() = 0;// работа в обучающем режиме
//	virtual void Train(double gamma, double alfa, double diff, std::vector<double> output) = 0;//  обучение нейронов посредством ОРО (Обратное Распространение Ошибки)
//
//
//	//замена фиртуальному деструктору, пока не разберусь как его починить
//	virtual void DeleteNeiron() = 0;
//
//private:
//
//};
//
////Neiron::~Neiron(){}
//
//
//
//
//
//class SimpleNeirons : public Neiron
//{
//public:
//	SimpleNeirons();
//	SimpleNeirons(size_t activation);
//	SimpleNeirons(size_t activation, double a);// номер фуекции и коофициент активирующие функции
//	SimpleNeirons(size_t activation, double a, double b);
//	//~SimpleNeirons();
//
//	// не ясно необходимы ли они
//
//	vector<double> GetX();// получение вектора X
//	//vector<double> GetY();// возможно понадобится потом
//	double GetY();// получение вектора Y
//	double GetT();// получение порога
//	double GetDiff();// получение дифференциала
//
//
//	//функции записи векторов изначальных значений
//
//	void SetX(double X);// записывает в вектор Х значение 
//	void SetX(vector<double> X);// тоже, что и выше, но может пригодится
//
//	// проставляем изначальные связи
//
//	void SetW(size_t quantity);// задаём количество весов
//	void SetPointersNextLevel(std::vector<Neiron*> p_next);// ложим указатели на следующий слой нейроны
//	void SetPointersPrevLevel(std::vector<Neiron*> p_prev);// ложим указатели на предыдущие нейроны
//
//	// функции работы
//
//	void Work();// работа нейрона
//
//	// функции очищения         можно перенести в приват, посмотреть как будет в реализации
//
//	void ClearAll();// очищение всех показателей
//	void ClearX();// очищение вектора X
//	void ClearY();// очищение вектора Y
//
//
//	// функции для обучения
//
//	void TrainWork();// работа в обучающем режиме
//	void Train(double gamma, double alfa, double diff, std::vector<double> output);//  обучение нейронов посредством ОРО (Обратное Распространение Ошибки)
//
//	//замена фиртуальному деструктору, пока не разберусь как его починить
//	void DeleteNeiron();
//
//private:
//
//	double Y;// напрогнозировано
//	double T;// порог
//	vector<double> X;// входные значения
//	vector<double> W;// веса
//	vector<Neiron*> p_next;// указатели на следующие нейроны
//	vector<Neiron*> p_prev;// указатели на предыдущие нейроны
//	ActivateFunc* activate;// функия активации
//
//
//	// получение рандомных весов 
//
//	double GetRandomDouble(); //просто рандом, в котором я проставил изначальные параметры
//	//double GetRandomDouble(double max);// задаём максимальное значение, минимальное имевертированый макс
//	//double GetRandomDouble(double min, double max);// задаём оба значения
//};
//
//
///*class LightNeirons : public AbstractNeirons // облегченная версия нейронов для меньшего потребления намяти и полносязной сети
//{
//public:
//	LightNeirons();
//	~LightNeirons();
//
//private:
//	double y;
//	vector<double> x;
//	vector<double> W;
//	//vector<Neiron*> p_next;
//	//vector<Neiron*> p_prev;
//	ActivateFunc* activate;
//	Layer* parent;
//
//};*/