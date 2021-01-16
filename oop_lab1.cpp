#include <iostream>
#include <cmath>
#include <locale.h>

double fun1(double a)
{
	double z1;
	if ((1 + cos(4 * a)) == 0 || (1 + cos(2 * a)) == 0) {
		z1 = std::numeric_limits<double>::quiet_NaN();
	}
	else {
		z1 = (sin(4 * a) / (1 + cos(4 * a))) * ((cos(2 * a)) / (1 + cos(2 * a)));
	}
	return z1;
}
double fun2(double a, const double pi)
{
	double z2;
	if (((abs(pi * 1.5 - a) / (pi / 2)) == (trunc(abs(pi * 1.5 - a)) / (pi / 2))) && ((abs(pi * 1.5 - a) / (pi)) != (trunc(abs(pi * 1.5 - a)) / (pi)))) {	
		// проверяем по модулю делится ли без остатка на pi/2 и не делится без остатка на pi
		z2 = std::numeric_limits<double>::quiet_NaN();
	}
	else {
		z2 = 1 / tan(pi * 1.5 - a);
	}
	return z2;
}


int main()
{
	double a;
	const double pi = atan(1) * 4;
	setlocale(LC_CTYPE, "Russian");
	std::cout << "Введите значение а в градусах:";
	std::cin >> a;
	int b = trunc(a);
	if (b == a) {	// проверяем, не дробное ли значение градусов
		if (b % 90 == 0 && b % 180 != 0) {
			std::cout << "Неверное значение а." << std::endl;
			return 0;
		}
	}
	a = a * (pi / 180);
	double z1 = fun1(a);
	double z2 = fun2(a, pi);
	if (z1 != z1) {		// NaN не равен ничему, в том числе самому себе
		std::cout << "Введено некорректное значение для первой функции." << std::endl;
	}
	std::cout << "z1=" << z1 << std::endl;
	if (z2 != z2) {
		std::cout << "Введено некорректное значение для второй функции." << std::endl;
	}
	std::cout << "z2=" << z2 << std::endl;
	if (abs(z1 - z2) < 0.000001) {		// проверяем с точностью до 6 знака после запятой
		std::cout << "Решения одинаковые" << std::endl;
	}
	else {
		std::cout << "Решения различаются." << std::endl;
	}
	std::cout << "Нажмите любую кнопку для завершения.";
	std::cin.ignore(5000, '\n');
	std::cin.clear();
	std::cin.get();
	return 0;
}