#include <iostream>
#include <string>
#include <cstdlib>
#include <locale.h>

int count_words(std::string& input_words)
{
    int count = 0;

    bool word = false;
    for (int i = 0; i < input_words.size(); i++)
    {
        if (input_words[i] == ' ')
        {
            if (word)
                count++;

            word = false;
        }
        else
            word = true;
    }
    if (word)
        count++;

    return count;
}

int enlarged_line(std::string& output, std::string& input_words, int target_len)
{
    int istr_size = input_words.size();
    if (istr_size < target_len)
    {
        const int quant_words = count_words(input_words);
        if (quant_words > 1)
        {
            int quant_AddSpaces = target_len - istr_size;
            int SpacBetweenTwoW = quant_AddSpaces / (quant_words - 1);
            int remainder = quant_AddSpaces - SpacBetweenTwoW * (quant_words - 1);

            bool word = false;
            for (int i = 0; i < istr_size; i++)
            {
                output += input_words[i];
                if (input_words[i] == ' ')
                {
                    if (word)
                    {
                        int add = 0;
                        if (remainder > 0)
                        {
                            add = 1;
                            remainder--;
                        }
                        output.insert(output.size(), SpacBetweenTwoW + add, ' ');
                    }

                    word = false;
                }
                else
                    word = true;
            }
        }
        else
            return 2;
    }
    else
        return 1;

    return 0;
}

int main()
{
    setlocale(LC_CTYPE, "Russian");
    std::cout << "Введите строку." << std::endl;
    std::string input_words;
    getline(std::cin, input_words);
    std::cout << "Введите длину строки." << std::endl;
    int target_len;
    std::cin >> target_len;
    std::cout << "Вы хотите строку " << input_words << " увеличить до " << target_len << " символов." << std::endl;
    std::string output;
    switch (enlarged_line(output, input_words, target_len))
    {
    case 0:      //если все сработало правильно
        std::cout << input_words << std::endl;
        std::cout << output << std::endl;
        break;

    case 1:     //если длина строки меньше заданной
        std::cerr << "Заданная длина строки короче существующей строки.\n";
        break;

    case 2:     //если слов в строке меньше двух
        std::cerr << "Количество слов меньше двух.\n";
        break;

    default:        //в непредвиденных случаях
        std::cerr << "Неизвестная ошибка.\n";
        break;
    }

    std::cout << "Нажмите любую кнопку для завершения.";
    std::cin.ignore(5000, '\n');
    std::cin.clear();
    std::cin.get();

    return 0;
}