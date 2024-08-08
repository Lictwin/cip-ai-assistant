

#include <iostream>
#include <vector>
#include <fstream>

struct informaormation { // полное опісаніе нейронной сеті
	size_t forecast_shift;//сдвиг по прогнозу (на сколько прогнозируем) // не актуально
	size_t data_shift;//сдвиг по данным (на сколько сдвигаемся по данным) // не актуально
	size_t data_to_layer;//сколько значений отправляется на вход
	size_t how_many_get;//сколько значений получаем на выходе
	size_t qua_layers;//количество слоёв
	double passport_E;//цель обучения задаваямая при обучении сети
	double total_E;//полная ошибка сети
	double MIN_E;//минимальная ошибка
	double MAX_E;//максимальная ошибка
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
	std::vector<layer_function> layers;
	std::vector<function_activation> function;
};

double rRand() {

	double res = rand();

	while (res > 0.01) {
		res /= 10;
	}

	return res;
}

int main()
{
    std::cout << "Hello in neiromaker!\n";
	informaormation informa;
	size_t forecast_shift = 1;//сдвиг по прогнозу (на сколько прогнозируем)
	size_t data_shift = 1;//сдвиг по данным (на сколько сдвигаемся по данным)
	size_t how_much_layers = 1;// сколько всего слоев
	size_t how_data_set = 1;// сколько отправляем на вход
	std::vector<size_t> neirons;
	std::vector<size_t> activations;
	std::vector<bool> connection_vector;
	std::cout << "How much forecast shift: ";
	std::cin >> forecast_shift;
	std::cout << "How much data shift: ";
	std::cin >> data_shift;
	std::cout << "How many layers: ";
	std::cin >> how_much_layers;
	std::cout << "How much data to set: ";
	std::cin >> how_data_set;

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
	informa.MAX_E = 100000000;
	informa.MIN_E = 100000000;
	informa.passport_E = 100000000;
	informa.total_E = 100000000;



	std::cout << "\n\n\n\n\nActivations Functions:\n\n\n" <<
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



	for (size_t i = 0; i < how_much_layers; i++) {
		size_t set_neiro, set_active;
		bool connection;
		std::cout << "How many in " << i + 1 << " layer: ";
		std::cin >> set_neiro;
		std::cout << "Function activation ";
		std::cin >> set_active;
		std::cout << "Type connection previous: (1 - all to all, 0 - one to one) ";
		std::cin >> connection;

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
		informa.layers.push_back({ set_neiro,connection,set_active });
	}

	std::cout << "build layers\n";
	for (size_t i = 0; i < neirons.size(); i++) {
		std::cout << i + 1 << " layer:\n";
		for (size_t j = 0; j < neirons[i]; j++) {
			double a = 1;
			double b = 1;
			switch (activations[i]) {
			case 1:
			case 6:
			case 7:
				std::cout << j + 1 << " neiron:\n";
				std::cout << "set a for activation function: ";
				std::cin >> a;
				informa.function.push_back({ activations[i],a,b });
				break;
			case 2:
			case 3:
				std::cout << j + 1 << " neiron:\n";
				std::cout << "set a for activation function: ";
				std::cin >> a;
				std::cout << "set b for activation function: ";
				std::cin >> b;
				informa.function.push_back({ activations[i],a,b });
				break;
			default:
				informa.function.push_back({ activations[i],a,b });
				break;
			}
		}
	
	}
	informa.how_many_get = neirons[neirons.size() - 1];

	std::cout << "end of builder\n\n\n\n Set name of file: ";

	std::string name;
	std::cin >> name;

	std::ofstream NN_file = std::ofstream(name + ".dnb", std::ios::binary);
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
		NN_file.write("000.02", 7);

		NN_file.write((char*)&informa.forecast_shift, sizeof(informa.forecast_shift));
		NN_file.write((char*)&informa.data_shift, sizeof(informa.data_shift));
		NN_file.write((char*)&informa.total_E, sizeof(informa.total_E));
		NN_file.write((char*)&informa.passport_E, sizeof(informa.passport_E));
		NN_file.write((char*)&informa.MAX_E, sizeof(informa.MAX_E));
		NN_file.write((char*)&informa.MIN_E, sizeof(informa.MIN_E));
		NN_file.write((char*)&informa.data_to_layer, sizeof(informa.data_to_layer));
		NN_file.write((char*)&informa.qua_layers, sizeof(informa.qua_layers));
		for (auto a : informa.layers) {
			NN_file.write((char*)&a.qua, sizeof(a.qua));
			NN_file.write((char*)&a.type_connection, sizeof(a.type_connection));
			NN_file.write((char*)&a.activation, sizeof(a.activation));
		}
		for (size_t i = 0; i < 128; i++) {
			NN_file.write("0", 1);
		}
		size_t neiro_itterator = 0;
		for (size_t i = 0; i < how_much_layers; i++) {
			for (size_t j = 0; j < neirons[i]; j++) {
				double T = rRand();
				size_t W_size = 0;
				if (informa.layers[i].type_connection) {
					if (i != 0 ) {
						W_size = informa.layers[i].qua;
					}
					else { 
						W_size = informa.how_many_get;
					}
				}
				else {
					W_size = 1;
				}
				std::vector<double> W;

				for (size_t z = 0; z < W_size; z++){
					W.push_back(rRand());
				}

				size_t qua = W.size();
				size_t function = informa.function[neiro_itterator].activation;
				double a = informa.function[neiro_itterator].a;
				double b = informa.function[neiro_itterator].b;
				neiro_itterator++;
				NN_file.write((char*)&T, sizeof(T));
				NN_file.write((char*)&function, sizeof(function));
				NN_file.write((char*)&a, sizeof(a));
				NN_file.write((char*)&b, sizeof(b));
				NN_file.write((char*)&qua, sizeof(qua));
				for (double w : W) {
					NN_file.write((char*)&w, sizeof(w));
				}
			}
		}
	}
	NN_file.close();
	
}

