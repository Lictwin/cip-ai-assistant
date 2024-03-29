#pragma once
#include <iostream>
#include <vector>
#include "ActivationFunction.h"
#include "Layer.h"

using std::pair;
using std::vector;

enum // ������ �������� ���������
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

	// �� ���� ���������� �� ���

	virtual vector<double> GetX() = 0;// ��������� ������� X
	virtual vector<double> GetW() = 0;// ��������� ����� W
	virtual double GetY() = 0;// ��������� ������� Y
	virtual double GetT() = 0;// ��������� ������
	virtual double GetDiff() = 0;// ��������� �������������
	virtual pair<double, double> Cooficients() = 0;//��������� ������������ ������� ���������


	//������� ������ �������� ����������� ��������

	virtual void SetX(double X) = 0;// ���������� � ������ � �������� 
	virtual void SetX(vector<double> X) = 0;// ����, ��� � ����, �� ����� ����������

	// ����������� ����������� �����

	virtual void SetW(size_t quantity) = 0;// ����� ���������� �����
	virtual void SetW(vector<double> set) = 0;// �������� ����
	virtual void SetPointersNextLevel(vector<Neiron*> p_next) = 0;// ����� ��������� �� ��������� ���� �������
	//virtual void SetPointersPrevLevel(std::vector<Neiron*> p_prev) = 0;// ����� ��������� �� ���������� �������

	// ������� ������

	virtual void Work() = 0;// ������ �������

	// ������� ��������         ����� ��������� � ������, ���������� ��� ����� � ����������

	virtual void ClearAll() = 0;// �������� ���� �����������
	virtual void ClearX() = 0;// �������� ������� X
	virtual void ClearY() = 0;// �������� ������� Y


	// ������� ��� ��������

	virtual void TrainWork() = 0;// ������ � ��������� ������
	virtual void Train(double gamma, double alfa, double diff, std::vector<double> output) = 0;//  �������� �������� ����������� ��� (�������� ��������������� ������)


	//������ ������������ �����������, ���� �� ��������� ��� ��� ��������
	virtual void DeleteNeiron() = 0;

private:

};

//Neiron::~Neiron(){}





class SimpleNeirons : public Neiron
{
public:
	SimpleNeirons();
	SimpleNeirons(size_t activation);
	SimpleNeirons(size_t activation, double a);// ����� ������� � ���������� ������������ �������
	SimpleNeirons(size_t activation, double a, double b);
	//~SimpleNeirons();
	
	// �� ���� ���������� �� ���

	vector<double> GetX();// ��������� ������� X
	vector<double> GetW();// ��������� ����� W
	//vector<double> GetY();// �������� ����������� �����
	double GetY();// ��������� ������� Y
	double GetT();// ��������� ������
	double GetDiff();// ��������� �������������
	pair<double, double> Cooficients();//��������� ������������ ������� ���������


	//������� ������ �������� ����������� ��������
	  
	void SetX(double X);// ���������� � ������ � �������� 
	void SetX(vector<double> X);// ����, ��� � ����, �� ����� ����������

	// ����������� ����������� �����

	void SetW(size_t quantity);// ����� ���������� �����
	void SetW(vector<double> set);// �������� ����
	void SetPointersNextLevel(std::vector<Neiron*> p_next);// ����� ��������� �� ��������� ���� �������
	//void SetPointersPrevLevel(std::vector<Neiron*> p_prev);// ����� ��������� �� ���������� �������

	// ������� ������

	void Work();// ������ �������

	// ������� ��������         ����� ��������� � ������, ���������� ��� ����� � ����������

	void ClearAll();// �������� ���� �����������
	void ClearX();// �������� ������� X
	void ClearY();// �������� ������� Y


	// ������� ��� ��������

	void TrainWork();// ������ � ��������� ������
	void Train(double gamma, double alfa, double diff, std::vector<double> output);//  �������� �������� ����������� ��� (�������� ��������������� ������)

	//������ ������������ �����������, ���� �� ��������� ��� ��� ��������
	void DeleteNeiron();

private:

	double Y;// ����������������
	double T;// �����
	vector<double> X;// ������� ��������
	vector<double> W;// ����
	vector<Neiron*> p_next;// ��������� �� ��������� �������
	ActivateFunc* activate;// ������ ���������


	// ��������� ��������� ����� 

	double GetRandomDouble(); //������ ������, � ������� � ��������� ����������� ���������
	//double GetRandomDouble(double max);// ����� ������������ ��������, ����������� ��������������� ����
	//double GetRandomDouble(double min, double max);// ����� ��� ��������
};




