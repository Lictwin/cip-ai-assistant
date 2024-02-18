// Neural_network.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//


/*
* Все типы классы и функции пишутся через Большие буквы
* Все переменные пишутся через нижние подчеркивания
* Все файлы пишутся через большие буквы
* Работу осуществлять только через 
*/

#include <iostream>
//#include "Neirons.h"
//#include "Layer.h"
#include "Builder.h"
//#include "Director.h"
#include "NeuralNetwork.h"
#include "Adapters.h"

int main()
{
    //Layer try1 = Layer();
    //try1.SetPointer(new SimpleNeirons(1));
    //Layer try2 = Layer();
    //try2.SetPointer(new SimpleNeirons(1));
    //Layer try3 = Layer();
    //try3.SetPointer(new SimpleNeirons(1));
    //Layer try4 = Layer();
    //try4.SetPointer(new SimpleNeirons(1));
    //Layer try5 = Layer(1, 4);
    //try5.SetPointer(new SimpleNeirons(1));

    //NeuralNetwork ser;
    //ser.PutLayer(&try1);
    //ser.PutLayer(&try2);
    //ser.PutLayer(&try3);
    //ser.PutLayer(&try4);
    //ser.PutLayer(&try5);
    //
    //ser.GetInformation();
    //std::cout << "End\n";

    Builder bild;

    NeuralNetwork* serq = bild.GetNNHand();
    for (size_t i = 0; i < serq->GetLayer(0)->NeironsInLayer(); i++)
    {
        serq->GetLayer(0)->GetNeiron(i)->SetX(0.4);
    }
    
    serq->Work();
    std::cout << "End\n";


    for (size_t i = 0; i < serq->GetLayer(0)->NeironsInLayer(); i++)
    {
        serq->GetLayer(0)->GetNeiron(i)->SetX(1.4);
    }

    serq->Work();
    std::cout << "End\n";

}

 //Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
 //Отладка программы: F5 или меню "Отладка" > "Запустить отладку"
 //Советы по началу работы 
 //  1. В окне обозревателя решений можно добавлять файлы и управлять ими.
 //  2. В окне Team Explorer можно подключиться к системе управления версиями.
 //  3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
 //  4. В окне "Список ошибок" можно просматривать ошибки.
 //  5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
 //  6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
