// DatasetsMaker.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "DataFormats.h"

int main()
{
    std::string file_name;
    size_t forecast_shift = 0,
        data_shift = 0,
        input = 0,
        output = 0;
    std::cout << "Hello in datasets maker\n\n\nSet file name:  ";
    std::getline(std::cin, file_name);

    if (!(file_name[file_name.length() - 4] == '.' &&
        file_name[file_name.length() - 3] == 'c' &&
        file_name[file_name.length() - 2] == 's' &&
        file_name[file_name.length() - 1] == 'v')) {
        std::cerr << "Error with format of file\n";
        return 0;

    }

    std::ifstream def(file_name);
    std::cout << file_name;
    std::vector<OCDF> from_file;
    std::vector<std::pair<vector<double>, vector<double>>> data_set;


    if (def.is_open()) {
        OCDF ffub;
        for (size_t i = 0; !def.eof(); i++) {
            char buffer_char;
            OCDF ffub;
            def >> ffub.cid >> buffer_char >> ffub.time >> buffer_char >> ffub.value;
            from_file.push_back(ffub);
        }
        std::cout << "\n\nGood with reading\n\n";
    }
    else{
        std::cerr << "\n\nProblem with open file\n\n";
        system("pause");
        return 0;
    }

    std::cout << "\n\nSet parameters\n";
    std::cout << "Set forecast shift: ";
    std::cin >> forecast_shift;
    std::cout << "Set data shift: ";
    std::cin >> data_shift;
    std::cout << "Set input neirons: ";
    std::cin >> input;
    std::cout << "Set output neirons: ";
    std::cin >> output;

    if (input <= 0 || output <= 0 || forecast_shift < 0 || data_shift < 1) {
        std::cerr << "\n\nProblem with parameters\n\n";
        system("pause");
        return 0;
    }

    for (size_t i = 0; i < from_file.size() - forecast_shift - data_shift - input - output; i+= data_shift)
    {
        std::vector<double> input_vector;
        std::vector<double> output_vector;
        for (size_t j = 0; j < input; j++) {
            input_vector.push_back(from_file[i + j].value);
        }
        for (size_t j = 0; j < output; j++) {
            output_vector.push_back(from_file[i + j + forecast_shift].value);
        }
        data_set.push_back(std::make_pair(input_vector, output_vector));
    }

    std::string file_name_dst;
    std::cout << "Set name of dataset file: ";
    std::cin >> file_name_dst;

    std::ofstream NN_file = std::ofstream(file_name_dst + ".dst", std::ios::binary);
    if (!NN_file.is_open()) {
        std::cerr << "error with open\n";
        return 0;
       

    }
    else {
        NN_file.write("000.02", 7);

        NN_file.write((char*)&forecast_shift, sizeof(forecast_shift));
        NN_file.write((char*)&data_shift, sizeof(data_shift));
        NN_file.write((char*)&input, sizeof(input));
        NN_file.write((char*)&output, sizeof(output));
        
        for (size_t i = 0; i < 128; i++) {
            NN_file.write("0", 1);
        }
        size_t neiro_itterator = 0;
        for (size_t i = 0; i < data_set.size(); i++) {
            for (size_t j = 0; j < input; j++) {
                NN_file.write((char*)&data_set[i].first[j], sizeof(data_set[i].first[j]));
            }

            for (size_t j = 0; j < output; j++) {
                NN_file.write((char*)&data_set[i].second[j], sizeof(data_set[i].second[j]));
            } 
        }
    }
    NN_file.close();


     
    std::cout << "End  ";
    system("pause");
    return 0;
}