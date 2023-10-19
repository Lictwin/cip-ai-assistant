#pragma once

#include <iostream>
#include <vector>
#include "neiron.h"
#include "data_form.h"



class autoencoder
{

	
	std::vector<size_t> size_of_set;// размер сети по слоям
	std::vector<std::vector<neiron*>> p_on_neiron; // указатель на каждый нейрон

public:
	
	autoencoder();//здесь вызывается конструктор и строитель, что создаёт саму сеть


	neiron* get_pointer_on_neiron(size_t height, size_t width)// получение казателя на конкретный нейрон в сети
	{
	
	
	}

	std::vector<DATA> put_and_get(std::vector<DATA> input)//сюда вводим данные и получаем результат
	{
		std::vector<DATA> output;
		return output;
	}
};


class AE_builder
{


public:



};