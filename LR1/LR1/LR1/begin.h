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
	std::cout << "Здравствуйте! Введите любой пункт из перечисленных:\n" << std::endl;
	std::cout << "a - увидеть все диски\n"
		<< "b - создание новой папки\n"
		<< "c - удаление папки\n"
		<< "d - создание нового файла\n"
		<< "e - перемещение файла\n"
		<< "f - копирование файла\n"
		<< "g - асинхронное копирование файла\n"
		<< "h - получить информацию об указанных атрибутах файла и изменить их при необходимости\n"
		<< "i - выход\n\n" << std::endl;
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
			std::cout << "Вы ввели неверное значение, повторите ввод с выбором из списка" << std::endl;
			
			break;
		}

		system("pause");
	}

	return 0;
}