#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#include <Functions.h>





std::vector<Point> WriteFileToVector(int i) {

    std::ifstream fin;

    std::string file_path;
    std::string trash;

    Point f;

    std::vector<Point> all_values;


        std::string v = std::to_string(i);
        file_path = "./files/data- (" + v + ").txt";

        fin.open(file_path);

        if (fin.is_open()) {
            getline(fin, trash);

            while (fin >> f.number >> f.area >> f.xm >> f.ym, fin >> trash, fin >> f.AR, getline(fin, trash)) {
                all_values.push_back(f);                                    //Добавление значений в вектор
            }
            fin.close();
        }
        else {
            std::cout << file_path << "\n";
        }

    
    return all_values;
}


std::vector<Point> SortedVector(const std::vector<Point>& a, double max_dist, double min_dist) {
    double z = (max_dist + min_dist) / 2;                                                       //Вычисление значения, по которому идет отбор
    double result = z * z / 8;

    std::vector<Point> sorted_values;

    std::copy_if(a.begin(), a.end(), std::back_inserter(sorted_values), [&](const Point& a) {   //Отбор значений по условиям и копирование их в вектор
        return !(a.area < result || a.AR < 2.);
        });

    return sorted_values;
}
