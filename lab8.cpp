#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cctype>
#include <locale.h>
#include <string>

void sentence(std::istream& in, std::ofstream& out)
{
    bool state = false;
    char c;

    while ((c = in.get()) && isspace(c))
        ;
    if (c == '-') // вместо тире знак "минус"
        state = true;
    else
        state = false;

    if (state) {
        while ((c = in.get()) && isspace(c)) // пропуск пробелов
            ;
        out << c ;
        while ((c = in.get()) && state) {
            out << c;
            if (c == '.' || c == '!' || c == '?')
                state = false;
        }
        out << std::endl;
    }
}

int main()
{
    setlocale(LC_CTYPE, "Russian");

    std::string file_name_input;
    std::cout << "Введите путь к исходному файлу: ";
    std::cin >> file_name_input;
    std::ifstream in;

    in.open(file_name_input.c_str(), std::ios::in);
    if (!in.good()) {
        std::cout << "Невозможно прочитать файл.\n";
        exit(1);
    }

    std::string file_name_output;
    std::cout << "введите путь к конечному файлу: ";
    std::cin >> file_name_output;
    std::ofstream out;

    out.open(file_name_output.c_str(), std::ios::out);
    if (!out.good()) {
        std::cout << "Невозможно прочитать файл.\n";
        exit(1);
    }

    while (!in.eof())
        sentence(in, out);

    in.close();
    out.close();
    std::cout << "Данные записаны в файл." << std::endl;
    std::cout << "Нажмите любую кнопку для завершения." << std::endl;

    std::cin.ignore(5000, '\n');
    std::cin.clear();
    std::cin.get();

    return 0;
}