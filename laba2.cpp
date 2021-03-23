#include <iostream>
#include <locale.h>

bool infunc(float x, float y)
{
	bool fun;
	if ((y >= 0 && y <= 1) && (x >= -1 && x <= 1) || (y <= 0 && y >= -1) && (x >= -1 && x <= 1) && (x * x + y * y <= 1)) {
		fun = true;
	}
	else {
		fun = false;
	}
	return fun;
}

int main()
{
	float x, y;
	setlocale(LC_CTYPE, "Russian");
	std::cout << "Введите координаты точки, сначала х, затем у." << std::endl;
	std::cin >> x;
	std::cout << "x = " << x << std::endl;
	std::cin >> y;
	std::cout << "y = " << y << std::endl;
	bool fun = infunc(x, y);
	if (fun) {
		std::cout << "Точка попадает в область." << std::endl;
	}
	else if (!fun) {
		std::cout << "Нет, точка не попадает в область." << std::endl;
	}
	std::cout << "Нажмите любую кнопку для продолжения..." << std::endl;
	std::cin.ignore(5000, '\n');
	std::cin.clear();
	std::cin.get();
	return 0;
}
