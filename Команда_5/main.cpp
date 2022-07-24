#include <iostream>
#include <fstream>
#include <vector>
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



            for (const auto& j : sorted_values) {
                std::cout << j << '\n';
            }
            std::cin >> test;
        }



    }














}






