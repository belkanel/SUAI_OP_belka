#include <iostream>
#include <locale.h>
#include <vector>

double function(double a, double b, double c, double x, bool* div_by_zero);

double function(double a, double b, double c, double x, bool*div_by_zero)
{
	*div_by_zero = false;
	if ((x < 0.6) && ((b + c) != 0)) {
		return a * pow(x, 3) - b * x + c;
	}

	if ((x > 0.6) && ((b + c) == 0)) {
		if (x - c == 0) {
			*div_by_zero = true;
			return 0;
		}

		return (x - a) / (x - c);
	}

	if (c == 0 || a == 0) {
		*div_by_zero = true;
		return 0;
	}
	return (x / c) + (x / a);
}

int main() {
	bool div_by_zero = false;
	double a, b, c, Xmin, Xmax, dx, x = 0, f;
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
	while (Xmax <= Xmin)
	{
		std::cout << "Введите Xmax больше, чем Xmin: ";
		std::cin >> Xmax;
	}

	std::cout << "Введите шаг dx: ";
	std::cin >> dx;
	while (dx <= 0)
	{
		std::cout << "Введите шаг dx больше нуля: ";
		std::cin >> dx;
	}

	for (x = Xmin; x <= Xmax; x= x + dx)
	{
		f = function(a, b, c, x, &div_by_zero);
		if (div_by_zero) {
			std::cout << "При х= " << x << " будет ошибка деления на ноль." << std::endl;
		}
		else {
			std::cout << "При х= " << x << " F= " << f << std::endl;
		}
	}

	std::cout << "Нажмите любую клавишу для завершения." << std::endl;
	std::cin.ignore(5000, '\n');
	std::cin.clear();
	std::cin.get();
	return 0;
}

