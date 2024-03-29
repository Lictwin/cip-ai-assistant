#include "Builder.h"
#include <fstream>
using std::cin;


Builder::Builder(){
	cout << "it a builder\n";
}

Builder::~Builder(){
	cout << "it an end\n";
}

CnNt* Builder::GetNN(){
	CnNt* result_conteiner = new CnNt();
	NeuralNetwork* result;// сеть, что отдастся нашим 
	Information informa;
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

	informa.data_shift = data_shift;
	informa.forecast_shift = forecast_shift;
	informa.qua_layers = how_much_layers;
	informa.data_to_layer = how_data_set;


	result = new NeuralNetwork();

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
		informa.layers.push_back({ set_neiro,connection,set_active });
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
				informa.function.push_back({ activations[i],a,b });
				break;
			case 2:
			case 3:
				cout << j + 1 << " neiron:\n";
				cout << "set a for activation function: ";
				cin >> a;
				cout << "set b for activation function: ";
				cin >> b;
				informa.function.push_back({ activations[i],a,b });
				break;
			default:
				informa.function.push_back({ activations[i],a,b });
				break;
			}
			neiron_set.push_back(NeironsMaker.SetNeirons(activations[i], a, b));
		}
		Layer* set_layer = LayersMaker.SetLayer(neiron_set);
		set_layer->SetTypeOfConnection(connection_vector[i]);
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
	informa.how_many_get = neirons[neirons.size() - 1];


	cout << "end of builder\n";
	result_conteiner->begin = result_adapter_begin;
	result_conteiner->network = result;
	result_conteiner->end = result_adapter_end;
	result_conteiner->inf = informa;

	return result_conteiner;
}

