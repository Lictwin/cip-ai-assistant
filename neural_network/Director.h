#pragma once
#include "NeuralNetwork.h"
#include <vector>
#include <iostream>
#include <fstream>
#include "Adapters.h"
#include "Builder.h"
#include "NeuralNetwork.h"


typedef vector<pair<size_t, pair<double, double>>> Activations;
using std::vector;
using std::pair;
class AdapterBegin;
class AdapterEnd;
class NeuralNetwork;
struct CotainerNetwork;
typedef CotainerNetwork CnNt;

struct Information {
	size_t forecast_shift;//����� �� �������� (�� ������� ������������)
	size_t data_shift;//����� �� ������ (�� ������� ���������� �� ������)
	size_t data_to_layer;//������� �������� ������������ �� ����
	size_t how_many_get;//������� �������� �������� �� ������
	size_t qua_layers;//���������� ����
	double passport_E;//���� �������� ���������� ��� �������� ����
	double total_E;//������ ������ ����
	double MIN_E;//����������� ������
	double MAX_E;//������������ ������
	struct layer_function {
		size_t qua;
		bool type_connection;
		size_t activation;
	};
	struct function_activation {
		size_t activation;
		double a;
		double b;
	};
	vector<layer_function> layers;
	vector<function_activation> function;
};

struct CotainerNetwork
{
	//����� ������� �� ���� � ����� � ���� ����
	//������� ����������� ������������� ��� ���������
	AdapterBegin* begin;
	NeuralNetwork* network;
	AdapterEnd* end;
	Information inf;

	~CotainerNetwork() {
		delete[] begin;
		delete[] network;
		delete[] end;
	}
	void SaveBin(std::string name);
};


typedef CotainerNetwork CnNt;

// ���� �� ����, ���� �������� �� ���� ����, ���� �� � ��������� ��������� ����� ������
// ���� ����� �� ��������� �����
//struct Information
//{
//	size_t forecast_shift;//����� �� �������� (�� ������� ������������)
//	size_t data_shift;//����� �� ������ (�� ������� ���������� �� ������)
//	size_t qua_layers;//���������� ����
//};
//struct CotainerNetwork
//{
////����� ������� �� ���� � ����� � ���� ����
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

// ��������� ����� ������������ ���� � ������ 
struct GeneralTypeNetwork {
	//std::string instruction_type;
	llong output_network_size; // ������ ������ ����
	llong input_network_size; // ������ ����� ����
	//llong hidden_layer_network_quantity; // ���������� ������� ����
};

struct HandleTN {
	llong hidden_layer_size; // ���������� �������� � ������� ����
	bool type_of_neurons; // ��� ����� � ����������
	bool copy_layer_flag; // ����������� �� ��������� ����
	llong copy_layer_quantitu; // ������� ���� ����� �����������
};*/

//struct Instruction
//{
//	size_t forecast_shift;//����� �� �������� (�� ������� ������������)
//	size_t data_shift;//����� �� ������ (�� ������� ���������� �� ������)
//	size_t qua_layers;//���������� ����
//	vector <int> qua_of_neirons;//�-�� ��������
//	vector <bool> type_of_pointers;//��� �����
//	vector<pair<size_t,vector<coef_func_pair>>> act_func;//������ ������� ��������� � ����������
//};

class Teacher
{
private:
	/*��������������� ����������*/
	double alfa;
	size_t itterations;//��������� �� �������
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
	void TrainBPE();// �������� ��������� ����������� ��� (��������� ��������������� ������)
	void TrainAutoencoder();// �������� ��������� ����������� ��������������� ������ (�� ��������� � ���)
	void TrainDeepAutoencoder();// �������� ��������� ����������� ��������������� ������ 
	void TrainDeepBolzman();// �������� ��������� ����������� ������������ ������ ��������� ( ���� �� ����� ������� �������)

};


class Director
{
public:
	Director();
	~Director();

	//void GetInstruction();
	//void BuildNetwork(Instruction set);
	void BuildNetworkHand();
	void BuildNetwork(std::string file);
	void SaveNetwork();
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
	void LoadNN(std::string name);
	vector<double> GetPredictData();

private:
	size_t how_many_NS;
	CnNt* network;
	vector<double> values;
	vector<double> predict;
};
