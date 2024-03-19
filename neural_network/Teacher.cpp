#include "Director.h"
#include<time.h>
#include<algorithm>

//void Teacher::BPE()
//{
//	
//}

void Teacher::BPE(vector<double> set, vector<double> e, vector<double> res)
{
	//cout << "its bpe\n";
	vector<double> gamma_now;
	vector<double> gamma_prev;
	vector<vector<double>> gammas;
	size_t qua_layers = this->container->network->GetLayers().size();

	for (size_t i = 0; i < e.size(); i++){ // ошибка на выходе
		gamma_now.push_back(res[i] - e[i]);
	}
	gammas.push_back(gamma_now);
	gamma_prev = gamma_now;
	gamma_now.clear();


	for (size_t i = qua_layers - 2; i < -1; i--) {
		
		size_t qua_of_neiro = this->container->network->GetLayer(i)->NeironsInLayer();
		vector<vector<double>> W_layer;
		bool flag_sv = 1;

		for (size_t z = 0; z < this->container->network->GetLayer(i+1)->GetThisLayer().size(); z++){//получение всех весов следующего уровня
			W_layer.push_back(this->container->network->GetLayer(i+1)->GetThisLayer()[z]->GetW());
		}

		if (W_layer[0].size() == 1 && this->container->network->GetLayer(i)->GetThisLayer().size() == this->container->network->GetLayer(i + 1)->GetThisLayer().size()) {
			flag_sv = 0;
		}

		for (size_t j = 0; j < qua_of_neiro; j++){
			double gamma = 0;
			vector<double> W; 
			if (flag_sv){
                for (size_t z = 0; z < W_layer.size(); z++){
					W.push_back(W_layer[z][j]);
				}

				for (size_t z = 0; z < W.size(); z++){
					double F = this->container->network->GetLayer(i + 1)->GetNeiron(z)->GetDiff();
					gamma += gamma_prev[z] * F * W[z];
				}
			}	
			else {
				double F = this->container->network->GetLayer(i + 1)->GetNeiron(j)->GetDiff();
			    W = W_layer[j];
				gamma = gamma_prev[j] * F * W[0];
			}

            gamma_now.push_back(gamma);
		}
		gammas.push_back(gamma_now);
		gamma_prev = gamma_now;
		gamma_now.clear();
	}

	std::reverse(gammas.begin(), gammas.end());

	for (size_t i = 0; i < this->container->network->GetLayers().size(); i++) {
		for (size_t j = 0; j < this->container->network->GetLayer(i)->NeironsInLayer(); j++){
			double F = this->container->network->GetLayer(i)->GetNeiron(j)->GetDiff();
			this->container->network->GetLayer(i)->GetNeiron(j)->Train(gammas[i][j], this->alfa, F, this->container->network->GetLayer(i)->GetNeiron(j)->GetX());
		}
	}
}

Teacher::Teacher()
{
	container = nullptr;
	alfa = 0.1;
	itterations = 10;
	E = 0.1;
	
}

Teacher::Teacher(CnNt* train): Teacher()
{
	container = train;
}

Teacher::Teacher(CnNt* train, size_t itterations):Teacher(train)
{
	SetItterations(itterations);
}

Teacher::Teacher(CnNt* train, double alfa) :Teacher(train)
{
	SetAlfa(alfa);
}

Teacher::Teacher(CnNt* train, size_t itterations, double alfa) :Teacher(train)
{
	SetAlfa(alfa);
	SetItterations(itterations);
}

void Teacher::TrainBPE()
{
	size_t forecast_shift = this->container->end->GetForecastShift();
	size_t data_shift = this->container->begin->GetDataShift(); 
	size_t many_set= this->container->begin->GetHowManySet();
	size_t last_layer = this->container->end->GetHowManyEnd();
	itterations = 100;

	cout << "\n\n\n \\BPE\n";

	for (size_t i = 0; i < itterations; i++){
		cout << "\nItteration " << i + 1 << "\n";
		clock_t start, finish;
		double duration = 0;
		double total_E = 0;
		double max_E = 0;
		double min_E = 10000;
		start = clock();
		for (size_t j = 0; j < data.size() - forecast_shift - many_set; j += data_shift){//изменить общее условие (вроде норм сейчас)
			vector<double> set;//отправляем на вход
			vector<double> e;//эталоны
			vector<double> predict;//напрогнозировано
			double now_E = 0;
			for (size_t z = 0; z < many_set; z++){
				set.push_back(data[j + z]);
			}

			for (size_t z = 0; z < last_layer; z++){// собираем эталоны
				e.push_back(data[j + many_set + forecast_shift - z - 1]);//дописать сюда -1
			}
			std::reverse(e.begin(), e.end());
			this->container->begin->SetData(set);
			this->container->begin->Work();
			this->container->network->TrainWork();
			predict = this->container->end->GetPredict();
			

			for (size_t z = 0; z < predict.size(); z++){
				now_E += 0.5 * pow(predict[z] - e[z], 2);
			}
			total_E += now_E;
			if (now_E > max_E)
				max_E = now_E;
			if (now_E < min_E)
				min_E = now_E;


			double lf = 0;//адаптивный шаг
			for (double a : set)
			{
				lf += pow(a, 2);
			}
			alfa = 1 / (1 + lf);

			if (now_E > E)
				BPE(set,e,predict);

		}
		finish = clock();
		duration = (double)(finish - start) / CLOCKS_PER_SEC;
		cout << "\nTime: " << duration << "seconds\n" <<
			" Total E\t" << total_E << "\t\n" <<
			" MAX E\t" << max_E << "\t\n" <<
			" MIN E\t" << min_E << "\t\n";
	}


}

void Teacher::TrainAutoencoder()
{
}

void Teacher::TrainDeepAutoencoder()
{
}

void Teacher::TrainDeepBolzman()
{
}

Teacher::~Teacher()
{
	cout << "end of teacher\n";
}

void Teacher::SetItterations(size_t itterations)
{
	this->itterations = itterations;
}

void Teacher::SetAlfa(double alfa)
{
	this->alfa = alfa;
}

void Teacher::SetData(vector<double> data)
{
	this->data = data;
}

void Teacher::SetE(double E)
{
	this->E = E;
}


