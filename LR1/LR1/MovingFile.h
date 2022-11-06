#pragma once
#include<iostream>
#include<windows.h>
#include <fileapi.h>

void MovingFile()
{
	wchar_t path[MAX_PATH], new_path[MAX_PATH];
	std::wcin.ignore(INT_MAX, '\n');

	std::cout << "Введите полное имя файла (например D:\Folder\File.txt): ";
	std::wcin.getline(path, MAX_PATH, L'\n');

	std::cout << "Введите полное имя файла (например D:\Folder\File.txt): ";
	std::wcin.getline(new_path, MAX_PATH, L'\n');

	if (MoveFile(path, new_path)) {
		std::cout << "Успешно!" << std::endl;
	}
	else {
		if (GetLastError() == 183L) {
			std::cout << "Файл уже существует" << std::endl;
		}
		else {
			std::cout << "Ошибка!" << std::endl;
		}
	}
}

