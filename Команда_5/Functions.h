#pragma once

struct Point {
    int  number,area;
    double xm, ym, AR;
};

//���������� vector �� ���������� ���������� �� �����
std::vector<Point> WriteFileToVector(int i);	

//���������� vector ��������������� �� ��������
std::vector<Point> SortedVector(const std::vector<Point>& a, double max_dist, double min_dist);	