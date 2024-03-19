#include "Builder.h"
using std::cin;


//void Builder::hand()
//{
//	cout << "nothing";
//}

Builder::Builder()
{
	cout << "it a builder\n";
}

Builder::~Builder()
{
	cout << "it an end\n";
}

CnNt* Builder::GetNN()
{
	CnNt* result_conteiner = new CnNt();
	NeuralNetwork* result;// сеть, что отдастся нашим 
	size_t forecast_shift;//сдвиг по прогнозу (на сколько прогнозируем)
	size_t data_shift;//сдвиг по данным (на сколько сдвигаемся по данным)
	size_t how_much_layers;// сколько всего слоев
	size_t how_data_set;// сколько отправляем на вход
	vector<size_t> neirons;
	vector<size_t> activations;
	vector<bool> connection_vector;
	cout << "How much forecast shift: ";
	cin >> forecast_shift;
	cout << "How much data shift: ";
	cin >> data_shift;
    cout << "How many layers: ";
	cin >> how_much_layers;
	cout << "How much data to set: ";
	cin >> how_data_set;

	// проверка на соответствие параметров
	if (forecast_shift < 0)
		forecast_shift = 0;
	if (data_shift <= 0)
		data_shift = 1;
	if (how_much_layers <= 0)
		how_much_layers = 3;
	if (how_data_set <= 0)
		how_data_set = 1;

	result = new NeuralNetwork(forecast_shift, data_shift, 0);

	cout << "\n\n\n\n\nActivations Functions:\n\n\n" <<
		"1 - Linear (1 parameters)\n" <<
		"2 - BiasLinear (2 parameters)\n" <<
		"3 - ThresholdLinear (2 parameters)\n" <<
		"4 - Logistic (no parameters)\n" <<
		"5 - BipolarLogistic (no parameters)\n" <<
		"6 - Sigmoid (1 parameters)\n" <<
		"7 - BipolarSigmoid (1 parameters)\n" <<
		"8 - HyperbolicTangent (no parameters)\n" <<
		"9 - SoftSign (no parameters)\n" <<
		"10 - CleanSinus (no parameters)\n" <<
		"11 - LimitedSinus (no parameters)\n" <<
		"12 - CleanCosinus (no parameters)\n" <<
		"13 - LimitedCosinus (no parameters)\n" <<
		"14 - Sinc (no parameters)\n" <<
		"15 - Gaussian (no parameters)\n" <<
		"16 - ReLu (no parameters)\n\n\n\n\n\n";
	


	for (size_t i = 0; i < how_much_layers; i++){
		size_t set_neiro, set_active;
		bool connection;
		cout << "How many in "<< i+1<<" layer: ";
		cin >> set_neiro;
		cout << "Function activation ";
		cin >> set_active;
		cout << "Type connection previous: (1 - all to all, 0 - one to one) ";
		cin >> connection;

		if (set_neiro <= 0)
			set_neiro = 6;
		if (set_active <= 0 || set_active >= 17)
			set_active = 1;

		neirons.push_back(set_neiro);
		activations.push_back(set_active);
		connection_vector.push_back(connection);


		//проверяем тип подключения
		if(i != 0){
			if (!connection_vector[i] && neirons[i] != neirons[i - 1]){
				connection_vector[i] = 1;
			}
		} 
		else{
			if (!connection_vector[i] && neirons[i] != how_data_set){
				connection_vector[i] = 1;
			}
		}


		/*if (i == how_much_layers - 1) {
			if (neirons[i] < forecast_shift) {
				neirons[i] = forecast_shift;
			}
		}*/
	}

	std::cout << "build layers\n";
	for (size_t i = 0; i < neirons.size(); i++){
		cout << i+1 <<" layer:\n";
		vector<Neiron*> neiron_set;
		for (size_t j = 0; j < neirons[i]; j++){
			double a = 1;
			double b = 1;
			switch (activations[i]){
			case 1:
			case 6:
			case 7:
				cout << j + 1 << " neiron:\n";
				cout << "set a for activation function: ";
				cin >> a;
				break;
			case 2:
			case 3:
				cout << j + 1 << " neiron:\n";
				cout << "set a for activation function: ";
				cin >> a;
				cout << "set b for activation function: ";
				cin >> b;
				break;
			default:
				cout << "no need params\n";
				break;
			}
			neiron_set.push_back(NeironsMaker.SetNeirons(activations[i], a, b));
		}
		Layer* set_layer = LayersMaker.SetLayer(neiron_set);
		result->PutLayer(set_layer);
	}

	std::cout << "build adapters\n";
	AdapterBegin* result_adapter_begin = new AdapterBegin(result, connection_vector[0], how_data_set, data_shift);
	AdapterEnd* result_adapter_end = new AdapterEnd(result, result_adapter_begin, data_shift,forecast_shift);



	std::cout << "build connection\n";
	result->GetLayer(0)->SetTypeOfConnection(connection_vector[0]);
	if (connection_vector[0]) {
		for (size_t i = 0; i < result->GetLayer(0)->NeironsInLayer(); i++) {
			result->GetLayer(0)->GetNeiron(i)->SetW(how_data_set);
		}
	}
	else {
		for (size_t i = 0; i < result->GetLayer(0)->NeironsInLayer(); i++){
			result->GetLayer(0)->GetNeiron(i)->SetW(1);
		}
	}

	for (size_t i = 1; i < how_much_layers; i++){
         result->MakeConnection(i, connection_vector[i]);
	}
	
	cout << "end of builder\n";
	result_conteiner->begin = result_adapter_begin;
	result_conteiner->network = result;
	result_conteiner->end = result_adapter_end;

	return result_conteiner;
}

Layer* Builder::GetLayer(){
	return new Layer;
}

Neiron* Builder::GetNeiron(){
	return NeironsMaker.SetNeirons();
}

Layer* Builder::GetLayer(size_t activation, size_t numb_of_neiron){
	return LayersMaker.SetLayer(activation, numb_of_neiron);
}

Neiron* Builder::GetNeiron(size_t activation){
	return NeironsMaker.SetNeirons(activation);
}

