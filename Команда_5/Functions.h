#pragma once

struct Point {
    int  number,area;
    double xm, ym, AR;
};

//Возвращает vector со считанными значениями из файла
std::vector<Point> WriteFileToVector(int i);	

//Возвращает vector отсортированный по условиям
std::vector<Point> SortedVector(const std::vector<Point>& a, double max_dist, double min_dist);

//По ссылке изменяет(создаёт) матрицу энергий и словарь с вероятностями
void EnergyMat_Probability (const std::vector <std::vector<double>>& base, std::vector <std::vector<double>>& energ, std::map <double, double>& val);