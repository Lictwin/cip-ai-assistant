#pragma once
#include <vector>
#include "Neirons.h"

using std::vector;
using std::pair;

class Neiron;
typedef pair<size_t, size_t> act_qua; // ���� ������� ��������� � �-�� ��������
typedef vector< act_qua> activations; // ���� ������� ��������� � �-�� ��������
//typedef AbstractNeirons Neiron;

class Layer
{
private:
	friend class Builder;
	

	/*��������� �� �������*/
	vector<Neiron*> pt_this;
	vector<Neiron*> pt_next;
	vector<Neiron*> pt_prev;


	bool type_connection;// ����� ��� �����������
	
	size_t qua_of_neirons;

	//������� ��� ���������
	void MakeConnectionNext(Layer* next, bool type);
	void SetPrevLayer(vector<Neiron*> prev_layer);
	void SetPrevLayer(vector<Neiron*> prev_layer, bool type_connection);
	
	void SetPointer(Neiron* some);
	
public:
	Layer();
	Layer(vector<Neiron*> set);
	Layer(vector<Neiron*> set, bool type_connection);
	~Layer();
	vector<Neiron*> GetThisLayer();// ��������� ������� ���������� �� ������� ����� ����
	vector<Neiron*> GetNextLayer();// ��������� ������� ���������� �� ������� ���������� ����
	vector<Neiron*> GetPrevLayer();// ��������� ������� ���������� �� ������� ����������� ����
	void TrainWorkLayer();
	Neiron* GetNeiron(size_t position); // ��������� ������� ��������� �� ������ � ������� 
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



