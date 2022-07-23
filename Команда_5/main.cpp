#include <iostream>
#include <fstream>

int main() {
	std::ifstream fin;
	fin.open("./files/data- (1).txt");
	if (fin.is_open()) {
		std::cout << "OK";
	}
	else {
		std::cout << "Err";
	}

	fin.close();

}