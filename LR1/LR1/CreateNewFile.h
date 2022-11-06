#pragma once
#include<iostream>
#include<windows.h>
#include <fileapi.h>

void CreateNewFile(){
	HANDLE file;
	wchar_t path[MAX_PATH];
	std::wcin.ignore(INT_MAX, '\n');

	std::cout << "Введите полное имя файла (например D:\Folder\File.txt):: ";
	std::wcin.getline(path, MAX_PATH, L'\n');

	file = CreateFile(path, GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
	if (file != INVALID_HANDLE_VALUE) {
		CloseHandle(file);
		std::cout << "Файл создан" << std::endl;
	}
	else {
		if (GetLastError() == ERROR_FILE_EXISTS) {
			std::cout << "Файл с таким именем уже существует" << std::endl;
		}
		else {
			std::cout << "Ошибка!" << std::endl;
		}
	}
}

