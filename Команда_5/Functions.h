#pragma once

struct Point {
    int  number,area;
    double xm, ym, AR;
};

//���������� vector �� ���������� ���������� �� �����
std::vector<Point> WriteFileToVector(int i);	

//���������� vector ��������������� �� ��������
std::vector<Point> SortedVector(const std::vector<Point>& a, double max_dist, double min_dist);

//�������� ��� ������������ �������(���������� � ������)
void Matrix_Relationship_Distance(const std::vector<Point>& sorted_values, std::vector <std::vector<double>>& relationship, std::vector <std::vector<double>>& distance, double max_dist, double min_dist);

//�� ������ ��������(������) ������� ������� � ������� � �������������
void EnergyMat_Probability (const std::vector <std::vector<double>>& base, std::vector <std::vector<double>>& energ, std::map <double, double>& val);
//������� �������,������ �� ����������,� �������� ��� ������������ �������
void KirMat_Valence(const std::vector <std::vector<double>>& matr, std::vector <std::vector<double>>& kir, std::map <double, double>& val)