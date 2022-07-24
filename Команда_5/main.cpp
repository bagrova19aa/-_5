#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>


#include<Functions.h>


std::istream& operator >> (std::istream& in, Point& a) {                        //Перегрузка ввода (>>)
	/*int num;*/
	in >> a.number >> a.area >> a.xm >> a.ym >> a.AR;
	return in;
}
std::ostream& operator << (std::ostream& out, const Point& a) {                 //Перегрузка вывода(<<)

	out << a.number << " " << a.area << " " << a.xm << " " << a.ym << " " << a.AR;

	return out;
}




int main() {

    double max_dist, min_dist;                                                          //Ввод расстояний
    std::cout << "Enter the max and min distance :\n";
    std::cin >> max_dist >> min_dist;

    int test;



    for (int i = 1; i <= 303; i++) {                              
        if (i % 15 == 0) {
            std::vector<Point>  all_values = WriteFileToVector(i);

            std::vector<Point> sorted_values = SortedVector(all_values, max_dist, min_dist);

            //std::vector <std::vector<double>> energ(a.size(), std::vector<double>(a.size(), 0)); // вектор матрицы энергий, a.size() - размер матрицы расстояний, 
                                                                                                 // как только мы ее создадим, нужно будет изменить имя
            std::map <double, double> en_val; //словарь для хранения вероятностей

            //EnergyMat_Valence(a, energ, en_val); //вызов функции, а - матрица расстояний, которой пока ещё нет

            for (const auto& j : sorted_values) {
                std::cout << j << '\n';
            }
            std::cin >> test;
        }



    }














}






