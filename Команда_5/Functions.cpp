#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <algorithm>

#include <Functions.h>





std::vector<Point> WriteFileToVector(std::string i) {

    std::ifstream fin;

    std::string file_path;
    std::string trash;

    Point f;

    std::vector<Point> all_values;

        file_path = "./files/data- (" + i + ").txt";

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
    double z = (max_dist - min_dist);                                                       //¬ычисление значени€, по которому идет отбор
    double result = z * z / 2;

    std::vector<Point> sorted_values;

	std::vector<Point> new_values;

	//std::copy_if(a.begin(), a.end(), std::back_inserter(sorted_values), [&](const Point& a) {   //ќтбор значений по услови€м и копирование их в вектор
	//	return !(a.area < result&& a.AR < 2.);
	//	});

    std::copy_if(a.begin(), a.end(), std::back_inserter(sorted_values), [&](const Point& a) {   //ќтбор значений по услови€м и копирование их в вектор
        return a.area > result ;
        });
	std::copy_if(sorted_values.begin(), sorted_values.end(), std::back_inserter(new_values), [&](const Point& a) {   //ќтбор значений по услови€м и копирование их в вектор
		return a.AR > 2.;
		});

    return new_values;
	//return sorted_values;
}

void Matrix_Relationship_Distance(const std::vector<Point>& sorted_values, std::vector <std::vector<double>>& relationship, std::vector <std::vector<double>>& distance, double max_dist, double min_dist) {

	for (int i = 0; i < sorted_values.size(); i++) {
		for (int j = i; j < sorted_values.size(); j++) {
			double dis = sqrt(pow(sorted_values[j].xm - sorted_values[i].xm, 2) + pow(sorted_values[j].ym - sorted_values[i].ym, 2));//находим рассто€ние между точками

			//матрица-св€зей
				if (dis > min_dist && dis  < max_dist) {
					relationship[i][j] = 1;
					relationship[j][i] = 1;
				}

				else {
					relationship[i][j] = 0;
					relationship[j][i] = 0;
				}

			//матрица рассто€ний
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
				if (i == j) { // если на главной диагонали - добавл€ем один раз
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
void KirMat_Valence(const std::vector <std::vector<double>>& matr, std::vector <std::vector<double>>& kir, std::map <double, double>& val)
{
	std::map <double, double> val_tmp; // счЄтчик валентностей

	for (int i = 0; i < matr.size(); i++)
	{
		int k = 0;
		for (int j = 0; j < matr.size(); j++) // проходим по матрице св€зей
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

	for (auto x : val_tmp) // расчет веро€тности валентностей
	{
		val[x.first] = x.second / kir.size(); // сколько раз встречалась/максимальное кол-во
	}
}

void WriteToXml(std::string i, const std::map <double, double>& valence_kir, const std::map <double, double>& valence_ener,
	const std::vector <std::vector<double>>& matrix_kir, const std::vector <std::vector<double>>& matrix_ener){

	std::ofstream XML_write;

	XML_write.open("./xml_files/Matrix_data-(" + i + ").XML");
	XML_write << "<File" + i + ">" << '\n';
	XML_write << "\t<MatrixKir>" << '\n';
	for (int i = 0; i < matrix_kir.size(); i++) {
		for (int j = 0; j < matrix_kir.size(); j++) {
			XML_write << matrix_kir[i][j] << ' ';
		}
		XML_write << '\n';
	}
	XML_write << "\t</MatrixKir>" << '\n';
	XML_write << "\t<Valence>" << '\n';
	for (auto j : valence_kir) {
		XML_write << j.first << ' ' << j.second << '\n';
	}
	XML_write << "\t</Valence>" << '\n';
	XML_write << "\t<MatrixEnergy>" << '\n';
	for (int i = 0; i < matrix_ener.size(); i++) {
		for (int j = 0; j < matrix_ener.size(); j++) {
			XML_write << matrix_ener[i][j] << ' ';
		}
		XML_write << '\n';
	}
	XML_write << "\t</MatrixEnergy>" << '\n';

	XML_write << "\t<ValenceEn>" << '\n';
	for (auto j : valence_ener) {
		XML_write << j.first << ' ' << j.second << '\n';
	}
	XML_write << "\t</ValenceEn>" << '\n';
	XML_write << "</File" + i + ">" << '\n';
	XML_write.close();
}

