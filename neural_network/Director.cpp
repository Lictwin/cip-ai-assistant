#include "Director.h"



Director::Director()
{
	how_many_NS = 0;
	this->network = nullptr;
}

Director::~Director()
{
}

//void Director::BuildNetwork(Instruction set)
//{
//}

void Director::BuildNetworkHand()
{
	Builder bild;
	this->network = bild.GetNN();
	
}

void Director::Train()
{
	Teacher trainer = Teacher(this->network);
	trainer.SetData(this->values);
	trainer.SetAlfa(0.1);
	trainer.SetE(0.001);
	trainer.TrainBPE();
}

void Director::Train(int type)
{
}

void Director::Work()
{
}

void Director::Work(vector<double> set){
	SetValues(set);
	Work();	
}

void Director::SetValues(vector<double> set)
{
	values = set;
}

vector<double> Director::GetPredictData()
{
	return predict;
}
