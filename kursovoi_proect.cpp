#include <iostream>		//потоковый ввод и вывод
#include <vector>		//для удобсва работы со структурой ,замена массива
#include <string>		//поддержка переменной тип стринг
#include <fstream>		 //для работы с файлами
#include <Windows.h>	 //SetConsoleCP и SetConsoleOutputCP

//для обнаружения утечек памяти

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define newDBG_NEW
#endif
#endif

using namespace std;

struct NOTE		//структура
{
	std::string name;		//переменные, хранящихся в структуре
	std::string lastname;
	std::string phone;
	int year;
	int month;
	int day;
};

bool checkPhone(char _phone[12]);		//правда или ложь : размерность массива
short inputCheckNumbers(short min, short max);		//валидация введенных данных
void showContacts(std::vector<NOTE> contacts, bool line);		//просмотр контактов
void searchContacts(std::vector<NOTE> contacts);		//поиск контактов
void bubble(std::vector<NOTE>& contacts);		//пузырек
void openFile(std::vector<NOTE>& contacts, string path);		//открытие файла
void saveFile(std::vector<NOTE>& contacts, string path);		//сохранение файла
void removeContact(std::vector<NOTE>& contacts);		//удаление контакта
NOTE addContact();		//функция с типом структура

int main()		//точка входа программы
{
	std::string path;		//путь до файла
	unsigned short tmp;			//временная переменная
	setlocale(LC_ALL, "rus");		//устанока региональных настроек
	SetConsoleCP(1251);		// установка кодовой страницы win-cp 1251 в поток ввода
	SetConsoleOutputCP(1251);		 // установка кодовой страницы win-cp 1251 в поток вывода
	std::vector<NOTE>* contacts = new std::vector<NOTE>;		//выделение памяти для массива контактов.динамический массив
	openFile(*contacts, "note.txt");

	while (true)		//начало бесконечного цикла
	{
		std::cout << "Введите номер команды:" << std::endl;
		std::cout << "1. Отобразить контакты" << std::endl;
		std::cout << "2. Поиск" << std::endl;
		std::cout << "3. Добавить файл" << std::endl;
		std::cout << "4. Добавить новый контакт" << std::endl;
		std::cout << "5. Удалить контакт" << std::endl;
		std::cout << "6. Сохранить файл " << std::endl;
		std::cout << "7. Сортировка контактов" << std::endl;
		std::cout << "8. Выход из программы" << std::endl;
		tmp = inputCheckNumbers(1, 8);		//валидация введенных данных
		// удобная замена конструкции
		switch (tmp)
		{
		case 1:
			showContacts(*contacts, false);		//отобразить контакты
			break;
		case 2:
			searchContacts(*contacts);
			break;
		case 3:		//добавить файл
			std::cout << "Укажите полный путь до файла." << std::endl;
			getline(std::cin, path);
			openFile(*contacts, path);
			break;
		case 4:		//добавить новый контакт
			while (true)
			{
				contacts->push_back(addContact());
				std::cout << std::endl;
				std::cout << "Добавить ещё запись?" << std::endl;
				std::cout << "1- Добавить, 2-отмена" << std::endl;
				tmp = inputCheckNumbers(1, 2);
				if (tmp == 2)
					break;
			}
			std::cout << std::endl;
			break;
		case 5:		//удалить контакт
			removeContact(*contacts);
			break;
		case 6:		//сохранение контакта
			saveFile(*contacts, "note.txt");
			break;
		case 7:		//сортировка
			bubble(*contacts);
			break;
		case 8:		//выйти из программы
			saveFile(*contacts, "note.txt");
			return 0;
			break;
		default:
			break;
		}
	}

	//очищаем вектор
	contacts->capacity();
	delete contacts;

	// Для обнаружения утечек памяти
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);
	_CrtDumpMemoryLeaks();
	return 0;
}

bool checkPhone(char _phone[12])		//проверка корректности введенного номера
{
	int attempt = 3;
	bool result;
	for (unsigned short i = 0; i < 11; i++)
		{
			if (i > 10 && _phone[i] == '\0')
				{
				break;
			}
			if (isdigit(static_cast<unsigned char>(_phone[i])) || (i == 0 && _phone[i] == '+'))
				result = true;
			else
				{
					while (std::cin.fail() && (attempt < 0))		//дает три попытки на ввод номера
						{
						std::cout << "У вас осталось " << attempt << " попыток на ввод." << std::endl;
							std::cin.clear();
							std::cin.ignore(std::cin.rdbuf()->in_avail());
							attempt--;
						}
					result = false;
					std::cout << "Неккоректное значение , в номере должно быть 11 цифр ERROR." << std::endl;
					break;		//выход из цикла
				}
		}
	return result;
}

short inputCheckNumbers(short min, short max)		//проверка введенного значения
{
	unsigned short result = max + 10;
	while (true)		//бесконечный цикл
	{
		char chr[10];		//обьявление массива
		bool _isDigit = false;		//переменная
		std::cin.getline(chr, 10, '\n');		//функция
		for (unsigned short i = 0; i < 10; i++)
		{
			if (chr[i] == '\0')
				break;
			if (isdigit(static_cast<unsigned char>(chr[i])))
				_isDigit = true;
			else
			{
				while (std::cin.fail())
				{
					std::cin.clear();
					std::cin.ignore(std::cin.rdbuf()->in_avail());
				}
				_isDigit = false;
				std::cout << "Введенное значение выходит за рамки допустимого диапазона!" << endl;
				std::cout << "Допустимый диапозон " << min << " - " << max << endl;
				break;
			}
		}
		if (_isDigit)
		{
			result = (unsigned short)strtoul(chr, NULL, 0);
			if (result >= min && result <= max)
				return result;
			else
			{
				std::cout << "Введенное значение выходит за рамки допустимого диапазона!" << std::endl;
				std::cout << "Допустимый диапозон " << min << " - " << max << std::endl;
			}
		}
	}
}

