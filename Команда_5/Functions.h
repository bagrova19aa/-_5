#pragma once

struct Point {
    int  area;
    double xm, ym, AR;
};


std::vector<Point> WriteFileToVector();															//���������� vector �� ���������� ���������� �� �����
std::vector<Point> SortedVector(const std::vector<Point>& a, double max_dist, double min_dist);	//���������� vector ��������������� �� ��������