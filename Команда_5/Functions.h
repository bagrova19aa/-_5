#pragma once

struct Point {
    int  number,area;
    double xm, ym, AR;
};

//Возвращает vector со считанными значениями из файла
std::vector<Point> WriteFileToVector(std::string i);	

//Возвращает vector отсортированный по условиям
std::vector<Point> SortedVector(const std::vector<Point>& a, double max_dist, double min_dist);

//Изменяет две существующие матрицы(расстояний и связей)
void Matrix_Relationship_Distance(const std::vector<Point>& sorted_values, std::vector <std::vector<double>>& relationship, std::vector <std::vector<double>>& distance, double max_dist, double min_dist);

//По ссылке изменяет(создаёт) матрицу энергий и словарь с вероятностями
void EnergyMat_Probability (const std::vector <std::vector<double>>& base, std::vector <std::vector<double>>& energ, std::map <double, double>& val, double max_dist, double min_dist);
//Создает матрицу,ничего не возвращает,а изменяет уже существующие вектора
void KirMat_Valence(const std::vector <std::vector<double>>& matr, std::vector <std::vector<double>>& kir, std::map <double, double>& val);

void WriteToXml(std::string i, const std::map <double, double>& valence_kir, const std::map <double, double>& valence_ener,
    const std::vector <std::vector<double>>& matrix_kir, const std::vector <std::vector<double>>& matrix_ener);