void showContacts(std::vector<NOTE> contacts, bool line)		//показывает контакты если правда то в линию если нет то в столбик
{
	for (int i = 0; i < contacts.size(); i++)
	{
		if (line)
		{
			std::cout << "id:" << i
				<< "\tИмя контакта: " << contacts[i].name
				<< "\tФамилия контакта: " << contacts[i].lastname
				<< "\tНомер телефона: " << contacts[i].phone
				<< "\tДата рождения: " << contacts[i].day << "." << contacts[i].month << "." << contacts[i].year << endl;
		}
		else
		{
			std::cout << "Контакт №" << i + 1 << std::endl;
			std::cout << "\tИмя контакта: \t" << contacts[i].name << std::endl;
			std::cout << "\tФамилия контакта: \t" << contacts[i].lastname << std::endl;
			std::cout << "\tНомер телефона: \t" << contacts[i].phone << std::endl;
			std::cout << "\tДата рождения: \t\t" << contacts[i].day << "." << contacts[i].month << "." << contacts[i].year << std::endl;
		}
	}
	std::cout << std::endl;
}

void searchContacts(std::vector<NOTE> contacts)		//поиск контактов
{
	std::vector<NOTE> _tmp;
	std::string search;
	std::cout << "Введите имя: ";
	getline(std::cin, search);
	for (int i = 0; i < contacts.size(); i++)
	{
		if (contacts[i].name.find(search) != -1)
			_tmp.push_back(contacts[i]);
	}
	if (_tmp.size() == 0)
		std::cout << "Контактов не найдено!" << std::endl;
	else
	{
		std::cout << "Контактов найденно " << _tmp.size() << std::endl;
		showContacts(_tmp, false);
	}
}

void bubble(std::vector<NOTE>& contacts)		//Сортировка Пузырьком
{
	for (int i = contacts.size() - 1; i > 0; i--)
		for (int j = 0; j < i; j++)
			if (contacts[j].name > contacts[j + 1].name)
			{
				iter_swap(&contacts[j], &contacts[j + 1]);		//поменять элементы местами
			}
	showContacts(contacts, false);
}

void openFile(std::vector<NOTE>& contacts, std::string path)		//открывает файл в котором храним контакты
{
	std::ifstream ifs(path);
	if (ifs.is_open())
	{
		while (!ifs.eof())		//цикл до конца файла
		{
			NOTE _note;
			char _phone[12];
			ifs >> _note.name >> _note.lastname >> _phone >> _note.day >> _note.month >>
				_note.year;
			if (checkPhone(_phone))
			{
				_note.phone = _phone;
				contacts.push_back(_note);
			}
		}
	}
	else
		std::cout << "Файл не найден!" << std::endl;
	ifs.close();
}

void saveFile(std::vector<NOTE>& contacts, std::string path)		//сохранение файла
{
	std::ofstream ofs(path);
	if (ofs.is_open())
	{
		for (int i = 0; i < contacts.size(); i++)
		{
			ofs << contacts[i].name << " " << contacts[i].lastname << " " << contacts[i].phone
				<< " " << contacts[i].day << " " << contacts[i].month << " " << contacts[i].year << (i +
					1 == contacts.size() ? "" : "\n");
		}
		std::cout << "Файл добавлен!" << std::endl;
	}
	else
		std::cout << "Файл не найден!" << std::endl;
	ofs.close();
}

void removeContact(std::vector<NOTE>& contacts)		//функция удаления контакта
{
	unsigned short id;
	std::cout << "Введите id элемента для удаления:" << std::endl;
	showContacts(contacts, true);
	id = inputCheckNumbers(0, contacts.size() - 1);
	contacts.erase(contacts.begin() + id);
}

NOTE addContact()		//функция с добавлением контакта с типом Note
{
	char _phone[12];
	NOTE _contact;
	std::cout << "Имя контакта: " << std::endl;
	std::cin >> _contact.name;
	std::cout << "Фамилия контакта: " << std::endl;
	std::cin >> _contact.lastname;
	std::cout << "Номер телефона: " << std::endl;
	std::cin.getline(_phone, 12, '\n');
	std::cin.getline(_phone, 12, '\n');
	while (!checkPhone(_phone))
	{
		std::cin.getline(_phone, 11, '\n');
	}
	while (std::cin.fail())
	{
		std::cin.clear();
		std::cin.ignore(std::cin.rdbuf()->in_avail());
	}
	_contact.phone = _phone;
	std::cout << "День: ";
	_contact.day = inputCheckNumbers(1, 31);
	std::cout << "Месяц: ";
	_contact.month = inputCheckNumbers(1, 12);
	std::cout << "Год: ";
	_contact.year = inputCheckNumbers(1900, 2021);
	return _contact;
}