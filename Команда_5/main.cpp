#include <iostream>
#include <fstream>
#include <vector>



#include<Functions.h>


std::istream& operator >> (std::istream& in, Point& a) {                        //Перегрузка ввода (>>)
	/*int num;*/
	in >> a.area >> a.xm >> a.ym >> a.AR;
	return in;
}
std::ostream& operator << (std::ostream& out, const Point& a) {                 //Перегрузка вывода(<<)

	out << a.area << " " << a.xm << " " << a.ym << " " << a.AR;

	return out;
}


int main() {

	double max_dist, min_dist;                                                          //Ввод расстояний
	std::cout << "Enter the max and min distance :\n";
	std::cin >> max_dist >> min_dist;

	std::vector<Point> all_values = WriteFileToVector();

	std::vector<Point> sorted_values = SortedVector(all_values, max_dist, min_dist);




}