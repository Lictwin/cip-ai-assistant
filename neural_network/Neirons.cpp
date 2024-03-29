#include "Neirons.h"
#include "ActivationFunction.h"


SimpleNeirons::SimpleNeirons()
{
	T = GetRandomDouble();
}

SimpleNeirons::SimpleNeirons(size_t activation): SimpleNeirons(activation,1,1){
	
}

SimpleNeirons::SimpleNeirons(size_t activation, double a): SimpleNeirons(activation, a, 1){
}

SimpleNeirons::SimpleNeirons(size_t activation, double a, double b):SimpleNeirons(){
	switch (activation){
	case Linn:
		if (a == 1)
			activate = new Identical();
		else
			activate = new Linear(a);
		break;

	case BLinn:
		activate = new BLin(a,b);
		break;

	case TLinn:
		activate = new TLin(a, b);
		break;

	case Logg:
		activate = new Logist();
		break;

	case BLogg:
		activate = new BipolLogist();
		break;

	case Sigmm:
		activate = new Sigmoid(a);
		break;

	case BSigmm:
		activate = new BipolSigm(a);
		break;

	case HypTann:
		activate = new HyperbolicTangent();
		break;

	case SoftSignn:
		activate = new SoftSign();
		break;

	case Sinn:
		activate = new Sinus();
		break;

	case LSinn:
		activate = new LSin();
		break;

	case Coss:
		activate = new Cosinus();
		break;

	case LCoss:
		activate = new LCos();
		break;

	case Sincc:
		activate = new Sinc();
		break;

	case Gauss:
		activate = new Gaussian();
		break;

	case Relu:
		activate = new ReLu();
		break;
		
	default:
		std::cout << "have not this type, will be used identical\n";
		activate = new Identical();
		break;
	}
}

vector<double> SimpleNeirons::GetX(){
	vector<double> result = X;
	X.clear();
	return result;
}

vector<double> SimpleNeirons::GetW(){
	return W;
}

double SimpleNeirons::GetY(){
	return Y;
}

double SimpleNeirons::GetT(){
	return T;
}

double SimpleNeirons::GetDiff(){
	return activate->dif_activate_per_activate(Y);
}

pair<double, double> SimpleNeirons::Cooficients()
{
	return activate->cooficients();
}

void SimpleNeirons::SetX(double X){
	this->X.push_back(X);
}

void SimpleNeirons::SetX(vector<double> X){
	this->X = X;
}

void SimpleNeirons::SetW(size_t quantity){
	for (size_t i = 0; i < quantity; i++){
		W.push_back(GetRandomDouble());
	}
}

void SimpleNeirons::SetW(vector<double> set){
	W = set;
}

void SimpleNeirons::SetPointersNextLevel(vector<Neiron*> p_next){
	this->p_next = p_next;
}

void SimpleNeirons::Work(){
	double summ = 0;
	for (size_t i = 0; i < W.size(); i++){
		summ += W[i] * X[i];
	}
	X.clear();
	summ -= T;
	Y = activate->activate(summ);
	
	if (!p_next.empty() && p_next[0] != NULL)
		for (size_t i = 0; i < p_next.size(); i++){
			p_next[i]->SetX(Y);
		}
	else
		std::cout << "problem in work or end";
}

void SimpleNeirons::ClearAll(){
	ClearX();	
}

void SimpleNeirons::ClearX(){
	X.clear();
}

void SimpleNeirons::ClearY(){
}

void SimpleNeirons::TrainWork(){
	double summ = 0;
	for (size_t i = 0; i < W.size(); i++){
		summ += W[i] * X[i];
	}
	summ -= T;
	Y = activate->activate(summ);

	if (!p_next.empty() && p_next[0] != NULL)
		for (size_t i = 0; i < p_next.size(); i++){
			p_next[i]->SetX(Y);
		}
}

void SimpleNeirons::Train(double gamma, double alfa, double diff, vector<double> output){
	for (size_t i = 0; i < W.size(); i++){
		W[i] = W[i] - alfa * gamma * diff * output[i];
	}
	T = T + alfa * gamma * diff;
}

void SimpleNeirons::DeleteNeiron(){
	delete activate;
}

double SimpleNeirons::GetRandomDouble(){
		double value;
		value = rand();

		while (value > 0.15 || value < -0.15)
			value /= 10;
		// получить вещественное число
		return value;
}
