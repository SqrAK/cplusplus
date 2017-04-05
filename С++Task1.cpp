// �++Task1.cpp: ���������� ����� ����� ��� ����������� ����������.
//


/*
	������������ ������ �������������
	8. �������� � ������� ����� ������ �������� �� ���������� �������� �����.
	A) ������ (std::vector)
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
	std::cout << "������ ������:" << std::endl;
	std::cout << "" << std::endl;
	std::cout << "1)��������� ���������� �����" << std::endl;
	std::cout << "2)�������������� ����� � ������" << std::endl;
	std::cout << "3)Modify" << std::endl;
	std::cout << "4)Modify(iterators)" << std::endl;
	std::cout << "5)Modify(transform)" << std::endl;
	std::cout << "6)Modify(foreach)" << std::endl;
	std::cout << "7)����� �������. ������� �������������� �������" << std::endl;
	std::cout << "8)����� �� �����" << std::endl;
	std::cout << "9)����� � ����" << std::endl;
	std::cout << "0)���������� ������" << std::endl;
	std::cout << "----------------------------------------------------" << std::endl;
	std::cout << "������� �������: ";
}

bool TryOpenFile(std::string filename) 
{
	std::ifstream file(filename);

	if (!file.is_open())
	{
		std::cout << "���������� ������� ����" << std::endl;
		return false;
	}
	file.close();
	return true;
}

std::string inputFileName()
{
	std::string filename;
	std::cout << "������� ��� �����:\n";
	std::cin >> filename;
	
	while (!TryOpenFile(filename))
	{
		std::cout << "������� ��� �����:\n";
		std::cin >> filename;
	}

	return filename;
}

//��������� ��������� ������� � ����
void RandomFileCycle(std::string fileName, int n, int m)
{
	std::ofstream file(fileName);

	for (int i = 0; i < n; i++)
	{
		file << (rand() % (2 * m) + 1) - m << " ";
	}

	file.close();
}

//��������� ��������� ������� � ���� (generate)
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

//�������� ������� �� �����
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

//����������� ������� ��������� ��-��
int getOdd(std::vector<int> v) 
{
	for (int x : v)
	{
		if (x % 2 == 1) 
		{
			return x;
		}
	}
	return 0;
}

//����������� ������� ��������� ��-��
int getOdd(std::vector<int>::iterator begin, std::vector<int>::iterator end)
{
	for (auto it = begin; it != end; it++)
	{
		if (*it % 2 == 1) 
		{
			return *it;
		}
	}
	return 0;
}

//���������� � ������� ����� ������ ��������
std::vector<int> modify(std::vector<int> v)
{
	int oddInt = getOdd(v);
	for (auto it = v.begin(); it != v.end(); it++)
	{
		*it = *it + oddInt;
	}
	return v;
}

//���������� � ������� ����� ������ �������� (iterator)
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

//���������� � ������� ����� ������ �������� (transform)
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

//���������� � ������� ����� ������ �������� (foreach)
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

//����� �������
int sum(std::vector<int> v)
{
	int sum = 0;

	for (int x : v)
	{
		sum += x;
	}

	return sum;}

//������� �������������� �������
double average(std::vector<int> v)
{
	return (double)sum(v) / v.size();
}

//������ � ����
void printFile(std::string fileName, std::vector<int> v)
{
	std::ofstream fout(fileName);

	for (int x : v)
	{
		fout << x << " ";
	}
	fout.close();

}

//������ �� �����
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
	std::vector<int> vector;

	while (!exit)
	{
		
		printMenu();
		std::cin >> res;
		switch (res)
		{
			case 1: 
				filename = inputFileName();
				std::cout << "������� ���������� ���������\n";
				std::cin >> x;
				std::cout << "������� ��������\n";
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
				std::cout << "������ �� ���������" << std::endl;
				printConsole(vector);
				vector = modify(vector);
				std::cout << "������ ����������" << std::endl;
				printConsole(vector);
				break;
			case 4:
				std::cout << "������ �� ���������" << std::endl;
				printConsole(vector);
				vector = modify(vector.begin(), vector.end());
				std::cout << "������ ����������" << std::endl;
				printConsole(vector);
				break;
			case 5:
				std::cout << "������ �� ���������" << std::endl;
				printConsole(vector);
				vector = modifyTransform(vector);
				std::cout << "������ ����������" << std::endl;
				printConsole(vector);
				break;
			case 6:
				std::cout << "������ �� ���������" << std::endl;
				printConsole(vector);
				vector = modifyForeach(vector);
				std::cout << "������ ����������" << std::endl;
				printConsole(vector);
				break;
			case 7:std::cout << "������" << std::endl;
				printConsole(vector);
				std::cout << "�����:" << sum(vector) << std::endl;
				std::cout << "������� ��������������:" << average(vector) << std::endl;
				break;
			case 8:
				std::cout << "������\n";
				printConsole(vector);
				break;
			case 9:
				filename = inputFileName();
				printFile(filename, vector);
				break;
			case 0:
				exit = true;
				break;
			default:
				std::cout << "����������� ������� �������! ��������� ����!" << std::endl;
				break;
		}
	}
    return 0;
}

