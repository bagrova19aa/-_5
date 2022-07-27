#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cmath>
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

void Matrix_Relationship_Distance(const std::vector<Point>& sorted_values, std::vector <std::vector<double>>& relationship, std::vector <std::vector<double>>& distance, double max_dist, double min_dist) {

	for (int i = 0; i < sorted_values.size(); i++) {
		for (int j = i; j < sorted_values.size(); j++) {
			double dis = sqrt(pow(sorted_values[j].xm - sorted_values[i].xm, 2) + pow(sorted_values[j].ym - sorted_values[i].ym, 2));//находим расстояние между точками

			//матрица-связей
				if (dis > min_dist && < max_dist) {
					relationship[i][j] = 1;
					relationship[j][i] = 1;
				}

				else {
					relationship[i][j] = 0;
					relationship[j][i] = 0;
				}

			//матрица расстояний
			if (relationship[i][j] == 1) {
				distance[i][j] = dis;
				distance[j][i] = dis;
			}
			else {
				distance[i][j] = 0;
				distance[j][i] = 0;
			}
		}
	}

}

void EnergyMat_Probability (const std::vector <std::vector<double>>& base, std::vector <std::vector<double>>& energ, std::map <double, double>& val)
{
	std::map <double, double> en_tmp; // счетчик энергий

	for (int i = 0; i < base.size(); i++)
	{
		for (int j = i; j < base.size(); j++) // проход по матрице(вар. 2)
		{
			if (!(base[i][j] > 0 && base[i][j] < 2.5) || base[i][j] == 1) { // если d принадлежит(-бесконечность, 0] и [2.5, +бесконечность) , e = 0
				if (i == j) { // если на главной диагонали - добавляем один раз
					en_tmp[0]++;
				}
				else {
					en_tmp[0]++;
					en_tmp[0]++;
				}
			}
			else {
				double tmp = base[i][j];
				double d12 = base[i][j];
				double d6;

				for (int l = 1; l < 12; l++) { // возведение в 12 и 6 степень
					if (l == 6) d6 = d12;
					d12 *= tmp;
				}
				double result = round((1 / d12 - 1 / d6) * 100) / 100; // расчет энергии

				energ[i][j] = result; // занесение в матрицу энергий
				energ[j][i] = result;

				en_tmp[result]++; // занесение значения энергии в словарь для подсчета кол-ва
				en_tmp[result]++; // встречается два раза
			}
		}
	}



	for (auto x : en_tmp) // расчет вероятности энергий
	{
		val[x.first] = x.second / (energ.size() * energ.size()); // сколько раз встречалась / максимальное кол-во
	}


}
void KirMat_Valence(const std::vector <std::vector<double>>& matr, std::vector <std::vector<double>>& kir, std::map <double, double>& val)
{
	std::map <double, double> val_tmp; // счётчик валентностей

	for (int i = 0; i < matr.size(); i++)
	{
		int k = 0;
		for (int j = 0; j < matr.size(); j++) // проходим по матрице связей
		{
			if (i != j)
			{
				if (matr[i][j]) {
					kir[i][j] = -1;
					k++;
				}
			}
		}

		kir[i][i] = k;
		val_tmp[k]++;
	}

	for (auto x : val_tmp) // расчет вероятности валентностей
	{
		val[x.first] = x.second / kir.size(); // сколько раз встречалась/максимальное кол-во
	}
}