#include <iostream>
#include <locale.h>

unsigned short zap(unsigned short a, unsigned short b,unsigned short d) {
    unsigned short c = 0; //число последнего бита
    unsigned short e = 198; //11000110
    unsigned short x = 0;
    x = c;
    x = b << 1 | x; //первое число
    x = a << 4 | x; //второе число
    x = d << 7 | x; //тип операнда
    x = e << 8 | x;
    return x;
}
int main() {
    unsigned short a, b, d;
    setlocale(LC_CTYPE, "Russian");
    std::cout << "Введите первое число" << std::endl;
    std::cin >> b;
    if (b < 0 || b > 7) {
        std::cout << "Введено некорректное значение. Введите число от 0 до 7." << std::endl;
        std::cin >> b;
    }
    std::cout << "b = " << b << std::endl;
    std::cout << "Введите второе число" << std::endl;
    std::cin >> a;
    if (a < 0 || a > 7) {
        std::cout << "Введено некорректное значение. Введите число от 0 до 7." << std::endl;
        std::cin >> a;
    }
    std::cout << "a = " << a << std::endl;
    std::cout << "Введите тип операнда" << std::endl;
    std::cin >> d;
    if (d < 0 || d > 1) {
        std::cout << "Введено некорректное значение. Введите число от 0 до 1." << std::endl;
            std::cin >> d;
    }
    std::cout << "d = " << d << std::endl;
    unsigned short x = zap(a, b, d);
    std::cout << "Упакованная структура " << std::hex << x << std::endl;
    std::cout << "Нажмите любую кнопку для продолжения..." << std::endl; 
    std::cin.ignore(5000, '\n'); 
    std::cin.clear(); 
    std::cin.get();    
    return 0;
}
