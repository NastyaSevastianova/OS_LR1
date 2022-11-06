#include <iostream>
#include <windows.h>

#include "CreateNewFolder.h"
#include "SeeDiscs.h"
#include "CreateNewFile.h"
#include "MovingFile.h"
#include "DeleteFolder.h"
#include "CopyTheFile.h"
#include "AsynchronousFileCopying.h"
#include "InfoAttributes.h"





void info() 
{
	std::cout << "������������! ������� ����� ����� �� �������������:\n" << std::endl;
	std::cout << "a - ������� ��� �����\n"
		<< "b - �������� ����� �����\n"
		<< "c - �������� �����\n"
		<< "d - �������� ������ �����\n"
		<< "e - ����������� �����\n"
		<< "f - ����������� �����\n"
		<< "g - ����������� ����������� �����\n"
		<< "h - �������� ���������� �� ��������� ��������� ����� � �������� �� ��� �������������\n"
		<< "i - �����\n\n" << std::endl;
}


int main()
{
	system("chcp 1251");
	setlocale(LC_ALL, "Russian");
	info();
	CHAR ch = 'y';
	
	while (ch != 'i')
	{
		
		system("cls");
		info();

		std::cin >> ch;

		switch (ch)
		{
		case 'a':
			SeeDiscs();
			break;
		case 'b':
			CreateNewFolder();
			break;
		case 'c':
			DeleteFolder();
			break;
		case 'd':
			CreateNewFile();
			break;
		case 'e':
			MovingFile();
			break;
		case 'f':
			CopyTheFile();
			break;
		case 'g':
			AsynchronousFileCopying();
			break;
		case 'h':
			InfoAttributes();
			break;
		case 'i':
			break;
		default:
			std::cout << "�� ����� �������� ��������, ��������� ���� � ������� �� ������" << std::endl;
			
			break;
		}

		system("pause");
	}

	return 0;
}