CnNt* Builder::NNFromFile(std::string file){
	std::ifstream NN_file = std::ifstream(file,std::ios::binary);
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
		char version[10];
		CnNt* result_conteiner = new CnNt();
		NeuralNetwork* result;// сеть, что отдастся нашим 
		Information informa;
		size_t forecast_shift = 1;//сдвиг по прогнозу (на сколько прогнозируем)
		size_t data_shift = 1;//сдвиг по данным (на сколько сдвигаемся по данным)
		size_t how_much_layers =1;// сколько всего слоев
		size_t how_data_set = 1;// сколько отправляем на вход
		vector<size_t> neirons;//к-во нейронов 
		vector<size_t> activations;// функции активации
		vector<pair<double, double>> cooficients;//коофициенты
		vector<bool> connection_vector;//тип подключения 
		
		struct neiron_pattern{
			double T;
			size_t function;
			double a;
			double b;
			vector<double> W;
		};
		vector<neiron_pattern> neiro;

		NN_file.read((char*)&version, 7);
		NN_file.read((char*)&informa.forecast_shift, sizeof(informa.forecast_shift));
		forecast_shift = informa.forecast_shift;
		NN_file.read((char*)&informa.data_shift, sizeof(informa.data_shift));
		data_shift = informa.data_shift;

		NN_file.read((char*)&informa.total_E, sizeof(informa.total_E));
		NN_file.read((char*)&informa.passport_E, sizeof(informa.passport_E));
		NN_file.read((char*)&informa.MAX_E, sizeof(informa.MAX_E));
		NN_file.read((char*)&informa.MIN_E, sizeof(informa.MIN_E));

		NN_file.read((char*)&informa.data_to_layer, sizeof(informa.data_to_layer));
		how_data_set = informa.data_to_layer;
		NN_file.read((char*)&informa.qua_layers, sizeof(informa.qua_layers));
		how_much_layers = informa.qua_layers;

		for (size_t i = 0; i < informa.qua_layers; i++) {
			size_t qua = 0;
			size_t acti = 0;
			bool type = 1;
			NN_file.read((char*)&qua, sizeof(qua));
			NN_file.read((char*)&type, sizeof(type));
			NN_file.read((char*)&acti, sizeof(acti));
			informa.layers.push_back({ qua,type,acti });
		}
		for (size_t i = 0; i < 128; i++) {
			char s = '0';
			NN_file.read((char*)&s, sizeof(s));
			if (s != '0')
				std::cerr << "problem\n";
		}
		size_t neiro_itterator = 0;
		for (size_t i = 0; i < informa.qua_layers; i++) {
			for (size_t j = 0; j < informa.layers[i].qua; j++) {
				double T = 0;
				vector<double> W;
				size_t qua = 0;
				size_t function = 0;
				double a = 0.0;
				double b = 0.0;
				neiro_itterator++;
				
				NN_file.read((char*)&T, sizeof(T));
				NN_file.read((char*)&function, sizeof(function));
				NN_file.read((char*)&a, sizeof(a));
				NN_file.read((char*)&b, sizeof(b));
				NN_file.read((char*)&qua, sizeof(qua));
				for (size_t z = 0; z < qua; z++){
					double w = 0.0;
					NN_file.read((char*)&w, sizeof(w));
					W.push_back(w);
				}
				informa.function.push_back({ function,a,b });
				neiro.push_back({ T,function,a,b,W });
			}
		}
		cout << "Load success\n";
		NN_file.close();
		// проверка на соответствие параметров
		if (forecast_shift < 0)
			forecast_shift = 0;
		if (data_shift <= 0)
			data_shift = 1;
		if (how_much_layers <= 0)
			how_much_layers = 3;
		if (how_data_set <= 0)
			how_data_set = 1;

		result = new NeuralNetwork();


		for (size_t i = 0; i < how_much_layers; i++) {
			size_t set_neiro = 1, set_active = 1;
			bool connection = 1;

			set_neiro = informa.layers[i].qua;
			set_active = informa.layers[i].activation;
			connection = informa.layers[i].type_connection;

			if (set_neiro <= 0)
				set_neiro = 6;
			if (set_active <= 0 || set_active >= 17)
				set_active = 1;

			neirons.push_back(set_neiro);
			activations.push_back(set_active);
			connection_vector.push_back(connection);

			//проверяем тип подключения
			if (i != 0) {
				if (!connection_vector[i] && neirons[i] != neirons[i - 1]) {
					connection_vector[i] = 1;
				}
			}
			else {
				if (!connection_vector[i] && neirons[i] != how_data_set) {
					connection_vector[i] = 1;
				}
			}

		}

		std::cout << "build layers\n";
		neiro_itterator = 0;
		for (size_t i = 0; i < neirons.size(); i++) {
			cout << i + 1 << " layer:\n";
			vector<Neiron*> neiron_set;
			for (size_t j = 0; j < neirons[i]; j++) {
				neiron_set.push_back(NeironsMaker.SetNeirons(activations[i], neiro[neiro_itterator].a, neiro[neiro_itterator].b));
				neiro_itterator++;
			}
			Layer* set_layer = LayersMaker.SetLayer(neiron_set);
			set_layer->SetTypeOfConnection(connection_vector[i]);
			result->PutLayer(set_layer);
		}

		std::cout << "build adapters\n";
		AdapterBegin* result_adapter_begin = new AdapterBegin(result, connection_vector[0], how_data_set, data_shift);
		AdapterEnd* result_adapter_end = new AdapterEnd(result, result_adapter_begin, data_shift, forecast_shift);



		std::cout << "build connection\n";
		neiro_itterator = 0;
		result->GetLayer(0)->SetTypeOfConnection(connection_vector[0]);
		
		for (size_t i = 0; i < result->GetLayer(0)->NeironsInLayer(); i++) {
			result->GetLayer(0)->GetNeiron(i)->SetW(neiro[neiro_itterator].W);
			neiro_itterator++;
		}
		

		for (size_t i = 1; i < how_much_layers; i++) {
			result->MakeConnection(i, connection_vector[i]);
			for (size_t j = 0; j < result->GetLayer(i)->NeironsInLayer(); j++){
				result->GetLayer(i)->GetNeiron(j)->SetW(neiro[neiro_itterator].W);
				neiro_itterator++;
			}
		}

		cout << "end of builder\n";
		result_conteiner->begin = result_adapter_begin;
		result_conteiner->network = result;
		result_conteiner->end = result_adapter_end;
		result_conteiner->inf = informa;

		return result_conteiner;
	}
	NN_file.close();
	return nullptr;
}

Layer* Builder::GetLayer(){
	return new Layer;
}

Neiron* Builder::GetNeiron(){
	return NeironsMaker.SetNeirons();
}


Neiron* Builder::GetNeiron(size_t activation){
	return NeironsMaker.SetNeirons(activation);
}

