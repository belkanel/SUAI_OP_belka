#include <iostream>
#include <locale.h>

int** mas, n, m;

void seal_matrix()
{
    int i, j, temp, y;
    for (i = 0; i < n; i++)     //удаление нулевых строк
    {
        temp = 0;
        for (j = 0; j < m; j++)
            if (mas[i][j] != 0)
                temp = 1;
        if (temp == 0)
        {
            for (y = i; y < n - 1; y++)
                for (j = 0; j < m; j++)
                    mas[y][j] = mas[y + 1][j];
            n--;
        }
    }

    for (i = 0; i < m; i++)     //удаление нулевых столбцов
    {
        temp = 0;
        for (j = 0; j < n; j++)
            if (mas[j][i] != 0)
                temp = 1;
        if (temp == 0)
        {
            for (y = i; y < m - 1; y++)
                for (j = 0; j < n; j++)
                    mas[j][y] = mas[j][y + 1];
            m--;
        }
    }
}

int positive_elem()
{
    int i, j, elem = 0;
    for (i = 0; i < n; i++) {     //цикл по строкам
        for (j = 0; j < m; j++)      //по столбцам
            if (mas[i][j] > 0) {     //нашли номер первой строки с положительным элементом
                elem = i + 1;
                break;
            }
        if (elem != 0) {
            break;
        }
    }

    return elem;
}

int main()
{
    int i, j;
    setlocale(LC_CTYPE, "Russian");
    std::cout << "Введите количество строк матрицы: " << std::endl;
    std::cin >> n;
    std::cout << "Введите количество столбцов матрицы: " << std::endl;
    std::cin >> m;
    mas = new int* [n];
    for (i = 0; i < n; i++)
        mas[i] = new int[m];
    std::cout << "Введите элемент матрицы: " << std::endl;
    for (i = 0; i < n; i++)     //ввод матрицы
        for (j = 0; j < m; j++)
        {
            std::cout << "[" << i << "][" << j << "]= ";
            std::cin >> mas[i][j];
        }
    std::cout << "Матрица задана" << std::endl;
    for (i = 0; i < n; i++)      //вывод введенной матрицы на экран
    {
        for (j = 0; j < m; j++)
            std::cout << mas[i][j] << "  ";
        std::cout << std::endl;
    }
    
    int elem = positive_elem();

    seal_matrix();

    std::cout << std::endl;
    std::cout << "Уплотненная матрица" << std::endl;
    for (i = 0; i < n; i++)     //вывод уплотненной матрицы на экран
    {
        for (j = 0; j < m; j++)
            std::cout << mas[i][j] << "  ";
        std::cout << std::endl;
    }
    std::cout << std::endl;

    std::cout << "Строка номер " << elem << " содержит положительный элемент." << std::endl;       // вывод номера строк

    std::cout << "Нажмите любую кнопку для завершения.";
    std::cin.ignore(5000, '\n');
    std::cin.clear();
    std::cin.get();
    return 0;
}