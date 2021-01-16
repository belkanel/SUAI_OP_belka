#include <iostream>
#include <locale.h>

void unzip(unsigned short *pb, unsigned short *pa, unsigned short *pd, unsigned short x) {
	(*pb) = (x >> 1) & 0x7;
	(*pa) = (x >> 4) & 0x7;
	(*pd) = (x >> 7) & 0x1;
}
int main() {

	setlocale(LC_CTYPE, "Russian");
	std::cout << "Введите упакованную структуру." << std::endl;
	unsigned short x;
	std::cin >> std::hex >> x;
	if (x < 0xc600 || x > 0xc6fe) {
		std::cout << "Введена неверная структура." << std::endl;
		return 0;
	}
	std::cout << "Упакованная структура " << std::hex << x << std::endl;
	unsigned short b, a, d;
	unzip(&b, &a, &d, x);
	std::cout << "B= " << std::dec << b << std::endl;
	std::cout << "A= " << std::dec << a << std::endl;
	std::cout << "D= " << std::dec << d << std::endl;
	std::cout << "Нажмите любую кнопку для завершения." << std::endl;
	std::cin.ignore(5000, '\n');
	std::cin.clear();
	std::cin.get();
	return 0;
}