#include "Layer.h"




void Layer::MakeConnectionNext(Layer* next, bool type)
{
	if (type)
	{
		for (size_t i = 0; i < pt_this.size(); i++)
		{
			pt_this[i]->SetPointersNextLevel(next->GetThisLayer());
		}
	}
	else
	{
		if (this->qua_of_neirons == next->GetThisLayer().size())
		{
			for (size_t i = 0; i < pt_this.size(); i++)
			{
				vector<Neiron*> put{ next->GetThisLayer()[i] };
				pt_this[i]->SetPointersNextLevel(put);
			}
		}
		else
		{
			std::cout << "no connection 1 to 1 in this layer\n";
			for (size_t i = 0; i < pt_this.size(); i++)
			{
				pt_this[i]->SetPointersNextLevel(next->GetThisLayer());
			}
		}

	}
}

void Layer::MakeConnectionPrev(Layer* prev, bool type)
{
	if (type)
	{
		for (size_t i = 0; i < pt_this.size(); i++)
		{
			//pt_this[i]->SetPointersPrevLevel(prev->GetThisLayer());
		}
	}
	else
	{
		if (this->qua_of_neirons == prev->GetThisLayer().size())
		{
			for (size_t i = 0; i < pt_this.size(); i++)
			{
				vector<Neiron*> put{ prev->GetThisLayer()[i] };
				//pt_this[i]->SetPointersPrevLevel(put);
			}
		}
		else
		{
			std::cout << "no connection 1 to 1 in this layer\n";
			for (size_t i = 0; i < pt_this.size(); i++)
			{
				//pt_this[i]->SetPointersPrevLevel(prev->GetThisLayer());
			}
		}

	}
}

Layer::Layer()
{
	qua_of_neirons = 0;
}

Layer::Layer(size_t type_of_active, size_t quantity)
{
	qua_of_neirons = quantity;
	for (int i = 0; i < quantity; i++)
	{
		Neiron* set = new SimpleNeirons(type_of_active);
		this->pt_this.push_back(set);
	}
	
}

Layer::Layer(size_t type_of_active, double a, double b, size_t quantity)
{
	qua_of_neirons = quantity;
	for (int i = 0; i < quantity; i++)
	{
		Neiron* set = new SimpleNeirons(type_of_active, a, b);
		this->pt_this.push_back(set);
	}
}

Layer::Layer(size_t type_of_active, double a, size_t quantity)
{
	qua_of_neirons = quantity;
	for (int i = 0; i < quantity; i++)
	{
		Neiron* set = new SimpleNeirons(type_of_active,a);
		this->pt_this.push_back(set);
	}
}

Layer::Layer(vector<Neiron*> set)
{
	qua_of_neirons = set.size();
	this->pt_this = set;
}

Layer::~Layer()
{
	for (size_t i = 0; i < pt_this.size(); i++)
	{
		pt_this[i]->DeleteNeiron();//удаление нейронов
		delete pt_this[i];
	}
}

vector<Neiron*> Layer::GetThisLayer()
{
	return pt_this;
}

vector<Neiron*> Layer::GetNextLayer()
{
	return pt_next;
}

vector<Neiron*> Layer::GetPrevLayer()
{
	return pt_prev;
}

Neiron* Layer::GetNeiron(size_t position)
{
	if (position < qua_of_neirons)
		return pt_this[position];
	else
		return nullptr;
}

size_t Layer::NeironsInLayer()
{
	return qua_of_neirons;
}

void Layer::SetPointer(Neiron* some)
{
	pt_this.push_back(some);
	qua_of_neirons += 1;
}

void Layer::SetPrevLayer(vector<Neiron*> prev_layer)
{
	pt_prev = prev_layer;
}

void Layer::SetPrevLayer(vector<Neiron*> prev_layer, bool type_connection)
{
	pt_prev = prev_layer;
	//if (type_connection)
	//{
	//	for (size_t i = 0; i < pt_this.size(); i++)
	//	{
	//		//pt_this[i]->SetPointersPrevLevel(pt_prev);
	//	}
	//}
	//else
	//{
	//	for (size_t i = 0; i < pt_this.size(); i++)
	//	{
	//		vector<Neiron*> set{ pt_prev[i] };
	//		//pt_this[i]->SetPointersPrevLevel(set);
	//	}
	//}
}

void Layer::SetNextLayer(vector<Neiron*> next_layer)
{
	pt_next = next_layer;
}

void Layer::SetNextLayer(vector<Neiron*> next_layer, bool type_connection)
{
	pt_next = next_layer;
	if (type_connection)
	{
		for (size_t i = 0; i < pt_this.size(); i++)
		{
			pt_this[i]->SetPointersNextLevel(pt_next);
		}
	}
	else
	{
		for (size_t i = 0; i < pt_this.size(); i++)
		{
			vector<Neiron*> set{ pt_next[i] };
			pt_this[i]->SetPointersNextLevel(set);
		}
	}

}

void Layer::WorkLayer()
{
	for (size_t i = 0; i < qua_of_neirons; i++)
	{
		pt_this[i]->Work();
	}
}

void Layer::PutValues(vector<double> in)
{
	for (size_t i = 0; i < qua_of_neirons; i++)
	{
		pt_this[i]->SetX(in[i]);
	}
}

vector<double> Layer::GetY()
{
	vector<double> Y;
	for (size_t i = 0; i < qua_of_neirons; i++)
	{
		Y.push_back(pt_this[i]->GetY());
	}
	return Y;
}

vector<double> Layer::GetDiff()
{
	vector<double> Diff;
	for (size_t i = 0; i < qua_of_neirons; i++)
	{
		Diff.push_back(pt_this[i]->GetDiff());
	}
	return Diff;
}

void Layer::ClearAll()
{
	for (size_t i = 0; i < qua_of_neirons; i++)
	{
		pt_this[i]->ClearX();
		//p_this[i]->ClearY();
	}
}

void Layer::ClearX()
{
	for (size_t i = 0; i < qua_of_neirons; i++)
	{
		pt_this[i]->ClearX();
	}
}