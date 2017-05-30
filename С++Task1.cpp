// С++Task1.cpp: определяет точку входа для консольного приложения.
//


/*
	Капранчикова Алисия Александровна
	8. Добавить к каждому числу первое нечетное по абсолютной величине число.
	A) вектор (std::vector)
*/

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <deque>        
#include <iterator>     
#include <vector>
#include <algorithm>
#include <functional>

void printMenu()
{
	std::cout << std::endl;
	std::cout << "----------------------------------------------------" << std::endl;
	std::cout << "Список команд:" << std::endl;
	std::cout << "" << std::endl;
	std::cout << "1)Рандомное заполнение файла" << std::endl;
	std::cout << "2)Преобразование файла в вектор" << std::endl;
	std::cout << "3)Modify" << std::endl;
	std::cout << "4)Modify(iterators)" << std::endl;
	std::cout << "5)Modify(transform)" << std::endl;
	std::cout << "6)Modify(foreach)" << std::endl;
	std::cout << "7)Сумма вектора. Среднее арифметическое вектора" << std::endl;
	std::cout << "8)Вывод на экран" << std::endl;
	std::cout << "9)Вывод в файл" << std::endl;
	std::cout << "0)Завершение работы" << std::endl;
	std::cout << "----------------------------------------------------" << std::endl;
	std::cout << "Введите команду: ";
}

void getRange(std::vector<int> v, int &a, int &b) {
	std::string str;
	bool in = false;
	a = -1;
	std::cout << "Введите левую границу" << std::endl;
	while ((a < 0) || (a >= v.size()))
	{
		in = false;
		while (!in)
		{
			try {
				std::cin >> str;
				a = stoi(str);
				in = true;
			}
			catch (std::invalid_argument e) {
				std::cout << "Введен неверный символ! Повторите ввод" << std::endl;
			}
		}
		if (a < 0)
			std::cout << "Число должно быть не меньше 0! Повторите ввод" << std::endl;
		else if (a >= v.size())
			std::cout << "Число превышает размер вектора (" << v.size() << ")! Повторите ввод" << std::endl;
		else in = true;
	}

	b = -1;
	std::cout << "Введите правую границу" << std::endl;
	while ((b >= v.size()) || (b < a))
	{
		in = false;
		while (!in)
		{
			try {
				
				std::cin >> str;
				b = stoi(str);
				in = true;
			}
			catch (std::invalid_argument e) {
				std::cout << "Введен неверный символ! Повторите ввод" << std::endl;
			}
		}
		if (b >= v.size())
			std::cout << "Число вне диапазона (0.." << v.size() - 1 << ")! Повторите ввод" << std::endl;
		else if (b < a)
			std::cout << "Число должно быть больше левой границы (" << a << ")! Повторите ввод" << std::endl;
		else in = true;
	}
}

void getToElems(std::vector<int>::iterator &left, std::vector<int>::iterator &right, int a, int b) {
	for (int i = 0; i < a; i++)
		left++;
	for (int i = 0; i <= b; i++)
		right++;
}


bool TryOpenFile(std::string filename) 
{
	std::ifstream file(filename);

	if (!file.is_open())
	{
		std::cout << "Невозможно открыть файл" << std::endl;
		return false;
	}
	file.close();
	return true;
}

std::string inputFileName()
{
	std::string filename;
	std::cout << "Введите имя файла:\n";
	std::cin >> filename;
	
	while (!TryOpenFile(filename))
	{
		std::cout << "Введите имя файла:\n";
		std::cin >> filename;
	}

	return filename;
}

//рандомная генерация вектора в файл
void RandomFileCycle(std::string fileName, int n, int m)
{
	std::ofstream file(fileName);

	for (int i = 0; i < n; i++)
	{
		file << (rand() % (2 * m) + 1) - m << " ";
	}

	file.close();
}

//рандомная генерация вектора в файл (generate)
void RandomFileGenerate(std::string fileName, int n, int m)
{
	std::ofstream file(fileName);
	std::vector<int> v(n);
	std::generate(v.begin(), v.end(), rand);

	for (int i = 0; i < n; i++)
	{
		file << (v[i] % (2 * m) + 1) - m << " ";
	}

	file.close();
}

//загрузка вектора из файла
std::vector<int> FileInVector(std::string fileName)
{
	std::vector<int> v;
	int x;
	std::ifstream fin(fileName);

	while (fin >> x)
	{
		v.push_back(x);
	}
	fin.close();
	
	return v;
}

//возвращение первого нечетного эл-та
int getOdd(std::vector<int> v) 
{
	for (int x : v)
	{
		if (x % 2 != 0) 
		{
			return x;
		}
	}
	return 0;
}

//возвращение первого нечетного эл-та
int getOdd(std::vector<int>::iterator begin, std::vector<int>::iterator end)
{
	for (auto it = begin; it != end; it++)
	{
		if (*it % 2 != 0) 
		{
			return *it;
		}
	}
	return 0;
}

//добавление к каждому числу первое нечетное
std::vector<int> modify(std::vector<int> v)
{
	int oddInt = getOdd(v);
	for (auto it = v.begin(); it != v.end(); it++)
	{
		*it = *it + oddInt;
	}
	return v;
}

