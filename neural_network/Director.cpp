#include "Director.h"
#include <fstream>



Director::Director(){
	how_many_NS = 0;
	this->network = nullptr;
}

Director::~Director(){
}



void Director::BuildNetworkHand(){
	Builder bild;
	this->network = bild.GetNN();
	
}

void Director::BuildNetwork(std::string file){
	Builder bild;
}

void Director::SaveNetwork(){
	network->SaveBin("first");
}

void Director::Train(){
	Teacher trainer = Teacher(this->network);
	trainer.SetData(this->values);
	trainer.SetAlfa(0.1);
	trainer.SetE(0.0001);
	trainer.TrainBPE();
}

void Director::Train(int type){
}

void Director::Work(){
}

void Director::Work(vector<double> set){
	SetValues(set);
	Work();	
}

void Director::SetValues(vector<double> set){
	values = set;
}

void Director::LoadNN(std::string name){
	Builder bild;
	this->network = bild.NNFromFile(name);
}

vector<double> Director::GetPredictData(){
	return predict;
}

void CotainerNetwork::SaveBin(std::string name){
	std::ofstream NN_file = std::ofstream(name + ".dnb",std::ios::binary);
	if (!NN_file.is_open()) {
		std::cerr << "error with open\n";
		/*  data type      byte          max value 
			bool               =  1         255.00
			char               =  1         255.00
			short int          =  2         32767.00
			unsigned short int =  2         65535.00
			int                =  4         2147483647.00
			unsigned int       =  4         4294967295.00
			long int           =  4         2147483647.00
			unsigned long int  =  4         4294967295.00
			float              =  4         2147483647.00
			long float         =  8         9223372036854775800.00
			double             =  8         9223372036854775800.00 
			size_t             =  8          */

	}
	else {
		NN_file.write("000.01", 7);
		NN_file.write((char*)&inf.forecast_shift, sizeof(inf.forecast_shift));
		NN_file.write((char*)&inf.data_shift, sizeof(inf.data_shift));
		NN_file.write((char*)&inf.total_E, sizeof(inf.total_E));
		NN_file.write((char*)&inf.passport_E, sizeof(inf.passport_E)); 
		NN_file.write((char*)&inf.MAX_E, sizeof(inf.MAX_E)); 
		NN_file.write((char*)&inf.MIN_E, sizeof(inf.MIN_E)); 
		NN_file.write((char*)&inf.data_to_layer, sizeof(inf.data_to_layer));
		NN_file.write((char*)&inf.qua_layers, sizeof(inf.qua_layers)); 
		for (auto a : inf.layers) {
			NN_file.write((char*)&a.qua, sizeof(a.qua));
			NN_file.write((char*)&a.type_connection, sizeof(a.type_connection));
			NN_file.write((char*)&a.activation, sizeof(a.activation));
		}
		for (size_t i = 0; i < 128; i++) {
			NN_file.write("0", 1);
		}
		size_t neiro_itterator = 0;
		for (size_t i = 0; i < network->GetLayers().size(); i++){
			for (size_t j = 0; j < network->GetLayers()[i]->NeironsInLayer(); j++) {
				double T = network->GetLayers()[i]->GetNeiron(j)->GetT();
				vector<double> W = network->GetLayers()[i]->GetNeiron(j)->GetW();
				size_t qua = W.size();
				size_t function = inf.function[neiro_itterator].activation;
				double a = inf.function[neiro_itterator].a;
				double b = inf.function[neiro_itterator].b;
				neiro_itterator++;
				NN_file.write((char*)&T, sizeof(T));
				NN_file.write((char*)&function, sizeof(function));
				NN_file.write((char*)&a, sizeof(a));
				NN_file.write((char*)&b, sizeof(b));
				NN_file.write((char*)&qua, sizeof(qua));
				for (double w : W){
					NN_file.write((char*)&w, sizeof(w));
				}
			}
		}
	}
	NN_file.close();
}
