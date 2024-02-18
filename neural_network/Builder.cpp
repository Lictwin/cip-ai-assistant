#include "Builder.h"
using std::cin;


void Builder::hand()
{
	cout << "nothing";
}

Builder::Builder()
{
	cout << "it a builder\n";
}

Builder::~Builder()
{
	cout << "it an end\n";
}

NeuralNetwork* Builder::GetNNHand()
{
	NeuralNetwork* result;// сеть, что отдастся нашим 
	size_t forecast_shift;//сдвиг по прогнозу (на сколько прогнозируем)
	size_t data_shift;//сдвиг по данным (на сколько сдвигаемся по данным)
	size_t how_much_layers;//
	vector<size_t> neirons;
	vector<size_t> activations;
	vector<bool> connection_vector;
	cout << "How much forecast shift: ";
	cin >> forecast_shift;
	cout << "How much data shift: ";
	cin >> data_shift;
    cout << "How many layers: ";
	cin >> how_much_layers;


	// проверка на соответствие параметров
	if (forecast_shift < 0)
		forecast_shift = 0;
	if (data_shift <= 0)
		data_shift = 1;
	if (how_much_layers <= 0)
		how_much_layers = 3;

	result = new NeuralNetwork(forecast_shift, data_shift, 0);

	cout << "\n\n\n\n\nActivations Functions:\n\n\n" <<
		//"1 - Identical (no parameters)\n" <<
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
	


	for (size_t i = 0; i < how_much_layers; i++)
	{
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
		if(i != 0)
			if (!connection_vector[i] && neirons[i] != neirons[i - 1])
			{
				connection_vector[i] = 1;
			}
	}

	std::cout << "build layers\n";
	for (size_t i = 0; i < neirons.size(); i++)
	{
		cout << i+1 <<" layer:\n";
		vector<Neiron*> neiron_set;
		for (size_t j = 0; j < neirons[i]; j++)
		{
			double a = 1;
			double b = 1;
			switch (activations[i])
			{
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
				cout << "I don't know\n";
				break;
			}
			/*if (activations[i] == 1 || activations[i] == 6 || activations[i] == 7)
			{
				cout << "set a for activation function: ";
				cin >> a;
			}
			else if (activations[i] == 2 || activations[i] == 3)
			{
				cout << "set a for activation function: ";
				cin >> a;
				cout << "set b for activation function: ";
				cin >> b;
			}*/
			neiron_set.push_back(NeironsMaker.SetNeirons(activations[i], a, b));
		}
		Layer* set_layer = LayersMaker.SetLayer(neiron_set);
		result->PutLayer(set_layer);
	}

	std::cout << "build adapters\n";
	for (size_t i = 0; i < neirons.size(); i++)
	{
		cout << i + 1 << " layer:\n";
		vector<Neiron*> neiron_set;
		for (size_t j = 0; j < neirons[i]; j++)
		{
			double a = 1;
			double b = 1;
			switch (activations[i])
			{
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
				cout << "I don't know\n";
				break;
			}
			/*if (activations[i] == 1 || activations[i] == 6 || activations[i] == 7)
			{
				cout << "set a for activation function: ";
				cin >> a;
			}
			else if (activations[i] == 2 || activations[i] == 3)
			{
				cout << "set a for activation function: ";
				cin >> a;
				cout << "set b for activation function: ";
				cin >> b;
			}*/
			neiron_set.push_back(NeironsMaker.SetNeirons(activations[i], a, b));
		}
		Layer* set_layer = LayersMaker.SetLayer(neiron_set);
		result->PutLayer(set_layer);
	}



	std::cout << "build connection\n";
	for (size_t i = 0; i < how_much_layers; i++)
	{
         result->MakeConnection(i, connection_vector[i]);
	}
	
	cout << "end of builder\n";
	return result;
}

Layer* Builder::GetLayer()
{
	return new Layer;
}

Neiron* Builder::GetNeiron()
{
	return NeironsMaker.SetNeirons();
}

Layer* Builder::GetLayer(size_t activation, size_t numb_of_neiron)
{
	return LayersMaker.SetLayer(activation, numb_of_neiron);
}

Neiron* Builder::GetNeiron(size_t activation)
{
	return  NeironsMaker.SetNeirons(activation);
}

void Builder::MakeConnection(Layer* prev, Layer* next)
{}