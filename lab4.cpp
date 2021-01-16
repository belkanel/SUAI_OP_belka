#include <iostream>
#include <locale.h>
#include <vector>

std::vector <double> Function(double a, double b, double c, double Xmin, double Xmax, double dx) {
	double  x, F; 
	F = 0;
	std::vector <double> answer;
	if (dx > 0) {
		for (x = Xmin; x <= Xmax; x = x + dx) {
			if ((x < 0.6) && ((b + c) != 0)) {
				F = a * pow(x, 3) - b * x + c;
				answer.insert(answer.end(), F);
			}
			else if ((x > 0.6) && ((b + c) == 0)) {
				if (x == c) {
					answer.insert(answer.end(), std::numeric_limits<double>::quiet_NaN());
				}
				else {
					F = (x - a) / (x - c);
					answer.insert(answer.end(), F);
				}
			}
			else {
				if ((c == 0) || (a == 0)) {
					answer.insert(answer.end(), std::numeric_limits<double>::quiet_NaN());
				}
				else {
					F = (x / c) + (x / a);
					answer.insert(answer.end(), F);
				}
			}
		}
	} 
	else if (dx < 0) {
		for (x = Xmax; x >= Xmin; x = x + (dx)) {
			if ((x < 0.6) && ((b + c) != 0)) {
				F = a * pow(x, 3) - b * x + c;
				answer.insert(answer.end(), F);
			}
			else if ((x > 0.6) && ((b + c) == 0)) {
				if (x == c) {
					answer.insert(answer.end(), std::numeric_limits<double>::quiet_NaN());
				}
				else {
					F = (x - a) / (x - c);
					answer.insert(answer.end(), F);
				}
			}
			else {
				if ((c == 0) || (a == 0)) {
					answer.insert(answer.end(), std::numeric_limits<double>::quiet_NaN());
				}
				else {
					F = (x / c) + (x / a);
					answer.insert(answer.end(), F);
				}
			}
		}
	}
	else if (dx == 0) {
		int i;
		for (i = 0; i < 2; i++) {
			if (i == 0) {
				x = Xmin;
			}
			else if (i == 1) {
				x = Xmax;
			}
			if ((x < 0.6) && ((b + c) != 0)) {
				F = a * pow(x, 3) - b * x + c;
				answer.insert(answer.end(), F);
			}
			else if ((x > 0.6) && ((b + c) == 0)) {
				if (x == c) {
					answer.insert(answer.end(), std::numeric_limits<double>::quiet_NaN());
				} 
				else {
					F = (x - a) / (x - c);
					answer.insert(answer.end(), F);
				}
			}
			else {
				if ((c == 0) || (a == 0)) {
					answer.insert(answer.end(), std::numeric_limits<double>::quiet_NaN());
				}
				else {
					F = (x / c) + (x / a);
					answer.insert(answer.end(), F);
				}
			}
		}
	}
	return answer;
}
int main() { 
	double a, b, c; 
	double Xmin, Xmax, dx; 
	setlocale(LC_CTYPE, "Russian");
	std::cout << "Введите a: "; 
	std::cin >> a; 
	std::cout << "Введите b: "; 
	std::cin >> b; 
	std::cout << "Введите c: "; 
	std::cin >> c; 
	std::cout << "Введите Хmin: "; 
	std::cin >> Xmin; 
	std::cout << "Введите Хmax: "; 
	std::cin >> Xmax; 
	std::cout << "Введите шаг dx: "; 
	std::cin >> dx; 
	std::vector <double> answer = Function(a, b, c, Xmin, Xmax, dx);
	for (auto now : answer) {
		if (isnan(now) != 0) {
			std::cout << "Ошибка деления на ноль." << std::endl;
		}
		else {
			std::cout << "F= " << now << std::endl;
		}
	}
	std::cout << "Нажмите любую клавишу для завершения." << std::endl;
	std::cin.ignore(5000, '\n'); 
	std::cin.clear(); 
	std::cin.get(); 
	return 0;
}