//добавление к каждому числу первое нечетное (iterator)
std::vector<int> modify(std::vector<int>::iterator begin, std::vector<int>::iterator end)
{
	std::vector<int> v;
	int oddInt = getOdd(begin, end);
	for (std::vector<int>::iterator it = begin; it != end; it++)
	{
		v.push_back(*it + oddInt);
	}
	return v;
}

//
struct functor {
	functor(int intOdd) : intOdd(intOdd) {}
	double operator()(int x) { return x + intOdd; }

private:
	int intOdd;
};

//добавление к каждому числу первое нечетное (transform)
std::vector<int> modifyTransform(std::vector<int> vInput)
{
	std::vector<int> vOutput;

	try
	{
		int intOdd = getOdd(vInput);
		vOutput.resize(vInput.size());
		std::transform(vInput.begin(), vInput.end(), vOutput.begin(), functor(intOdd));
	}
	catch (std::string err)
	{
		std::cout << err << std::endl;
	}

	return vOutput;
}

//
struct functorForEach {
	functorForEach(int intOdd) : intOdd(intOdd) {}
	void operator()(int &x) { x = x + intOdd; }

private:
	int intOdd;
};

//добавление к каждому числу первое нечетное (foreach)
std::vector<int> modifyForeach(std::vector<int> vInput)
{
	std::vector<int> vOutput;

	try
	{
		int intOdd = getOdd(vInput);
		for (std::vector<int>::iterator it = vInput.begin(); it != vInput.end(); it++)
		{
			vOutput.push_back(*it);
		}

		std::for_each(vOutput.begin(), vOutput.end(), functorForEach(intOdd));

	}
	catch (std::string err)
	{
		std::cout << err << std::endl;
	}
	return vOutput;
}

//сумма вектора
int sum(std::vector<int> v)
{
	int sum = 0;

	for (int x : v)
	{
		sum += x;
	}

	return sum;}

//среднее арифметическое вектора
double average(std::vector<int> v)
{
	return (double)sum(v) / v.size();
}

//Печать в файл
void printFile(std::string fileName, std::vector<int> v)
{
	std::ofstream fout(fileName);

	for (int x : v)
	{
		fout << x << " ";
	}
	fout.close();

}

//Печать на экран
void  printConsole(std::vector<int> v)
{
	if (!v.empty())
	{
		std::cout << "[";
		for (int x : v)
		{
			std::cout << x << ", ";
		}
		std::cout << "\b\b" << "]";
		std::cout << std::endl;
	}
}


int main()
{
	setlocale(LC_ALL, "rus");

	bool exit = false;
	int res, x, y;
	std::string filename;
	std::vector<int> vector, modV;
	std::vector<int>::iterator left = vector.begin();
	std::vector<int>::iterator right = vector.begin();


	while (!exit)
	{
		
		printMenu();
		std::cin >> res;
		switch (res)
		{
			case 1: 
				std::cout << "Введите имя файла\n";
				std::cin >> filename;
				std::cout << "Введите количество элементов\n";
				std::cin >> x;
				std::cout << "Введите диапазон\n";
				std::cin >> y;
				RandomFileCycle(filename, x, y);
				RandomFileGenerate("gen_"+filename, x ,y);
				break;
			case 2:
				filename = inputFileName();
				vector = FileInVector(filename);
				printConsole(vector);
				break;
			case 3:
				std::cout << "Вектор до изменений" << std::endl;
				printConsole(vector);
				vector = modify(vector);
				std::cout << "Вектор измененный" << std::endl;
				printConsole(vector);
				break;
			case 4:
				std::cout << "Вектор до изменений" << std::endl;
				printConsole(vector);
				int a, b;
				getRange(vector, a, b);
				left = right = vector.begin();
				getToElems(left, right, a, b);
				modV = modify(left, right);
				std::cout << "Вектор измененный" << std::endl;
				printConsole(modV);
				break;
			case 5:
				std::cout << "Вектор до изменений" << std::endl;
				printConsole(vector);
				vector = modifyTransform(vector);
				std::cout << "Вектор измененный" << std::endl;
				printConsole(vector);
				break;
			case 6:
				std::cout << "Вектор до изменений" << std::endl;
				printConsole(vector);
				vector = modifyForeach(vector);
				std::cout << "Вектор измененный" << std::endl;
				printConsole(vector);
				break;
			case 7:std::cout << "Вектор" << std::endl;
				printConsole(vector);
				std::cout << "Сумма:" << sum(vector) << std::endl;
				std::cout << "Среднее арифметическое:" << average(vector) << std::endl;
				break;
			case 8:
				std::cout << "Вектор\n";
				printConsole(vector);
				break;
			case 9:
				std::cout << "Введите имя файла\n";
				std::cin >> filename;
				printFile(filename, vector);
				break;
			case 0:
				exit = true;
				break;
			default:
				std::cout << "Неправильно введена команда! Повторите ввод!" << std::endl;
				break;
		}
	}
    return 0;
}

