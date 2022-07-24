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
                all_values.push_back(f);                                    //���������� �������� � ������
            }
            fin.close();
        }
        else {
            std::cout << file_path << "\n";
        }

    
    return all_values;
}


std::vector<Point> SortedVector(const std::vector<Point>& a, double max_dist, double min_dist) {
    double z = (max_dist + min_dist) / 2;                                                       //���������� ��������, �� �������� ���� �����
    double result = z * z / 8;

    std::vector<Point> sorted_values;

    std::copy_if(a.begin(), a.end(), std::back_inserter(sorted_values), [&](const Point& a) {   //����� �������� �� �������� � ����������� �� � ������
        return !(a.area < result || a.AR < 2.);
        });

    return sorted_values;
}


void EnergyMat_Valence(const std::vector <std::vector<double>>& base, std::vector <std::vector<double>>& energ, std::map <double, double>& val)
{
	std::map <double, double> en_tmp; // ������� �������

	for (int i = 0; i < base.size(); i++)
	{
		for (int j = i; j < base.size(); j++) // ������ �� �������(���. 2)
		{
			if (!base[i][j]) { // ���� d = 0, e = 0
				if (i == j) { // ���� �� ������� ��������� - ��������� ���� ���
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

				for (int l = 1; l < 12; l++) { // ���������� � 12 � 6 �������
					if (l == 6) d6 = d12;
					d12 *= tmp;
				}
				double result = 1 / d12 - 1 / d6; // ������ �������

				energ[i][j] = result; // ��������� � ������� �������
				energ[j][i] = result;

				en_tmp[result]++; // ��������� �������� ������� � ������� ��� �������� ���-��
				en_tmp[result]++; // ����������� ��� ����
			}
		}
	}



	for (auto x : en_tmp) // ������ ����������� �������
	{
		val[x.first] = x.second / (energ.size() * energ.size()); // ������� ��� ����������� / ������������ ���-��
	}


}