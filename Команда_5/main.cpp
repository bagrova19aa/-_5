#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>


#include<Functions.h>


std::istream& operator >> (std::istream& in, Point& a) {                        //Перегрузка ввода (>>)

	in >> a.number >> a.area >> a.xm >> a.ym >> a.AR;
	return in;
}
std::ostream& operator << (std::ostream& out, const Point& a) {                 //Перегрузка вывода(<<)

	out << a.number << " " << a.area << " " << a.xm << " " << a.ym << " " << a.AR;

	return out;
}




int main() {

    double max_dist, min_dist;
    do{                                                      //Ввод расстояний
        std::cout << "Enter the max and min distance :\n";
        std::cin >> max_dist >> min_dist;
    } while (!(max_dist > min_dist && max_dist > 0 && min_dist >= 0));




    int test;

    for (int i = 1; i <= 303; i++) {                              
        if (i % 15 == 0) {
            std::string v = std::to_string(i);

            std::vector<Point>  all_values = WriteFileToVector(v);
            std::vector<Point> sorted_values = SortedVector(all_values, max_dist, min_dist);

            //создаем основу для матриц связей и расстояний
            std::vector <std::vector<double>> relationship(sorted_values.size(), std::vector<double>(sorted_values.size(), 0));
            std::vector <std::vector<double>> distance(sorted_values.size(), std::vector<double>(sorted_values.size(), 0));

            Matrix_Relationship_Distance(sorted_values, relationship, distance, max_dist, min_dist); // вызов функции
            //Создаём основу для матрицы К.,заполняем её нулями, s.size (размер матрицы связей)
            std::vector <std::vector<double>> kir(relationship.size(), std::vector<double>(relationship.size(), 0));

            std::map <double, double> kir_val;//словарь вероятности валентности 
            KirMat_Valence(relationship, kir, kir_val);// s (матрица связей), kir матрица К., kir_val словарь
         /*   for (int i = 0; i < sorted_values.size(); i++) {
                for (int j = 0; j < sorted_values.size(); j++) {
                    std::cout << kir[i][j] << " ";
                }
                std::cout << "\n";
            }
            std::cout << "kir" << "\n";
            std::cin >> test;*/
            std::vector <std::vector<double>> energ(distance.size(), std::vector<double>(distance.size(), 0)); // вектор матрицы энергий, a.size() - размер матрицы расстояний, 
                                                                                                 // как только мы ее создадим, нужно будет изменить имя
            std::map <double, double> en_prob; //словарь для хранения вероятностей


            
            WriteToXml(v, kir_val, en_prob, kir, energ);




        }
    }


}






