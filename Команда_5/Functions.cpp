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
                all_values.push_back(f);                                    //ƒобавление значений в вектор
            }
            fin.close();
        }
        else {
            std::cout << file_path << "\n";
        }

    
    return all_values;
}


std::vector<Point> SortedVector(const std::vector<Point>& a, double max_dist, double min_dist) {
    double z = (max_dist + min_dist) / 2;                                                       //¬ычисление значени€, по которому идет отбор
    double result = z * z / 8;

    std::vector<Point> sorted_values;

    std::copy_if(a.begin(), a.end(), std::back_inserter(sorted_values), [&](const Point& a) {   //ќтбор значений по услови€м и копирование их в вектор
        return !(a.area < result || a.AR < 2.);
        });

    return sorted_values;
}


void EnergyMat_Valence(const std::vector <std::vector<double>>& base, std::vector <std::vector<double>>& energ, std::map <double, double>& val)
{
	std::map <double, double> en_tmp; // счетчик энергий

	for (int i = 0; i < base.size(); i++)
	{
		for (int j = i; j < base.size(); j++) // проход по матрице(вар. 2)
		{
			if (!base[i][j]) { // если d = 0, e = 0
				if (i == j) { // если на главной диагонали - добавл€ем один раз
					energ[i][j] = 0;
					en_tmp[0]++;
				}
				else {
					energ[i][j] = 0;
					energ[j][i] = 0;
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
				double result = 1 / d12 - 1 / d6; // расчет энергии

				energ[i][j] = result; // занесение в матрицу энергий
				energ[j][i] = result;

				en_tmp[result]++; // занесение значени€ энергии в словарь дл€ подсчета кол-ва
				en_tmp[result]++; // встречаетс€ два раза
			}
		}
	}



	for (auto x : en_tmp) // расчет веро€тности энергий
	{
		val[x.first] = x.second / (energ.size() * energ.size()); // сколько раз встречалась / максимальное кол-во
	}


}